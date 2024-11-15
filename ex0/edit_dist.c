#include <stdio.h>
#include <string.h>

#define MAX_WORD_LEN 100

int edit_dist(char word1[], char word2[]);

int main() {
	char word1[MAX_WORD_LEN], word2[MAX_WORD_LEN];
	
	fgets(word1, MAX_WORD_LEN, stdin);
	word1[strlen(word1) - 1] = '\0';
	fgets(word2, MAX_WORD_LEN, stdin);
	word2[strlen(word2) - 1] = '\0';

	printf("%d\n", edit_dist(word1, word2));

	return (0);
}

int edit_dist(char word1[], char word2[]) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);

    //set up a 2D array to store the edit distance
    int dp[len1 + 1][len2 + 1];

    //initialize the first row and column
    for (int i = 0; i <= len1; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= len2; j++) {
        dp[0][j] = j;
    }

    //filling the 2D array
    for(int i = 1; i<=len1; i++){
        for(int j = 1; j<=len2; j++){
            int cost = (word1[i-1] == word2[j-1]) ? 0 : 1; //if the characters are the same, cost is 0, otherwise 1
            //get the minimum of the three possible operations
            //insert - dp[i][j-1] + 1
            //delete - dp[i-1][j] + 1
            //replace - dp[i-1][j-1] + cost
            dp[i][j] = dp[i-1][j-1] + cost;
            if(dp[i][j] > dp[i][j-1] + 1){
                dp[i][j] = dp[i][j-1] + 1;
            }else if(dp[i][j] > dp[i-1][j] + 1){
                dp[i][j] = dp[i-1][j] + 1;
            }
        }
    }
    printf("%d\n", dp[len1][len2]);
}
