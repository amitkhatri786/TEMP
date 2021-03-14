#include<stdio.h>

struct d{
	int point;
	int article_id;
	int section_id;
	int heap_index;
	int is_deleted;
};
typedef struct d DATA;
DATA data[20];

int max_heap[20];
int max_heap_size;
int min_heap[11];
int min_heap_size;
int total_article=0;


int my_cmp(int a,int b)
{
		if(data[a].point == data[b].point)
			return (data[a].article_id > data[b].article_id);
		return data[a].point > data[b].point;
}



void heapify_down(int arr[],int n,int i)
{
	int largest = i;
	int l = 2*i+1;
	int r = 2*i+2;
	int t;
	if(l<n && my_cmp(l,largest))
		largest = l;
	if(r<n && my_cmp(r,largest))
		largest = r;
	if(i!=largest) {
		t = arr[largest];
		arr[largest] = arr[i];
		arr[i] = t;
		data[arr[i]].heap_index = i;
		data[arr[largest]].heap_index = largest;
		heapify_down(arr,n,largest);
	}
}

void heapify_up(int arr[],int n,int i)
{
	int parent = (i-1)/2;
	int t;
	if (i) {
		if (my_cmp(i, parent)) {
			t = arr[parent];
			arr[parent] = arr[i];
			arr[i] = t;
			data[arr[i]].heap_index = i;
			data[arr[parent]].heap_index = parent;
			heapify_up(arr, n, parent);
		}
	}
}

void insert_article(int sec_id,int article_id)
{
		data[article_id-1].article_id = article_id;
		data[article_id-1].section_id = sec_id;
		data[article_id-1].is_deleted = 0;
		data[article_id-1].point = 0;
		data[article_id-1].heap_index = max_heap_size;
		total_article++;

		max_heap[max_heap_size] = article_id-1;
		max_heap_size++;
		heapify_up(max_heap,max_heap_size,max_heap_size-1);
}

void print_array(int arr[],int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("article id = %d, point = %d heap_index = %d \n",data[arr[i]].article_id,data[arr[i]].point,data[arr[i]].heap_index);
}

void erase_article(int article_id)
{
	int heap_index = data[article_id-1].heap_index;
	int parent = (heap_index-1)/2;
	max_heap[heap_index] = max_heap[max_heap_size-1];
	data[max_heap[heap_index]].heap_index = max_heap_size-1;
	max_heap_size--;
	data[article_id-1].is_deleted = 1;
	
	if(parent) {
		if(my_cmp(parent,heap_index))
			heapify_up(max_heap,max_heap_size,heap_index);
		else
			heapify_down(max_heap,max_heap_size,heap_index);
	}
}

int main()
{
	insert_article(0,1);
	insert_article(1,2);
	insert_article(0,3);
	insert_article(1,4);
	insert_article(2,5);
	insert_article(0,6);
	insert_article(1,7);
	insert_article(2,8);
	print_array(max_heap,max_heap_size);
	erase_article(5);
	printf("After erase\n");
	print_array(max_heap,max_heap_size);
	return(0);
}
