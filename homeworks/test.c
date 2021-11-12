#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// process control block (PCB)
struct pcb {
  unsigned int pid;
  char pname[20];
  unsigned int ptimeleft;
  unsigned int ptimearrival;
};

typedef struct pcb pcb;

// queue node
struct dlq_node {
  struct dlq_node *pfwd;
  struct dlq_node *pbck;
  struct pcb *data;
};

typedef struct dlq_node dlq_node;

// queue
struct dlq {
  struct dlq_node *head;
  struct dlq_node *tail;
};

typedef struct dlq dlq;

// function to add a pcb to a new queue node
dlq_node *get_new_node(pcb *ndata) {
  if (!ndata)
    return NULL;

  dlq_node *new = malloc(sizeof(dlq_node));
  if (!new) {
    fprintf(stderr, "Error: allocating memory\n");
    exit(1);
  }

  new->pfwd = new->pbck = NULL;
  new->data = ndata;
  return new;
}

// function to add a node to the tail of queue
void add_to_tail(dlq *q, dlq_node *new) {
  if (!new)
    return;

  if (q->head == NULL) {
    if (q->tail != NULL) {
      fprintf(stderr, "DLList inconsitent.\n");
      exit(1);
    }
    q->head = new;
    q->tail = q->head;
  } else {
    new->pfwd = q->tail;
    new->pbck = NULL;
    new->pfwd->pbck = new;
    q->tail = new;
  }
}

// function to remove a node from the head of queue
dlq_node *remove_from_head(dlq *const q) {
  if (q->head == NULL) { // empty
    if (q->tail != NULL) {
      fprintf(stderr, "DLList inconsitent.\n");
      exit(1);
    }
    return NULL;
  } else if (q->head == q->tail) { // one element
    if (q->head->pbck != NULL || q->tail->pfwd != NULL) {
      fprintf(stderr, "DLList inconsitent.\n");
      exit(1);
    }

    dlq_node *p = q->head;
    q->head = NULL;
    q->tail = NULL;

    p->pfwd = p->pbck = NULL;
    return p;
  } else { // normal
    dlq_node *p = q->head;
    q->head = q->head->pbck;
    q->head->pfwd = NULL;

    p->pfwd = p->pbck = NULL;
    return p;
  }
}

// function to print our queue
void print_q(const dlq *q) {
  dlq_node *n = q->head;
  if (n == NULL)
    return;

  while (n) {
    printf("%s(%d),", n->data->pname, n->data->ptimeleft);
    n = n->pbck;
  }
}

// function to check if the queue is empty
int is_empty(const dlq *q) {
  if (q->head == NULL && q->tail == NULL)
    return 1;
  else if (q->head != NULL && q->tail != NULL)
    return 0;
  else {
    fprintf(stderr, "Error: DLL queue is inconsistent.");
    exit(1);
  }
}

