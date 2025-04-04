#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"heap_sort.c"
void my_heap_sort(int a[], int n);
void my_swap(int* a, int* b);
int comp_int(const void* x1, const void* x2);

int main(){
    int LEN = 10000;
    int nums1[LEN];
    int nums2[LEN];
    srand(time(NULL));
    for(int i = 0; i<10; i++){
        for(int j=0; j<LEN; j++){
            nums1[j] = rand() % 100;
            nums2[j] = nums1[j];
        }
        
        my_heap_sort(nums1, LEN);
        heap_sort(nums2, LEN);
        //qsort(nums2, LEN, sizeof(int), comp_int);
        for(int i=0; i<LEN; i++){
            if(nums1[i] != nums2[i]){
                printf("%d%s", nums1[i], (i != LEN - 1) ? ", ": "\n");
            }
        }
        printf("done");
    }
    return 0;
}

// bubble up method, and without making a max heap first
// gpt says it is not a heapsort??
void my_heap_sort(int a[], int n){
    //build heap: just use given array
    int i, j, p;
    //find the max and swap
    for(i=n-1; i>=0; i--){
        for(j=i; j>=0; j--){
            p = (j-1)/2;
            if(p>=0 && (a[j] > a[p])){
                my_swap(&a[j], &a[p]);
            }
        }
        my_swap(&a[0], &a[i]);
    }
}

void my_swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int comp_int(const void* x1, const void* x2){
    return (*(int*)x1) - (*(int*)x2);
}