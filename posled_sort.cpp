#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ITEMS 3000

#define swap(v, a, b) {unsigned tmp; tmp=v[a]; v[a]=v[b]; v[b]=tmp;}
static int *array;

int saved = 0;
void save_to_file() {
 if(saved){
   return;
 }
 FILE *fp;
 char output[] = "output.txt";
 int n;
 fp = fopen(output, "w");
 for (n = 0; n < MAX_ITEMS; n++) {
   fprintf(fp, "%d\n", array[n]);
 }
 fclose(fp);
}

static void init() {
 int i;
 array = (int *) malloc(MAX_ITEMS * sizeof(int));
 for (i = 0; i < MAX_ITEMS; i++) {
   array[i] = rand();
 }
}

static unsigned partition(int *array, unsigned low, unsigned high, unsigned pivot_index) {
 if (pivot_index != low) swap(array, low, pivot_index);
 pivot_index = low;
 low++;
 while (low <= high) {
   if (array[low] <= array[pivot_index])
     low++;
   else if (array[high] > array[pivot_index])
     high--;
   else swap(array, low, high);
 }
 if (high != pivot_index) swap(array, pivot_index, high);
 return high;
}
static void quick_sort(int *array, unsigned low, unsigned high) {
 unsigned pivot;

 if (low >= high)
   return;
 pivot = (low + high) / 2;
 pivot = partition(array, low, high, pivot);

 if (low < pivot) {
   quick_sort(array, low, pivot - 1);
 }

 if (pivot < high) {
   quick_sort(array, pivot + 1, high);
 }

}
int main(int argc, char **argv) {
 int i = 0;
 double sum = 0;
 for (; i < 10; i++) {
   init();
   struct timespec quickStart, quickEnd;
   clock_gettime(CLOCK_REALTIME, &quickStart);
   quick_sort(array, 0, MAX_ITEMS - 1);
   clock_gettime(CLOCK_REALTIME, &quickEnd);
   double time_spent = (quickEnd.tv_sec - quickStart.tv_sec) +
       (quickEnd.tv_nsec - quickStart.tv_nsec) / 1000000000.0;
   printf("%f \n", time_spent);
   save_to_file();
   free(array);
   sum += time_spent;
 }
 sum /= 10;
 printf("Mid: %f\n\n\n", sum);
