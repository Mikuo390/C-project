#define _CRT_SECURE_NO_WARNINGS

#include<math.h>
#include<stdio.h>

typedef struct {
	float realpart;//实部
	float imagpart;//虚部
}Complex;//定义复数抽象类型

void assign(Complex* Com, float real, float imag);//赋值
void add(Complex* Com, float real, float imag);//A+B
void minus(Complex* Com, float real, float imag);//A-B
void munltiply(Complex* Com, float real, float imag);//A*B
void divide(Complex* Com, float real, float imag);//A/B
float GetReal(Complex* Com);//取复数实部
float GetImag(Complex* Com);//去复数虚部
void Print_C(Complex* Com);//复数输出


void assign(Complex* Com, float real, float imag) {
	Com->realpart = real;//实部赋值
	Com->imagpart = imag;//虚部赋值
}                        //End of assign()

void add(Complex* Com, Complex A, Complex B) {
	Com->realpart = A.realpart + B.realpart;//实部相加
	Com->imagpart = A.imagpart + B.imagpart;//虚部相加
}											//End of add()

void minus(Complex* Com, Complex A, Complex B) {
	Com->realpart = A.realpart - B.realpart;//实部相减
	Com->imagpart = A.imagpart - B.imagpart;//虚部相减
}											//End of minus()

void munltiply(Complex* Com, Complex A, Complex B) {
	Com->realpart = A.realpart * B.realpart - A.imagpart * B.imagpart;
	Com->imagpart = A.imagpart * B.realpart + A.realpart * B.imagpart;
}											//End of munlt()

void divide(Complex* Com, Complex A, Complex B) {
	Com->realpart = (A.realpart * B.realpart + A.imagpart * B.imagpart)
					/ (pow(B.realpart, 2) + pow(B.imagpart, 2));
	Com->imagpart = (A.imagpart * B.realpart - A.realpart * B.imagpart)
					/ (pow(B.realpart, 2) + pow(B.imagpart, 2));
}											//End of divide()

float GetReal(Complex* Com) {
	//printf("%f\n", Com->realpart);
	return Com->realpart;
}

float GetImag(Complex* Com) {
	//printf("%f\n", Com->imagpart);
	return Com->imagpart;
}

void Print_C(Complex* Com) {
	printf("%.2f + %.2f *i\n", Com->realpart, Com->imagpart);
}

int main() {
	Complex z1, z2, z3, z4, z;
	float RealPart = 0, ImagPart = 0;
	assign(&z1, 8.0, 6.0);//z1 = 8+6i 
	assign(&z2, 4.0, 3.0);//z2 = 4+3i
	add(&z3, z1, z2);//z3 = (8 + 6i) + (4 + 3i)
	munltiply(&z4, z1, z2);//z4 = (8 + 6i) * (4 + 3i)
	divide(&z, z4, z3);//z = z4/z3 = (8 + 6i) * (4 + 3i) / ((8 + 6i) + (4 + 3i))
	GetReal(&z, RealPart);
	GetImag(&z, ImagPart);
	Print_C(&z);
}
