#include <stdio.h>
#include <string.h>

#define MATCH 1
#define MISMATCH -1
#define GAP -2

int rec_sw(char* s1, char* s2, int i, int j) {
    if (i == 0 || j == 0) return 0;
    int diag = rec_sw(s1, s2, i - 1, j - 1) + (s1[i - 1] == s2[j - 1] ? MATCH : MISMATCH);
    int up = rec_sw(s1, s2, i - 1, j) + GAP;
    int left = rec_sw(s1, s2, i, j - 1) + GAP;
    int res = 0;
    if (diag > res) res = diag;
    if (up > res) res = up;
    if (left > res) res = left;
    return res;
}

void print_rec_sw(char* s1, char* s2, int i, int j, char* a, char* m, char* b, int* p) {
    if (i == 0 || j == 0 || rec_sw(s1, s2, i, j) == 0) return;

    int cur = rec_sw(s1, s2, i, j);
    if (cur == rec_sw(s1, s2, i - 1, j - 1) + (s1[i - 1] == s2[j - 1] ? MATCH : MISMATCH)) {
        print_rec_sw(s1, s2, i - 1, j - 1, a, m, b, p);
        a[*p] = s1[i - 1]; b[*p] = s2[j - 1]; m[*p] = (s1[i - 1] == s2[j - 1]) ? '|' : ' ';
    } else if (cur == rec_sw(s1, s2, i - 1, j) + GAP) {
        print_rec_sw(s1, s2, i - 1, j, a, m, b, p);
        a[*p] = s1[i - 1]; b[*p] = '-'; m[*p] = ' ';
    } else {
        print_rec_sw(s1, s2, i, j - 1, a, m, b, p);
        a[*p] = '-'; b[*p] = s2[j - 1]; m[*p] = ' ';
    }
    (*p)++;
}

int main() {
    char *s1 = "GATCGGGAC", *s2 = "CGTACACACTAG";
    int max_s = 0, mi = 0, mj = 0;
    for(int i=1; i<=9; i++) {
        for(int j=1; j<=12; j++) {
            int s = rec_sw(s1, s2, i, j);
            if(s > max_s) { max_s = s; mi = i; mj = j; }
        }
    }
    char a[50]={0}, m[50]={0}, b[50]={0}; int p = 0;
    printf("--- NAIVE RECURSIVE (LOCAL) ---\nMax Score: %d\n", max_s);
    print_rec_sw(s1, s2, mi, mj, a, m, b, &p);
    printf("Seq A: %s\nMatch: %s\nSeq B: %s\n", a, m, b);
    return 0;
}
