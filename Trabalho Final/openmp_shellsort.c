#include <stdio.h>
#include <stdlib.h>

void InsertionSort(int N, int *A)
{
  int i, j, v;
  for (i = 1; i < N; i++) {
    v = A[i]; 
    j = i;
    while (A[j-1] > v) {
      A[j] = A[j-1]; 
      j--;
      if (j <= 0) break;
    }
    A[j] = v;
  }
}

int parallel_shellsort(int N, int *A)
{
  int k, h;
  h = 1; while (h < N) h = 2*h + 1;
  h /= 2;
#pragma omp parallel firstprivate(h)
 {
  while (h != 1) {
#pragma omp for
    for (k = 0; k < h; k++) {
      int i, j, v;
      for (i = k; i < N; i+=h) {
        v = A[i]; 
        j = i;
        while (A[j-h] > v) {
        	A[j] = A[j-h]; 
        	j = j - h;
		if (j <= h) break;
        }
        A[j] = v;
      } // for i
    }  // for k
    h /= 2;
  } //  end while 
 }  // end parallel region
  InsertionSort(N,A);  // clean up
}

int main(){

	int temp[7] = {1093, 364, 121, 40, 13, 4, 1};

	

	parallel_shellsort(7, temp);
	

	int i;
	for(i=0; i<7; i++){
		printf("%d ",temp[i]);
	}
	printf("\n");
}