// function to sort the queue on completion time
void sort_by_timetocompletion(const dlq *q) {
  // bubble sort
  dlq_node *start = q->tail;
  dlq_node *end = q->head;

  while (start != end) {
    dlq_node *node = start;
    dlq_node *next = node->pfwd;

    while (next != NULL) {
      if (node->data->ptimeleft < next->data->ptimeleft) {
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

// function to sort the queue on arrival time
void sort_by_arrival_time(const dlq *q) {
  // bubble sort
  dlq_node *start = q->tail;
  dlq_node *end = q->head;

  while (start != end) {
    dlq_node *node = start;
    dlq_node *next = node->pfwd;

    while (next != NULL) {
      if (node->data->ptimearrival < next->data->ptimearrival) {
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

// function to tokenize the one row of data
pcb *tokenize_pdata(char *buf) {
  pcb *p = (pcb *)malloc(sizeof(pcb));
  if (!p) {
    fprintf(stderr, "Error: allocating memory.\n");
    exit(1);
  }

  char *token = strtok(buf, ":\n");
  if (!token) {
    fprintf(stderr, "Error: Expecting token pname\n");
    exit(1);
  }
  strcpy(p->pname, token);

  token = strtok(NULL, ":\n");
  if (!token) {
    fprintf(stderr, "Error: Expecting token pid\n");
    exit(1);
  }
  p->pid = atoi(token);

  token = strtok(NULL, ":\n");
  if (!token) {
    fprintf(stderr, "Error: Expecting token duration\n");
    exit(1);
  }

  p->ptimeleft = atoi(token);

  token = strtok(NULL, ":\n");
  if (!token) {
    fprintf(stderr, "Error: Expecting token arrival time\n");
    exit(1);
  }
  p->ptimearrival = atoi(token);

  token = strtok(NULL, ":\n");
  if (token) {
    fprintf(stderr, "Error: Oh, what've you got at the end of the line?\n");
    exit(1);
  }

  return p;
}

// implement the FIFO scheduling code

void sched_FIFO(dlq *const p_fq, int *p_time) {
  // *p_time += 1;
  dlq active_q;
  active_q.head = active_q.tail = NULL;
  pcb *cur = NULL;

  while (1) {

    if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur != NULL) {

      cur->ptimeleft--;
    } else if (is_empty(p_fq) == 1 && is_empty(&active_q) == 0 && cur == NULL) {

      cur = remove_from_head(&active_q)->data;
    } else if (is_empty(p_fq) == 1 && is_empty(&active_q) == 0 && cur != NULL) {

      cur->ptimeleft--;

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 1 && cur == NULL) {

      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
        cur = remove_from_head(&active_q)->data;
      }
      // printf("%d:idle:empty:\n", *p_time);

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 1 && cur != NULL) {
      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
      }
      // printf("%d:%s:empty:\n", *p_time, cur->pname);

      cur->ptimeleft--;

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 0 && cur == NULL) {

      if (p_fq->head->data->ptimearrival == *p_time) {

        add_to_tail(&active_q, remove_from_head(p_fq));
        cur = remove_from_head(&active_q)->data;
      }

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 0 && cur != NULL) {

      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
      }

      cur->ptimeleft--;
    }
    if (cur != NULL && cur->ptimeleft == 0) {
      if (is_empty(&active_q) == 1) {
        cur = NULL;
      } else {
        cur = remove_from_head(&active_q)->data;
      }
    }
    if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur == NULL) {
      break;
    }
    *p_time += 1;

    printf("%d:", *p_time);
    if (cur == NULL) {
      printf("idle:");
    } else {
      printf("%s:", cur->pname);
    }
    if (is_empty(&active_q) == 0) {
      print_q(&active_q);
      printf(":\n");
    } else {
      printf("empty:\n");
    }
  }
}
// implement the SJF scheduling code
void sched_SJF(dlq *const p_fq, int *p_time) {
  dlq active_q;
  active_q.head = active_q.tail = NULL;
  pcb *cur = NULL;

  while (1) {

    if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur != NULL) {

      cur->ptimeleft--;
    } else if (is_empty(p_fq) == 1 && is_empty(&active_q) == 0 && cur == NULL) {

      sort_by_timetocompletion(&active_q);
      cur = remove_from_head(&active_q)->data;
    } else if (is_empty(p_fq) == 1 && is_empty(&active_q) == 0 && cur != NULL) {

      cur->ptimeleft--;

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 1 && cur == NULL) {

      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
        sort_by_timetocompletion(&active_q);
        cur = remove_from_head(&active_q)->data;
      }
      // printf("%d:idle:empty:\n", *p_time);

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 1 && cur != NULL) {
      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
        sort_by_timetocompletion(&active_q);
      }

      cur->ptimeleft--;

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 0 && cur == NULL) {

      if (p_fq->head->data->ptimearrival == *p_time) {

        add_to_tail(&active_q, remove_from_head(p_fq));
        sort_by_timetocompletion(&active_q);
        cur = remove_from_head(&active_q)->data;
      }

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 0 && cur != NULL) {

      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
        sort_by_timetocompletion(&active_q);
      }

      cur->ptimeleft--;
    }
    if (cur != NULL && cur->ptimeleft == 0) {
      if (is_empty(&active_q) == 1) {
        cur = NULL;
      } else {
        sort_by_timetocompletion(&active_q); // sort by time to completion
        cur = remove_from_head(&active_q)->data;
      }
    }
    if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur == NULL) {
      break;
    }
    *p_time += 1;

    printf("%d:", *p_time);
    if (cur == NULL) {
      printf("idle:");
    } else {
      printf("%s:", cur->pname);
    }
    if (is_empty(&active_q) == 0) {
      print_q(&active_q);
      printf(":\n");
    } else {
      printf("empty:\n");
    }
  }
}
// implement the STCF scheduling code
void sched_STCF(dlq *const p_fq, int *p_time) {
  // *p_time += 1;
  dlq active_q;
  active_q.head = active_q.tail = NULL;
  pcb *cur = NULL;

  while (1) {

    if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur != NULL) {

      cur->ptimeleft--;
    } else if (is_empty(p_fq) == 1 && is_empty(&active_q) == 0 && cur == NULL) {

      sort_by_timetocompletion(&active_q);
      cur = remove_from_head(&active_q)->data;
    } else if (is_empty(p_fq) == 1 && is_empty(&active_q) == 0 && cur != NULL) {

      cur->ptimeleft--;
      if (cur->ptimeleft > active_q.head->data->ptimeleft) {
        dlq_node cur_node;
        cur_node.data = cur;
        add_to_tail(&active_q, &cur_node);
        cur = remove_from_head(&active_q)->data;
        sort_by_timetocompletion(&active_q);
      }
    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 1 && cur == NULL) {

      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
        sort_by_timetocompletion(&active_q);
        cur = remove_from_head(&active_q)->data;
      }
      // printf("%d:idle:empty:\n", *p_time);
    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 1 && cur != NULL) {
      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
        sort_by_timetocompletion(&active_q);
      }
      // printf("%d:%s:empty:\n", *p_time, cur->pname);

      cur->ptimeleft--;
    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 0 && cur == NULL) {

      if (p_fq->head->data->ptimearrival == *p_time) {

        add_to_tail(&active_q, remove_from_head(p_fq));
        sort_by_timetocompletion(&active_q);
        cur = remove_from_head(&active_q)->data;
      }
    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 0 && cur != NULL) {

      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
        sort_by_timetocompletion(&active_q);
      }

      cur->ptimeleft--;
      if (cur->ptimeleft > active_q.head->data->ptimeleft) {
        dlq_node cur_node;
        cur_node.data = cur;
        add_to_tail(&active_q, &cur_node);
        cur = remove_from_head(&active_q)->data;
        sort_by_timetocompletion(&active_q);
      }
    }
    if (cur != NULL && cur->ptimeleft == 0) {
      if (is_empty(&active_q) == 1) {
        cur = NULL;
      } else {
        sort_by_timetocompletion(&active_q); // sort by time to completion
        cur = remove_from_head(&active_q)->data;
      }
    }
    if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur == NULL) {
      break;
    }
    *p_time += 1;

    printf("%d:", *p_time);
    if (cur == NULL) {
      printf("idle:");
    } else {
      printf("%s:", cur->pname);
    }
    if (is_empty(&active_q) == 0) {
      print_q(&active_q);
      printf(":\n");
    } else {
      printf("empty:\n");
    }
  }
}
// implement the RR scheduling code
void sched_RR(dlq *const p_fq, int *p_time) {
  dlq active_q;
  active_q.head = active_q.tail = NULL;
  pcb *cur = NULL;

  while (1) {

    if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur != NULL) {

      cur->ptimeleft--;

    } else if (is_empty(p_fq) == 1 && is_empty(&active_q) == 0 && cur == NULL) {

      cur = remove_from_head(&active_q)->data;
    } else if (is_empty(p_fq) == 1 && is_empty(&active_q) == 0 && cur != NULL) {
      cur->ptimeleft--;
      

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 1 && cur == NULL) {
        //Works
      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
        cur = remove_from_head(&active_q)->data;
      }

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 1 && cur != NULL) {
      if (p_fq->head->data->ptimearrival == *p_time) {
        add_to_tail(&active_q, remove_from_head(p_fq));
      }

      cur->ptimeleft--;
 

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 0 && cur == NULL) {

      if (p_fq->head->data->ptimearrival == *p_time) {

        add_to_tail(&active_q, remove_from_head(p_fq));
        cur = remove_from_head(&active_q)->data;
      }

    } else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 0 && cur != NULL) {

        if (p_fq->head->data->ptimearrival == *p_time) {
            add_to_tail(&active_q, remove_from_head(p_fq));
        }

        cur->ptimeleft--;

    }
    
    if (cur != NULL && is_empty(&active_q) == 0){
        dlq_node cur_node;
        cur_node.pbck = cur_node.pfwd = NULL;
        cur_node.data = cur;
        add_to_tail(&active_q, &cur_node);
        cur = remove_from_head(&active_q)->data;
    }

    if (cur != NULL && cur->ptimeleft == 0) {
      if (is_empty(&active_q) == 1) {
        cur = NULL;
      } else {
        cur = remove_from_head(&active_q)->data;
      }
    }
    if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur == NULL) {
      break;
    }
    *p_time += 1;

    printf("%d:", *p_time);
    if (cur == NULL) {
      printf("idle:");
    } else {
      printf("%s:", cur->pname);
    }
    if (is_empty(&active_q) == 0) {
      print_q(&active_q);
      printf(":\n");
    } else {
      printf("empty:\n");
    }
  }
}

P1 3 3

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int N = 0;
  char tech[20] = {'\0'};
  char buffer[100] = {'\0'};
  scanf("%d", &N);
  scanf("%s", tech);

  dlq queue;
  queue.head = NULL;
  queue.tail = NULL;
  for (int i = 0; i < N; ++i) {
    scanf("%s\n", buffer);
    pcb *p = tokenize_pdata(buffer);
    add_to_tail(&queue, get_new_node(p));
  }
  // print_q(&queue);
  unsigned int system_time = 0;
  sort_by_arrival_time(&queue);
  // print_q (&queue);

  // run scheduler
  // if(!strncmp(tech,"FIFO",4))
  // sched_FIFO(&queue, &system_time);
  // else if(!strncmp(tech,"SJF",3))
  // sched_SJF(&queue, &system_time);
  // else if(!strncmp(tech,"STCF",4))
  // sched_STCF(&queue, &system_time);
  // else if(!strncmp(tech,"RR",2))
  sched_RR(&queue, &system_time);
  // else
  // fprintf(stderr, "Error: unknown POLICY\n");
  return 0;
}