#include "machine.h"
#include "patient.h"
#include "exam.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct machine_list
{
    MachineNode *first;
};

struct machine_node
{
    int id_machine;
    int is_occupied;
    int machine_timestamp;
    Patient *machine_patient;
    MachineNode *next;
};

struct patient
{
    int id;
    char name[100];
    int timestamp;   
};



MachineNode *createMachine(int id)
{
    MachineNode *machine_node = (MachineNode *)malloc(sizeof(MachineNode));
    machine_node->id_machine = id;
    machine_node->is_occupied = 0;
    machine_node->machine_patient = NULL;
    machine_node->next = NULL;
    
    return machine_node;
}

MachineList *createMachineList()
{   
    MachineList *machine_list = (MachineList *)malloc(sizeof(MachineList));
    machine_list->first = NULL;
    return machine_list;
}

void initializeMachinesOnList(MachineList *machine_list)
{
    for (int i = 5; i > 0; --i)
    {
        MachineNode *machine_node = createMachine(i);
        machine_node->next = machine_list->first;
        machine_list->first = machine_node;
    }
}

void printMachines(MachineList *machine_list)
{
    MachineNode *current = machine_list->first;

    while (current != NULL)
    {
        printf("Machine ID: %d\n", current->id_machine);
        printf("Machine is occupied: %d\n", current->is_occupied);
        printf("Machine timestamp: %d\n", current->machine_timestamp);
        printf("Machine patient: %d\n", current->machine_patient->id);
        printf("Machine patient name: %s\n", current->machine_patient->name);
        printf("\n --------------");
        
        current = current->next;    
    }
}

void insertPatientOnMachine(MachineList *machine_list, Patient *patient, int timestamp)
{
    MachineNode *current = machine_list->first;
    while (current != NULL)
    {
        if (current->is_occupied == 0)
        {
            current->is_occupied = 1;
            current->machine_timestamp = timestamp;
            current->machine_patient = patient;
            
            break;
        }

        current = current->next;
    }
}

int machine_is_available(MachineList *machine_list)
{
    MachineNode *current = machine_list->first;
    while (current != NULL)
    {
        if (current->is_occupied == 0)
        {
            
            return current->id_machine;
        }
        current = current->next;
    }

    
    return 0;
}

Patient *removePatientFromMachine(MachineList *machine_list, int machine_id)
{
    MachineNode *current = machine_list->first;
    

    while (current != NULL)
    {
        if (current->id_machine == machine_id)
        {
            current->is_occupied = 0;
            current->machine_timestamp = 0;
            Patient *patient = current->machine_patient;
            current->machine_patient = NULL;
            
            if (patient != NULL)
            {
                return patient;
            }
            
            else
            {
                break;
            }

        }

        current = current->next;
    }
    
    return NULL;
}

void checkExamDuration(int id_exam, QueueExam *queue_exam, MachineList *machine_list, int timestamp, QueuePatient *patient_queue, QueuePatient *q_patient_outs)
{
    MachineNode *current = machine_list->first;
    while (current != NULL)
    {
        if (current->is_occupied == 1 && timestamp >= current->machine_timestamp + 10)
        {
            printf("Exam finished for patient %s arrived %d at machine %d out at %d\n", current->machine_patient->name,current->machine_timestamp, current->id_machine, timestamp);
            Patient *removed_patient = removePatientFromMachine(machine_list, current->id_machine);

            id_exam = exam_creation(queue_exam, id_exam, current->id_machine, removed_patient->id, timestamp);

            q_enqueue(q_patient_outs, removed_patient);

            movePatientToQueue(machine_list, current->id_machine, q_patient_outs, removed_patient);
        }
        current = current->next;
    }
};

void movePatientToQueue(MachineList *machine_list, int machine_id, QueuePatient *new_queue, Patient *patient)
{
    MachineNode *current = machine_list->first;
    while (current != NULL)
    {
        if (current->id_machine == machine_id)
        {
            current->is_occupied = 0;
            current->machine_timestamp = 0;
            current->machine_patient = NULL;
            break;
        }

        current = current->next;
    }
}