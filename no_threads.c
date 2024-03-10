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

void BitonicMerge(SortArgs* args){
	if(args->size == 1){
		return;
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

	
	BitonicMerge(&left_args);
	BitonicMerge(&right_args);
}


void BitonicSort(SortArgs *args){
	if(args->size == 1){
		return;
	}
	SortArgs left_args;

	left_args.array = args->array;
	left_args.size = args->size / 2;
	left_args.direction = 1;

	SortArgs right_args;

	right_args.array = &args->array[args->size / 2];
	right_args.size = args->size / 2;
	right_args.direction = 0;
	
	pthread_t thread_left, thread_right;
	
	BitonicSort(&left_args);
	BitonicSort(&right_args);
	BitonicMerge(args);
}


int main(int argc, char* argv[]){
	if (argc > 2){
		printf("too many arguments");
		return 0;
	}

	int thread_count = atoi(argv[1]);

	int array[1000];
	int size;
	scanf("%d", &size);
	for(int i = 0; i < size; i++){
		scanf("%d", &array[i]);
	}

	SortArgs args;

	args.array = array;
	args.size = size;
	args.direction = 1;

	BitonicSort(&args);

		
	printf("\n");
	for(int i = 0; i < size; i++){
		printf("%d ",array[i]);
	}
}
