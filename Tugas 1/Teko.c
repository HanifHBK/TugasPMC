/*
Nama    : Muhammad Hanif Hibatullah
NIM     : 13220051
Kelas   : 01
*/

#include <stdio.h>

int main(){
    int a, b;
    a = 0;
    b = 0;
    int x = 0;
    while(b!= 4){
        printf("------------------------------------------------\n");
        printf("Ember A (3 Liter) : %d\n", a);
        printf("Ember B (5 Liter) : %d\n", b);
        printf("------------------------------------------------\n");
        printf("List perintah yang dapat dilakukan : \n");
        printf("1. Isi penuh ember A\n");
        printf("2. Isi penuh ember B\n");
        printf("3. Tuang isi ember A ke ember B\n");
        printf("4. Tuang isi ember B ke ember A\n");
        printf("5. Kosongkan ember A\n");
        printf("6. Kosongkan ember B\n");
        printf("Masukkan perintah yang diinginkan : ");
        scanf("%d", &x);
        while (x > 6 || x < 1){
            fflush(stdin);
            printf("Masukan harus integer di antara 1-6, mohon ulangi masukan!\n");
            printf("Masukkan perintah yang diinginkan : ");
            scanf("%d", &x);
        }
        if(x == 1){
            a = 3;
        } else if(x == 2){
            b = 5;
        } else if(x == 3){
            if (a+b > 5){
                a = a+b-5;
                b = 5;
            } else {
                b = a + b;
                a = 0;
            }
        } else if(x == 4){
            if (a + b > 3){
                b = a + b - 3;
                a = 3;
            } else {
                a = a + b;
                b = 0;
            }
        } else if(x == 5){
            a = 0;
        } else if(x == 6){
            b = 0;
        }
        fflush(stdin);
    }
    printf("------------------------------------------------\n");
    printf("Ember A (3 Liter) : %d\n", a);
    printf("Ember B (5 Liter) : %d\n", b);
    printf("------------------------------------------------\n");
    printf("Ember B sudah terisi sampai 4 Liter, permainan selesai!");
}
