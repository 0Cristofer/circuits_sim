/* Digital circuits simulator main header.
   Author: Cristofer Oswald
   Created: 19/03/2019
   Edited: 19/03/2019 */

#ifndef CIRUITS_SIM_CIRCUITSSIM_H
#define CIRUITS_SIM_CIRCUITSSIM_H

typedef enum gate_type gate_type_t;
typedef enum signal_state signal_state_t;
typedef struct signal signal_t;
typedef struct gate gate_t;

/**
 * Possible gate types.
 */
enum gate_type {
    OR, AND, XOR, NOR, NAND
};

/**
 * Possible signal states.
 */
enum signal_state {
    LOW = 0, HIGH
};

/**
 * A user made signal.
 */
struct signal {
    int _id;

    signal_state_t signal;
};

/**
 * A 2 in 1 out gate. Inputs must come from an existing signal and the output is updated according when ran.
 */
struct gate {
    int _id;

    gate_type_t gate_type;
    signal_t *in1, *in2;
    signal_t out;

    int (*update) (gate_t *);
};

extern int circuit_has_init;

/**
 * Initiates the structures for the simulator. Must be ran first and only once.
 * On success, returns a reference to the first signal.
 * @return A reference to a signal, else NULL.
 */
signal_t *initCicuitsSim();

/**
 * Creates a new gate of given type and returns it to the user.
 * @param type Type of the new gate.
 * @return A reference to the new gate or NULL on failure.
 */
gate_t *newGate(gate_type_t type);

/**
 * Creates a new signal.
 * @return A reference to the new signal or NULL on failure.
 */
signal_t *newSignal();

/**
 * Removes a gate from the circuit and frees the gate. It does not modify other data.
 * @param gate Gate to be removed.
 * @return 0 on success, else 1.
 */
int removeGate(gate_t *gate);

/**
 * Removes a signal from the circuit and frees the signal. It does not modify other data.
 * @param signal Signal to be removed.
 * @return 0 on success, else 1.
 */
int removeSignal(signal_t *signal);

/**
 * Runs until all signals are stable.
 * WARNING: Running a circuit with unassigned gate ports (inputs/outputs) leads to undefined behavior.
 * @return 0 on success, else 1.
 */
int runCircuit();

/**
 * Resets all data used by the circuit, freeing all memory used.
 * Must be called at the end of use.
 * If called, initCircuitsSim() must be called again to use the simulator.
 * If the circuit was not initialized, it fails.
 * @return On success 0, else 1.
 */
int clearCircuit();

#endif //CIRUITS_SIM_CIRCUITSSIM_H
