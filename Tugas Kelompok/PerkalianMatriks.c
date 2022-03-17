#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max 12000
static int result[max][max];
void basicmulti(int len, int matriksA[][max], int matriksB[][max]){
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
    char nama_filematriks[max];
    // Input nama file matriks
    printf("Program Untuk Menghitung Perkalian Matriks.\n");
    printf("Masukkan nama file yang berisi matriks a dan matriks b : ");
    scanf("%s", &nama_filematriks);
    
    // Akses isi file
    FILE* fin_matriks = fopen(nama_filematriks, "r");
    if(fin_matriks == NULL){
        printf("File tidak ada!");
        exit(0);
    }
    char baris[max];
    char* token;
    static int matriksA[max][max] = {0};
    static int matriksB[max][max] = {0};
    int matlen;
    int j = -1, k, m;
    m = 0;
    while(fgets(baris, max, fin_matriks)){
        k = 0;
        token = strtok(baris, " ");
        if(j == -1){
            matlen = atoi(token);
        } else {
            while(token != NULL){
                if(j < matlen){
                    matriksA[j][k] = atoi(token);
                } else {
                    matriksB[m][k] = atoi(token);
                }
                k += 1;
                token = strtok(NULL, " ");
            }
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
        basicmulti(matlen, matriksA, matriksB);
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
        int i;
        for(i = 0; i < matlen; i++){
            for(j = 0; j < matlen; j++){
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    }
    clock_t end = clock();
    timespent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time execution : %.3f seconds\n", timespent);
    fclose(fin_matriks);
}