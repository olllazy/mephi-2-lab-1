#pragma once

typedef enum { INT, REAL/*, COMPLEX*/ } Eltype;
typedef float real;

typedef struct Matrix {
	Eltype eltype;
	int width;
	int height;
	void** values;
} Matrix;

Matrix CreateMatrix(Eltype eltype, int width, int height);

void DeleteMatrix(Matrix m);

Matrix CreateZeroMatrix();

Matrix ScanMatrix();

void WriteMatrix(Matrix m);

Matrix AddMatrix(Matrix m1, Matrix m2);

Matrix MultiplyMatrix(Matrix m1, Matrix m2);

Matrix TransposMatrix(Matrix m);

void LinCombMatrix(Matrix m);

void InterfaceMatrix();

