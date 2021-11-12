#include "q.c"

void sched_FIFO(dlq *const p_fq, int *p_time){   
    //Queue for keeping processes that are ready
    dlq ready_queue; 
    ready_queue.head = ready_queue.tail = NULL;
    //A node for handling the current process
    dlq_node *currentprocess = NULL;
    //The while loop will run until the break condition arrives
    while(1){
        //The nested if/else block checks the states of p_fq, ready_queue, and currentprocess;
        if(is_empty(p_fq) == 0){
            if(is_empty(&ready_queue) == 0){
                if(currentprocess != NULL){
                    //Whenever the current process is not null, we can reduce timeleft
                    if(p_fq->head->data->ptimearrival == *p_time){
                        add_to_tail(&ready_queue, remove_from_head(p_fq));
                    }
                    currentprocess->data->ptimeleft -=1;
                }
            }
            else{
                
                if(currentprocess != NULL){
                    //if p_fq is not empty but readyqueue is then we can add it if ptimearrival matches current time                    
                    if(p_fq->head->data->ptimearrival == *p_time){
                        add_to_tail(&ready_queue, remove_from_head(p_fq));
                    }
                    currentprocess->data->ptimeleft -=1;
                }
                else{
                    //if p_fq is not empty but readyqueue is then we can add it if ptimearrival matches current time
                    if(p_fq->head->data->ptimearrival == *p_time){
                        add_to_tail(&ready_queue, remove_from_head(p_fq));
                        //if currentprocess is also empty then we can update it
                        currentprocess = remove_from_head(&ready_queue);
                    }
                }
            }
        }
        else{
            if(is_empty(&ready_queue) == 0){
                if(currentprocess != NULL){
                currentprocess->data->ptimeleft -=1;
                }
            }
            else{
                if(currentprocess != NULL){
                currentprocess->data->ptimeleft -=1;
                }
            }
        }
        // If current process is finished, update it.
        if (currentprocess != NULL && currentprocess->data->ptimeleft == 0){
            if(is_empty(&ready_queue) == 0){
                currentprocess = remove_from_head(&ready_queue);
            }
            else{
                currentprocess = NULL;
            }
        }
        // Break condition 
        if (currentprocess == NULL && is_empty(p_fq) && is_empty(&ready_queue))        {
            break;    
            
        }
        *p_time+=1;
        //These print statements execute once every iteration
        
        printf("%d:", *p_time);
        
        if (currentprocess == NULL){
            printf("idle:");
        }
        else{
            printf("%s:", currentprocess->data->pname);
        }
        if (is_empty(&ready_queue) == 1){
            printf("empty:\n");
        }
        else{
            print_q(&ready_queue);
            printf(":\n");
        }
    }
}