/* Digital circuits simulator linked list implementation.
   Author: Cristofer Oswald
   Created: 19/03/2019
   Edited: 19/03/2019 */

#ifndef CIRUITS_SIM_LINKEDLIST_H
#define CIRUITS_SIM_LINKEDLIST_H

#include "../../circuits/include/circuitsSim.h"

typedef struct linkedList linkedList_t;
typedef struct data data_t;

/**
 * The list can hold a signal or a gate.
 */
struct data {
    signal_t *signal;
    gate_t *gate;
};

/**
 * Main structure of the linked list. Holds information about its neighbours and the data itself.
 */
struct linkedList {
    int _id;

    data_t data;

    linkedList_t *next;
    linkedList_t *prev;
};

extern int has_init;
extern linkedList_t *first;
extern linkedList_t *last;

/**
 * Initiates the linked list structure. Must be called before using the linked list.
 * If a list was already initiated, does nothing and fails.
 * @return 0 on success, 1 on fail.
 */
int initLinkedList();

/**
 * Adds a new element to the end of the list. If the list was not
 * initialized, it fails.
 * @return The newly created element, or NULL on fail.
 */
linkedList_t *addElement();

/**
 * Removes an element from the list by its ID. If the ID does not exists or the list was not
 * initialized, it fails.
 * @param id The ID of the element to be removed.
 * @return 0 on success, 1 on fail.
 */
int removeElementById(int id);

/**
 * Removes an element from the list by its reference. If the element is NULL or the list was not
 * initialized, it fails.
 * @param elem The element to be removed.
 * @return On success, 0, else 1.
 */
int removeElement(linkedList_t *elem);

/**
 * Finds an element by its ID. If the list was not
 * initialized, it fails.
 * @param id The ID to be found.
 * @return On success, a reference to the element, else NULL.
 */
linkedList_t *findElementById(int id);

/**
 * Resets all data used by the list, freeing all memory used.
 * Must be called at the end of use.
 * If called, initLinkedList() must be called again to use the list.
 * If the list was not nitialized, it fails.
 * @return On success 0, else 1.
 */
int clearLinkedList();

#endif //CIRUITS_SIM_LINKEDLIST_H
