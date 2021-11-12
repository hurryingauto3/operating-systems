    
#include "hw1.c"


void sched_FIFO(dlq *const p_fq, int *p_time){

    *p_time = *p_time + 1;
    dlq ready_q;
    ready_q.head = NULL;
    ready_q.tail = NULL;
    dlq_node *current = NULL;
    
    while(1 == 1){
        if(is_empty(p_fq)){
            if(is_empty(&ready_q)){
                if(current == NULL) break;
                else{
                    printf("%d", *p_time);
                    printf(":");
                    printf("%s", current->data->pname);
                    printf(":empty:\n");
                    current->data->ptimeleft--;
                }
            }
            else{
                if(current == NULL){
                    //irrelevant;
                }
                else{
                    printf("%d", *p_time);
                    printf(":");
                    printf("%s", current->data->pname);
                    printf(":");
                    print_q(&ready_q);
                    printf(":\n");
                    current->data->ptimeleft--;
                }
            }
        }
        else{
            if(is_empty(&ready_q)){
                if(current == NULL){
                    printf("%d", *p_time);
                    printf("%s", ":idle:empty:\n");
                }
                else{
                    printf("%d", *p_time);
                    printf(":");
                    printf("%s", current->data->pname);
                    printf(":empty:\n");
                    current->data->ptimeleft--;
                    
                }
            }
            else{
                if(current == NULL){
                    //irrelevant;
                }
                else{
                    printf("%d", *p_time);
                    printf(":");
                    printf("%s", current->data->pname);
                    printf(":");
                    print_q(&ready_q);
                    printf(":\n");
                    current->data->ptimeleft--;
                }
            }
            if(p_fq->head->data->ptimearrival == *p_time){
                add_to_tail(&ready_q, remove_from_head(p_fq));
                if(current == NULL) current = remove_from_head(&ready_q);
            }
        }
        *p_time = *p_time + 1;
        if(current != NULL && current->data->ptimeleft == 0){
            if(is_empty(&ready_q)) current = NULL;
            else current = remove_from_head(&ready_q);
        }
    }
}