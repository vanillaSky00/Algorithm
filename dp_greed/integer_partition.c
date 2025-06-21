#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


bool canPartition_dp(int* nums, int numsSize) {
    int target = 0;
    for(int i = 0; i < numsSize; i++){
        target += nums[i];
    }
    if(target % 2 != 0) return false;
    target /= 2;

    bool** c = (bool**) malloc((numsSize + 1) * sizeof *c);
    for(int i = 0; i <= numsSize; i++){
        c[i] = (bool*) calloc((target + 1), sizeof **c);
    }
    
    for(int i = 1; i <= numsSize; i++){
        for(int j = 1; j <= target; j++){
            if(nums[i-1] == j){ 
                c[i][j] = true;
            }
            else{
                int next_j = j - nums[i-1];
                c[i][j] = (next_j < 0 || next_j > target) ? 
                false || c[i - 1][j] : c[i - 1][next_j] || c[i - 1][j];
            }
        }
    }

    bool result = c[numsSize][target];
    
    for(int i = 0; i <= numsSize; i++){
        free(c[i]);
    }
    free(c);
    return result;
}

bool canPartition_recursive(int* nums, int numsSize, int target, int idx){
    if(target == 0) {
        printf("target is 0\n");
        return true;
    }
    if(idx >= numsSize) return false;
    printf("nums[idx]: %d, target: %d\n", nums[idx], target);
    return canPartition_recursive(nums, numsSize, target - nums[idx], idx + 1) ||
    canPartition_recursive(nums, numsSize, target, idx + 1);
}

bool canPartition(int* nums, int numsSize) {
    int target = 0;
    for(int i = 0; i < numsSize; i++){
        target += nums[i];
    }
    
    if(target % 2 != 0) return false;
    return canPartition_recursive(nums, numsSize, target / 2, 0);
}

int main(){
    int input[] = {3,3,6,8,16,16,16,18,20};
    //canPartition(input, 9);
    canPartition_dp(input, 9);
}