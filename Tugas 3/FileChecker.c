#include <stdio.h>
#include <string.h>

// fungsi didapatkan dari website : https://www.includehelp.com/c/convert-ascii-string-to-hexadecimal-string-in-c.aspx
void string2hexString(char* input, char* output)
{
    int loop;
    int i; 
    
    i=0;
    loop=0;
    
    while(input[loop] != '\0')
    {
        sprintf((char*)(output+i),"%02X", input[loop]);
        loop+=1;
        i+=2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
}

int main(){
    FILE *testfile;
    char input[100];
    char info[6];
    printf("Program untuk mengecek format sebuah file, pastikan file berada di directory yang sama dengan program!\n");
    printf("Masukkan nama file yang ingin dicek formatnya (sertakan formatnya juga): ");
    scanf("%[^\n]s", input);
    testfile = fopen(input, "r+");
    if(testfile == NULL){
        printf("File tidak ada di folder!\n");
    } else {
        fgets(info, 6, testfile);
        int len = strlen(info);
        char hex_str[(len*2)+1];
        string2hexString(info, hex_str);
        char *pdf, *jpg;
        pdf = strstr(hex_str, "255044462D"); // file signature sudah sesuai pada program HxD
        jpg = strstr(hex_str, "FFFFFFFF"); 
        /* File signature jpg berbeda (?) dengan program HxD
        Kemungkinan penyebab perbedaan karena karakternya dibaca dengan null, detailnya terdapat pada gambar error.png di folder yang sama 
        Untuk solusinya sendiri masih dipikirkan */
        if(pdf){
            printf("Format file berupa PDF.\n");
        } else if (jpg){
            printf("Format file berupa JPG.\n");
        } else {
            printf("Format file tidak terdefinisi (bukan PDF ataupun JPG).\n");
        }
    }
    fclose(testfile);
    system("pause");
}


