#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// find the recursive formula for catalan number
unsigned long catalan(int n) {
    unsigned long res = 1;
    for (int i = 0; i < n; ++i) {
        res = res * 2 * (2 * i + 1) / (i + 2);
    }
    return res;
}


void backtrack(char** result, int* returnSize, int n, int open, int close, char* text, int textLen){

    if(open == n && close == n){
        text[textLen] = '\0';
        result[*returnSize] = strdup(text);
        (*returnSize)++;
        return;
    }

    if(open < n){
        text[textLen] = '(';
        backtrack(result, returnSize, n, open + 1, close, text, textLen + 1);
    }   

    if(close < open){
        text[textLen] = ')';
        backtrack(result, returnSize, n, open, close + 1, text, textLen + 1);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    //maxSize is catalen number
    int maxSize = catalan(n);// safe upper bound
    char** result = malloc(sizeof(char*) * maxSize);
    char* text = malloc(sizeof(char) * (2 * n + 1)); // +1 for null terminator
    *returnSize = 0;

    backtrack(result, returnSize, n, 0, 0, text, 0);
    free(text);
    return result;
}


int main(void){
    int returnSize;
    char** result = generateParenthesis(3, &returnSize);
    for(int i = 0; i < returnSize; i++){
        printf("%s\n", result[i]);
    }

    for(int i = 0; i < 9; i++){
        printf("%d\n", catalan(i));
    }
    return 0;
}