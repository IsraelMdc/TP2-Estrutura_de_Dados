#ifndef MACHINE_H
#define MACHINE_H

#include <stdio.h>
#include "patient.h"

typedef struct patient Patient;
typedef struct queue_patient QueuePatient;
typedef struct machine_list MachineList;
typedef struct machine_node MachineNode;
typedef struct queue_exam QueueExam;

MachineList *createMachineList();

MachineNode *createMachine(int id);

void initializeMachinesOnList(MachineList *machine_list);

void printMachines(MachineList *machine_list);

void insertPatientOnMachine(MachineList *machine_list, Patient *patient, int timestamp);

//1 to open machine, 0 to closed machine
int machine_is_available(MachineList *machine_list);

Patient * removePatientFromMachine(MachineList *machine_list, int machine_id);

void movePatientToQueue(MachineList *machine_list, int machine_id, QueuePatient *new_queue, Patient *patient);

void checkExamDuration(int id_exam, QueueExam *queue_exam, MachineList *machine_list, int timestamp, QueuePatient *patient_queue, QueuePatient *q_patient_outs);

#endif