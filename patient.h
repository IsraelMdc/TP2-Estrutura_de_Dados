#ifndef PATIENT_H
#define PATIENT_H

#include <stdio.h>
#include "machine.h"

// Forward declarations of structures
typedef struct patient Patient; // Definition for a patient structure
typedef struct queue_patient QueuePatient; // Definition for a queue of patients
typedef struct queue_node_patient QueueNodePatient; // Definition for a node in the patient queue
typedef struct machine_list MachineList; // Definition for a list of machines

// Function declarations//

// Creates a new patient with the given ID and timestamp.

Patient* createPatient(int id, int timestamp);

// Creates a new empty patient queue.

QueuePatient *q_patient_create();

// Adds a patient to the end of the queue.

void q_enqueue(QueuePatient *q, Patient *patient);

// Checks if the patient queue is empty.

int q_is_empty(QueuePatient *q);

// Prints all patients in the queue.

void q_print(QueuePatient *q);

// Prints the details of a patient.

void print_patient(Patient *patient);

// Generates a random name for a patient.

char* gen_name();

// Writes the details of a patient to a file.

void pacient_writer(Patient *patient);

// Generates a random integer within a specified range.

int gen_randint(int initial_number, int final_number);

// Prints the patient at the front of the queue.

void print_queue_front(QueuePatient *q);

// Removes and returns the patient at the front of the queue.

Patient *patient_dequeue(QueuePatient *q);

// Creates a patient based on a random chance and adds them to the queue.

int patient_Creation(int id, int timestamp, QueuePatient *q_patient);

// Frees the memory allocated for the patient queue and its nodes.

void destroyPatientQueue(QueuePatient *q);

#endif
