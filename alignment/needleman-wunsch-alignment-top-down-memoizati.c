#include <stdio.h>
#include <string.h>

int memo[20][20];

int top_down(char* s1, char* s2, int i, int j) {
    if (memo[i][j] != -999) return memo[i][j];
    if (i == 0) return memo[i][j] = j * -2;
    if (j == 0) return memo[i][j] = i * -2;
    int sc = (s1[i-1] == s2[j-1]) ? 1 : -1;
    int d = top_down(s1, s2, i-1, j-1) + sc;
    int u = top_down(s1, s2, i-1, j) - 2;
    int l = top_down(s1, s2, i, j-1) - 2;
    return memo[i][j] = (d >= u && d >= l) ? d : (u >= l ? u : l);
}

int main() {
    char *s1 = "GATCGGGAC", *s2 = "CGTACACACTAG";
    for(int i=0; i<20; i++) for(int j=0; j<20; j++) memo[i][j] = -999;
    
    int score = top_down(s1, s2, 9, 12);
    char a1[50], a2[50], mid[50];
    int i = 9, j = 12, idx = 0;

    while (i > 0 || j > 0) {
        int sc = (i > 0 && j > 0) ? (s1[i-1] == s2[j-1] ? 1 : -1) : -999;
        if (i > 0 && j > 0 && memo[i][j] == memo[i-1][j-1] + sc) {
            mid[idx] = (s1[i-1] == s2[j-1]) ? '|' : ' ';
            a1[idx] = s1[--i]; a2[idx] = s2[--j];
        } else if (i > 0 && memo[i][j] == memo[i-1][j] - 2) {
            a1[idx] = s1[--i]; a2[idx] = '-'; mid[idx] = ' ';
        } else {
            a1[idx] = '-'; a2[idx] = s2[--j]; mid[idx] = ' ';
        }
        idx++;
    }

    printf("--- METHOD 2: TOP-DOWN (MEMOIZATION) ---\nScore: %d\nSeq A: ", score);
    for(int k=idx-1; k>=0; k--) printf("%c", a1[k]);
    printf("\nMatch: "); for(int k=idx-1; k>=0; k--) printf("%c", mid[k]);
    printf("\nSeq B: "); for(int k=idx-1; k>=0; k--) printf("%c", a2[k]);
    printf("\n");
    return 0;
}
