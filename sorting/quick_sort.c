#include<stdio.h>
#include<time.h>
#include<stdlib.h>



void quick_sort(int a[], int n);//wrapper
static void quicksort(int a[], int p, int r);//main logic
static int partition(int a[], int p, int r);
void randomized_quicksort(int a[], int n);
static int randomized_partition(int a[], int p, int r);
static void randomizedQuickSort(int a[], int p, int r);
static void swap(int* a, int* b);

void quick_sort(int a[], int n){
    quicksort(a, 0, n-1);
}

static void quicksort(int a[], int p, int r){
    if(p >= r){
        return;
    }
    int q = partition(a, p, r);
    quicksort(a, p, q-1);//do not include pivot
    quicksort(a, q+1, r);
}

static int partition(int a[], int p, int r){
    int x = a[r];
    int i = p - 1;
    for(int j=p; j<r; j++){//we do stop at j-1=r-1'th loop even though j = r (but not do the j=r'th part)
        if(a[j] <= x){
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i+1], &a[r]);

    return i+1;
}

void randomized_quicksort(int a[], int n){
    randomizedQuickSort(a, 0, n-1);
}

static void randomizedQuickSort(int a[], int p, int r){
    if(p >= r){
        return;
    }
    int q = randomized_partition(a, p, r);
    randomizedQuickSort(a, p, q-1);
    randomizedQuickSort(a, q+1, r);
}

static int randomized_partition(int a[], int p, int r){
    int i = p + rand() % (r - p + 1);
    swap(&a[i], &a[r]);
    return partition(a, p, r);
}


static void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// int main(){
//     int nums1[]= {3, 2, 44, 0, 4, 12, 6, 3, -6};
//     int len = sizeof(nums1)/ sizeof(nums1[0]);
//     quick_sort(nums1, len);
//     for(int i=0; i<len; i++){
//         printf("%d,", nums1[i]);
//     }

//     printf("\n");
//     int nums2[]= {3, 2, 44, 0, 4, 12, 6, 3, -6};
//     srand(time(NULL));
//     randomized_quicksort(nums2, len);
//     for(int i=0; i<len; i++){
//         printf("%d,", nums2[i]);
//     }
//     return 0;
// }