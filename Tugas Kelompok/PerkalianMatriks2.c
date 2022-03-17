#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max 120
static int result[max][max] = {0};
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

void divider(int len, int matriksA[][max], int A11[][max], int A12[][max], int A21[][max], int A22[][max]){
    int i,j;
    for(i = 0; i < 2*len; i++){
        for(j = 0; j < 2*len; j++){
            if(i < len && j < len){
                A11[i][j] = matriksA[i][j];
            } else if(i < len && j >= len){
                A12[i][j - len] = matriksA[i][j];
            } else if(i >= len && j < len){
                A21[i-len][j] = matriksA[i][j];
            } else if(i >= len && j >= len){
                A22[i-len][j-len] = matriksA[i][j];
            }
        }
    }
}
void addition(int len, int matriks1[][max], int matriks2[][max], int matriksres[][max]){
    int i, j;
    for(i = 0; i < len; i++){
        for(j = 0; j < len; j++){
            matriksres[i][j] = (matriks1[i][j] + matriks2[i][j]);
        }
    }
}
void subtraction(int len, int matriks1[][max], int matriks2[][max], int matriksres[][max]){
    int i, j;
    for(i = 0; i < len; i++){
        for(j = 0; j < len; j++){
            matriksres[i][j] = (matriks1[i][j] - matriks2[i][j]);
        }
    }
}

void join(int len, int matriksA[][max], int matriksB[][max], int matriksC[][max], int matriksD[][max], int res[][max]){
    int i, j;
    int x = len/2;
    for(i = 0; i < len; i++){
        for(j = 0; j < len; j++){
            if(i < x && j < x){
                res[i][j] = matriksA[i][j];
            } else if(i < x && j >= x){
                res[i][j] = matriksB[i][j-x];
            } else if(i >= x && j < x){
                res[i][j] = matriksC[i-x][j];
            } else if(i >= x && j >= x){
                res[i][j] = matriksD[i-x][j-x];
            }
        }
    }
}


void strassen(int len, int matriksA[][max], int matriksB[][max], int res[][max]){
    int x = len/2;
    int C1[x][x], C2[x][x], C3[x][x], C4[x][x];
    int M0[x][x],M1[x][x],M2[x][x],M3[x][x],M4[x][x],M5[x][x],M6[x][x];
    int A11[x][x], A12[x][x], A21[x][x], A22[x][x];
    int B11[x][x], B12[x][x], B21[x][x], B22[x][x];
    int A11aA22[x][x], B11aB22[x][x], A21aA22[x][x], A11aA12[x][x], B11aB12[x][x], B21aB22[x][x];
    int B12sB22[x][x], B21sB11[x][x], A21sA11[x][x], A12sA22[x][x];
    if(len == 1){
        res[0][0] = (matriksA[0][0]*matriksB[0][0]);
    } else {
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
        strassen(x, A22, B21sB11,M3);
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
        int i, j;
        printf("M0 : \n");
        for(i = 0; i < x; i++){
            for(j = 0; j < x; j++){
                printf("%d ", M0[i][j]);
            }
            printf("\n");
        }
        printf("M1 : \n");
        for(i = 0; i < x; i++){
            for(j = 0; j < x; j++){
                printf("%d ", M1[i][j]);
            }
            printf("\n");
        }
        printf("M2 : \n");
        for(i = 0; i < x; i++){
            for(j = 0; j < x; j++){
                printf("%d ", M2[i][j]);
            }
            printf("\n");
        }
        printf("M3 : \n");
        for(i = 0; i < x; i++){
            for(j = 0; j < x; j++){
                printf("%d ", M3[i][j]);
            }
            printf("\n");
        }
        printf("M4 : \n");
        for(i = 0; i < x; i++){
            for(j = 0; j < x; j++){
                printf("%d ", M4[i][j]);
            }
            printf("\n");
        }
        printf("M5 : \n");
        for(i = 0; i < x; i++){
            for(j = 0; j < x; j++){
                printf("%d ", M5[i][j]);
            }
            printf("\n");
        }
        printf("M6 : \n");
        for(i = 0; i < x; i++){
            for(j = 0; j < x; j++){
                printf("%d ", M6[i][j]);
            }
            printf("\n");
        }
        printf("res : \n");
        for(i = 0; i < len; i++){
            for(j = 0; j < len; j++){
                printf("%d ", res[i][j]);
            }
            printf("\n");
        }
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
        strassen(matlen2, matriksA, matriksB, result);
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