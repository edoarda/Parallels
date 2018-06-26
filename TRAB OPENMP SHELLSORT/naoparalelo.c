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

void Shellsort(int N, int *A)
{
  int i, j, h, v;
  h = 1; while (h < N) h = 2*h + 1;
  h /= 2;
  while (h != 1) {
    h /= 2;
    for (i = h; i < N; i++) {
      v = A[i]; j = i;
      while (A[j-h] > v) {
        A[j] = A[j-h]; j = j - h;
        if (j <= h) break;
      }
      A[j] = v;
    }
    h /= 2;
  }
  InsertionSort(N,A);  // clean up
}

int main(){
	printf("oi");
	int temp[11] = {2,5,9,7,1,6,8,3,4,5,-666};
	int *a = malloc(11 *sizeof(int));
	a=temp;
	
	printf("oi");
	Shellsort(11, a);
	printf("oi");
	int i;
	for(i=0; i<11; i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	//free(a);
}
