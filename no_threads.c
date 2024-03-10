#include "stdio.h"
#include "stdbool.h"
#include "pthread.h"
#include "stdlib.h"

typedef struct SortArgs{
	int *array; 
	int size; 
	bool direction;
} SortArgs;

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void * BitonicMerge(void* void_args){
	SortArgs* args = (SortArgs*)void_args;
	if(args->size == 1){
		return NULL;
	}

	int half = args->size / 2;
	for(int i = 0; i < half; i++){
		if(args->direction == (args->array[i] > args->array[i + half])){
			swap(&args->array[i], &args->array[i+half]);
		}
	}

	SortArgs left_args;

	left_args.array = args->array;
	left_args.size = half;
	left_args.direction = args->direction;

	SortArgs right_args;

	right_args.array = &args->array[args->size / 2];
	right_args.size = half;
	right_args.direction = args->direction;

	

	BitonicMerge ((void*)&left_args);
	BitonicMerge ((void*)&right_args);
}


void* BitonicSort(void* void_args){
	SortArgs* args = (SortArgs*)void_args;
	if(args->size == 1){
		return NULL;
	}
	SortArgs left_args;

	left_args.array = args->array;
	left_args.size = args->size / 2;
	left_args.direction = 1;

	SortArgs right_args;

	right_args.array = &args->array[args->size / 2];
	right_args.size = args->size / 2;
	right_args.direction = 0;
	
	BitonicSort ((void*)&left_args);
	BitonicSort ((void*)&right_args);	

	BitonicMerge(args);
}


int main(){
	struct timespec start, end;


	int array[2000];
	int size;
	scanf("%d", &size);
	for(int i = 0; i < size; i++){
		scanf("%d", &array[i]);
	}

    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	SortArgs args;

	args.array = array;
	args.size = size;
	args.direction = 1;

	BitonicSort(&args);

	/*		
	printf("\n");
	for(int i = 0; i < size; i++){
		printf("%d ",array[i]);
	}*/
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("Time taken: %f seconds\n", time_taken);
}
