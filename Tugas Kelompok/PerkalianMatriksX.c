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
    printf("Terdapat - algoritma yang dapat digunakan\n1. Iterative Algorithm (Algoritma yang diajarkan di sekolah)\nPilih algoritma yang akan digunakan : ");
    scanf(" %d", &choice);
    double timespent = 0.0;
    clock_t begin = clock();
    if(choice == 1){
        basic_multi(A, B,matlenA);
    }
    clock_t end = clock();
    timespent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time execution : %.3f seconds\n", timespent);
    free(A);
    free(B);
}