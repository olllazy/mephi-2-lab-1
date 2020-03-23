#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <conio.h>
#include "Matrix.h"




//typedef struct complex {
//	real re;
//	real im;
//} complex;
//complex addComplex(complex z1, complex z2) {
//	complex z;
//	z.re = z1.re + z2.re;
//	z.im = z1.im + z2.im;
//	return z;
//}
//
//complex ScalMultComplex(complex z, real t) {
//	complex r;
//	r.re = t*z.re;
//	r.im = t*z.im;
//	return r;
//}
//
//complex MultComplex(complex z1, complex z2) {
//	complex z;
//	z.re = z1.re * z2.re - z1.im * z2.im;
//	z.im = z1.re * z2.im + z1.im * z2.re;
//}

Matrix CreateMatrix(Eltype eltype, int width, int height) {
	Matrix m;
	m.eltype = eltype;
	m.width = width;
	m.height = height;

	int typesize = sizeof(int);

	switch (eltype) {
	case INT: 
		typesize = sizeof(int); 
		break;
	case REAL:
		typesize = sizeof(real);
		break;
	/*case COMPLEX:
		typesize = sizeof(complex);
		break;*/
	default: break;
	}

	if (m.eltype == INT) {
		m.values = (int**)malloc(sizeof(int*) * m.height);
		for (int i = 0; i < height; i++)
			m.values[i] = (int*)malloc(typesize * m.width);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				((int**)m.values)[i][j] = 0;
			}
		}
	}
	else {
		m.values = (real**)malloc(sizeof(real*) * m.height);
		for (int i = 0; i < height; i++)
			m.values[i] = (real**)malloc(typesize * m.width);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				((real**)m.values)[i][j] = 0;
			}
		}
	}
	

	
	
	return m;
}

void DeleteMatrix(Matrix m) {
	//for (int i = 0; i < m.height; i++)
	//	free(m.values[i]);
	//m.values = NULL;
	free(m.values);
	return;
};

Matrix CreateZeroMatrix() {
	Matrix m;
	m.eltype = INT;
	m.width = 0;
	m.height = 0;
	m.values = NULL;

	int typesize = sizeof(int);
	
	return m;
}

Matrix ScanMatrix() {
	Eltype eltype = INT;
	int w = 0, h = 0;
	int tmp;
	printf("%s", "Type of elements:\n" 
		"1. Integer\n" 
		"2. Real\n" 
	/*"3. Complex\n"*/);
	scanf_s("%d", &tmp);

	switch (tmp) {
	case 1:
		eltype = INT;
		break;
	case 2:
		eltype = REAL;
		break;
	/*case 3:
		eltype = COMPLEX;
		break;*/
	default:
		printf("%s", "Wrong type of elements.");
		exit(2);
		break;
	}

	printf("%s", "Height:\n"); //высота
	scanf_s("%d", &h);
	if (h < 0) {
		printf("%s", "Wrong height of matrix.");
		exit(2);
	}
	printf("%s", "Width:\n"); //ширина
	scanf_s("%d", &w);
	if (h < 0) {
		printf("%s", "Wrong width of matrix.");
			exit(2);
	}

	Matrix m = CreateMatrix(eltype, w, h);
	printf("%s", "Enter the elements of matrix:\n"); //ширина
	switch (eltype)
	{
	//case COMPLEX:
	//	for (int i = 0; i < w; i++) {
	//		real re;
	//		real im;
	//		//real part
	//		printf("%s", "Real part of elements\n");
	//		for (int j = 0; j < h; j++) {
	//			scanf_s("%f", &re);
	//			((complex**)m.values)[i][j].re = re;
	//		}
	//		//imaginary part
	//		printf("%s", "Real part of elements\n");
	//		
	//		for (int j = 0; j < h; j++) {
	//			scanf_s("%f", &im);
	//			((complex**)m.values)[i][j].im = im;
	//		}
	//	}
	//	break;
	case INT:		
		for (int i = 0; i < h; i++) {
			int tmp;
			for (int j = 0; j < w; j++) {
				scanf_s("%d", &tmp);
				((int**)m.values)[i][j] = tmp;
			}
		}
		break;
	case REAL:
		for (int i = 0; i < h; i++) {
			real tmp ;
			for (int j = 0; j < w; j++) {
				scanf_s("%f", &tmp);
				((real**)m.values)[i][j] = tmp;
			}
		}
		break;
	default:
		break;
	}	
	return m;
}

