/* Digital circuits simulator
   Author: Cristofer Oswald
   Created: 19/03/2019
   Edited: 19/03/2019 */

#include <stdio.h>

#include "circuits/include/circuitsSim.h"

int main() {
    signal_t *in1, *in2, *cin, *cout, *out;
    gate_t *and1, *and2, *xor1, *xor2, *or;

    printf("Simulando somador de 1 bit\n");

    cin = initCicuitsSim();
    in1 = newSignal();
    in2 = newSignal();

    xor1 = newGate(XOR);
    xor2 = newGate(XOR);

    and1 = newGate(AND);
    and2 = newGate(AND);

    or = newGate(OR);

    in1->signal = HIGH;
    in2->signal = HIGH;
    cin->signal = HIGH;

    xor1->in1 = in1;
    xor1->in2 = in2;

    and1->in1 = in1;
    and1->in2 = in2;

    and2->in1 = &(xor1->out);
    and2->in2 = cin;

    xor2->in1 = &(xor1->out);
    xor2->in2 = cin;

    or->in1 = &(and1->out);
    or->in2 = &(and2->out);

    out = &(xor2->out);
    cout = &(or->out);

    runCircuit();

    printf("Entrada: in1: %d, in2: %d, cin: %d\n", in1->signal, in2->signal, cin->signal);
    printf("Saída: out: %d, cout: %d\n", out->signal, cout->signal);

    clearCircuit();

    return 0;
}