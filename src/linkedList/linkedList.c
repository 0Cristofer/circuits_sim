/* Digital circuits simulator linked list implementation.
   Author: Cristofer Oswald
   Created: 19/03/2019
   Edited: 19/03/2019 */

#include <stdlib.h>

#include "include/linkedList.h"

int has_init = 0;
linkedList_t *first = NULL;
linkedList_t *last = NULL;

int initLinkedList() {
    if(has_init) return 1;

    has_init = 1;

    first = malloc(sizeof(linkedList_t));
    first->_id = 0;
    first->next = NULL;
    first->prev = NULL;

    last = first;

    return 0;
}

linkedList_t *addElement() {
    static int n_id = 1;

    linkedList_t *new;

    if(!has_init) return NULL;

    new = malloc(sizeof(linkedList_t));
    new->_id = n_id;
    new->prev = last;
    new->next = NULL;

    last->next = new;
    last = new;

    n_id = n_id + 1;

    return new;
}

int removeElementById(int id) {
    linkedList_t *current;

    if(!has_init) return 1;

    current = findElementById(id);

    removeElement(current);

    return 0;
}

int removeElement(linkedList_t *elem) {
    if((!has_init) || (elem == NULL)) return 1;

    if(elem->prev != NULL) elem->prev->next = elem->next;
    else first = first->next;

    if(elem->next != NULL) elem->next->prev = elem->prev;
    else last = last->prev;

    free(elem);

    return 0;
}

linkedList_t *findElementById(int id) {
    linkedList_t *current;

    if(!has_init) return NULL;

    current = first;
    while(current->_id != id) {
        if(current->next == NULL) return NULL;
        else current = current->next;
    }

    return current;
}

int clearLinkedList() {
    linkedList_t *current;

    if(!has_init) return 1;

    current = first;
    while(current->next != NULL) {
        current = current->next;

        if(current->prev->data.signal != NULL) free(current->prev->data.signal);
        if(current->prev->data.gate != NULL) free(current->prev->data.gate);

        free(current->prev);
    }

    if(current->data.signal != NULL) free(current->data.signal);
    if(current->data.gate != NULL) free(current->data.gate);

    free(current);

    first = NULL;
    last = NULL;
    has_init = 0;

    return 0;
}