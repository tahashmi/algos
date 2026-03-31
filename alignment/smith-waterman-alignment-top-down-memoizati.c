#include <stdio.h>
#include <string.h>

int memo[20][20];

int top_down_sw(char* s1, char* s2, int i, int j) {
    if (i == 0 || j == 0) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    int sc = (s1[i-1] == s2[j-1]) ? 1 : -1;
    int d = top_down_sw(s1, s2, i-1, j-1) + sc;
    int u = top_down_sw(s1, s2, i-1, j) - 2;
    int l = top_down_sw(s1, s2, i, j-1) - 2;
    
    int res = 0;
    if (d > res) res = d;
    if (u > res) res = u;
    if (l > res) res = l;
    return memo[i][j] = res;
}

int main() {
    char *s1 = "GATCGGGAC", *s2 = "CGTACACACTAG";
    memset(memo, -1, sizeof(memo));
    
    int max_s = 0, mi = 0, mj = 0;
    for(int i=1; i<=9; i++) {
        for(int j=1; j<=12; j++) {
            int s = top_down_sw(s1, s2, i, j);
            if(s > max_s) { max_s = s; mi = i; mj = j; }
        }
    }

    char a1[50], a2[50], mid[50];
    int i = mi, j = mj, idx = 0;
    while (i > 0 && j > 0 && memo[i][j] > 0) {
        int sc = (s1[i-1] == s2[j-1]) ? 1 : -1;
        if (memo[i][j] == memo[i-1][j-1] + sc) {
            mid[idx] = (s1[i-1] == s2[j-1]) ? '|' : ' ';
            a1[idx] = s1[--i]; a2[idx] = s2[--j];
        } else if (memo[i][j] == memo[i-1][j] - 2) {
            a1[idx] = s1[--i]; a2[idx] = '-'; mid[idx] = ' ';
        } else {
            a1[idx] = '-'; a2[idx] = s2[--j]; mid[idx] = ' ';
        }
        idx++;
    }

    printf("--- TOP-DOWN MEMOIZATION (LOCAL) ---\nMax Score: %d\nSeq A: ", max_s);
    for(int k=idx-1; k>=0; k--) printf("%c", a1[k]);
    printf("\nMatch: "); for(int k=idx-1; k>=0; k--) printf("%c", mid[k]);
    printf("\nSeq B: "); for(int k=idx-1; k>=0; k--) printf("%c", a2[k]);
    printf("\n");
    return 0;
}
