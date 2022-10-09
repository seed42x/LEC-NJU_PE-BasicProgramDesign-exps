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
	//构造与析构***
	Calculator();
	~Calculator();
	//运行*********
	void Run();
private:
	//创建组*******
	void CreateVar(string order);
	void CreateFunc(string order);
	//展示组*******
	void ShowVars() const;
	void ShowFuncs() const;
	//变量定义修改*
	void VarAssignment(string order);
	//运算组*******
	//1.稳定性维护
	int BracketCheck(string order);
	string RemoveDuplication(string order);				//去除重复加减号
	//2.基本运算(Base Case调用)
	string VarEval(string order, int depth);			//变量求值
	string FuncCall(string order, int depth);			//函数调用
	string BinaryOperation(string order, int depth);	//基本二元运算
	//3.综合运算
	string ExpVarsEval(string order, int depth);		//求 所有变量的值
	string ExpFuncsEval(string order, int depth);		//求 所有函数的值
	string Calculate(string order, int depth);			//求 表达式的值(Main Recursive Function)
	//4.辅助函数
	double StringToDouble(string order);				//string转换为double
	string DoubleToString(double order);				//double转换为string
	//未用********
	string SuperAdd(string operand1, string operand2);			//任意两个大数相加
	string SuperMultiply(string operand1, string operand2);		//任意两个大数相乘
private:
	//变量对象
	struct Var 
	{
		string Name;
		string Defini;
	};
	//函数对象
	struct Func
	{
		string Name;
		string Defini;
		int ParameterNum = 0;			//形式参数数量
		string ParameterTable[10]{};	//形式参数表(后续用于绑定实参)
	};
	int IfCorrect;				//结果正确性，决定是否输出结果(1.正确 2.错误)
	//数目
	int VarsNum;				//变量库中的变量数目
	int FuncsNum;				//函数库中的函数数目
	int MaxRecursiveDepth;		//设置最大递归深度
	//库
	Var* VarsLib;				//变量库
	Func* FuncsLib;				//函数库
};

