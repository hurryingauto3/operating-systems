#include <stdio.h>
#include <stdlib.h>

//dll_node is the doubly linked list node
struct dll_node {
	struct dll_node *pfwd; //forward pointer 
	struct dll_node *pbck; //backward pointer
	int size;              //size of allocation in bytes
}; 

typedef struct dll_node dll_node;

//doubly linkedlist
struct dll {
	struct dll_node *head;     //head pointer
	struct dll_node *tail;     //tail pointer
	int available_memory;      //total size of memory available in bytes
};

typedef struct dll dll;

//function declarations
dll_node * get_new_node (int size);
void add_to_tail (dll *list, dll_node *new, int is_freelist);
dll_node * remove_from_head(dll *list);
void print_list (const dll *list);
int is_empty (const dll *list); 

dll_node *get_new_node(int size)
{
	if (size == 0)
		return NULL;

	dll_node *new = malloc(sizeof(dll_node));
	if (!new)
	{
		fprintf(stderr, "Error: allocating memory\n");
		exit(1);
	}

	new->pfwd = new->pbck = NULL;
	new->size = size;
	return new;
}



void print_list(const dll *list)
{
	dll_node *n = list->head;
	if (n == NULL)
		return;

	while (n)
	{
		printf("( %d ),", n->size);
		n = n->pbck;
	}
}

int is_empty(const dll *list)
{
	if (list->head == NULL && list->tail == NULL)
		return 1;
	else if (list->head != NULL && list->tail != NULL)
		return 0;
	else
	{
		fprintf(stderr, "Error: List is inconsistent.");
		exit(1);
	}
}

int main() {
    dll list, freelist;
    int available  = 0;
    int num_allocs = 0;
    int num_deallocs = 0;
    
    list.head = NULL;
    list.tail = NULL;
    freelist.head = NULL;
    freelist.tail = NULL;
    freelist.available_memory = 0;    //freelist is empty
    
    //first line is available memory given in bytes
    scanf("%d", &available);
    list.available_memory = available - 8;  
    
    //second line is the number of allocations
    scanf("%d", &num_allocs);
    
    for(int i=0; i<num_allocs; ++i)
    {
        int alloc=0;
        scanf("%d", &alloc);
        add_to_tail(&list, get_new_node(alloc), 0);
    }
     
    //following line is the number of deallocations
    scanf("%d", &num_deallocs);
    for(int i=0; i<num_deallocs; ++i)
    {
         add_to_tail(&freelist, remove_from_head(&list), 1);
    }
    
    puts("Allocator:");
    print_list(&list);    
    printf("\nAvailable mem: %d\n", list.available_memory);

    puts("Freelist:");
    print_list(&freelist);
    printf("\nAvailable mem (freelist): %d\n", freelist.available_memory);
    return 0;
}
