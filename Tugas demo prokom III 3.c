#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

 int a, b, c, d, i, j;
 char m,n,o, t;
double one = 1.0;
double ten = 10.0;

char *DoubleToScientific(double d){
    char *s = malloc(11);
    snprintf(s, 11, "%1.3g", d);
    int phase = 0;
    int i, j, k, l, m, n, o;
    j = -1;
    k = -1;
    l = 10;
    o = -1;
    for (i = 0; i < 11; i++){
        if (s[i] == '.')
            o = i;
        if (s[i] == 'e'){
            j = i;
            s[i] = '\0';
            for (m = i+2; m < 11; m++){
                if (k < 0){
                    if (s[m] != '0')
                        k = m;
                }else{
                    if (s[m] == '\0'){
                        l = m;
                        break;
                    }
                }
            }
            break;
        }
        if (s[i] == '\0')
            break;
    }
    if (j > -1){
        for (i = k; i < l; i++){
            s[j+4+i-k] = s[i];
        }
        s[j] = '*';
        s[j+1] = '1';
        s[j+2] = '0';
        s[j+3] = '^';
        s[j+4+l-k] = '\0';
    }else if (o < 0 && (d > 9.99999999 || modf(d, &one) != 0.0)){
        double q = d;
        int p = 0;
        while (q > 9){
            q = q / 10.0;
            p++;
        }
        snprintf(s, 5, "%3g", q);
        if (p > 0){
            int r = -1;

            for (i = 0; i < 11; i++){
                if (s[i] == '\0'){
                    r = i;
                    break;
                }
            }

            if (r > -1){
                s[r] = '*';
                s[r+1] = '1';
                s[r+2] = '0';
                s[r+3] = '^';
                r+=4;
                while (p/10 != 0){
                    s[r] = p/10 + '0';
                    p/=10;
                    r++;
                }
                s[r] = p + '0';
                s[r+1] = '\0';
            }
        }
    }

    return s;
}

void PrintError(char* err){
    while (kbhit())
        getchar();
    printf("\n%s\nTekan enter untuk melanjutkan ...", err);
    getchar();
    system("cls");
}

char *InsertCharToEndOfString(char** s, char c){
    int len = strlen(*s);
    *s = realloc(*s, len+2);
    (*s)[len] = c;
    (*s)[len+1] = '\0';
    return *s;
}

char *DeleteLastCharFromString(char** s){
    int len = strlen(*s);
    if (len == 0)
        return *s;
    *s = realloc(*s, len);
    (*s)[len-1] = '\0';
    return *s;
}

char c0 = '\0';
int x = 0;
int y = 0;

void SetSelection(int a, int b){
    switch(getch()){
        case 72:{
            //printf("pressed up arrow\n");
            if (y > 0)
                y--;
            break;
        }
        case 80:{
            //printf("pressed down arrow\n");
            if (y < a-1)
                y++;
            break;
        }
        case 75:{
            //printf("pressed left arrow\n");
            if (x > 0)
                x--;
            break;
        }
        case 77:{
            //printf("pressed right arrow\n");
            if (x < b - 1)
                x++;
            break;
        }
    }
}

void SetValue(char ****M){
    if (c0 == '1' || c0 == '2' || c0 == '3' || c0 == '4'
        || c0 == '5' || c0 == '6' || c0 == '7' || c0 == '8'
        || c0 == '9' || c0 == '0')
        InsertCharToEndOfString(&(*M)[y][x], c0);
    else if (c0 == '.'){
        int h, len;
        char *s = (*M)[y][x];
        len = strlen(s);
        for (h = 0; h < len; h++){
            if (s[h] == '.')
                return;
        }
        InsertCharToEndOfString(&(*M)[y][x], c0);
    }
    else if (c0 == 8)
        DeleteLastCharFromString(&(*M)[y][x]);
}

