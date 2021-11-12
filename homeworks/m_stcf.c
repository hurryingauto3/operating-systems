#include "m_sjf.c"

void sched_STCF(dlq *const p_fq, int *p_time)
{
    // *p_time += 1;
    dlq active_q;
    active_q.head = active_q.tail = NULL;
    pcb *cur = NULL;

    while (1)
    {

        if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur != NULL)
        {

            // printf("%d:%s:empty:\n", *p_time, cur->pname);

            cur->ptimeleft--;
        }
        else if (is_empty(p_fq) == 1 && is_empty(&active_q) == 0 && cur == NULL)
        {

            // printf("%d:idle:", *p_time);
            // print_q(&active_q);
            // printf(":\n");
            sort_by_timetocompletion(&active_q);
            cur = remove_from_head(&active_q)->data;
        }
        else if (is_empty(p_fq) == 1 && is_empty(&active_q) == 0 && cur != NULL)
        {
            // printf("%d:%s:", *p_time, cur->pname);
            // print_q(&active_q);
            // printf(":\n");

            cur->ptimeleft--;
            if (cur->ptimeleft > active_q.head->data->ptimeleft)
            {
                dlq_node cur_node;
                cur_node.data = cur;
                add_to_tail(&active_q, &cur_node);
                cur = remove_from_head(&active_q)->data;
                sort_by_timetocompletion(&active_q);
            }
        }
        else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 1 && cur == NULL)
        {

            if (p_fq->head->data->ptimearrival == *p_time)
            {
                add_to_tail(&active_q, remove_from_head(p_fq));
                sort_by_timetocompletion(&active_q);
                cur = remove_from_head(&active_q)->data;
            }
            // printf("%d:idle:empty:\n", *p_time);
        }
        else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 1 && cur != NULL)
        {
            if (p_fq->head->data->ptimearrival == *p_time)
            {
                add_to_tail(&active_q, remove_from_head(p_fq));
                sort_by_timetocompletion(&active_q);
            }
            // printf("%d:%s:empty:\n", *p_time, cur->pname);

            cur->ptimeleft--;
        }
        else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 0 && cur == NULL)
        {

            if (p_fq->head->data->ptimearrival == *p_time)
            {

                add_to_tail(&active_q, remove_from_head(p_fq));
                sort_by_timetocompletion(&active_q);
                cur = remove_from_head(&active_q)->data;
            }
        }
        else if (is_empty(p_fq) == 0 && is_empty(&active_q) == 0 && cur != NULL)
        {

            if (p_fq->head->data->ptimearrival == *p_time)
            {
                add_to_tail(&active_q, remove_from_head(p_fq));
                sort_by_timetocompletion(&active_q);
            }
            // printf("%d:%s:", *p_time +1, cur->pname);

            // print_q(&active_q);
            // printf(":\n");

            cur->ptimeleft--;
            if (cur->ptimeleft > active_q.head->data->ptimeleft)
            {
                dlq_node cur_node;
                cur_node.data = cur;
                add_to_tail(&active_q, &cur_node);
                cur = remove_from_head(&active_q)->data;
                sort_by_timetocompletion(&active_q);
            }
        }
        if (cur != NULL && cur->ptimeleft == 0)
        {
            if (is_empty(&active_q) == 1)
            {
                cur = NULL;
            }
            else
            {
                sort_by_timetocompletion(&active_q); //sort by time to completion
                cur = remove_from_head(&active_q)->data;
            }
        }
        if (is_empty(p_fq) == 1 && is_empty(&active_q) == 1 && cur == NULL)
        {
            break;
        }
        *p_time += 1;

        printf("%d:", *p_time);
        if (cur == NULL)
        {
            printf("idle:");
        }
        else
        {
            printf("%s:", cur->pname);
        }
        if (is_empty(&active_q) == 0)
        {
            print_q(&active_q);
            printf(":\n");
        }
        else
        {
            printf("empty:\n");
        }
    }
}