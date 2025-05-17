#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * 1. use enumerate and compare all subsequence
 * 2. dp with full 2D array
 * 3. dp with 2 1D arrays
 * 4. dp with full 2D array that can rebuild the original sequence
 */
char** get_all_substrings(const char *str, int *count);
char** get_all_subsequences(const char* str, int* count);
char** LCS_brute_force(char* str1, char* str2, int* match_count, char** lcs);

int lcs(char* text1, char* text2);

int lcs_1(char* text1, char* text2);

void lcs_length(char* text1, char* text2, int len1, int len2, int*** dp, int*** trackers);
void print_lcs_helper(int** tracker, char* text1, int i, int j);
void print_lcs(char* text1, char* text2);
int max(int a, int b);

//use full 2D array
int lcs(char* text1, char* text2) {
    int len1 = strlen(text1);
    int len2 = strlen(text2);

    int** dp = (int**) malloc(sizeof(int*) * (len1 + 1));
    for(int i = 0; i <= len1; i++){
        dp[i] = (int*) calloc(len2 + 1,sizeof(int));
    }

    for(int i = 1; i <= len1; i++){
        for(int j = 1; j <= len2; j++){
            if(text1[i - 1] == text2[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    int result = dp[len1][len2];
    for(int i = 0; i < len1; i++){
        free(dp[i]);
    }
    return result;
}

//lcs use 2 1D array
int lcs_1(char* text1, char* text2) {
    int len1 = strlen(text1);
    int len2 = strlen(text2);

    int* prev = (int*) calloc(len2 + 1, sizeof(int));
    int* curr = (int*) calloc(len2 + 1, sizeof(int));

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                curr[j] = prev[j - 1] + 1;
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        // Swap rows
        int* temp = prev;
        prev = curr;
        curr = temp;
    }

    int result = prev[len2];
    free(prev);
    free(curr);
    return result;
}

//with the ability to reconstruct the lcs
void lcs_length(char* text1, char* text2, int len1, int len2, int*** dp, int*** trackers){

    int** c = malloc(sizeof(int*) * (len1 + 1));
    int** b = malloc(sizeof(int*) * (len1 + 1));
    for(int i = 0; i <= len1; i++){
        c[i] = (int*)calloc(len2 + 1, sizeof(int));//dp
        b[i] = (int*)calloc(len2 + 1, sizeof(int));//trackers
    }

    for(int i = 1; i <= len1; i++){
        for(int j = 1; j <= len2; j ++){
            if(text1[i - 1] == text2[j - 1]){
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 0; // diagonal (↖)
            }
            else if(c[i - 1][j] > c[i][j - 1]){
                c[i][j] = c[i - 1][j];
                b[i][j] = 1; // up (↑)
            }
            else{
                c[i][j] = c[i][j - 1];
                b[i][j] = 2; // left (←)
            }
        }
    }

    *dp = c;
    *trackers = b;
}

void print_lcs_helper(int** tracker, char* text1, int i, int j){
    if(i == 0 || j == 0) return;

    if(tracker[i][j] == 0){
        print_lcs_helper(tracker, text1, i - 1, j - 1);
        printf("%c", text1[i - 1]);
    }
    else if(tracker[i][j] == 1){
        print_lcs_helper(tracker, text1, i - 1, j);
    }
    else{
        print_lcs_helper(tracker, text1, i, j - 1);
    }
}

void print_lcs(char* text1, char* text2){
    int len1 = strlen(text1);
    int len2 = strlen(text2);

    if(!(len1 && len2)) {
        printf("Length of LCS is 0");
        return;
    }

    int** dp;
    int** trackers;
    lcs_length(text1, text2, len1, len2, &dp, &trackers);
    printf("Longest Common Subsequences: ");
    print_lcs_helper(trackers, text1, len1, len2);

    int result = dp[len1][len2];
    printf(", Length: %d\n", result);
    for(int i = 0; i < len1; i ++){
        free(dp[i]);
        free(trackers[i]);
    }
    free(dp);
    free(trackers);
}

//substring of abcd = {a,ab,abc,abcd,b,bc,bcd,c,cd,d} != subsequece
char** get_all_substrings(const char *str, int *count) {
    int len = strlen(str);
    int total = len * (len + 1) / 2; // Total substrings
    char **result = (char **)malloc(sizeof(char *) * total);
    
    int index = 0;
    for (int start = 0; start < len; start++) {
        for (int end = start; end < len; end++) {
            int substr_len = end - start + 1;
            result[index] = (char *)malloc(substr_len + 1);
            strncpy(result[index], str + start, substr_len);
            result[index][substr_len] = '\0';
            index++;
        }
    }

    *count = total; // set the output parameter
    return result;
}

// subsequece of abcd = {a,b,c,d,ab,ac,ad,bc,bd,cd,abc,abd,acd,bcd,abcd}
char** get_all_subsequences(const char* str, int* count) {
    int len = strlen(str);
    int total = (1 << len) - 1;  // 2^len - 1 non-empty subsequences
    char** result = (char**)malloc(sizeof(char*) * total);

    int index = 0;
    // len of abcd = 4 -> have 2^4 -1 = 15 -> 1111, 4 bits
    // each bits represent the occurence 
    // checks if the i-th bit of mask is set to 1.
    for (int mask = 1; mask < (1 << len); mask++) {
        char* subseq = (char*)malloc(len + 1);
        int pos = 0;

        for (int i = 0; i < len; i++) {
            // if that bit = 1, it shows up and be included
            if (mask & (1 << i)) {
                subseq[pos++] = str[i];
            }
        }

        subseq[pos] = '\0';
        result[index++] = subseq;
    }

    *count = total;
    return result;
}


char** LCS_brute_force(char* str1, char* str2, int* match_count, char** lcs){
    int len1 = 0, len2 = 0;
    char** substrings1 = get_all_subsequences(str1, &len1);
    char** substrings2 = get_all_subsequences(str2, &len2);

    char** matches = (char**) malloc(sizeof(char*) * (len1 < len2 ? len1 : len2));
    *match_count = 0;
    int max_len = 0;
    *lcs = NULL;

    for(int i = 0; i < len1; i++){
        for(int j = 0; j < len2; j++){
            if(strcmp(substrings1[i], substrings2[j]) == 0){
                int cur_len = strlen(substrings1[i]);

                //save match
                matches[*match_count] = (char*) malloc(sizeof(char) * (cur_len + 1 ));
                strncpy(matches[*match_count], substrings1[i], cur_len);
                matches[*match_count][cur_len] = '\0';
                (*match_count)++;

                if(cur_len > max_len){
                    if(*lcs) free(*lcs);
                    *lcs = (char*)malloc(sizeof(char) * (cur_len + 1));
                    strncpy(*lcs, substrings1[i], cur_len);
                    (*lcs)[cur_len] = '\0';
                    max_len = cur_len;
                }
            }
        }
    }

    // Free allocated memory for all substrings
    for (int i = 0; i < len1; i++) free(substrings1[i]);
    for (int i = 0; i < len2; i++) free(substrings2[i]);
    free(substrings1);
    free(substrings2);

    return matches; // Caller must free each string + array
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    // const char *s = "abc";
    // int substring_count = 0;
    // char **substrings = get_all_substrings(s, &substring_count);
    // for (int i = 0; i < substring_count; i++) {
    //     printf("%s\n", substrings[i]);
    //     free(substrings[i]);
    // }
    // free(substrings); 


    //text1 = "abcde", text2 = "ace" 
    char* lcs = NULL;
    int match_count = 0;
    char** matches = LCS_brute_force("abcde", "ace", &match_count, &lcs);
    printf("Longest Common Subsequences: %s, Length: %zu\n", lcs, strlen(lcs));
    printf("Matches count: %d\n", match_count);
    for(int i=0; i<match_count; i++){
        printf("%s\n", matches[i]);
    }

    for (int i = 0; i < match_count; i++) free(matches[i]);
    free(matches);
    free(lcs);

    //USE dp
    print_lcs("abcde", "ace");
    return 0;
}