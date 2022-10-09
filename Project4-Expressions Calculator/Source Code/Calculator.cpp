#include "Calculator.h"

//****构造与析构**********************************
//************************************************
//构造函数
Calculator::Calculator()
{
	this->VarsNum = 0;
	this->FuncsNum = 0;
	this->VarsLib = new Var[300]{};
	this->FuncsLib = new Func[100]{};
	this->MaxRecursiveDepth = 200;
	this->IfCorrect = 1;
}
//析构函数
Calculator::~Calculator()
{
	delete[]VarsLib;
	delete[]FuncsLib;
}


//****流程控制************************************
//************************************************
//流程控制
void Calculator::Run()
{
	regex varcreate("Var[ ][a-zA-Z]+[=]{1}[()a-zA-Z0-9.+-//*//]+");
	regex funccreate("Func[ ][a-zA-Z]+[(][a-zA-Z,+-//*//]*[)][=]{1}[()a-zA-Z0-9.+-/*//]+");
	regex varsshow("SHOW[ ]VAR");
	regex funcsshow("SHOW[ ]FUNC");
	regex varassignment("[a-zA-Z]+[=]{1}[()a-zA-Z0-9.+-//*//]+");
	//综合运算
	regex calculate("[)(]*([a-zA-Z]+|[\\-0-9.]+|([a-zA-Z]*[(][a-zA-Z0-9.\\+\\-,//*//)(]*[)])){1}([)()]*[)(]*([\\+\\-//*//]{1}[)(]*([a-zA-Z]+|[\\-\\+0-9.]+|([a-zA-Z]+[(][\\-\\+a-zA-Z0-9.)(\\+\\-//*//,]*[)]))[)()]*)*)*[)(]*");
	regex quit("EXIT");
	while (true)
	{
		IfCorrect = 1;
		printf("-->");
		string order;
		getline(cin, order);
		if (regex_match(order, varcreate)) CreateVar(order);			//变量创建
		else if (regex_match(order, funccreate)) CreateFunc(order);		//函数创建
		else if (regex_match(order, quit)) return;						//退出程序
		else if (regex_match(order, varassignment))VarAssignment(order);//变量定义修改
		else if (regex_match(order, varsshow))ShowVars();				//变量展示
		else if (regex_match(order, funcsshow)) ShowFuncs();			//函数展示
		else if (regex_match(order, calculate))							//综合运算
		{
			string coutbuffer = Calculate(order, 1);
			if (IfCorrect == 1)
			{
				cout << coutbuffer << endl;
			}
		}
		else if (order == "");
		else printf("Wrong expression, please re-enter the expression!\n");
	}
}

