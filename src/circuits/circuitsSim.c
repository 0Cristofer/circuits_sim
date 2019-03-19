/* Digital circuits simulator implementation.
   Author: Cristofer Oswald
   Created: 19/03/2019
   Edited: 19/03/2019 */

#include <stdlib.h>

#include "../linkedList/include/linkedList.h"
#include "include/circuitsSim.h"

int updateOR(gate_t *gate);
int updateAND(gate_t *gate);
int updateXOR(gate_t *gate);
int updateNOR(gate_t *gate);
int updateNAND(gate_t *gate);

int circuit_has_init = 0;

signal_t *initCicuitsSim() {
    if(circuit_has_init) return NULL;

    initLinkedList();

    circuit_has_init = 1;

    first->data.signal = malloc(sizeof(signal_t));
    first->data.signal->signal = LOW;
    first->data.gate = NULL;

    return first->data.signal;
}

gate_t *newGate(gate_type_t type) {
    gate_t *gate;
    linkedList_t *list;

    if(!circuit_has_init) return NULL;

    gate = malloc(sizeof(gate_t));
    gate->gate_type = type;
    gate->in1 = NULL;
    gate->in2 = NULL;
    gate->out.signal = LOW;

    switch (type) {
        case OR:
            gate->update = updateOR;
            break;
        case AND:
            gate->update = updateAND;
            break;
        case XOR:
            gate->update = updateXOR;
            break;
        case NOR:
            gate->update = updateNOR;
            break;
        case NAND:
            gate->update = updateNAND;
            break;
    }

    list = addElement();
    list->data.gate = gate;
    list->data.signal = NULL;

    gate->_id = list->_id;

    return gate;
}

signal_t *newSignal() {
    signal_t *signal;
    linkedList_t *list;

    if(!circuit_has_init) return NULL;

    signal = malloc(sizeof(signal_t));
    signal->signal = LOW;

    list = addElement();
    list->data.signal = signal;
    list->data.gate = NULL;

    signal->_id = list->_id;

    return signal;
}

int removeGate(gate_t *gate) {
    if(!circuit_has_init) return 1;

    removeElementById(gate->_id);
    free(gate);

    return 0;
}

int removeSignal(signal_t *signal) {
    if(!circuit_has_init) return 1;

    removeElementById(signal->_id);
    free(signal);

    return 0;
}

int runCircuit() {
    int has_changed;
    linkedList_t *current;

    if(!circuit_has_init) return 1;

    has_changed = 1;

    while(has_changed) {
        has_changed = 0;
        current = first;

        while(current != NULL) {
            if(current->data.gate != NULL) {
                if(current->data.gate->update(current->data.gate)) {
                    has_changed = 1;
                }
            }

            current = current->next;
        }
    }

    return 0;
}

int clearCircuit() {
    if(!circuit_has_init) return 1;

    clearLinkedList();
    return 0;
}

int updateOR(gate_t *gate) {
    signal_t prev_out;

    prev_out = gate->out;
    gate->out.signal = (gate->in1)->signal | (gate->in2)->signal;

    return prev_out.signal != gate->out.signal;
}

int updateAND(gate_t *gate) {
    signal_t prev_out;

    prev_out = gate->out;
    gate->out.signal = (gate->in1)->signal & (gate->in2)->signal;

    return prev_out.signal != gate->out.signal;
}

int updateXOR(gate_t *gate) {
    signal_t prev_out;

    prev_out = gate->out;
    gate->out.signal = (gate->in1)->signal ^ (gate->in2)->signal;

    return prev_out.signal != gate->out.signal;
}

int updateNOR(gate_t *gate) {
    signal_t prev_out;

    prev_out = gate->out;
    gate->out.signal = !((gate->in1)->signal | (gate->in2)->signal);

    return prev_out.signal != gate->out.signal;
}

int updateNAND(gate_t *gate) {
    signal_t prev_out;

    prev_out = gate->out;
    gate->out.signal = !((gate->in1)->signal & (gate->in2)->signal);

    return prev_out.signal != gate->out.signal;
}