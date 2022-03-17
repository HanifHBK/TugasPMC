#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define max 30000

typedef struct matrix{
    int* array;
} matrix;

matrix* open_file(matrix* data, int* jml_sampel){
    FILE* seq_file;
    char namaFile[max]; //asumsi maksimal panjang nama file 7
    char line[max]; 
    char* token;
    int n=0, k;

    scanf("%s", &namaFile);

    seq_file=fopen(namaFile, "r");
    if(seq_file == NULL){
        printf("File tidak ada!");
        exit(0);
    }

    while (fgets(line, max, seq_file)){
        k = 0;
        if(n>0){
            data=(matrix*) realloc(data, (n+1)*sizeof(matrix));
        }
        token = strtok(line, " ");
        (data+n)->array = (int*) malloc(sizeof(int));
        while(token != NULL){
            (data+n)->array = (int*) realloc((data+n)->array, (k+1)*sizeof(int));
            (data+n)->array[k] = atoi(token);
            token = strtok(NULL, " ");
            k += 1;
        }
        n++; 
    }fclose(seq_file);

    *jml_sampel=n;

    return data;
}

void basic_multi(matrix* matA, matrix* matB, int matlen){
    matrix* result;
    result = (matrix*) malloc(matlen*sizeof(matrix));
    int i, j, k;
    for(i = 0; i < matlen; i++){
        (result+i)->array = (int*) calloc(matlen, sizeof(int));
        for(j = 0; j < matlen; j++){
            for(k = 0; k < matlen; k++){
                (result+i)->array[j] += ((matA + i)->array[k] * (matB + k)->array[j]);
            }
        }
    }
    printf("Hasil perkalian Matriks : \n");
    for(i = 0; i < matlen; i++){
        for(j = 0; j < matlen; j++){
            printf("%d ", (result+i)->array[j]);
        }
        printf("\n");   
    }
}

void divider(int len, matrix* mat, matrix* A11, matrix* A12, matrix* A21, matrix* A22){
    int i,j;
    for(i = 0; i < 2*len; i++){
        (A11+i)->array = (int*) malloc(len*sizeof(int));
        (A12+i)->array = (int*) malloc(len*sizeof(int));
        (A21+i)->array = (int*) malloc(len*sizeof(int));
        (A22+i)->array = (int*) malloc(len*sizeof(int));
        for(j = 0; j < 2*len; j++){
            if(i < len && j < len){
                (A11+i)->array[j] = (mat+i)->array[j];
            } else if(i < len && j >= len){
                (A12+i)->array[j - len] = (mat+i)->array[j];
            } else if(i >= len && j < len){
                (A21 + (i-len))->array[j] = (mat+i)->array[j];
            } else if(i >= len && j >= len){
                (A22 + (i-len))->array[j-len] = (mat+i)->array[j];
            }
        }
    }
}
void addition(int len, matrix* matriks1, matrix* matriks2, matrix* matriksres){
    int i, j;
    for(i = 0; i < len; i++){
        (matriksres+i)->array = (int*) malloc(len*sizeof(int));
        for(j = 0; j < len; j++){
            (matriksres+i)->array[j] = ((matriks1+ i)->array[j] + (matriks2+ i)->array[j]);
        }
    }
}
void subtraction(int len, matrix* matriks1, matrix* matriks2, matrix* matriksres){
    int i, j;
    for(i = 0; i < len; i++){
        (matriksres+i)->array = (int*) malloc(len*sizeof(int));
        for(j = 0; j < len; j++){
            (matriksres+i)->array[j] = ((matriks1+ i)->array[j] - (matriks2+ i)->array[j]);
        }
    }
}
void join(int len, matrix* matriksA, matrix* matriksB, matrix* matriksC, matrix* matriksD, matrix* res){
    int i, j;
    int x = len/2;
    for(i = 0; i < len; i++){
        for(j = 0; j < len; j++){
            if(i < x && j < x){
                (res + i)->array[j] = (matriksA + i)->array[j];
            } else if(i < x && j >= x){
                (res + i)->array[j] = (matriksB + i)->array[j-x];
            } else if(i >= x && j < x){
                (res + i)->array[j] = (matriksC + (i-x))->array[j];
            } else if(i >= x && j >= x){
                (res + i)->array[j] = (matriksD + (i-x))->array[j-x];
            }
        }
    }
}
void strassen(int len, matrix* matriksA, matrix* matriksB, matrix* res){
    int i;
    for(i = 0; i < len; i++){
        (res+i)->array = (int*) malloc(len*sizeof(int));
    }
    int x = len/2;
    if(len == 1){
        res->array[0] = (matriksA->array[0]*matriksB->array[0]);
    } else {
        matrix *C1, *C2, *C3, *C4, *A11, *A12, *A21, *A22, *B11, *B12, *B21, *B22 = (matrix*) malloc(x*sizeof(matrix));
        matrix *A11aA22, *B11aB22, *A21aA22, *A11aA12, *B11aB12, *B21aB22, *B12sB22, *B21sB11, *A21sA11, *A12sA22 = (matrix*) malloc(x*sizeof(matrix));
        matrix *M0, *M1 , *M2 , *M3, *M4, *M5, *M6 = (matrix*) malloc(x*sizeof(matrix));
        divider(x, matriksA, A11, A12, A21, A22);
        divider(x, matriksB, B11, B12, B21, B22);
        addition(x, A11, A22, A11aA22);
        addition(x, B11, B22, B11aB22);
        addition(x, A21, A22, A21aA22);
        addition(x, A11, A12, A11aA12);
        addition(x, B11, B12, B11aB12);
        addition(x, B21, B22, B21aB22);
        subtraction(x, B12, B22, B12sB22);
        subtraction(x, B21, B11, B21sB11);
        subtraction(x, A21, A11, A21sA11);
        subtraction(x, A12, A22, A12sA22);
        strassen(x, A11aA22, B11aB22, M0);
        strassen(x, A21aA22, B11, M1);
        strassen(x, A11, B12sB22, M2);
        strassen(x, A22, B21sB11, M3);
        strassen(x, A11aA12, B22, M4);
        strassen(x, A21sA11, B11aB12, M5);
        strassen(x, A12sA22, B21aB22, M6);
        // C1
        addition(x, M0, M3, C1);
        subtraction(x, C1, M4, C1);
        addition(x, C1, M6, C1);
        // C2
        addition(x, M2, M4, C2);
        // C3
        addition(x, M1, M3, C3);
        // C4
        subtraction(x, M0, M1, C4);
        addition(x, C4, M2, C4);
        addition(x, C4, M5, C4);
        join(len, C1, C2, C3, C4, res);
        // freeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
        free(C1);free(C2);free(C3);free(C4);free(A11);free(A21);free(A12);free(A22);free(B11);free(B12);free(B21);free(B22);
        free(A11aA22);free(B11aB22);free(A21aA22);free(A11aA12);free(B11aB12);free(B21aB22);free(B12sB22);free(B21sB11);free(A21sA11);free(A12sA22);
        free(M0);free(M1);free(M2);free(M3);free(M4);free(M5);free(M6);
    }
}

