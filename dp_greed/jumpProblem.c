#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//O(n)
//shift the goal to the end; another is shift the goal to the start
bool canJump_greedy(int* nums, int numsSize){
    int maxReach = 0;
    for(int i = 0; i < numsSize; i++){
        if(i > maxReach) return false;
        maxReach = (i + nums[i] > maxReach) ? i + nums[i] : maxReach;
    }
    return true;
}


//O(n^2)
bool canJump_1Ddp(int* nums, int numsSize){
    bool* dp = (bool*) calloc(numsSize, sizeof(bool));
    //base case
    dp[0] = true;

    for(int i = 0; i < numsSize; i++){
        if(!dp[i]) continue;
        for(int j = i + 1; (j <= i + nums[i]) && (j < numsSize); j++){
            dp[j] = true;
        }
    }
    bool result = dp[numsSize - 1];
    free(dp);
    return result;
}


//O(n^3)
/**
 * divide
 */
bool canJump_2Ddp(int* nums, int numsSize) {
    bool** dp = (bool**) malloc(sizeof(bool*) * numsSize);
    for(int i = 0; i < numsSize; i++){
        dp[i] = (bool*) calloc(numsSize ,sizeof(bool));
    }

    //base case
    for(int i = 0; i < numsSize; i++){
        int farthest_loc = i + nums[i];
        for(int j = i; j <= farthest_loc && j < numsSize; j++){
            dp[i][j] = true;
        }
    }

    //problem len, start idx end idx, find i->k k->j
    for (int len = 2; len <= numsSize; len++) {
        for (int i = 0; i <= numsSize - len; ++i) {
            int j = i + len - 1;
            for (int k = i + 1; k < j; ++k) {
                if (dp[i][k] && dp[k][j]) {
                    dp[i][j] = true;
                    break;
                }
            }
        }
    }

    bool result = dp[0][numsSize-1];
    for(int i = 0; i < numsSize; i++){
        free(dp[i]);
    }
    free(dp);
    return result;
}


int main(void){
    #define LEN 5
    int input[LEN] = {2,3,1,1,4};

    bool result_g = canJump_greedy(input, LEN);
    bool result_1 = canJump_1Ddp(input, LEN);
    bool result_2 = canJump_2Ddp(input, LEN);

    printf("Result:{greedy:%d,1Ddp:%d,2Ddp:%d}\n",result_g, result_1, result_2);

    return 0;
}