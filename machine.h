#ifndef MACHINE_H
#define MACHINE_H

#include <stdio.h>
#include "patient.h"

typedef struct patient Patient;
typedef struct queue_patient QueuePatient;
typedef struct machine_list MachineList;
typedef struct machine_node MachineNode;

MachineList *createMachineList();

MachineNode *createMachine(int id);

void initializeMachinesOnList(MachineList *machine_list);

void printMachines(MachineList *machine_list);

void insertPatientOnMachine(MachineList *machine_list, Patient *patient, int timestamp);

//1 to open machine, 0 to closed machine
int machine_is_available(MachineList *machine_list);

void removePatientFromMachine(MachineList *machine_list, int machine_id);

void pre_diagnosis_manager(MachineList *machine_list, int timestamp, QueuePatient *patient_queue);

Patient * machine_done(MachineList *machine_list, int timestamp);


#endif