#define _CRT_SECURE_NO_WARNINGS
#include "Reversi.h"

#define random(x) (rand()%x)
#define ROWS 19
#define COLS 19
#define ROUNDS 3
int LocalChessBoard[19][19]{ -1 };//本地棋盘
extern int round_number = 0;
extern int doc_state = 0;


Reversi::Reversi() {
	client_socket = ClientSocket();
	oppositeColor = ownColor = -1;
}

Reversi::~Reversi() {}
void Reversi::setOwnColor(int color)
{
	if (color != 0 || color != 1)
		return;
	ownColor = color;
	oppositeColor = 1 - color;
}
;

/*
 send id and password to server by socket
 rtn != 0 represents socket transfer error
 */
void Reversi::authorize(const char* id, const char* pass)
{
	client_socket.connectServer();
	std::cout << "Authorize " << id << std::endl;
	char msgBuf[BUFSIZE];
	memset(msgBuf, 0, BUFSIZE);
	msgBuf[0] = 'A';
	memcpy(&msgBuf[1], id, 9);
	memcpy(&msgBuf[10], pass, 6);
	int rtn = client_socket.sendMsg(msgBuf);
	if (rtn != 0) printf("Authorized Failed!\n");
}

// 用户id输入，服务器上需要有对应的账号密码：对应文件 players-0.txt
void Reversi::gameStart()
{
	char id[12] = { 0 }, passwd[10] = { 0 };
	strcpy(id, ID);
	strcpy(passwd, PASSWORD);
	authorize(id, passwd);

	printf("Game Start!\n");

	for (int round = 0; round < ROUNDS; round++) {
		roundStart(round);
		oneRound();
		roundOver(round);
	}
	gameOver();
	client_socket.close();
}

void Reversi::gameOver()
{
	printf("Game Over!\n");
}

//发一次消息，走哪一步，等两个消息，1.自己的步数行不行 2.对面走了哪一步 
void Reversi::roundStart(int round)
{
	//本地棋盘初始化
	for (int r = 0; r < 19; r++) {
		for (int c = 0; c < 19; c++) {
			LocalChessBoard[r][c] = -1;
		}
	}
	LocalChessBoard[9][9] = 1;
	printf("Round %d Ready Start!\n", round);

	// first time receive msg from server
	int rtn = client_socket.recvMsg();
	if (rtn != 0) return;
	if (strlen(client_socket.getRecvMsg()) < 2)
		printf("Authorize Failed!\n");
	else
		printf("Round start received msg %s\n", client_socket.getRecvMsg());
	switch (client_socket.getRecvMsg()[1]) {
		// this client : black chessman
	case 'B':
		ownColor = 0;
		oppositeColor = 1;
		rtn = client_socket.sendMsg("BB");
		printf("Send BB -> rtn: %d\n", rtn);
		if (rtn != 0) return;
		break;
	case 'W':
		ownColor = 1;
		oppositeColor = 0;
		rtn = client_socket.sendMsg("BW");
		printf("Send BW -> rtn: %d\n", rtn);
		if (rtn != 0) return;
		break;
	default:
		printf("Authorized Failed!\n");
		break;
	}
}

void Reversi::oneRound()
{
	int STEP = 1;
	switch (ownColor) {
	case 0:
		while (STEP < 10000) {

			pair<pair<int, int>, pair<int, int>> chess = step();                        // take action, send message

			// lazi only excute after server's message confirm  in observe function
			generateOneStepMessage(chess.first.first, chess.first.second, chess.second.first, chess.second.second);


			if (observe() >= 1) break;     // receive RET Code

			if (observe() >= 1) break;    // see white move
			STEP++;
			// saveChessBoard();
		}
		printf("One Round End\n");
		break;
	case 1:
		while (STEP < 10000) {

			if (observe() >= 1) break;    // see black move

			pair<pair<int, int>, pair<int, int>> chess = step();                        // take action, send message
			// lazi only excute after server's message confirm  in observe function
			generateOneStepMessage(chess.first.first, chess.first.second, chess.second.first, chess.second.second);


			if (observe() >= 1) break;     // receive RET Code
			// saveChessBoard();
			STEP++;
		}
		printf("One Round End\n");
		break;

	default:
		break;
	}
}