//****变量类**************************************
//************************************************
//创建变量
void Calculator::CreateVar(string order)
{
	order = order.substr(4);
	Var* p = new Var;
	p->Name = order.substr(0, order.find("="));
	order = order.substr(order.find("=") + 1);
	p->Defini = order;
	//检查变量是否已定义
	for (int i = 0; i < VarsNum; i++) {
		if (VarsLib[i].Name == p->Name)
		{
			printf("Variable %s already exists!\n", p->Name.c_str());
			delete p;
			return;
		}
	}
	//检查变量定义中是否有未定义变量
	for (size_t i = 0; i < order.length(); i++) {
		int check = (int)order[i];
		if (!(check >= 65 && check <= 90) &&
			!(check >= 97 && check <= 122)
			) order[i] = '|';
	}
	while (order.find("|") != string::npos)
	{
		string testif = order.substr(0, order.find("|"));
		if (testif.length() > 0)
		{
			int find = 0;
			for (int i = 0; i < VarsNum; i++)
			{
				if (VarsLib[i].Name == testif || p->Name == testif)	//后续搜索如果同名加速跳出
				{
					find = 1;
					break;
				}
			}
			if (p->Name == testif) find = 1;						//当添加第一个变量时变量库为空，单独判断
			if (find == 0)
			{
				printf("The variable %s does not exist!\n", testif.c_str());
				delete p;
				return;
			}
		}
		order = order.substr(order.find("|") + 1);
	}
	if (order.length() > 0)
	{
		int find = 0;
		for (int i = 0; i < VarsNum; i++)
		{
			if (VarsLib[i].Name == order || p->Name == order)	//后续搜索如果同名加速跳出
			{
				find = 1;
				break;
			}
		}
		if (p->Name == order) find = 1;						//当添加第一个变量时变量库为空，单独判断
		if (find == 0)
		{
			printf("The variable %s does not exist!\n", order.c_str());
			delete p;
			return;
		}
	}
	//变量库中添加变量
	VarsLib[VarsNum] = *p;
	VarsNum++;
	p = NULL;
	delete p;
}
//展示变量
void Calculator::ShowVars() const
{
	printf("变量名\t\t\t变量定义\n");
	for (int i = 0; i < VarsNum; i++)
	{
		printf("%s\t\t\t%s\n", VarsLib[i].Name.c_str(), VarsLib[i].Defini.c_str());
	}
}
//变量修改
void Calculator::VarAssignment(string order)
{
	string targetname = order.substr(0, order.find("="));
	order = order.substr(order.find("=") + 1);
	int targeti = -1;
	//查询要修改的变量是否存在
	for (int i = 0; i < VarsNum; i++)
	{
		if (VarsLib[i].Name == targetname)
		{
			targeti = i;
			break;
		}
	}
	if (targeti == -1)
	{
		printf("The variable %s does not exist!\n", targetname.c_str());
		return;
	}
	string newdefini = order;
	//查询修改的变量定义中是否有未定义变量
	for (size_t i = 0; i < order.length(); i++) {
		int check = (int)order[i];
		if (!(check >= 65 && check <= 90) &&
			!(check >= 97 && check <= 122)
			) order[i] = '|';
	}
	while (order.find("|") != string::npos)
	{
		string testif = order.substr(0, order.find("|"));
		if (testif.length() > 0)
		{
			int find = 0;
			for (int i = 0; i < VarsNum; i++)
			{
				if (VarsLib[i].Name == testif)
				{
					find = 1;
					break;
				}
			}
			if (find == 0)
			{
				printf("The variable %s does not exist!\n", testif.c_str());
				return;
			}
		}
		order = order.substr(order.find("|") + 1);
	}
	if (order.length() > 0)
	{
		int find = 0;
		for (int i = 0; i < VarsNum; i++)
		{
			if (VarsLib[i].Name == order)
			{
				find = 1;
				break;
			}
		}
		if (find == 0)
		{
			printf("The variable %s does not exist!\n", order.c_str());
			return;
		}
	}
	//更改变量定义
	VarsLib[targeti].Defini = newdefini;
}

//****函数类**************************************
//************************************************
//创建函数
void Calculator::CreateFunc(string order)
{
	Func* p = new Func;
	order = order.substr(5);
	p->Name = order.substr(0, order.find("("));
	//检查函数是否已定义
	for (int i = 0; i < FuncsNum; i++)
	{
		if (FuncsLib[i].Name == p->Name)
		{
			printf("The Function %s has already existed!\n", p->Name.c_str());
			delete p;
			return;
		}
	}
	//获取变量表
	order = order.substr(order.find("(") + 1);
	string parameterlist = order.substr(0, order.find(")"));
	for (size_t i = 0; i < parameterlist.length(); i++)
	{
		int check = (int)parameterlist[i];
		if (!(check >= 65 && check <= 90) &&
			!(check >= 97 && check <= 122)
			) parameterlist[i] = '|';
	}
	while (parameterlist.find("|") != string::npos)
	{
		string parameter = parameterlist.substr(0, parameterlist.find("|"));
		if (parameter.length() > 0)
		{
			p->ParameterTable[p->ParameterNum] = parameter;
			p->ParameterNum++;
		}
		parameterlist = parameterlist.substr(parameterlist.find("|") + 1);
	}
	if (parameterlist.length() > 0)
	{
		p->ParameterTable[p->ParameterNum] = parameterlist;
		p->ParameterNum++;
	}
	//获取函数体，检查函数体中是否有非法变量
	order = order.substr(order.find(")") + 2);
	p->Defini = order;
	for (size_t i = 0; i < order.length(); i++)
	{
		int check = (int)order[i];
		if (!(check >= 65 && check <= 90) &&
			!(check >= 97 && check <= 122)
			) order[i] = '|';
	}
	while (order.find('|') != string::npos)
	{
		string testif = order.substr(0, order.find("|"));
		if (testif.length() > 0)
		{
			int find = 0;
			for (int i = 0; i < p->ParameterNum; i++)
			{
				if (p->ParameterTable[i] == testif)
				{
					find = 1;
					break;
				}
			}
			if (find == 0)
			{
				for (int i = 0; i < VarsNum; i++)
				{
					if (VarsLib[i].Name == testif)
					{
						find = 1;
						break;
					}
				}
			}
			if (find == 0)
			{
				printf("Variables %s in function body do not exist as parameters or variables!\n", testif.c_str());
				delete p;
				return;
			}
		}
		order = order.substr(order.find("|") + 1);
	}
	if (order.length() > 0)
	{
		int find = 0;
		for (int i = 0; i < p->ParameterNum; i++)
		{
			if (p->ParameterTable[i] == order)
			{
				find = 1;
				break;
			}
		}
		/*if (find == 0)				//函数体中找不到的变量不会再去变量库中找，因为这样会导致矛盾与冲突
		{
			for (int i = 0; i < VarsNum; i++)
			{
				if (VarsLib[i].Name == order)
				{
					find = 1;
					break;
				}
			}
		}*/
		if (find == 0)
		{
			printf("Variables %s in function body do not exist as parameters or variables!\n", order.c_str());
			delete p;
			return;
		}
	}
	//挂载函数到库中
	FuncsLib[FuncsNum] = *p;
	FuncsNum++;
	p = NULL;
	delete p;
}
//展示函数
void Calculator::ShowFuncs() const
{
	printf("函数名\t\t\t参数表\t\t\t\t\t定义\n");
	for (int i = 0; i < FuncsNum; i++)
	{
		printf("%s\t\t\t", FuncsLib[i].Name.c_str());
		for (int k = 0; k < FuncsLib[i].ParameterNum; k++) printf("%s ", FuncsLib[i].ParameterTable[k].c_str());
		printf("\t\t\t\t\t");
		printf("%s\n", FuncsLib[i].Defini.c_str());
	}
}


