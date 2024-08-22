#ifndef PATIENT_H
#define PATIENT_H

#include <stdio.h>
#include "machine.h"


typedef struct patient Patient;
typedef struct queue_patient QueuePatient;
typedef struct queue_node_patient QueueNodePatient;
typedef struct machine_list MachineList;

Patient* createPatient(int id, int timestamp);

QueuePatient *q_create();

void q_enqueue(QueuePatient *q, Patient *patient);

int q_is_empty(QueuePatient *q);

void q_print(QueuePatient *q);

void print_patient(Patient *patient);

char* gen_name();

void pacient_writer(Patient *patient);

int gen_randint(int initial_number, int final_number);

void print_queue_front(QueuePatient *q);

Patient *patient_dequeue(QueuePatient *q);

int patient_Creation(int id, int timestamp, QueuePatient *q_patient);


#endif  





