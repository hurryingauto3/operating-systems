#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//process control block (PCB)
struct pcb 
{
	unsigned int pid;
	char pname[20];
	unsigned int ptimeleft;
	unsigned int ptimearrival;
};

typedef struct pcb pcb;

//queue node
struct dlq_node 
{
	struct dlq_node *pfwd;
	struct dlq_node *pbck;
	struct pcb *data;
}; 

typedef struct dlq_node dlq_node;

//queue
struct dlq 
{
	struct dlq_node *head;
	struct dlq_node *tail;
};

typedef struct dlq dlq;
 
//function to add a pcb to a new queue node
dlq_node * get_new_node (pcb *ndata) 
{
	if (!ndata)
		return NULL;

	dlq_node *new = malloc(sizeof(dlq_node));
	if(!new)
    {
		fprintf(stderr, "Error: allocating memory\n");exit(1);
	}

	new->pfwd = new->pbck = NULL;
	new->data = ndata;
	return new;
}

//function to add a node to the tail of queue
void add_to_tail (dlq *q, dlq_node *new)
{
	if (!new)
		return;

	if (q->head==NULL)
    {
		if(q->tail!=NULL)
        {
			fprintf(stderr, "DLList inconsitent.\n"); exit(1);
		}
		q->head = new;
		q->tail = q->head;
	}
	else 
    {		
		new->pfwd = q->tail;
		new->pbck = NULL;
		new->pfwd->pbck = new;
		q->tail = new;
	}
}

//function to remove a node from the head of queue
dlq_node* remove_from_head(dlq * const q){
	if (q->head==NULL){ //empty
		if(q->tail!=NULL){fprintf(stderr, "DLList inconsitent.\n"); exit(1);}
		return NULL;
	}
	else if (q->head == q->tail) { //one element
		if (q->head->pbck!=NULL || q->tail->pfwd!=NULL) {
			fprintf(stderr, "DLList inconsitent.\n"); exit(1);
		}

		dlq_node *p = q->head;
		q->head = NULL;
		q->tail = NULL;
	
		p->pfwd = p->pbck = NULL;
		return p;
	}
	else { // normal
		dlq_node *p = q->head;
		q->head = q->head->pbck;
		q->head->pfwd = NULL;
	
		p->pfwd = p->pbck = NULL;
		return p;
	}
}

//function to print our queue
void print_q (const dlq *q) 
{
	dlq_node *n = q->head;
	if (n == NULL)
		return;

	while (n) 
    {
		printf("%s(%d),", n->data->pname, n->data->ptimeleft);
		n = n->pbck;
	}
}

//function to check if the queue is empty
int is_empty (const dlq *q)
{
	if (q->head == NULL && q->tail==NULL)
		return 1;
	else if (q->head != NULL && q->tail != NULL)
		return 0;
	else 
    {
		fprintf(stderr, "Error: DLL queue is inconsistent."); exit(1);
	}
}

//function to sort the queue on completion time
void sort_by_timetocompletion(const dlq *q) 
{ 
	// bubble sort
	dlq_node *start = q->tail;
	dlq_node *end = q->head;
	
	while (start != end) 
    {
		dlq_node *node = start;
		dlq_node *next = node->pfwd;

		while (next != NULL) 
        {
			if (node->data->ptimeleft < next->data->ptimeleft)
            {
				// do a swap
				pcb *temp = node->data;
				node->data = next->data;
				next->data = temp;
			}
			node = next;
			next = node->pfwd;
		}
		end = end ->pbck;
	} 
}

//function to sort the queue on arrival time
void sort_by_arrival_time (const dlq *q) 
{
	// bubble sort
	dlq_node *start = q->tail;
	dlq_node *end = q->head;
	
	while (start != end) 
    {
		dlq_node *node = start;
		dlq_node *next = node->pfwd;

		while (next != NULL) 
        {
			if (node->data->ptimearrival < next->data->ptimearrival)
            {
				// do a swap
				pcb *temp = node->data;
				node->data = next->data;
				next->data = temp;
			}
			node = next;
			next = node->pfwd;
		}
		end = end->pbck;
	}
}

//function to tokenize the one row of data
pcb* tokenize_pdata (char *buf) 
{
	pcb* p = (pcb*) malloc(sizeof(pcb));
	if(!p)
    { 
        fprintf(stderr, "Error: allocating memory.\n"); exit(1);
    }

	char *token = strtok(buf, ":\n");
	if(!token)
    { 
        fprintf(stderr, "Error: Expecting token pname\n"); exit(1);
    }  
	strcpy(p->pname, token);

	token = strtok(NULL, ":\n");
	if(!token)
    { 
        fprintf(stderr, "Error: Expecting token pid\n"); exit(1);
    }  
	p->pid = atoi(token);

	token = strtok(NULL, ":\n");
	if(!token)
    { 
        fprintf(stderr, "Error: Expecting token duration\n"); exit(1);
    } 
	 
	p->ptimeleft= atoi(token);

	token = strtok(NULL, ":\n");
	if(!token)
    { 
        fprintf(stderr, "Error: Expecting token arrival time\n"); exit(1);
    }  
	p->ptimearrival = atoi(token);

	token = strtok(NULL, ":\n");
	if(token)
    { 
        fprintf(stderr, "Error: Oh, what've you got at the end of the line?\n");exit(1);
    } 

	return p;
}