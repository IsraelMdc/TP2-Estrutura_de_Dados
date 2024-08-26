#include "machine.h"
#include "patient.h"
#include "exam.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Definition of the machine list structure
struct machine_list
{
    MachineNode *first; // Pointer to the first machine node in the list
};

// Definition of a machine node
struct machine_node
{
    int id_machine; // ID of the machine
    int is_occupied; // Flag to indicate if the machine is currently occupied
    int machine_timestamp; // Timestamp when the machine was occupied
    Patient *machine_patient; // Pointer to the patient currently using the machine
    MachineNode *next; // Pointer to the next machine node in the list
};

// Definition of a patient
struct patient
{
    int id; // Patient ID
    char name[100]; // Patient name
    int timestamp; // Timestamp of patient arrival
};

// Create a new machine node with the given ID
MachineNode *createMachine(int id)
{
    MachineNode *machine_node = (MachineNode *)malloc(sizeof(MachineNode));
    machine_node->id_machine = id; // Set the machine ID
    machine_node->is_occupied = 0; // Initialize as not occupied
    machine_node->machine_patient = NULL; // No patient assigned initially
    machine_node->next = NULL; // Initialize the next pointer to NULL
    
    return machine_node;
}

// Create a new machine list
MachineList *createMachineList()
{   
    MachineList *machine_list = (MachineList *)malloc(sizeof(MachineList));
    machine_list->first = NULL; // Initialize the list as empty
    return machine_list;
}

// Initialize the machine list with a set of machines
void initializeMachinesOnList(MachineList *machine_list)
{
    for (int i = 5; i > 0; --i)
    {
        MachineNode *machine_node = createMachine(i); // Create a new machine node
        machine_node->next = machine_list->first; // Insert it at the beginning of the list
        machine_list->first = machine_node; // Update the first pointer to the new node
    }
}

// Print the details of all machines in the list
void printMachines(MachineList *machine_list)
{
    MachineNode *current = machine_list->first; // Start at the first node

    while (current != NULL)
    {
        // Print the details of the current machine node
        printf("Machine ID: %d\n", current->id_machine);
        printf("Machine is occupied: %d\n", current->is_occupied);
        printf("Machine timestamp: %d\n", current->machine_timestamp);
        printf("Machine patient: %d\n", current->machine_patient ? current->machine_patient->id : -1);
        printf("Machine patient name: %s\n", current->machine_patient ? current->machine_patient->name : "None");
        printf("\n --------------");
        
        current = current->next; // Move to the next node    
    }
}

// Assign a patient to an available machine in the list
void insertPatientOnMachine(MachineList *machine_list, Patient *patient, int timestamp)
{
    MachineNode *current = machine_list->first; // Start at the first node
    while (current != NULL)
    {
        if (current->is_occupied == 0) // Find an available machine
        {
            current->is_occupied = 1; // Mark the machine as occupied
            current->machine_timestamp = timestamp; // Set the timestamp
            current->machine_patient = patient; // Assign the patient to the machine
            
            break; // Exit the loop once a machine is found
        }

        current = current->next; // Move to the next node
    }
}

// Find the ID of an available machine
int machine_is_available(MachineList *machine_list)
{
    MachineNode *current = machine_list->first; // Start at the first node
    while (current != NULL)
    {
        if (current->is_occupied == 0) // Check if the machine is not occupied
        {
            return current->id_machine; // Return the ID of the available machine
        }
        current = current->next; // Move to the next node
    }

    return 0; // Return 0 if no machine is available
}

// Remove a patient from a machine and free the machine's resources
Patient *removePatientFromMachine(MachineList *machine_list, int machine_id)
{
    MachineNode *current = machine_list->first; // Start at the first node
    
    while (current != NULL)
    {
        if (current->id_machine == machine_id) // Find the machine with the given ID
        {
            current->is_occupied = 0; // Mark the machine as not occupied
            current->machine_timestamp = 0; // Reset the timestamp
            Patient *patient = current->machine_patient; // Store the patient
            current->machine_patient = NULL; // Remove the patient from the machine
            
            return patient; // Return the removed patient
        }

        current = current->next; // Move to the next node
    }
    
    return NULL; // Return NULL if no patient is found
}

// Check the duration of exams and create new exams if needed
void checkExamDuration(ExamPriorityQueue *exam_priority_queue, MachineList *machine_list, int timestamp, QueuePatient *patient_queue)
{
    MachineNode *current = machine_list->first; // Start at the first node
    while (current != NULL)
    {
        if (current->is_occupied == 1 && timestamp >= current->machine_timestamp + 10) // Check if the exam duration is over
        {
            Patient *removed_patient = removePatientFromMachine(machine_list, current->id_machine); // Remove the patient from the machine

            // Create a new exam with the removed patient details
            exam_creation(exam_priority_queue, removed_patient->id, current->id_machine, removed_patient->id, timestamp);
        }
        current = current->next; // Move to the next node
    }
};

// Free all resources used by the machine list
void destroyMachineList(MachineList *machine_list)
{
    MachineNode *current = machine_list->first; // Start at the first node
    while (current != NULL)
    {
        MachineNode *temp = current; // Store the current node
        current = current->next; // Move to the next node
        free(temp); // Free the stored node
    }
    free(machine_list); // Free the machine list itself
};
