#include "machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct machine
{
    int id;
    MachineNode *front;
};

struct machine_node
{
    machine *machine;
    MachineNode *next;
};


void createMachine(int id, int timestamp)
{
    Machine *machine = (Machine *)malloc(sizeof(Machine));
    machine->id = id;
    machine->timestamp = timestamp;
    machine_writer(machine);
}



void XRMachineManager();