int main(){
    // Input nama file matriks
    printf("Program Untuk Menghitung Perkalian Matriks.\n");
    matrix* A;
    matrix* B;
    A = (matrix*) malloc(sizeof(matrix));
    int matlenA;
    printf("Masukkan nama file matriks A (pertama) : ");
    A = open_file(A, &matlenA);
    int matlenB;
    printf("Masukkan nama file matriks B (kedua) : ");
    B = (matrix*) malloc(sizeof(matrix));
    B = open_file(B, &matlenB);
    if(matlenA != matlenB){
        printf("Ukuran matriks tidak sama, program akan keluar!");
        exit(0);
    }
    int choice;
    printf("Terdapat - algoritma yang dapat digunakan\n1. Iterative Algorithm (Algoritma yang diajarkan di sekolah)\n2. Strassen Algorithm\nPilih algoritma yang akan digunakan : ");
    scanf(" %d", &choice);
    double timespent = 0.0;
    clock_t begin = clock();
    if(choice == 1){
        basic_multi(A, B,matlenA);
    } else if(choice == 2){
        int matlen2 = matlenA;
        if(matlenA == 10){
            matlen2 = 16;
        } else if(matlenA == 100){
            matlen2 = 128;
        } else if(matlenA == 1000){
            matlen2 = 1024;
        } else if(matlenA == 10000){
            matlen2 = 16384;
        }
        A = (matrix*) realloc(A, matlen2*sizeof(matrix));
        B = (matrix*) realloc(A, matlen2*sizeof(matrix));
        int i, j;
        for(i = 0; i < matlen2; i++){
            (A+i)->array = (int*) realloc((A+i)->array, matlen2*sizeof(int));
            (B+i)->array = (int*) realloc((A+i)->array,  matlen2*sizeof(int));
            for(j = matlenA; j <matlen2; j++){
                (A+i)->array[j] = 0;
                (B+i)->array[j]= 0;
            }
        }
        matrix* result = (matrix*) malloc(matlen2*sizeof(matrix));
        strassen(matlen2, A, B, result);
        for(i = 0; i < matlenA; i++){
            for(j = 0; j < matlenA; j++){
                printf("%d ", (result+i)->array[j]);
            }
            printf("\n");
        }
        free(result);
    }
    clock_t end = clock();
    timespent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time execution : %.3f seconds\n", timespent);
    free(A);
    free(B);
}