void WriteMatrix(Matrix m) {
	switch (m.eltype) {
	case INT:
		for (int i = 0; i < m.height; i++) {
			for (int j = 0; j < m.width; j++)
				printf("%d ", ((int**)m.values)[i][j]);
			printf("\n");
		}
			
		break;	
	case REAL: 
		for (int i = 0; i < m.height; i++) {
			for (int j = 0; j < m.width; j++)
				printf("%7.3f ", ((real**)m.values)[i][j]);
			printf("\n");
		}
			
		break;
	/*case COMPLEX:

		break;*/
	default:
		break;
	}
	return;
}

Matrix AddMatrix(Matrix m1, Matrix m2) {
	if (m1.width != m2.width || m1.height != m2.height) {
		printf("%s","Wrong size of matrices.\n");
		return CreateZeroMatrix();
	}
	
	Eltype resEltype;
	if (m1.eltype == INT && m2.eltype == INT) resEltype = INT;
	else resEltype = REAL;

	//COMPLEX??
	int w = m1.width;
	int h = m1.height;

	Matrix result = CreateMatrix(resEltype,w,h);

	if (result.eltype == INT) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				((int**)result.values)[i][j] = ((int**)m1.values)[i][j] + ((int**)m2.values)[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < h; i++) 
			for (int j = 0; j < w; j++) 
				((real**)result.values)[i][j] = ((real**)m1.values)[i][j] + ((real**)m2.values)[i][j];
			
	}

	return result;
}

Matrix MultiplyMatrix(Matrix m1, Matrix m2) {
	if (m1.width != m2.height) {
		printf("%s", "Wrong size of matrices.\n");
		return CreateZeroMatrix();
	}
	int w = m2.width;
	int h = m1.height;
	Eltype resEltype;
	if (m1.eltype == INT && m2.eltype == INT) resEltype = INT;
	else resEltype = REAL;
	//COMPLEX??

	Matrix result = CreateMatrix(resEltype, w, h);

	if (result.eltype == INT) {
		for (int i = 0; i < h; i++) 
			for (int j = 0; j < w; j++)
				for (int k = 0; k < m1.width; k++) 
				((int**)result.values)[i][j] += ((int**)m1.values)[i][k]*((int**)m2.values)[k][j];
	}
	else {
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				for (int k = 0; k < m1.width; k++) {
					real tmp1;
					real tmp2;
					if (m1.eltype == INT) tmp1 = ((int**)m1.values)[i][k];
					else tmp1 = ((real**)m1.values)[i][k];

					if (m2.eltype == INT) tmp2 = ((int**)m2.values)[k][j];
					else tmp2 = ((real**)m2.values)[k][j];

				//	real res = ((real**)result.values)[i][j];
					((real**)result.values)[i][j] += tmp1 * tmp2;
					//res = ((real**)result.values)[i][j];
				}
					
	}
	
	return result;
}

Matrix TransposMatrix(Matrix m) {
	Matrix result = CreateMatrix(m.eltype, m.height, m.width);
	if (result.eltype == INT) {
		for (int i = 0; i < m.width; i++)
			for (int j = 0; j < m.height; j++)
					((int**)result.values)[i][j] = ((int**)m.values)[j][i];
	}
	else {
		for (int i = 0; i < m.width; i++)
			for (int j = 0; j < m.height; j++)
				((real**)result.values)[i][j] = ((real**)m.values)[j][i];
	}

	return result;
}

//Matrix ScalIntMultiplyMatrix(Matrix m, int x) {
//
//}
//
//Matrix ScalRealMultiplyMatrix(Matrix m, real x) {
//
//}

