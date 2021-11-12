#include "m_stcf.c"

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N = 0;
    char tech[20] = {'\0'};
    char buffer[100] = {'\0'};
    scanf("%d", &N);
    scanf("%s", tech);

    dlq queue;
    queue.head = NULL;
    queue.tail = NULL;
    for (int i = 0; i < N; ++i)
    {
        scanf("%s\n", buffer);
        pcb *p = tokenize_pdata(buffer);
        add_to_tail(&queue, get_new_node(p));
    }
    // print_q(&queue);
    unsigned int system_time = 0;
    sort_by_arrival_time(&queue);
    // print_q (&queue);

    // run scheduler
    sched_FIFO(&queue, &system_time);
    sched_RR(&queue, &system_time);
    sched_SJF(&queue, &system_time);
    sched_STCF(&queue, &system_time);

    return 0;
}
