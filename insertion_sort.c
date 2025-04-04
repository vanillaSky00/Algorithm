#include<stdio.h>

void insertion_sort(int a[], int len);

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

// int main(){
//     int nums1[]= {3, 2, 44, 0, 4, 12, 6, 3, -6};
//     int len = sizeof(nums1)/ sizeof(nums1[0]);
//     insertion_sort(nums1, len);
//     for(int i=0; i<len; i++){
//         printf("%d,", nums1[i]);
//     }
// }