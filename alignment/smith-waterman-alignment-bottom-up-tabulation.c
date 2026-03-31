#include <stdio.h>
#include <string.h>

void smith_waterman(char* s1, char* s2) {
    int n = strlen(s1), m = strlen(s2), dp[20][20] = {0};
    int max_score = 0, max_i = 0, max_j = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int score = (s1[i-1] == s2[j-1]) ? 1 : -1;
            int diag = dp[i-1][j-1] + score;
            int up = dp[i-1][j] - 2;
            int left = dp[i][j-1] - 2;
            
            int res = 0;
            if (diag > res) res = diag;
            if (up > res) res = up;
            if (left > res) res = left;
            dp[i][j] = res;

            if (dp[i][j] > max_score) {
                max_score = dp[i][j];
                max_i = i; max_j = j;
            }
        }
    }

    // Backtracking
    char a1[40], a2[40], mid[40];
    int i = max_i, j = max_j, idx = 0;
    while (i > 0 && j > 0 && dp[i][j] > 0) {
        int sc = (s1[i-1] == s2[j-1]) ? 1 : -1;
        if (dp[i][j] == dp[i-1][j-1] + sc) {
            mid[idx] = (s1[i-1] == s2[j-1]) ? '|' : ' ';
            a1[idx] = s1[--i]; a2[idx] = s2[--j];
        } else if (dp[i][j] == dp[i-1][j] - 2) {
            a1[idx] = s1[--i]; a2[idx] = '-'; mid[idx] = ' ';
        } else {
            a1[idx] = '-'; a2[idx] = s2[--j]; mid[idx] = ' ';
        }
        idx++;
    }

    printf("--- Smith-Waterman Bottom-Up ---\nScore: %d\nLocal Alignment:\n", max_score);
    printf("Seq A: "); for(int k=idx-1; k>=0; k--) printf("%c", a1[k]);
    printf("\nMatch: "); for(int k=idx-1; k>=0; k--) printf("%c", mid[k]);
    printf("\nSeq B: "); for(int k=idx-1; k>=0; k--) printf("%c", a2[k]);
    printf("\n");
}

int main() {
    smith_waterman("GATCGGGAC", "CGTACACACTAG");
    return 0;
}