void LinCombMatrix(Matrix m) {
	if (m.height <= 0) {
		printf("%s", "Wrong size of matrix.\n");
		return;
	}
	int k;
	printf("The number of the line to add (from 0 to %d):\n",m.height-1);
	scanf_s("%d", &k);
	if (k >= m.height || k < 0) {
		printf("%s", "The wrong number.\n");
		return;
	}
	if (m.eltype == INT) {
		int* row = (int*)malloc(sizeof(int) * (m.width));
		for (int i = 0; i < m.width; i++) {
			row[i] = ((int**)m.values)[k][i];
		}
		printf("%s", "Sequentially enter the coefficients for each row.\n");
		for (int i = 0; i < m.height; i++) {
			if (i != k) {
				printf("The coefficient of the %d row:\n", i);
				int c;
				scanf_s("%d", &c);
				for (int j = 0; j < m.width; j++)
					row[j] += c*((int**)m.values)[i][j];
			}			
		}
		for (int j = 0; j < m.width; j++)
			printf("%d ", row[j]);
		printf("\n");
	}
	else {
		real* row = (real*)malloc(sizeof(real) * (m.width));
		for (int i = 0; i < m.width; i++) {
			row[i] = ((real**)m.values)[k][i];
		}
		printf("%s", "Sequentially enter the coefficients for each row.\n");
		for (int i = 0; i < m.height; i++) {
			if (i != k) {
				printf("The coefficient of the %d row:\n", i);
				real c;
				scanf_s("%f", &c);
				for (int j = 0; j < m.width; j++)
					row[j] += c * ((real**)m.values)[i][j];
			}
		}
		for (int j = 0; j < m.width; j++)
			printf("%g ", row[j]);
		printf("\n");
	}
	return;
}

typedef enum { OK, ERROR } Notification;

//Matrix AddMatrix(Matrix m1, Matrix m2) {}
//Matrix MultiplyMatrix(Matrix m1, Matrix m2) {}
//Matrix TransposMatrix(Matrix m) {}
//void LinCombMatrix(Matrix m) {}

void setMatrix(Matrix m) {
	int h = m.height;
	int w = m.width;
	if (m.eltype == INT) {
		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				((int**)m.values)[i][j] = i + j;
	}
	else {
		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				((real**)m.values)[i][j] = i + j;
	}
}
void setMatrixOne(Matrix m) {
	int h = m.height;
	int w = m.width;
	if (m.eltype == INT) {
		for (int i = 0; i < m.width; i++)
			for (int j = 0; j < m.height; j++)
				((int**)m.values)[i][j] = 1;
	}
	else {
		for (int i = 0; i < m.width; i++)
			for (int j = 0; j < m.height; j++)
				((real**)m.values)[i][j] = 1;
	}
}
void setMatrixZero(Matrix m) {
	int h = m.height;
	int w = m.width;
	if (m.eltype == INT) {
		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				((int**)m.values)[i][j] = 0;
	}
	else {
		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				((real**)m.values)[i][j] = 0;
	}
}
void setMatrixE(Matrix m) {
	int h = m.height;
	int w = m.width;
	if (m.eltype == INT) {
		for (int i = 0; i < m.width; i++)
			for (int j = 0; j < m.height; j++)
				if (i == j) ((int**)m.values)[i][j] = 1;
				else ((int**)m.values)[i][j] = 0;
	}
	else {
		for (int i = 0; i < m.width; i++)
			for (int j = 0; j < m.height; j++)
				if (i == j) ((int**)m.values)[i][j] = 1;
				else ((int**)m.values)[i][j] = 0;
	}
}
void setRandomMatrix(Matrix m) {
	int h = m.height;
	int w = m.width;
	srand(time(NULL));
	if (m.eltype == INT) {
		for (int i = 0; i < m.width; i++)
			for (int j = 0; j < m.height; j++) {
				((int**)m.values)[i][j] = rand() % 5000;
			}

	}
	else {
		for (int i = 0; i < m.width; i++)
			for (int j = 0; j < m.height; j++)
				((real**)m.values)[i][j] = rand() / 5000;
	}
}

