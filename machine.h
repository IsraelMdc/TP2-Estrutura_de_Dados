#ifndef MACHINE_H
#define MACHINE_H

#include <stdio.h>
#include "patient.h"

// Forward declarations of structures used in the functions
typedef struct patient Patient; // Forward declaration of the Patient structure
typedef struct queue_patient QueuePatient; // Forward declaration of the QueuePatient structure
typedef struct machine_list MachineList; // Forward declaration of the MachineList structure
typedef struct machine_node MachineNode; // Forward declaration of the MachineNode structure
typedef struct queue_exam QueueExam; // Forward declaration of the QueueExam structure
typedef struct exam_priority_queue ExamPriorityQueue; // Forward declaration of the ExamPriorityQueue structure

// Function prototypes

// Create a new MachineList and return a pointer to it//
MachineList *createMachineList();

// Create a new MachineNode with the given ID and return a pointer to it
MachineNode *createMachine(int id);

// Initialize the machine list with a set of machines
void initializeMachinesOnList(MachineList *machine_list);

// Print the details of all machines in the list
void printMachines(MachineList *machine_list);

// Assign a patient to an available machine in the list
void insertPatientOnMachine(MachineList *machine_list, Patient *patient, int timestamp);

// Check if there is any available machine in the list
// Returns 1 if a machine is available, 0 if no machine is available
int machine_is_available(MachineList *machine_list);

// Remove a patient from the specified machine and return the patient pointer
Patient *removePatientFromMachine(MachineList *machine_list, int machine_id);

// Check the duration of exams and create new exams if needed
void checkExamDuration(ExamPriorityQueue *exam_priority_queue, MachineList *machine_list, int timestamp, QueuePatient *patient_queue);

// Free all resources used by the machine list
void destroyMachineList(MachineList *machine_list);

#endif
