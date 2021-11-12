#include "hw2.c"

void add_to_tail(dll *list, dll_node *new, int is_freelist) {
  // For the case when the list is not empty
    if (is_empty(list) == 0) {
            //point tail.next to new
            list->tail->pbck = new;
            //point new.prev to tail
            new->pbck = list->tail;
            //make new the new tail
            list->tail = new;
            //point new.next to null
            list->tail->pbck = NULL;
            
    }
    // For the case when the list is empty
    else {
        //point head and tail to new
        list->head = list->tail = new;
        //point head.prev to null and tail.next to null
        list->tail->pfwd = list->head->pbck = NULL;
    }
    //if the new node is a freelist node then add the size to the available memory
    if (is_freelist == 1) {
        list->available_memory += new->size;
    }
    //if the new node is not a freelist node then 
    //subtract size+8 bytes from the available memory
    else {
        list->available_memory -= (new->size + 8);
    }
}

dll_node *remove_from_head(dll *const list) {
    //Checks if list is empty
    if (is_empty(list) == 0){
        dll_node *temp = list->head;
        //If only one element in list
        if(list->head == list->tail){
            list->head = list->tail = NULL;
        }
        //If multiple elements in list
        else{
            list->head = list->head->pbck;
            list->head->pfwd = NULL;

        }
        //free memeory from list
        list->available_memory += (temp->size + 8);
        return temp;
    }
    //Returns null if list empty
    else{
        return NULL;
    }
}