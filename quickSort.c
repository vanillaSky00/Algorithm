#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void swap(int* a, int* b);
int partition(int a[], int p, int r);
void quicksort(int a[], int p, int r);
int randomized_partition(int a[], int p, int r);
void randomized_quicksort(int a[], int p, int r);


int main(){
    int nums1[]= {3, 2, 44, 0, 4, 12, 6, 3, -6};
    int len = sizeof(nums1)/ sizeof(nums1[0]);
    quicksort(nums1, 0, len-1);
    for(int i=0; i<len; i++){
        printf("%d,", nums1[i]);
    }

    printf("\n");
    int nums2[]= {3, 2, 44, 0, 4, 12, 6, 3, -6};
    srand(time(NULL));
    randomized_quicksort(nums2, 0, len-1);
    for(int i=0; i<len; i++){
        printf("%d,", nums2[i]);
    }
    return 0;
}

void quicksort(int a[], int p, int r){
    if(p >= r){
        return;
    }
    int q = partition(a, p, r);
    quicksort(a, p, q-1);//do not include pivot
    quicksort(a, q+1, r);
}

int partition(int a[], int p, int r){
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

void randomized_quicksort(int a[], int p, int r){
    if(p >= r){
        return;
    }
    int q = randomized_partition(a, p, r);
    randomized_quicksort(a, p, q-1);
    randomized_quicksort(a, q+1, r);
}

int randomized_partition(int a[], int p, int r){
    int i = p + rand() % (r - p + 1);
    swap(&a[i], &a[r]);
    return partition(a, p, r);
}


void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}