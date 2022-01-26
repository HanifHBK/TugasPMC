/*
Nama    : Muhammad Hanif Hibatullah
NIM     : 13220051
Kelas   : 01
*/

#include <stdio.h>

int main(){
    printf("Round Robin Scheduling\n");
    int kuantum;
    int n;
    printf("Masukkan waktu kuantum (ms) : ");
    scanf("%d", &kuantum);
    printf("Berapa proses yang dilakukan : ");
    scanf("%d", &n);
    int time[n],arr[n];
    int b[n],c[n],i, sum; // b[n] waktu datang, c[n] lama proses, i iterator
    // diasumsikan input waktu kedatangan proses terurut (proses 1 lebih dulu dari proses 2 dan seterusnya) dan berbeda nilainya
    for(i = 0; i < n; i++){
        printf("Waktu kedatangan proses ke-%d : ", i+1);
        scanf("%d", &b[i]);
        printf("Waktu eksekusi proses ke-%d : ", i+1);
        scanf("%d", &c[i]);
        sum += c[i];
        time[i] = 0;
        arr[i] = -1;
    }
    int k = 0;
    int x = 0;
    int selesai = 0;
    int count = 0;
    while(selesai != n){
        if(arr[0] != -1){
            if(time[arr[0]] == c[arr[0]]){
                printf("-------------------------\n");
                printf("Waktu : %d ms\n", x);
                int j;
                for(j = 0; j < n; j++){
                    printf("Time Proses ke-%d : %d\n", j+1, time[j]);
                }
                printf("Proses ke-%d selesai\n", arr[0]+1);
                int m;
                int temp;
                temp = arr[0];
                for(m = 1; m < (k-selesai); m++){
                    arr[m-1] = arr[m];
                }
                arr[k-selesai-1] = temp;
                selesai += 1;
                count = 0;
            }
        }
        if(count == kuantum){
            printf("-------------------------\n");
            count = 0;
            printf("Waktu : %d ms\n", x);
            int j;
            for(j = 0; j < n; j++){
                printf("Time Proses ke-%d : %d\n", j+1, time[j]);
            }
            printf("Proses ke-%d diantrikan kembali\n", arr[0]+1);
            int m;
            int temp;
            temp = arr[0];
            for(m = 1; m < (k-selesai); m++){
                arr[m-1] = arr[m];
            }
            arr[k-selesai-1] = temp;
        }
        if(x == b[k]){
            printf("-------------------------\n");
            printf("Waktu : %d ms\n", x);
            arr[k-selesai] = k;
            int j;
            for(j = 0; j < n; j++){
                printf("Time Proses ke-%d : %d\n", j+1, time[j]);
            }
            printf("Proses ke-%d masuk ke antrian\n", k+1);
            k+=1;
        }
        x += 1;
        count += 1;
        if(arr[0] != -1){
            time[arr[0]] += 1;
        }
    }
    printf("-------------------------\n");
    printf("Algoritma selesai, total waktu proses : %d ms", x-1);
}