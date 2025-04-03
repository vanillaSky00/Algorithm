#include<stdio.h>

void insertion_sort(int a[], int len);

int main(){
    int nums[]= {3, 2, 44, 0, 4, 12, 6, 3, -6};
    int len = sizeof(nums)/ sizeof(nums[0]);
    insertion_sort(nums, len);
    for(int i=0; i<len; i++){
        printf("%d%s", nums[i], (i == len - 1) ? "\n" : ", ");
    }
}

void insertion_sort(int a[], int n){
    int temp, j;
    for(int i=1; i<n; i++){
        temp = a[i];
        for(j=i-1; j>=0 && (a[j] > temp); j--){
            a[j+1] = a[j];
        }
        a[j+1] = temp;
    }
}

/** better readability:
 * void insertionSort(int arr[], int n) {
    int temp, j;
    for (int i = 1; i < n; i++) {
        temp = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}
 */