//****计算类**************************************
//************************************************
//括号检查
int Calculator::BracketCheck(string order)
{
	int leftnum = 0, rightnum = 0;
	for (size_t i = 0; i < order.length(); i++)
	{
		if (order[i] == '(') leftnum++;
		else if (order[i] == ')') rightnum++;
	}
	if (leftnum == rightnum) return leftnum;
	else return -1;
}
//去除表达式中重复加减号
string Calculator::RemoveDuplication(string order)
{
	size_t starti = 0, endi = 0;
	string result;
	for (; starti < order.length(); starti++)
	{
		size_t addnum = 0, subnum = 0;
		if (order[starti] == '+' || order[starti] == '-')
		{
			if (order[starti] == '+') addnum++;
			else if (order[starti] == '-') subnum++;
			for (endi = starti + 1; endi < order.length() && order[endi] == '+' || order[endi] == '-'; endi++)
			{
				if (order[endi] == '+') addnum++;
				else if (order[endi] == '-') subnum++;
			}
			if (addnum + subnum > 1)
			{
				subnum = subnum % 2;
				if (subnum == 1) result += "-";
				else if (subnum == 0) result += "+";
			}
			else if (addnum + subnum == 1)
			{
				if (addnum == 1) result += "+";
				else if (subnum == 1) result += "-";
			}
		}
		else
		{
			for (endi = starti; endi < order.length() && order[endi] != '+' && order[endi] != '-'; endi++);
			result += order.substr(starti, endi - starti);
		}
		starti = endi - 1;
	}
	return result;
}
//函数调用
string Calculator::FuncCall(string order, int depth)
{
	string callname = order.substr(0, order.find("("));
	int funci = -1;
	//查询该函数，未找到报错返回0
	for (int i = 0; i < FuncsNum; i++)
	{
		if (FuncsLib[i].Name == callname)
		{
			funci = i;
			break;
		}
	}
	if (funci == -1)
	{
		printf("The function %s does not exist!\n", callname.c_str());
		IfCorrect = 0;
		return "0";
	}
	//获取实参变量表
	string realvarslist = order.substr(order.find("(") + 1);
	realvarslist.pop_back();
	int realvarnum = 0;
	string realvarstable[10];
	int state = 0;
	//对复合/函数表达式中括号进行处理
	for (int i = 0; i < realvarslist.length(); i++)
	{
		if (realvarslist[i] == '(') state = 1;
		else if (realvarslist[i] == ')') state = 0;
		if (state == 1 && realvarslist[i] == ',') realvarslist[i] = '`';
	}
	//Debug用
	//cout << "实参表为：" << realvarslist << endl;
	while (realvarslist.find(",") != string::npos)
	{
		//cout << "当前的实参：" << realvarslist.substr(0, realvarslist.find(",")) << endl;
		string suborder = realvarslist.substr(0, realvarslist.find(","));
		for (int i = 0; i < suborder.length(); i++)
		{
			if (suborder[i] == '`') suborder[i] = ',';
		}
		realvarstable[realvarnum] = Calculate(suborder, depth + 1);
		realvarnum++;
		realvarslist = realvarslist.substr(realvarslist.find(",") + 1);
	}
	if (realvarslist.length() > 0)
	{
		string suborder = realvarslist.substr(0, realvarslist.find(","));
		for (int i = 0; i < suborder.length(); i++)
		{
			if (suborder[i] == '`') suborder[i] = ',';
		}
		realvarstable[realvarnum] = Calculate(suborder, depth + 1);
		realvarnum++;
	}
	//对照实参变量表和形参变量表
	if (realvarnum != FuncsLib[funci].ParameterNum)
	{
		printf("The number of formal and actual parameters is inconsistent when the function %s is called"
			, FuncsLib[funci].Name.c_str());
		IfCorrect = 0;
		return "0";
	}
	//函数定义中用实参替换形参，调用Calculate运算
	string definition = FuncsLib[funci].Defini;
	for (int i = 0; i < realvarnum; i++)
	{
		//Question:	实参替换定义式中的形参，利用replace替换regex防止正则表达式的违规操作
		//regex pattern(FuncsLib->ParameterTable[i]);
		//Definition = regex_replace(Definition, pattern, realvarstable[i]);
		string currpara = FuncsLib->ParameterTable[i];
		definition.replace(definition.find(currpara), definition.find(currpara) + currpara.length(), realvarstable[i]);
	}
	return Calculate(definition, depth + 1);
}
//表达式中所有函数求值并替换
string Calculator::ExpFuncsEval(string order, int depth)
{
	string result = "";
	int starti = 0, endi = 0;
	for (; starti < order.length(); starti++)
	{
		/*
		if (order[starti] == ')')
		{
			cout << "wdnmd,bug原来在这里！ " << starti << endl;
		}
		*/
		int check = (int)order[starti];
		if ((check >= 65 && check <= 90) ||
			(check >= 97 && check <= 122))
		{
			endi = starti;
			for (; endi < order.length() &&
				(((int)order[endi] >= 65 && (int)order[endi] <= 90) ||
					(int)order[endi] >= 97 && (int)order[endi] <= 122)
				; endi++);
			if (order[endi] == '(')
			{	//如果为函数调用
				int leftnum = 1, rightnum = 0;
				for (endi++; endi < order.length(); endi++)
				{
					if (order[endi] == '(') leftnum++;
					else if (order[endi] == ')') rightnum++;
					if (leftnum == rightnum && leftnum != 0) break;
				}
				result += FuncCall(order.substr(starti, endi - starti + 1), depth + 1);
				/*
				cout << "什么tm的叫tm的惊喜！" << FuncCall(order.substr(starti, endi - starti + 1), depth + 1) << endl;
				cout << "什么tm的叫tm的惊喜！" << result << endl;
				*/
				starti = endi;
			}
			else						//如果不为函数调用
			{
				result += order.substr(starti, endi - starti);
			}
		}
		else
		{
			result += order[starti];
		}
	}
	//cout << "函数替换后的结果式子：" << result << endl;
	return result;
}
//变量求值
string Calculator::VarEval(string order, int depth)
{
	int vari = -1;
	//检查变量是否存在
	for (int i = 0; i < VarsNum; i++)
	{
		if (VarsLib[i].Name == order)
		{
			vari = i;
			break;
		}
	}
	if (vari == -1)
	{
		printf("The variable %s does not exist!\n", order.c_str());
		IfCorrect = 0;
		return "0";
	}
	//调用Calculate求取变量值
	return Calculate(VarsLib[vari].Defini, depth + 1);
}
//表达式中所有变量求值
string Calculator::ExpVarsEval(string order, int depth)
{
	int starti = 0, endi = 0;
	string result;
	for (; starti < order.length(); starti++)
	{
		int check = (int)order[starti];
		if ((check >= 65 && check <= 90) ||
			(check >= 97 && check <= 122))
		{
			endi = starti;
			for (; endi < order.length() &&
				(((int)order[endi] >= 65 && (int)order[endi] <= 90) ||
					(int)order[endi] >= 97 && (int)order[endi] <= 122)
				; endi++);
			if (order[endi] != '(')			//判断是否为函数调用
			{
				result += Calculate(order.substr(starti, endi - starti), depth + 1);

			}
			else if (order[endi] == '(')	//如果为函数调用
			{
				result += order.substr(starti, endi - starti);
			}
			starti = endi - 1;	//使用endi - 1是因为等会进入循环for中又会加回来
		}
		else
		{
			result += order[starti];
		}
	}
	return result;
}
//二元运算
string Calculator::BinaryOperation(string order, int depth)
{
	//Debug用
	
	//cout << "获得操作材料：" << order << endl;
	

	int operatori = 0;
	for (; operatori < order.length(); operatori++)
	{
		int check = (int)order[operatori];
		if (!(check >= 48 && check <= 57) && !(check == 46) && operatori != 0) break;
	}
	//当操作符为指令order首个或者是最后一个时
	if (operatori == 0 || operatori == order.length() - 1)
	{
		printf("The order is not correct!\n");
		IfCorrect = 2;
		return "";
	}
	double operand1 = StringToDouble(order.substr(0, operatori));
	double operand2 = StringToDouble(order.substr(operatori + 1));

	/*
	cout << "二元运算对象：" << order << endl;
	cout << "操作数1：" << order.substr(0, operatori) << endl;
	cout << "操作数2：" << order.substr(operatori + 1) << endl;
	*/

	//Debug用
	/*
	cout << "操作符下标：" << operatori << endl;
	cout << "操作数1：" << operand1 << endl;
	cout << "操作数2：" << operand2 << endl;
	*/

	switch (order[operatori])
	{
	case('+'):
		return DoubleToString(operand1 + operand2);
		break;
	case('-'):
		return DoubleToString(operand1 - operand2);
		break;
	case('*'):
		return DoubleToString(operand1 * operand2);
		break;
	case('/'):
		if (operand2 == 0)
		{
			printf("Divisor is 0, operation error!\n");
			IfCorrect = 0;
			return "0";
			break;
		}
		else return DoubleToString(operand1 / operand2);
		break;
	default:
		return "0";
		break;
	}
}
//string转换为double
double Calculator::StringToDouble(string order)
{
	int notion = 1;
	double result = 0;
	//获取符号
	if (order[0] == '+')
	{
		notion = 1;
		order = order.substr(1);
	}
	else if (order[0] == '-')
	{
		notion = -1;
		order = order.substr(1);
	}
	//string类型转化为double类型
	int mode = 1;	//模式 1为整数，0为小数
	int integernum = 0;
	for (; integernum < order.length() && order[integernum] != '.'; integernum++);
	for (size_t i = 0; i < order.length(); i++)
	{
		if (order[i] == '.') mode = 0;
		else if (mode == 1)		//整数部分转换
		{
			result += ((double)order[i] - 48) * pow(10, integernum - (int)i - 1);	//size_t和int运算隐式类型转换会导致溢出
		}
		else if (mode == 0)		//小数部分转换
		{
			result += ((double)order[i] - 48) * pow(10, integernum - (int)i);
		}
	}
	//结果添加符号
	return result * notion;
}
//double转化为string
string Calculator::DoubleToString(double order)
{
	stringstream Oss;
	Oss << order;
	return Oss.str();
}
//总计算
string Calculator::Calculate(string order, int depth)
{
	//cout << endl << "接收到的计算式子：" << order << endl;
	//最大递归深度限制(不超过C++程序的真实最大递归深度)
	if (depth == MaxRecursiveDepth)
	{
		printf("Reached the max recursive depth!\n");
		//Debug用
		//cout << "此处已经修改了IfCorrect:" << endl;
		Calculator::IfCorrect = 2;
		return "0";
	}
	//括号匹配检查
	int bracketsnum = BracketCheck(order);
	if (bracketsnum == -1)
	{
		printf("Mismatched left and right brackets, wrong expression!\n");
		return "0";
	}
	//Base Case基本情况
	regex singlevar("[a-zA-Z]+");								//单个变量求值
	regex singlefunc("[a-zA-Z]+[(][0-9.,]*[)]");				//单个函数调用
	regex simplenumber("[\\-\\+]*[0-9.]+");						//纯数字求值
	regex binaryoperation("([\\-\\+]*[0-9.]+)[+-/*//]{1}[0-9.]+");	//二元运算

	
	//Debug用
	/*
	cout << "Calculate函数当前接收到的式子 " << order << endl;
	if (regex_match(order, singlevar)) cout << "进入单变量求值" << endl;
	else if (regex_match(order, singlefunc)) cout << "进入单个函数调用" << endl;
	else if (regex_match(order, simplenumber)) cout << "进入纯数字求值" << endl;
	else if (regex_match(order, binaryoperation)) cout << "进入二元运算" << endl;
	else cout << "进入综合运算" << endl;
	*/
	//Debug用

	if (regex_match(order, singlevar)) return VarEval(order, depth);					//单个变量求值
	else if (regex_match(order, singlefunc)) return FuncCall(order, depth);				//单个函数调用
	else if (regex_match(order, simplenumber)) return order;							//纯数字求值
	else if (regex_match(order, binaryoperation)) return BinaryOperation(order, depth);	//二元运算
	//非Base Case综合处理
	int ifalladdandsub = 1;
	for (int i = 0; i < order.length(); i++)
	{
		if (order[i] != '-' && order[i] != '+')
		{
			ifalladdandsub = 0;
			break;
		}
	}
	if (ifalladdandsub == 1)
	{
		printf("The order is not correct, please re-enter!\n");
		IfCorrect = 2;
		return "";
	}
	order = RemoveDuplication(order);		//去除表达式重复加减号
	order = ExpVarsEval(order, depth);				//表达式所有变量求值
	order = ExpFuncsEval(order, depth);			//表达式所有函数求值
	//cout << "处理后的指令:" << order << endl;

	if (regex_match(order, singlevar)) return VarEval(order, depth);					//单个变量求值
	else if (regex_match(order, singlefunc)) return FuncCall(order, depth);				//单个函数调用
	else if (regex_match(order, simplenumber)) return order;							//纯数字求值
	else if (regex_match(order, binaryoperation)) return BinaryOperation(order, depth);	//二元运算

	//无括号	由左至右&四则运算优先级
	bracketsnum = BracketCheck(order);
	if (bracketsnum == 0)
	{
		int starti = 0, endi = 0;
		int operatori = -1;
		//依据四则运算优先级&同优先级从左至右运算找到操作符
		for (int i = 0; i < order.length(); i++)
		{
			if ((order[i] == '*' || order[i] == '/') && i != 0)
			{
				operatori = i;
				break;
			}
		}
		if (operatori == -1)
		{
			for (int i = 0; i < order.length(); i++)
			{
				if ((order[i] == '+' || order[i] == '-') && i != 0)
				{
					operatori = i;
					break;
				}
			}
		}
		starti = operatori - 1, endi = operatori + 1;
		for (; starti > 0 && (((int)order[starti] >= 48 && (int)order[starti] <= 57) || order[starti] == '.'); starti--);
		for (; endi < order.length() && (((int)order[endi] >= 48 && (int)order[endi] <= 57) || order[endi] == '.'); endi++);
		if (starti != 0) starti++;
		/*
		system("pause");
		cout << operatori << " " << starti << " " << endi << endl;
		cout << order << "|" << endl;
		system("pause");
		*/
		if (endi == order.length() - 1)
		{
			return Calculate(order.substr(0, starti) + Calculate(order.substr(starti), depth + 1), depth + 1);
		}
		else
		{
			return Calculate(order.substr(0, starti) + Calculate(order.substr(starti, endi - starti), depth + 1) + order.substr(endi), depth + 1);
		}
	}
	//有括号	括号指定优先级&从左至右
	else
	{
		int starti = 0, endi = 0;
		int leftnum = 0, rightnum = 0;
		for (size_t i = 0; i < order.length(); i++)
		{
			if (order[i] == '(')
			{
				leftnum++;
				if (leftnum == 1) starti = i;
			}
			else if (order[i] == ')')
			{
				rightnum++;
				if (rightnum == leftnum && rightnum != 0)
				{
					endi = i;
					break;
				}
			}
		}
		//cout << starti << " " << endi << endl;
		if (endi == order.length() - 1)
		{

			return Calculate(order.substr(0, starti) + Calculate(order.substr(starti + 1, endi - starti - 1), depth + 1), depth + 1);
		}
		else
		{
			//cout << "starti + 1的值为：" << starti + 1 << endl;
			//cout << "endi - starti - 1的值为：" << endi - starti - 1 << endl;
			return Calculate(order.substr(0, starti) + Calculate(order.substr(starti + 1, endi - starti - 1), depth + 1) + order.substr(endi + 1), depth = 1);
		}
	}
}