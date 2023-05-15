int a[25][25];
int b[25][25];
int c[25][25];
int getDigitNum(int n) {
    int num = 0;
    if(n == 0) {
        return 1;
    }
    if(n < 0) {
        num = 1;
    }
    while (n != 0) {
        n = n / 10;
        num = num + 1;
    }
    return num;
}
int printString(string a){
    int i = 0;
    while(a[i] != 0) {
        putch(a[i]);
        i = i + 1;
    }
    return 0;
}

int main(){
    int ma, na, mb, nb, i, j, k;
    int spaceNum;
    string space = " ";
    string line = "\n";
    string prompt = "Incompatible Dimensions\n";
    ma = getint();
    na = getint();
    i = 0;
    j = 0;
    while(i < ma) {
        j = 0;
        while(j < na) {
            a[i][j] = getint();
            j = j + 1;
        }
        i = i + 1;
    }
    mb = getint();
    nb = getint();
    i = 0;
    j = 0;
    while(i < mb) {
        j = 0;
        while(j < nb) {
            b[i][j] = getint();
            j = j + 1;
        }
        i = i + 1;
    }
    if (na != mb) {
        printString(prompt);
        return 0;
    }
    i = 0;
    j = 0;
    while(i < ma){
        j = 0;
        while(j < nb){
            k = 0;
            c[i][j] = 0;
            while(k < na){
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
                k = k + 1;
            }
            j = j + 1;
        }
        i = i + 1;
    }
    i = 0;
    j = 0;
    while(i < ma){
        j = 0;
        while(j < nb){
            k = 0;
            spaceNum = getDigitNum(c[i][j]);
            spaceNum = 10 - spaceNum;
            while(k < spaceNum) {
                printString(space);
                k = k + 1;
            }
            putint(c[i][j]);
            j = j + 1;
        }
        printString(line);
        i = i + 1;
    }
    return 0;
}
