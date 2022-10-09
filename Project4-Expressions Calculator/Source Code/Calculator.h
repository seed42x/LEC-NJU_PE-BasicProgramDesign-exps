#pragma once
#include<stdio.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<regex>
#include<math.h>
#include<sstream>
using namespace std;

class Calculator
{
public:
	//����������***
	Calculator();
	~Calculator();
	//����*********
	void Run();
private:
	//������*******
	void CreateVar(string order);
	void CreateFunc(string order);
	//չʾ��*******
	void ShowVars() const;
	void ShowFuncs() const;
	//���������޸�*
	void VarAssignment(string order);
	//������*******
	//1.�ȶ���ά��
	int BracketCheck(string order);
	string RemoveDuplication(string order);				//ȥ���ظ��Ӽ���
	//2.��������(Base Case����)
	string VarEval(string order, int depth);			//������ֵ
	string FuncCall(string order, int depth);			//��������
	string BinaryOperation(string order, int depth);	//������Ԫ����
	//3.�ۺ�����
	string ExpVarsEval(string order, int depth);		//�� ���б�����ֵ
	string ExpFuncsEval(string order, int depth);		//�� ���к�����ֵ
	string Calculate(string order, int depth);			//�� ���ʽ��ֵ(Main Recursive Function)
	//4.��������
	double StringToDouble(string order);				//stringת��Ϊdouble
	string DoubleToString(double order);				//doubleת��Ϊstring
	//δ��********
	string SuperAdd(string operand1, string operand2);			//���������������
	string SuperMultiply(string operand1, string operand2);		//���������������
private:
	//��������
	struct Var 
	{
		string Name;
		string Defini;
	};
	//��������
	struct Func
	{
		string Name;
		string Defini;
		int ParameterNum = 0;			//��ʽ��������
		string ParameterTable[10]{};	//��ʽ������(�������ڰ�ʵ��)
	};
	int IfCorrect;				//�����ȷ�ԣ������Ƿ�������(1.��ȷ 2.����)
	//��Ŀ
	int VarsNum;				//�������еı�����Ŀ
	int FuncsNum;				//�������еĺ�����Ŀ
	int MaxRecursiveDepth;		//�������ݹ����
	//��
	Var* VarsLib;				//������
	Func* FuncsLib;				//������
};

