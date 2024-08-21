#include "machine.h"
#include "patient.h"
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
    Patient *patient;
    MachineNode *next;
};


MachineNode *createMachine(int id)
{
    MachineNode *machine_node = (MachineNode *)malloc(sizeof(MachineNode));
    machine_node->id_machine = id;
    machine_node->is_occupied = 0;
    machine_node->patient = NULL;
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
    for (int i = 1; i < 6; i++)
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
        printf("\n --------------\n");
        
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
            current->patient = patient;
            break;
        }

        current = current->next;
    }
}