void GetEquation(){
    while(1){
        system("cls");
        printf("Masukkan ordo kedua matriks dan operatornya.\nOperator : +, -, *\nContoh : 2x3 * 3x2 untuk perkalian matriks ordo 2x3 dan 3x2.\nInput : ");
        if (scanf(" %d %c %d %c %d %c %d%c", &a, &m, &b, &o, &c, &n, &d, &t) == 8
                && a > 0 && b > 0 && c > 0 && d > 0 && (m == 'x' || m == 'X')
                && (n == 'x' || n == 'X') && t == '\n'){
            if (o == '+' || o == '-'){
                if (a == c && b == d)
                    break;
                else{
                    PrintError("Untuk penjumlahan dan pengurangan, ordo kedua matriks harus sama");
                }
            }else if (o=='*'){
                if (b == c)
                    break;
                else{
                    PrintError("Untuk perkalian, jumlah kolom matriks pertama harus sama dengan jumlah baris matriks kedua");
                }
            }else{
                PrintError("Invalid operator");
            }
        }else{
            PrintError("Invalid input");
        }
    }
}

void FillMatrix(char**** M, int a, int b, char* s){
    while(1){
        system("cls");
        printf("Isi matriks %s\n\n", s);

        int h = b * 11;

    printf("/");
            for (j = 0; j < h; j++){
                printf(" ");
            }
            printf("\\\n");


        for (i = 0; i < a; i++){
            printf("|");
            for (j = 0; j < b; j++){
                if (i == y && j == x){
                    printf(" (%s[%d][%d]) ", s, i, j);
                }else{
                    printf("  %s[%d][%d]  ", s, i, j);
                }
            }
            if (i != a - 1){
            printf("|\n|");
            for (j = 0; j < b; j++){
                printf("           ");
            }
            }
            printf("|\n");
        }


    printf("\\");
            for (j = 0; j < h; j++){
                printf(" ");
            }
            printf("/\n");

        printf("\n\n%s[%d][%d] = %s", s, y, x, (*M)[y][x]);
        c0 = getch();
        if (c0 == 224 || c0 == -32) {
            SetSelection(a, b);
        }else if (c0 == 13){
            int g = 0, h = 0;
            int i1, j1;
            for (i = 0; i < a; i++){
                for (j = 0; j < b; j++){
                    char *s1 = (*M)[i][j];
                    int len = strlen(s1);
                    if (len == 0){
                        i1=i;
                        j1=j;
                        h = 1;
                        break;
                    }
                    if (len == 1 && s1[0] == '.'){
                        i1=i;
                        j1=j;
                        h = 1;
                        break;
                    }
                }
                if (h == 1){
                    g = 1;
                    break;
                }
            }
            if (g == 0){
                x = 0;
                y = 0;
                break;
            }
            printf("\nMasih ada elemen matriks yang kosong : %s[%d][%d]", s, i1, j1);
            PrintError("");
        }else{
            SetValue(M);
        }
    }
}

void PrintMatrix(double ***M, int a, int b){
    char *MC[a][b];
    int lens[b];
    int maxLen = 0;

    for (i = 0; i < a; i++){
        for (j = 0; j < b; j++){
            MC[i][j] = DoubleToScientific((*M)[i][j]);
            int len = strlen(MC[i][j]);
            maxLen = len > maxLen ? len : maxLen;
            if (i == 0)
                lens[j] = len;
            else{
                lens[j] = len > lens[j] ? len : lens[j];
            }
        }
    }
    printf("\n/");
            for (j = 0; j < b; j++){
                int k;
                for (k = maxLen; k > 0; k--){
                    printf(" ");
                }
                printf("  ");
            }
            printf("\\\n");


    for (i = 0; i < a; i++){
        printf("|");
        for (j = 0; j < b; j++){
            int len = strlen(MC[i][j]);
            printf(" %s ", MC[i][j]);
            int k;
            for (k = maxLen - len; k > 0; k--){
                printf(" ");
            }
        }
        if (i != a - 1){
            printf("|\n|");
            for (j = 0; j < b; j++){
                int k;
                for (k = maxLen; k > 0; k--){
                    printf(" ");
                }
                printf("  ");
            }
        }
        //printf("  ");
        printf("|\n");
    }


            printf("\\");
            for (j = 0; j < b; j++){
                int k;
                for (k = maxLen; k > 0; k--){
                    printf(" ");
                }
                printf("  ");
            }
            printf("/");
}

