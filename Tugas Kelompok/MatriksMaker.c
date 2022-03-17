#include <stdio.h>
#include <stdlib.h>
#define max 255
int main(){ 
    printf("Program untuk membuat 2 matriks random dengan ukuran N x N dengan isi file berupa baris pertama panjang matriks, dan selanjutnya 2 matriks ukuran N x N .\nMatriks yang dihasilkan hanya akan berisi bilangan antara 0-9.\n");
    printf("Note : Matriks ukuran 10k x 10k akan menghasilkan file dengan ukuran sampai 500mb, jadi tolong berhati hati dalam menggunakan program!\n");
    printf("Masukkan ukuran matriks (N) : ");
    int n;
    scanf("%d", &n);
    printf("Masukkan nama file output : ");
    char namafile[max];
    scanf(" %s", &namafile);
    FILE* fileoutput = fopen(namafile, "w");
    fprintf(fileoutput, "%d\n", n);
    int i, j;
    for(i = 0; i < 2*n; i++){
        for(j = 0; j < n; j++){
            fprintf(fileoutput, "%d ", rand()%10);
        }
        fprintf(fileoutput, "\n");
    }
    fclose(fileoutput);
}