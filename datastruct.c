//定义复数数据类型
#include <stdio.h>
typedef struct {
	float realpart;
	float imagpart;
} Complex;

void assign(Complex* A, float real, float image);
void add(Complex* C, const Complex A, const Complex B);
void minus(Complex* C, const Complex A, const Complex B);
void multiply(Complex* C, const Complex A, const Complex B);
void divide(Complex* C, const Complex A, const Complex B);

void assign(Complex* A, float real, float imag)
{
	A->realpart = real;
	A->imagpart = imag;
}
void add(Complex* C, const Complex A, const Complex B)
{
	C->realpart = A.realpart + B.realpart;
	C->imagpart = A.imagpart + B.imagpart;
}
void minus(Complex* C, const Complex A, const Complex B)
{
	C->realpart = A.realpart - B.realpart;
	C->imagpart = A.imagpart - B.imagpart;
}
void multiply(Complex* C, const Complex A, const Complex B)
{
	C->realpart = A.realpart * B.realpart - A.imagpart * B.imagpart;
	C->imagpart = A.realpart * B.imagpart + A.imagpart * B.realpart;
}
void divide(Complex* C, const Complex A, const Complex B)
{
	Complex temp;
	Complex B1;
	B1.realpart = B.realpart;
	B1.imagpart = -B.imagpart;
	multiply(&temp, A, B1);
	C->realpart = temp.realpart / (B.realpart * B.realpart + B.imagpart * B.imagpart);
	C->imagpart = temp.imagpart / (B.realpart * B.realpart + B.imagpart * B.imagpart);
}

main(){
	const Complex test;
	assign(test) 
}