int ConfirmMatrix(double ***M, int a, int b, char* s){
    int choice = 0;
    while(1){
        system("cls");
        printf("Matriks %s ordo %dx%d\n", s, a, b);
        PrintMatrix(M, a, b);
        printf("\nApa ini sudah benar?\n");
        if (choice == 0)
            printf("(Tidak)  Ya ");
        else
            printf(" Tidak  (Ya)");
        int c0 = getch();
        if (c0 == 13)
            return choice;
        else if (c0 == 224 || c0 == -32){
            c0 = getch();
            if (choice == 0 && c0 == 77)
                choice = 1;
            else if (choice == 1 && c0 == 75)
                choice = 0;
        }
    }
}

int main(){
    while(1){
    GetEquation();
    char ***M1C, ***M2C;
    M1C = malloc(a*4);
    M2C = malloc(c*4);
    for (i = 0; i < a; i++){
        M1C[i] = malloc(b*4);
        for (j = 0; j < b; j++){
            char *s = malloc(1);
            s[0] = '\0';
            M1C[i][j] = s;
        }
    }
    for (i = 0; i < c; i++){
        M2C[i] = malloc(d*4);
        for (j = 0; j < d; j++){
            char *s = malloc(1);
            s[0] = '\0';
            M2C[i][j] = s;
        }
    }
    //printf("");
    double **M1, **M2;
    M1 = malloc(a*4);
    for (i = 0; i < a; i++){
        M1[i] = malloc(b * 8);
    }
    M2 = malloc(c*4);
    for (i = 0; i < c; i++){
        M2[i] = malloc(d*8);
    }
    int confirm = 0;
    while(!confirm){
        FillMatrix(&M1C, a, b, "A");
        for (i = 0; i < a; i++){
            for (j = 0; j< b; j++){
                M1[i][j] = strtod(M1C[i][j], (char**) NULL);
            }
        }
        confirm = ConfirmMatrix(&M1, a, b, "A");

    }
    confirm = 0;
    while(!confirm){
        FillMatrix(&M2C, c, d, "B");
        for (i = 0; i < c; i++){
            for (j = 0; j< d; j++){
                M2[i][j] = strtod(M2C[i][j], (char**) NULL);
            }
        }
        confirm = ConfirmMatrix(&M2, c, d, "B");
    }

    double **M3;
    int m, n;
    switch(o){
        case '+':{
            M3 = malloc(a*4);
            m = a;
            n = b;
            for (i = 0; i < a; i++){
                M3[i] = malloc(b*8);
                for (j = 0; j < b; j++){
                    M3[i][j] = M1[i][j] + M2[i][j];
                }
            }
            break;
        }
        case '-':{
            M3 = malloc(a*4);
            m = a;
            n = b;
            for (i = 0; i < a; i++){
                M3[i] = malloc(b*8);
                for (j = 0; j < b; j++){
                    M3[i][j] = M1[i][j] - M2[i][j];
                }
            }
            break;
        }
        case '*':{
            M3 = malloc(a*4);
            m = a;
            n = d;
            for (i = 0; i < a; i++){
                M3[i] = malloc(d*8);
                for (j = 0; j < d; j++){
                    M3[i][j] = 0;
                    int k;
                    for (k = 0; k < b; k++){
                        M3[i][j] += M1[i][k] * M2[k][j];
                    }
                }
            }
            break;
        }
    }
    system("cls");
    printf("Hasil : Matrix %dx%d\n", a, b);
    PrintMatrix(&M3, m, n);

    for(i = 0; i < a; i++){
        for (j = 0; j < b; j++){
            free(M1C[i][j]);
        }
        free(M1C[i]);
        free(M1[i]);
    }
    free(M1C);
    free(M1);

    for(i = 0; i < c; i++){
        for (j = 0; j < d; j++){
            free(M2C[i][j]);
        }
        free(M2C[i]);
        free(M2[i]);
    }
    free(M2C);
    free(M2);

    for (i = 0; i < m; i++){
        free(M3[i]);
    }
    free(M3);
    while (kbhit())
        getchar();
    printf("\nTekan enter untuk melanjutkan ...");
    getchar();
    }
    return 0;
}
