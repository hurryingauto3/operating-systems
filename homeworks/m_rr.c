#include "m_fifo.c"

void sched_RR(dlq *const p_fq, int *p_time) {
  dlq active_q;
  active_q.head = active_q.tail = NULL;
  dlq_node *cur = NULL;

  while (1) {
    // break condition
    if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur == NULL) {
      break;
    }

    // If we don't have an active process
    if (cur != NULL) {
      cur->data->ptimeleft--;
      if (cur->data->ptimeleft != 0) {
        add_to_tail(&active_q, cur);
      }
      cur = NULL;
    }

    // If a process has arrived push it in active queue
    if (is_empty(p_fq) == 0 && p_fq->head->data->ptimearrival == *p_time) {
      add_to_tail(&active_q, remove_from_head(p_fq));
    }

    if (is_empty(&active_q) == 0) {
      cur = remove_from_head(&active_q);
    }
    // break condition
    if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur == NULL) {
      break;
    }

    *p_time += 1;

    printf("%d:", *p_time);

    if (cur == NULL) {
      printf("idle:");
    } else {
      printf("%s:", cur->data->pname);
    }
    if (is_empty(&active_q) == 0) {
      print_q(&active_q);
      printf(":\n");
    } else {
      printf("empty:\n");
    }
  }
}