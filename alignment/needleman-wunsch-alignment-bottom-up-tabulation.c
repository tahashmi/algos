#include <stdio.h>
#include <string.h>

void bottom_up(char* s1, char* s2) {
    int n = strlen(s1), m = strlen(s2), dp[20][20];
    for (int i = 0; i <= n; i++) dp[i][0] = i * -2;
    for (int j = 0; j <= m; j++) dp[0][j] = j * -2;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int match = dp[i-1][j-1] + (s1[i-1] == s2[j-1] ? 1 : -1);
            int del = dp[i-1][j] - 2;
            int ins = dp[i][j-1] - 2;
            dp[i][j] = (match >= del && match >= ins) ? match : (del >= ins ? del : ins);
        }
    }

    char a1[50], a2[50], mid[50];
    int i = n, j = m, idx = 0;
    while (i > 0 || j > 0) {
        int sc = (i > 0 && j > 0) ? (s1[i-1] == s2[j-1] ? 1 : -1) : -999;
        if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + sc) {
            mid[idx] = (s1[i-1] == s2[j-1]) ? '|' : ' ';
            a1[idx] = s1[--i]; a2[idx] = s2[--j];
        } else if (i > 0 && dp[i][j] == dp[i-1][j] - 2) {
            a1[idx] = s1[--i]; a2[idx] = '-'; mid[idx] = ' ';
        } else {
            a1[idx] = '-'; a2[idx] = s2[--j]; mid[idx] = ' ';
        }
        idx++;
    }

    printf("--- METHOD 3: BOTTOM-UP (TABULATION) ---\nScore: %d\nSeq A: ", dp[n][m]);
    for(int k=idx-1; k>=0; k--) printf("%c", a1[k]);
    printf("\nMatch: "); for(int k=idx-1; k>=0; k--) printf("%c", mid[k]);
    printf("\nSeq B: "); for(int k=idx-1; k>=0; k--) printf("%c", a2[k]);
    printf("\n");
}

int main() {
    bottom_up("GATCGGGAC", "CGTACACACTAG");
    return 0;
}