void Reversi::roundOver(int round)
{
	printf("Round %d Over!\n", round);
	// reset initializer

	ownColor = oppositeColor = -1;
}

int Reversi::observe()
{
	int rtn = 0;
	int recvrtn = client_socket.recvMsg();
	if (recvrtn != 0) return 1;
	printf("receive msg %s\n", client_socket.getRecvMsg());
	switch (client_socket.getRecvMsg()[0]) {
	case 'R':
	{
		switch (client_socket.getRecvMsg()[1]) {
		case 'Y':   // valid step
			switch (client_socket.getRecvMsg()[2]) {
			case 'P':   // update chessboard
			{
				int desRow1 = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol1 = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int desRow2 = (client_socket.getRecvMsg()[7] - '0') * 10 + client_socket.getRecvMsg()[8] - '0';
				int desCol2 = (client_socket.getRecvMsg()[9] - '0') * 10 + client_socket.getRecvMsg()[10] - '0';
				int color = (client_socket.getRecvMsg()[11] - '0');
				//你应该在这里处理desRow和desCol，推荐使用函数
				handleMessage(desRow1, desCol1, desRow2, desCol2, color);

				printf("a valid step of : (%d %d) (%d %d)\n", desRow1, desCol1, desRow2, desCol2);
				break;
			}
			case 'N':   // R0N: enemy wrong step
			{
				//
				printf("a true judgement of no step\n");
				break;
			}
			}

			break;
		case 'W':
			// invalid step
			switch (client_socket.getRecvMsg()[2]) {
			case 'P': {
				int desRow1 = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol1 = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int desRow2 = (client_socket.getRecvMsg()[7] - '0') * 10 + client_socket.getRecvMsg()[8] - '0';
				int desCol2 = (client_socket.getRecvMsg()[9] - '0') * 10 + client_socket.getRecvMsg()[10] - '0';
				int color = (client_socket.getRecvMsg()[11] - '0');
				printf("Invalid step , server random a true step of : (%d %d) (%d %d)\n", desRow1, desCol1, desRow2, desCol2);
				//你应该在这里处理desRow和desCol，推荐使用函数
				handleMessage(desRow1, desCol1, desRow2, desCol2, color);
				break;
			}
			case 'N': {
				printf("a wrong judgement of no step\n");
				break;
			}
			default:
				break;
			}
			break;
		case '1':

			printf("Error -1: Msg format error!\n");
			rtn = -1;
			break;
		case '2':

			printf("Error -2: Corrdinate error!\n");
			rtn = -2;
			break;
		case '4':

			printf("Error -4: Invalid step!\n");
			rtn = -4;
			break;
		default:

			printf("Error -5: Other error!\n");
			rtn = -5;
			break;
		}
		break;
	}
	case 'E':
	{
		switch (client_socket.getRecvMsg()[1]) {
		case '0':
			// game over
			rtn = 2;
			break;
		case '1':
			// round over
			rtn = 1;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return rtn;
}

void Reversi::generateOneStepMessage(int row1, int col1, int row2, int col2)
{
	char msg[BUFSIZE];
	memset(msg, 0, sizeof(msg));

	//put row and col in the message
	msg[0] = 'S';
	msg[1] = 'P';
	msg[2] = '0' + row1 / 10;
	msg[3] = '0' + row1 % 10;
	msg[4] = '0' + col1 / 10;
	msg[5] = '0' + col1 % 10;
	msg[6] = '0' + row2 / 10;
	msg[7] = '0' + row2 % 10;
	msg[8] = '0' + col2 / 10;
	msg[9] = '0' + col2 % 10;
	msg[10] = '\0';

	//print
	printf("generate one step at possition (%2d,%2d,%2d,%2d) : %s\n", row1, col1, row2, col2, msg);


	client_socket.sendMsg(msg);
}

/*-------------------------last three function--------------------------------
* step : find a good position to lazi your chess.
* saveChessBoard : save the chess board now.
* handleMessage: handle the message from server.
*/

inline int is_able(int r, int c) {
	if (LocalChessBoard[r][c] != -1)return 0;
	else if ((c - 1 >= 0 && LocalChessBoard[r][c - 1] != -1)
		|| (c + 1 < 19 && LocalChessBoard[r][c + 1] != -1)
		|| (r - 1 >= 0 && LocalChessBoard[r - 1][c] != -1)
		|| (r + 1 < 19 && LocalChessBoard[r + 1][c] != -1)
		|| (r + 1 < 19 && c + 1 < 19 && LocalChessBoard[r + 1][c + 1] != -1)
		|| (r - 1 >= 0 && c - 1 >= 0 && LocalChessBoard[r - 1][c - 1] != -1)
		|| (r - 1 >= 0 && c + 1 < 19 && LocalChessBoard[r - 1][c + 1] != -1)
		|| (r + 1 < 19 && c - 1 >= 0 && LocalChessBoard[r + 1][c - 1] != -1)) {
		return 1;
	}
	return 0;
}

inline int Score_Helper(int ownchess_number, int opposit_number) {
	if (opposit_number == 0 && ownchess_number != 0) {
		if (ownchess_number == 1)return 1;
		else if (ownchess_number == 2) return 2;
		else if (ownchess_number == 3) return 3;
		else if (ownchess_number == 4) return 10000;
		else if (ownchess_number == 5) return 80000;
	}
	else if (ownchess_number == 0 && opposit_number != 0) {
		if (opposit_number == 1) return 1;
		else if (opposit_number == 2) return 2;
		else if (opposit_number == 3) return 3;
		else if (opposit_number == 4) {
			return 9000;
		}
		else if (opposit_number == 5) return 14000;
	}
	return 0;
}

int Score(int objr, int objc, int color) {
	int result = 0;
	int max_buffer = 0, buffer = 0;
	int ownchess_number = 0, opposit_number = 0;
	//水平路评估
	int start = 0, tail = 0;
	while (objc - start > 0 && start < 5) start++;
	while (objc + tail < 18 && tail < 5) tail++;
	for (int i = objc - start; i <= objc + tail - 5; i++) {
		for (int k = i; k < i + 6; k++) {
			if (LocalChessBoard[objr][k] == color) ownchess_number++;
			else if (LocalChessBoard[objr][k] != color && LocalChessBoard[objr][k] != -1)opposit_number++;
		}
		buffer = Score_Helper(ownchess_number, opposit_number);
		if (buffer > max_buffer) max_buffer = buffer;
		ownchess_number = 0, opposit_number = 0;
	}
	//if (max_buffer > result) result = max_buffer;
	result += max_buffer;
	start = 0, tail = 0;
	max_buffer = 0;
	buffer = 0;
	//竖直路评估
	while (objr - start > 0 && start < 5) start++;
	while (objr + tail < 18 && tail < 5) tail++;
	for (int i = objr - start; i <= objr + tail - 5; i++) {
		for (int k = i; k < i + 6; k++) {
			if (LocalChessBoard[k][objc] == color) ownchess_number++;
			else if (LocalChessBoard[k][objc] != color && LocalChessBoard[k][objc] != -1) opposit_number++;
		}
		buffer = Score_Helper(ownchess_number, opposit_number);
		if (buffer > max_buffer) max_buffer = buffer;
		ownchess_number = 0, opposit_number = 0;
	}
	//if (max_buffer > result) result = max_buffer;
	result += max_buffer;
	start = 0, tail = 0;
	max_buffer = 0;
	buffer = 0;
	//左下至右上路评估
	while (objr - start > 0 && objc - start > 0 && start < 5) start++;
	while (objr + tail < 18 && objc + tail < 18 && tail < 5)tail++;
	for (int i = -start; i <= tail - 5; i++) {
		for (int k = i; k < i + 6; k++) {
			if (LocalChessBoard[objr + k][objc + k] == color) ownchess_number++;
			else if (LocalChessBoard[objr + k][objc + k] != color && LocalChessBoard[objr + k][objc + k] != -1)opposit_number++;
		}
		buffer = Score_Helper(ownchess_number, opposit_number);
		if (buffer > max_buffer) max_buffer = buffer;
		ownchess_number = 0, opposit_number = 0;
	}
	//if (max_buffer > result) result = max_buffer;
	result += max_buffer;
	start = 0, tail = 0;
	max_buffer = 0;
	buffer = 0;
	//另一条斜向路
	while (objr + start < 18 && objc - start > 0 && start < 5) start++;
	while (objr - tail > 0 && objc + tail < 18 && tail < 5) tail++;
	for (int i = -start; i <= tail - 5; i++) {
		for (int k = i; k < i + 6; k++) {
			if (LocalChessBoard[objr + k][objc - k] == color) ownchess_number++;
			else if (LocalChessBoard[objr + k][objc - k] != color && LocalChessBoard[objr + k][objc - k] != -1)opposit_number++;
		}
		buffer = Score_Helper(ownchess_number, opposit_number);
		if (buffer > max_buffer) max_buffer = buffer;
		ownchess_number = 0, opposit_number = 0;
	}
	//if (max_buffer > result) result = max_buffer;
	result += max_buffer;
	start = 0, tail = 0;
	max_buffer = 0;
	buffer = 0;
	return result;
}

inline void single_step(int& objr, int& objc, int color) {
	int max_score = 0;
	for (int r = 0; r < 19; r++) {
		for (int c = 0; c < 19; c++) {
			int buffer = Score(r, c, color);
			if (is_able(r, c) == 0) continue;
			else if (is_able(r, c) == 1 && (buffer >= max_score)) {
				max_score = buffer;
				objr = r;
				objc = c;
			}
		}
	}
}

pair<pair<int, int>, pair<int, int>> Reversi::step()
{
	/*
	文件复盘说明：
	文件以相对路径形式存储在项目文件夹中
	round0.txt, round1.txt, round2.txt分别为对局1、2、3对应的复盘记录
	在文件中，x代表黑子，o代表白子， .代表无子
	*/
	int r1 = 1, c1 = 1, r2 = 1, c2 = 1;
	single_step(r1, c1, Reversi::ownColor);
	LocalChessBoard[r1][c1] = Reversi::ownColor;
	single_step(r2, c2, Reversi::ownColor);
	LocalChessBoard[r2][c2] = Reversi::ownColor;
	/*LocalChessBoard[r1][c1] = -1;
	LocalChessBoard[r2][c2] = -1;*/
	pair<int, int> step1 = make_pair(r1, c1);
	pair<int, int> step2 = make_pair(r2, c2);
	return make_pair(step1, step2);
}

void Reversi::saveChessBoard()
{
	string address = "./round";
	address.push_back(char(round_number + 48));
	address += ".txt";
	//FILE* f = fopen(address.c_str(), "w");
	FILE* f = NULL;
	if (doc_state == 0) f = fopen(address.c_str(), "w");
	else if (doc_state == 1) f = fopen(address.c_str(), "a");
	//if (doc_state == 0)	f = fopen(address.c_str(), "w");
	//else if (doc_state == 1) f = fopen(address.c_str(), "a");
	for (int r = 0; r < 19; r++) {
		for (int c = 0; c < 19; c++) {
			if (LocalChessBoard[r][c] == -1) fprintf(f, ".");
			else if (LocalChessBoard[r][c] == 0) fprintf(f, "x");
			else if (LocalChessBoard[r][c] == 1)fprintf(f, "o");
		}
		fprintf(f, "\n");
	}
	fprintf(f, "\n");
	fclose(f);
}

void Reversi::handleMessage(int row1, int col1, int row2, int col2, int color) {
	LocalChessBoard[row1][col1] = color;
	LocalChessBoard[row2][col2] = color;
	saveChessBoard();
}
