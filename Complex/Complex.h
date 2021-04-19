#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include <cerrno>

//定义数据结构类型 
typedef struct Complex {
	float realpart;//实部
	float imagpart;//虚部
}Complex;

//————————————————基本函数声明—————————————————— 
//赋值
void assign(Complex* Com, float real, float imag);

//加法 
void addi(Complex* Com, Complex A, Complex B);

//减法 
void minus(Complex* Com, Complex A, Complex B);

//乘法 
void mult(Complex* Com, Complex A, Complex B);

//除法 
void div(Complex* Com, Complex A, Complex B);

//取复数实部
float GetReal(Complex* Com);

//取复数虚部
float GetImag(Complex* Com);

//绝对值 
float fab(Complex* Com);

//复数转实数
float rr2c(Complex* Com);

//输出完整的复数 
void Print_C(Complex* Com);

//————————————————功能函数声明——————————————————
//菜单
void menu();

//赋值函数 
void assignValue(Complex* Com);

//加法函数
void addCalc(Complex* Com);

//减法函数
void minCalc(Complex* Com);

//乘法函数
void multCalc(Complex* Com);

//除法函数
void divCalc(Complex* Com);

//绝对值函数
void fabCalc(Complex* Com);

//计算根
void formula(float a, float b, float c);

//解方程函数
void equationCalc();

//验证方程函数
void checkCalc(Complex Com1, Complex Com2);
