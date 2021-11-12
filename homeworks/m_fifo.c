#include "q.c"

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