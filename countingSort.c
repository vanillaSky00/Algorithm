#include<stdio.h>

void countingSort(int a[], int n);
int findMaxValue(int a[], int n);
//if the given number is sparse, 3, 99, 10000, 2, then counting sort may not suit
//In such cases, using a radix/hash map/bucket sort might be better instead of counting sort.

int main(){
    int nums1[]= {3, 2, 44, 0, 4, 12, 6, 3, 2};
    //n=length, k=unique_number_count
    int len = sizeof(nums1)/sizeof(nums1[0]);
    countingSort(nums1, len);

    for(int i=0; i<len; i++){
        printf("%d,", nums1[i]);
    }
    return 0;
}

//int k
void countingSort(int a[], int n){
    //get max, the size should be at lease max+1
    int k = findMaxValue(a, n);

    int c[k + 1];
    int b[n];

    for(int i=0; i<=k; i++){
        c[i] = 0;
    }
    for(int j=0; j<n; j++){
        c[a[j]]++;
    }
    for(int i=1; i<=k; i++){
        c[i] += c[i-1];
    }
    for(int i=n-1; i>=0; i--){
        b[c[a[i]] - 1] = a[i];
        c[a[i]] -= 1;
    }
    // Copy sorted array back to original array
    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}

int findMaxValue(int a[], int n){
    int max = a[0];
    for(int i=1; i<n; i++){
        if(a[i] > max){
            max = a[i];
        }
    }
    return max;
}

