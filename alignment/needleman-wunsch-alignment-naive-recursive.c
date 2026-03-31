#include <stdio.h>
#include <string.h>

#define MATCH 1
#define MISMATCH -1
#define GAP -2

int rec_score(char* s1, char* s2, int i, int j) {
    if (i == 0) return j * GAP;
    if (j == 0) return i * GAP;
    int m = rec_score(s1, s2, i - 1, j - 1) + (s1[i - 1] == s2[j - 1] ? MATCH : MISMATCH);
    int d = rec_score(s1, s2, i - 1, j) + GAP;
    int r = rec_score(s1, s2, i, j - 1) + GAP;
    return (m >= d && m >= r) ? m : (d >= r ? d : r);
}

void print_rec(char* s1, char* s2, int i, int j, char* a, char* m, char* b, int* p) {
    if (i == 0 && j == 0) return;
    int cur = rec_score(s1, s2, i, j);
    if (i > 0 && j > 0 && cur == rec_score(s1, s2, i-1, j-1) + (s1[i-1] == s2[j-1] ? MATCH : MISMATCH)) {
        print_rec(s1, s2, i-1, j-1, a, m, b, p);
        a[*p] = s1[i-1]; b[*p] = s2[j-1]; m[*p] = (s1[i-1] == s2[j-1]) ? '|' : ' ';
    } else if (i > 0 && cur == rec_score(s1, s2, i-1, j) + GAP) {
        print_rec(s1, s2, i-1, j, a, m, b, p);
        a[*p] = s1[i-1]; b[*p] = '-'; m[*p] = ' ';
    } else {
        print_rec(s1, s2, i, j-1, a, m, b, p);
        a[*p] = '-'; b[*p] = s2[j-1]; m[*p] = ' ';
    }
    (*p)++;
}

int main() {
    char *s1 = "GATCGGGAC", *s2 = "CGTACACACTAG";
    char a[50] = {0}, m[50] = {0}, b[50] = {0};
    int pos = 0;
    printf("--- METHOD 1: NAIVE RECURSIVE ---\n");
    printf("Score: %d\n", rec_score(s1, s2, 9, 12));
    print_rec(s1, s2, 9, 12, a, m, b, &pos);
    printf("Seq A: %s\nMatch: %s\nSeq B: %s\n", a, m, b);
    return 0;
}