//обычная целочисленная 
Notification test1_addMatrix() {

	Matrix a = CreateMatrix(INT, 4, 4);
	Matrix b = CreateMatrix(INT, 4, 4);
	setMatrix(a); 
	setMatrixOne(b);
	Matrix m = AddMatrix(a, b);
	if (m.width == 0) return ERROR;
	if (m.width != 4 || m.height != 4) return ERROR;
	if (m.eltype == INT) {
		for (int i = 0; i < m.width; i++)
			for (int j = 0; j < m.height; j++)
				if (((int**)m.values)[i][j] != i + j + 1) return ERROR;
	}
	else {
		for (int i = 0; i < m.width; i++)
			for (int j = 0; j < m.height; j++)
				if (((real**)m.values)[i][j] != i + j + 1) return ERROR;
	}
	DeleteMatrix(a); 
	DeleteMatrix(b);
	DeleteMatrix(m);
	return OK;
}
//одна не задана 
Notification test2_addMatrix() {
	Matrix a = CreateZeroMatrix();
	Matrix b = CreateMatrix(INT, 4, 4);
	setMatrixOne(b);
	Matrix m = AddMatrix(a, b);
	if (m.width != 0 || m.height != 0) return ERROR;
	DeleteMatrix(a); 
	DeleteMatrix(b);
	DeleteMatrix(m);
	return OK;
}
//размеры не сопадают 
Notification test3_addMatrix() {

	Matrix a = CreateMatrix(REAL, 4, 5);
	Matrix b = CreateMatrix(INT, 4, 4);
	setMatrix(a); setMatrixOne(b);
	Matrix m = AddMatrix(a, b);
	if (m.width != 0 || m.height != 0) return ERROR;
	DeleteMatrix(a); 
	DeleteMatrix(b);
	DeleteMatrix(m);
	return OK;
}
//типы не совпадают 
Notification test4_addMatrix() {
	Matrix a = CreateMatrix(REAL, 4, 5);
	Matrix b = CreateMatrix(INT, 4, 5);
	setMatrix(a); setMatrixOne(b);
	Matrix m = AddMatrix(a, b);
	if (m.eltype != REAL) return ERROR;
	DeleteMatrix(a); 
	DeleteMatrix(b);
	DeleteMatrix(m);
	return OK;
}

//обычная целочисленная 
Notification test1_MultiplyMatrix() {

 	Matrix a = CreateMatrix(INT, 4, 6);
	Matrix b = CreateMatrix(INT, 5, 4);
	setMatrix(a);
	Matrix m = MultiplyMatrix(a, b);
	if (m.width == 0) return ERROR;
	if (m.width != 5 || m.height != 6) return ERROR;
	if (m.eltype == INT) {
		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				if (((int**)m.values)[i][j] != 0) return ERROR;
	}
	else {
		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				if (((real**)m.values)[i][j] != 0) return ERROR;
	}
	DeleteMatrix(a); 
	DeleteMatrix(b);
	DeleteMatrix(m);
	return OK;
}
//одна не задана 
Notification test2_MultiplyMatrix() {

	Matrix a = CreateZeroMatrix();
	Matrix b = CreateMatrix(INT, 4, 4);
	setMatrixOne(b);
	Matrix m = MultiplyMatrix(a, b);
	if (m.width != 0 || m.height != 0) return ERROR;
	DeleteMatrix(a); 
	DeleteMatrix(b);
	DeleteMatrix(m);
	return OK;
}
//размеры не сопадают 
Notification test3_MultiplyMatrix() {

	Matrix a = CreateMatrix(REAL, 3, 5);
	Matrix b = CreateMatrix(INT, 4, 4);
	setMatrix(a); setMatrixOne(b);
	Matrix m = MultiplyMatrix(a, b);
	if (m.width != 0 || m.height != 0) return ERROR;
	DeleteMatrix(a); 
	DeleteMatrix(b);
	DeleteMatrix(m);
	return OK;
}
//типы не совпадают 
Notification test4_MultiplyMatrix() {
	Matrix a = CreateMatrix(REAL, 5, 4);
	Matrix b = CreateMatrix(INT, 4, 5);
	setMatrix(a); setMatrixOne(b);
	Matrix m = MultiplyMatrix(a, b);
	if (m.eltype != REAL) return ERROR;
	DeleteMatrix(a); 
	DeleteMatrix(b);
	DeleteMatrix(m);
	return OK;
}

