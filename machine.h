#ifndef MACHINE_H
#define MACHINE_H

#include "patient.h"

typedef struct machine_list MachineList;
typedef struct machine_node MachineNode;

MachineList *createMachineList();

MachineNode *createMachine(int id);

void initializeMachinesOnList(MachineList *machine_list);

void printMachines(MachineList *machine_list);

void insertPatientOnMachine(MachineList *machine_list, Patient *patient, int timestamp);

#endif