#include<stdio.h>

void radix_sort(int a[], int n);//wrapper
static void radixSort(int a[], int n);//main logic
static void countingSort(int a[], int n, int place);
static int get_max(int a[], int n);

void radix_sort(int a[], int n){
    //check if negative
    for(int i=0; i<n; i++){
        if(a[i] < 0){
            perror("Invalid input, this radix sort does not support for negative value");
            return;
        }
    }
    radixSort(a, n);
}

static void radixSort(int a[], int n){
    int max = get_max(a, n);
    for(int place=1; max>0 ;place*=10, max/=10){
        countingSort(a, n, place);
        //printf("%d, %d\n", max, place);
    }
}

static void countingSort(int a[], int n, int place){
    int b[n];
    int c[10] = {0};//bins for 0-9
    
    // digit got extracted = (a[i]/place) % 10
    for(int i=0; i<n; i++){
        c[(a[i]/place)%10]++;
    }

    for(int j=1; j<10; j++){
        c[j] += c[j-1];
    }

    int index;
    for(int i=n-1; i>=0; i--){
        index = (a[i]/place)%10;
        b[c[index] - 1] = a[i]; 
        c[index]--;
    }

    for(int i=0; i<n; i++){
        a[i] = b[i];
    }
}

static int get_max(int a[], int n){
    int max = a[0];
    for(int i=0; i<n; i++){
        if(a[i] > max){
            max=a[i];
        }
    }
    return max;
}

// int main(){
//     int nums1[]= {3, 2, 44, 0, 4, 12, 6, 3, 2};
//     int len = sizeof(nums1)/ sizeof(nums1[0]);
//     radix_sort(nums1, len);
//     for(int i=0; i<len; i++){
//         printf("%d%s", nums1[i], (i!=len-1) ? ", ":"\n");
//     }
// }