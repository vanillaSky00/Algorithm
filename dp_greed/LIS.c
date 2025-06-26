#include <stdio.h>
#include <stdlib.h>

int binary_search(int* arr, int target, int p, int r){
    while(p < r){
        int mid = p + (r - p) / 2;
        if(target > arr[mid]){
            p = mid + 1;
        } 
        else{
            r = mid; //arr[mid] could be an answer cause the above only check >
        } 
    }
    return p;
}

int lengthOfLIS(int* nums, int numsSize) {
    /** patience sorting concept
     *  edge case: at least 1 pile and at most numsSize pile
     *  theorem: len of lcs = pile count
     */
    if(numsSize == 0) return 0;

    int pile_count = 0;
    int piles[numsSize];

    for(int i = 0; i < numsSize; i++){

        int pos = binary_search(piles, nums[i], 0, pile_count);

        piles[pos] = nums[i];
        if(pos == pile_count){
            pile_count++;
        }
    }
    return pile_count;
}


int binary_search_index(int* nums, int* piles, int target, int p, int r){
    while(p < r){
        int mid = p + (r - p) / 2;
        if(target > nums[piles[mid]]){
            p = mid + 1;
        } 
        else{
            r = mid; //arr[mid] could be an answer cause the above only check >
        } 
    }
    return p;
}

int lengthOfLIS_backtrack(int* nums, int numsSize) {
    //only if you're using the LIS binary search approach with index tracking.
    if(numsSize == 0) return 0;

    int prev[numsSize];     // prev[i] = index of previous element for backtracking
    int piles[numsSize];
    int pile_count = 0;

    for(int i = 0; i < numsSize; i++){
        int pos = binary_search_index(nums, piles, nums[i], 0, pile_count);

        //record 
        prev[i] = (pos > 0) ? piles[pos - 1] : -1;

        //update piles via "index" tracking
        piles[pos] = i;
        if(pos == pile_count){
            pile_count++;
        }
    }

    //reconstruct LIS by backtracking, but print in reverse order
    int last = piles[pile_count - 1];
    while(last != -1){
        printf("%d, ", nums[last]);
        last = prev[last];
    }

    return pile_count;
}

#define ASSERT(actual, expected, message) \
  do { \
    int _actual = (actual); \
    int _expected = (expected); \
    if (_actual != _expected ) { \
      fprintf(stderr, "\nAssertion failed: %s == %s\n  Actual: %d, Expected: %d\n  File: %s, Line: %d\n", \
        #actual, #expected, _actual, _expected, __FILE__, __LINE__); \
      exit(1); \
    } else { \
      fprintf(stderr, "%s", message); \
    } \
  } while(0)

//unit test
void test_basic_cases() {
    int test_bs_1[9] = {1,3,6,7,9,4,10,5,6};
    ASSERT(binary_search(test_bs_1, test_bs_1[3], 0, 8), 3, "\nPassed binary_search test1.\n");

    int test_lis_1[9] = {1,3,6,7,9,4,10,5,6};
    ASSERT(lengthOfLIS(test_lis_1, 9), 6, "\nPassed lengthOfLIS test1.\n");    
    int test_lis_2[6] = {4,10,4,3,8,9};
    ASSERT(lengthOfLIS(test_lis_2, 6), 3, "\nPassed lengthOfLIS test2.\n"); 

    //output is weridly ordered why printf is slower then printf in Assert?
    ASSERT(lengthOfLIS_backtrack(test_lis_1, 9), 6, "\nPassed reconstruct of LIS test1.\n");
    printf("\n");
    ASSERT(lengthOfLIS_backtrack(test_lis_2, 6), 3, "\nPassed reconstruct of LIS test2.\n");    
}


int main(){
    printf("\n********  Test binary search/ LIS and reconstruction.  ********\n");
    test_basic_cases();

    printf("\n********  All tests passed.  ********\n");
    return 0;
}