#include <stdio.h>

int main(){
    int n;
    char temp;
    printf("Jumlah mahasiswa dalam kelas : ");
    scanf("%d", &n);
    struct DataKelas{
        char Nama[80];
        int NIM;
        int Kehadiran;
    } Kelas[n];
    int i;
    for(i = 0; i < n; i++){
        printf("Nama Mahasiswa : ");
        scanf("%c", &temp);
        scanf("%[^\n]", Kelas[i].Nama);
        printf("NIM : ");
        scanf("%d",&Kelas[i].NIM);
        printf("Kehadiran (%%) : ");
        scanf("%d", &Kelas[i].Kehadiran);
    }
    printf("Mahasiswa yang tidak dapat mengikuti UAS (Kehadiran < 80 %%) : \n");
    for(i = 0; i < n; i++){
        if(Kelas[i].Kehadiran < 80){
            printf("Nama Mahasiswa : %s\n", Kelas[i].Nama);
            printf("NIM : %d\n", Kelas[i].NIM);
        }
    }
}