#include<iostream>
using namespace std;
#define SIZE 2
void MatrixCin(double A[][SIZE]) {
	cout<<"Please enter the Matrix:\n";
	for(int i=0; i<SIZE; i++) {
		for(int j=0; j<SIZE; j++) {
			cin>>A[i][j];
		}
	}
}
void MatrixCout(double A[][SIZE]) {
	for(int i=0; i<SIZE; i++) {
		for(int j=0; j<SIZE; j++) {
			cout<<A[i][j]<<"\t";
		}
		cout<<"\n";
	}
}
void MatrixAdd(double A[][SIZE], double B[][SIZE], double Result[][SIZE],int N) {
	for(int i=0; i< N; i++) {
		for(int j=0; j<N; j++) {
			Result[i][j] = A[i][j] + B[i][j];
		}
	}
}
void MatrixSub(double A[][SIZE], double B[][SIZE], double Result[][SIZE],int N) {
	for(int i=0; i< N; i++) {
		for(int j=0; j<N; j++) {
			Result[i][j] = A[i][j] - B[i][j];
		}
	}
}

void Strassen(double A[][SIZE], double B[][SIZE], double C[][SIZE],int N) {
	if(N == 1) {
		C[0][0] = A[0][0] * B[0][0];
		return;
	} else {
		int mid  = (int)(N/2);
		double A11[SIZE][SIZE], A12[SIZE][SIZE], A21[SIZE][SIZE], A22[SIZE][SIZE];
		double B11[SIZE][SIZE], B12[SIZE][SIZE], B21[SIZE][SIZE], B22[SIZE][SIZE];
		double C11[SIZE][SIZE], C12[SIZE][SIZE], C21[SIZE][SIZE], C22[SIZE][SIZE];
		double M1[SIZE][SIZE], M2[SIZE][SIZE], M3[SIZE][SIZE], M4[SIZE][SIZE], M5[SIZE][SIZE], M6[SIZE][SIZE], M7[SIZE][SIZE];
		double TempA[SIZE][SIZE],TempB[SIZE][SIZE];

		for (int i = 0; i < mid; i++) {
			for (int j = 0; j < mid; j++) {
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][j + mid];
				A21[i][j] = A[i + mid][j];
				A22[i][j] = A[i + mid][j + mid];

				B11[i][j] = B[i][j];
				B12[i][j] = B[i][j + mid];
				B21[i][j] = B[i + mid][j];
				B22[i][j] = B[i + mid][j + mid];
			}
		}

		//M1=(B21-B22)*A11
		MatrixSub(B12, B22, TempB,mid);
		Strassen(A11, TempB,M1,mid);

		//M2=(A11+A12)*B22
		
		MatrixAdd(A11, A12, TempA, mid);
		Strassen(TempA, B22, M2, mid);

		//M3=(A21+A22)*B11
		MatrixAdd(A21, A22, TempA,mid);
		Strassen(TempA,B11,M3,mid);

		//M4=(B21-B11)*A22
		MatrixSub(B21, B11,TempB, mid);
		Strassen(A22, TempB, M4, mid);

		//M5=(A11+A22)*(B11+B22)
		MatrixAdd(A11, A22, TempA,mid);
		MatrixAdd(B11, B22, TempB,mid);
		Strassen(TempA, TempB, M5,mid);

		//M6=(A12-A22)*(B21+B22)
		MatrixSub(A12, A22, TempA, mid);
		MatrixAdd(B21, B22, TempB, mid);
		Strassen(TempA, TempB, M6, mid);

		//M7=(A11-A21)*(B11+B12)
		MatrixSub(A11, A21, TempA, mid);
		MatrixAdd(B11, B12, TempB, mid);
		Strassen(TempA, TempB, M7, mid);

		//C11=M5+M4-M2+M6
		MatrixAdd(M5, M4, TempA, mid);
		MatrixSub(TempA, M2, TempB, mid);
		MatrixAdd(TempB, M6, C11, mid);

		//C12=M1+M2
		MatrixAdd(M1, M2, C12, mid);

		//C21=M3+M4
		MatrixAdd(M3, M4, C21, mid);

		//C22=M5+M1-M3-M7
		MatrixAdd(M5, M1, TempA, mid); 
		MatrixSub(TempA,M3,TempB,mid);
		MatrixSub(TempB, M7, C22, mid);
		
		//union the matrix
		for (int i = 0; i < mid ; i++){
            for (int j = 0 ; j < mid ; j++){
                C[i][j] = C11[i][j];
                C[i][j + mid] = C12[i][j];
                C[i + mid][j] = C21[i][j];
                C[i + mid][j + mid] = C22[i][j];
            }
        }
	}
}

int main() {
	double A[SIZE][SIZE], B[SIZE][SIZE], Result[SIZE][SIZE];
	MatrixCin(A);
	MatrixCin(B);
	Strassen(A,B,Result,2);
	cout<<"The result is:\n";
	MatrixCout(Result);
}