//единичная 
Notification test1_TransposMatrix() {
	Matrix a = CreateMatrix(INT, 4, 4);
	setMatrixE(a);
	Matrix m = TransposMatrix(a);
	if (m.width == 0) return ERROR;
	if (m.width != 4 || m.height != 4) return ERROR;
	for (int i = 0; i < m.height; i++)
		for (int j = 0; j < m.width; j++)
			if (((int**)m.values)[i][j] != ((int**)m.values)[i][j]) return ERROR;
	DeleteMatrix(a);
	DeleteMatrix(m);
	return OK;
}
//не задана 
Notification test2_TransposMatrix() {
	Matrix a = CreateZeroMatrix();
	Matrix m = TransposMatrix(a);
	if (m.width != 0 || m.height != 0) return ERROR;

	DeleteMatrix(a);
	DeleteMatrix(m); 
	return OK;
}
//обычная
Notification test3_TransposMatrix() {
	Matrix a = CreateMatrix(REAL, 4, 5);
	setMatrix(a);
	Matrix m = TransposMatrix(a);
	if (m.width != 5 || m.height != 4) return ERROR;
	for (int i = 0; i < m.height; i++)
		for (int j = 0; j < m.width; j++)
			if (((real**)m.values)[i][j] != ((real**)a.values)[j][i]) return ERROR;
	DeleteMatrix(a);
	DeleteMatrix(m); 
	return OK;
}


int tests() {
	if (test1_addMatrix() == ERROR) return 1;
	if (test2_addMatrix() == ERROR) return 2;
	if (test3_addMatrix() == ERROR) return 3;
	if (test4_addMatrix() == ERROR) return 4;

	if (test1_MultiplyMatrix() == ERROR) return 5;
	if (test2_MultiplyMatrix() == ERROR) return 6;
	if (test3_MultiplyMatrix() == ERROR) return 7;
	if (test4_MultiplyMatrix() == ERROR) return 8;

	if (test1_TransposMatrix() == ERROR) return 9;
	if (test2_TransposMatrix() == ERROR) return 10;
	if (test3_TransposMatrix() == ERROR) return 11;
	   
	return 0;
}

void InterfaceMatrix() {
	Matrix a = { INT, 0, 0, NULL };
	Matrix b = { INT, 0, 0, NULL };
	int ans;
	int tmp;

	while (1) {
		printf("%s", "Menu:\n"
			"1. Matrix A;\n"
			"2. Matrix B;\n"
			"3. Matrix A+B;\n"
			"4. Matrix A*B;\n"
			"5. Transposed matrix;\n"
			"6. Adding a linear combination of other rows to a row;\n"
			"7. Tests;\n"
			"8. Exit.\n");
		scanf_s("%d", &ans);
		switch (ans)
		{
		case 1: 
			a = ScanMatrix();
			break;
		case 2:
			b = ScanMatrix();
			break;
		case 3: 
			WriteMatrix(AddMatrix(a, b));
			break;
		case 4:
			WriteMatrix(MultiplyMatrix(a, b));
			break;
		case 5:
			printf("%s", "Select the matrix:\n"
				"1. Matrix A;\n"
				"2. Matrix B;\n");			
			scanf_s("%d", &tmp);
			if (tmp == 1) WriteMatrix(TransposMatrix(a));
			else WriteMatrix(TransposMatrix(b));
			break;
		case 6:
			printf("%s", "Select the matrix:\n"
				"1. Matrix A;\n"
				"2. Matrix B;\n");
			scanf_s("%d", &tmp);
			if (tmp == 1) LinCombMatrix(a);
			else LinCombMatrix(b);
			break;
		case 7: 
			tmp = tests();
			if (tmp == 0) printf("%s","Tests are completed.\n");
			  else printf("Wrong test: %d.\n", tmp);
			break;
		case 8: exit(0);
		default:
			printf("%s\n","Wrong answer.");
			exit(3);
			break;
		}
	}
	DeleteMatrix(a);
	DeleteMatrix(b);
	return;

}




int main() {
	InterfaceMatrix();
	return 0;
}