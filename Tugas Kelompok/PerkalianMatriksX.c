#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define max 10000

void basicmulti(int len, int matriksA[][len], int matriksB[][len], int result[][len]){
    int i, j, k;
    for(i = 0; i < len; i++){
        for(j = 0; j < len; j++){
            result[i][j]= 0;
            for(k = 0; k < len; k++){
                result[i][j] += (matriksA[i][k] * matriksB[k][j]);
            }
        }
    }
    printf("Hasil perkalian Matriks : \n");
    for(i = 0; i < len; i++){
        for(j = 0; j <len; j++){
            printf("%d ", result[i][j]);
        }
        printf("\n");   
    }
}

int main(){
    char namafile[max];
    printf("Program untuk menghitung perkalian 2 buah matriks.\n");
    printf("Masukkan nama file matriks yang akan dihitung : ");
    scanf("%s", &namafile);
    FILE* fin_matriks = fopen(namafile, "r");
    char baris[max];
    char* token;
    int matlen;
    fgets(baris, max, fin_matriks);
    matlen = atoi(baris);
    static int matriksA[max][max];
    static int matriksB[max][max];
    static int result[max][max];
    int j = 0, k, m;
    m = 0;
    while(fgets(baris, max, fin_matriks)){
        k = 0;
        token = strtok(baris, " ");
        while(token != NULL){
            if(j < matlen){
                matriksA[j][k] = atoi(token);
            } else {
                matriksB[m][k] = atoi(token);
            }
            k += 1;
            token = strtok(NULL, " ");
        }
        if(j < matlen){
            j += 1;
        } else {
            m += 1;
        }
    }
    int choice;
    printf("Terdapat - algoritma yang dapat digunakan\n1. Iterative Algorithm (Algoritma yang diajarkan di sekolah)\n2. Strassen Algorithm\nPilih algoritma yang akan digunakan : ");
    scanf(" %d", &choice);
    double timespent = 0.0;
    clock_t begin = clock();
    if(choice == 1){
        basicmulti(matlen, matriksA, matriksB, result);
    } else if(choice == 2){
        int matlen2 = matlen;
        if(matlen == 10){
            matlen2 = 16;
        } else if(matlen == 100){
            matlen2 = 128;
        } else if(matlen == 1000){
            matlen2 = 1024;
        } else if(matlen == 10000){
            matlen2 = 16384;
        }
        for(j = 0; j < matlen; j++){
            for(k = 0; k < matlen; k++){
                printf("%d ", result[j][k]);
            }
            printf("\n");
        }
    }
    clock_t end = clock();
    timespent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time execution : %.3f seconds\n", timespent);
    fclose(fin_matriks);
}