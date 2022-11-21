#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 2
typedef struct Matrix {
	double** Mat;
	int Size;
	char* name;
};
struct Matrix** m = NULL;
int static  _in = 0;
int static count = 1;
int static _in2 = 0;
struct Matrix* initMatrix(struct Matrix** m) {
	m = (struct Matrix**)malloc(sizeof(struct Matrix));

	return m;
}
struct Matrix* addSize(struct Matrix** m) {
	m[_in] = malloc(sizeof(struct Matrix) + 1);
	m[_in]->Size = N;
	m[_in]->name = NULL;
	m[_in]->Mat = (double**)malloc(sizeof(int*) * N);
	m[_in]->name = (char*)malloc(sizeof(int*) * N);
	for (int j = 0; j < N; j++) {
		m[_in]->Mat[j] = malloc(sizeof(int*) * N);
	}
	return m;
}
struct Matrix* Resize(struct Matrix** m, int index) {
	m[index] = malloc(sizeof(struct Matrix) + 1);
	m[index]->Size = N;
	m[index]->name = NULL;
	m[index]->Mat = (double**)malloc(sizeof(int*) * N);
	m[index]->name = (char*)malloc(sizeof(int*) * N);
	for (int j = 0; j < N; j++) {
		m[index]->Mat[j] = malloc(sizeof(int*) * N);
	}
	return m;
}
int check(struct Matrix** m, int index, char* name) {
	if (strlen(name) < 1 || strlen(name) > 2)
		return 0;
	if (name[0] < 'A' || name[0]>'Z')
		return 0;
	if (name[1] < '1' || name[1]>'9')
		return 0;
	return 1;

}
void AddMatrix(double mat[N][N], char* name) {
	m = addSize(m);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			m[_in]->Mat[i][j] = mat[i][j];
		}
	}
	m[_in]->name = name;
	++_in;
	printf("Added Successfully\n");
}
void printMatrix() {
	for (int i = 0; i < _in; i++) {
		printf("%s: \n", m[i]->name);
		for (int j = 0; j < m[i]->Size; j++) {
			for (int k = 0; k < m[i]->Size; k++) {
				printf("{    %.2f   }", m[i]->Mat[j][k]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
}


void pop_back(struct Matrix** m) {
	if (_in > -1) {
		/*free(m[_in]->Mat);
		m[_in]->Size = NULL;
		free(m[_in]->name);
		free(m[_in]);*/
		free(m[_in - 1]->Mat);
		m[_in - 1]->Size = NULL;
		m[_in - 1]->name = NULL;
		free(m[_in - 1]);
		--_in;
	}
}
struct Matrix* deleteMatrix(struct Matrix** m, char* name) {
	struct Matrix** m2;
	m2 = (struct Matrix**)malloc(sizeof(struct Matrix));
	int _in2 = 0;
	for (int i = 0; i < _in; i++) {
		if (m[i]->name != name) {
			m2 = Resize(m2, _in2);
			m2[_in2]->Mat = m[i]->Mat;
			m2[_in2]->name = m[i]->name;
			m2[_in2]->Size = m[i]->Size;
			_in2++;

		}
	}
	m = m2;
	_in--;
	printf("Delet Succefully\n");
	return m;
}
int SearchIndex(char* name) {
	for (int i = 0; i < _in + 1; i++) {
		if (m[i]->name == name)
			return i;
	}
	return -1;
}
struct Matrix* Sum_Matrix(struct Matrix** m, char* name, char* name2) {
	int index = SearchIndex(name);
	int index2 = SearchIndex(name2);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			m[index2]->Mat[i][j] = m[index]->Mat[i][j] + m[index2]->Mat[i][j];
		}
	}
	return m;
}
struct Matrix* Sub_Matrix(struct Matrix** m, char* name, char* name2) {
	int index = SearchIndex(name);
	int index2 = SearchIndex(name2);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			m[index2]->Mat[i][j] = m[index]->Mat[i][j] - m[index2]->Mat[i][j];
		}
	}
	return m;
}
struct Matrix* Mul_Matrix(struct Matrix** m, char* name, char* name2) {
	int index = SearchIndex(name);
	int index2 = SearchIndex(name2);
	double sum = 0;
	struct Matrix** m2 = NULL;
	m2 = initMatrix(m2);
	m2 = Resize(m2, 0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				for (int p = 0; p < N; p++) {
					sum += m[index]->Mat[j][p] * m[index2]->Mat[p][k];

				}
				m2[0]->Mat[j][k] = sum;
				sum = 0;
			}
		}
	}
	m[index2]->Mat = m2[0]->Mat;
	return m;
}
struct Matrix* Pow_Matrix(struct Matrix** m, char* name, int power) {
	int index = SearchIndex(name);
	double mat[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			mat[i][j] = m[index]->Mat[i][j];
		}
	}
	AddMatrix(mat, "Z4");
	if (power < 10) {
		for (int i = 1; i < power; i++) {
			m = Mul_Matrix(m, "Z4", name);
		}
	}
	pop_back(m);
	return m;
}
void printMatrix2(char* name) {
	int index = SearchIndex(name);
	for (int j = 0; j < N; j++) {
		printf("{");
		for (int k = 0; k < N; k++) {
			printf("    %.2f   ", m[index]->Mat[j][k]);
		}
		printf("}");
		printf("\n");
	}
}
void List() {
	printf("--------------------\n");
	printf("||      Menu      ||\n");
	printf("--------------------\n");
	printf("1. Add a new Matrix\n");
	printf("2. Delete an existing Matrix\n");
	printf("3. Add Matrices\n");
	printf("4. Sub Matrices\n");
	printf("5. Mul Matrices\n");
	printf("6. Pow Matrix\n");
	printf("7. Print Matrix\n");
	printf("8. retrun Index\n");
	printf("9. End\n");

}
int main() {
	m = initMatrix(m);
	/*double mat[N][N] = { {1,2},{3,4} };
	double mat2[N][N] = { {4,5},{8,7} };
	AddMatrix(mat, "A1");
	AddMatrix(mat2, "A2");
	AddMatrix(mat2, "A3");
	m = deleteMatrix(m, "A1");
	m = deleteMatrix(m, "A2");
	AddMatrix(mat2, "A4");
	m = deleteMatrix(m, "A3");
	printMatrix();*/
	int choose;
	int flag = 0;
	char name1[2];
	char name2[2];
	double mat[N][N];
	int power;
	
	do {
		List();
		printf("Pick your option : ");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			printf("Enter The name Matrix\n");
			fgets(name1, strlen(name1), stdin);
			scanf_s("%2s", name1,2);
			for (int i = 0; i < N; i++) {
				printf("Enter %d Row \n", i);
				for (int j = 0; j < N; j++) {
					scanf("%lf", &mat[i][j]);
				}
			}
			printf("%s", name1);
			AddMatrix(mat, name1);
			break;
		case 2:
			printf("Enter the name Matrix to Delete\n");
			scanf("%s", name1);
			if (SearchIndex(name1) == -1) {
				printf("This Name Not Exist in Data Structer\n");
			}
			else {
				m = deleteMatrix(m, name1);
			}
			break;
		case 3:
			printf("Enter Add Name 1 Matrix\n");
			scanf("%s", name1);
			printf("Enter Add Name 2 Matrix\n");
			scanf("%s", name2);
			m = Sum_Matrix(m, name1, name2);
			break;
		case 4:
			printf("Enter Add Name 1 Matrix\n ");
			scanf("%s", name1);
			printf("Enter Add Name 2 Matrix\n ");
			scanf("%s", name2);
			m = Sub_Matrix(m, name1, name2);
			break;
		case 5:
			printf("Enter Add Name 1 Matrix\n ");
			scanf("%s", name1);
			printf("Enter Add Name 2 Matrix\n ");
			scanf("%s", name2);
			m = Mul_Matrix(m, name1, name2);
			break;
		case 6:
			printf("Enter Add Name 1 Matrix\n ");
			scanf("%s", name1);
			printf("Enter the number is power\n");
			scanf_s("%d", &power);
			m = Pow_Matrix(m, name1, name1, power);
			break;
		case 7:
			printf("Enter Add Name 1 Matrix\n");
			scanf("%s", name1);
			printMatrix2(name1);
			break;
		case 8:
			printf("Enter Add Name 1 Matrix\n");
			scanf("%s", name1);
			printf("%d\n", SearchIndex(name1));
			break;
		case 9:
			flag = 1;
			break;
		default:
			break;
		}

	} while (flag == 0);
	/*
	double mat1[N][N] = { {1,2},{3,4} };
	double mat2[N][N] = { {1,2},{3,4} };
	AddMatrix(mat1, "A1");
	AddMatrix(mat2, "A2");
	m = Sum_Matrix(m, "A1", "A2");
	printMatrix();
	m = Sub_Matrix(m, "A1", "A2");
	printMatrix();
	m = Mul_Matrix(m, "A1", "A2");
	printMatrix();
	m = Pow_Matrix(m, "A1",5);
	printMatrix();
	m = deleteMatrix(m, "A1");
	printMatrix();
	pop_back(m);
	printMatrix();
	*/
	return 0;
}