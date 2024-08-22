#include "patient.h"
#include "machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct patient
{
    int id;
    char name[100];
    int timestamp;   
};

struct queue_patient
{
   QueueNodePatient *front; // Pointer to the front of the queue.
   QueueNodePatient *rear;  // Pointer to the rear of the queue.
};

// Define a structure for a node in the linked list.
struct queue_node_patient
{
   Patient *patient; // A pointer to the data for this node.
   QueueNodePatient *next; // A pointer to the next node in the linked list.
};

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

// Function to create a new empty queue.
QueuePatient *q_create()
{
   QueuePatient *q = (QueuePatient *)malloc(sizeof(QueuePatient)); // Allocate memory for the queue structure.
   q->front = q->rear = NULL;                 // Initialize the front and rear pointers to NULL, indicating an empty queue.
   return q;
}

// Function to check whether the queue is empty.
int q_is_empty(QueuePatient *q)
{
   return q->front == NULL;
}

void q_enqueue(QueuePatient *q, Patient *patient)
{
   QueueNodePatient *node = (QueueNodePatient *)malloc(sizeof(QueueNodePatient)); // Allocate memory for the new node.
   node->patient = patient; // Set the data for the new node.
   node->next = NULL; // Set the next pointer for the new node to NULL.
    
   if (q->rear == NULL) // If the queue is empty, set both the front and rear pointers to the new node.
   {
      q->front = node;
      q->rear = node;
   }
   else // Otherwise, add the new node to the end of the queue and update the rear pointer.
   {
      q->rear->next = node;
      q->rear = node;
   }
}

void q_print(QueuePatient *q)
{
   assert(q != NULL); 
   printf("Queue contents:\n");
   QueueNodePatient *p = q->front;
   
   while (p != NULL)
   {
      printf("Patient ID: %d, Name: %s, Timestamp: %d\n", p->patient->id, p->patient->name, p->patient->timestamp);
      p = p->next;
   }
}

void pacient_writer(Patient *patient)
{
   assert(patient != NULL);

   char *filename = "db_patient.txt";

   // open the file for writing
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return;
    }
    // write to the text file
    fprintf(fp, "Patient ID: %d, Name: %s, Timestamp: %d\n", patient->id, patient->name, patient->timestamp);

    // close the file
    fclose(fp);

}

Patient* createPatient(int id, int timestamp)
{   
    Patient* patient = (Patient*)malloc(sizeof(Patient));
    assert(patient != NULL);

    char *name_patient = gen_name();
    patient->id = id;
    strncpy(patient->name, name_patient, sizeof(patient->name) - 1);
    patient->name[sizeof(patient->name) - 1] = '\0';

    patient->timestamp = timestamp;
    return patient;
}

char* gen_name()
{
   char* name = (char*)malloc(100 * sizeof(char)); // Allocate memory for the name string.

   char *first[] = {"John", "Jane", "Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Henry"};
   char *last[] = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor"};

   strcpy(name, first[rand() % 10]);
   strcat(name, " ");
   strcat(name, last[rand() % 10]);

   return name;
}


int gen_randint(int initial_number, int final_number)
{
   return initial_number + rand()%(final_number - initial_number + 1);
}


void print_queue_front(QueuePatient *q)
{
    printf("Patient ID: %d, Name: %s, Timestamp: %d\n", q->front->patient->id, q->front->patient->name, q->front->patient->timestamp);
}

void print_patient(Patient *patient)
{
   printf("Patient ID: %d, Name: %s, Timestamp: %d\n", patient->id, patient->name, patient->timestamp);
}

void d_queue_pacient_to_machine(QueuePatient *q, MachineList *machine_list, int timestamp)
{
    if (q_is_empty(q))
    {
        return;
    }

    MachineNode *current = machine_list->first;
    while (current != NULL)
    {
        if (machine_is_available(machine_list))
        {
            current->is_occupied = 1;
            current->machine_patient = q->front->patient;
            current->machine_timestamp = timestamp;
            q->front = q->front->next;
            return;
        }
        current = current->next;
    }
}

Patient *patient_dequeue(QueuePatient *q)
{
   assert(!q_is_empty(q));

   Patient *patient = q->front->patient; // Store the patient data from the front of the queue.

   QueueNodePatient *temp = q->front; // Store the front node of the queue.

   if(q->front != q->rear) // If the front and rear pointers arent equal, there is more than one node in the queue.
   {
      q->front = q->front->next;   }
   else // Otherwise, update the front pointer to the next node in the queue.
   {
      
      q->front = q->rear = NULL; // Set both the front and rear pointers to NULL to indicate an empty queue.

   }
   
   free(temp); // Free the memory allocated for the front node.
   return patient; // Return the patient data that was dequeued.


}

void d_queue(QueuePatient *q)
{
    if (q_is_empty(q))
    {
        return;
    }

    QueueNodePatient *temp = q->front;
    q->front = q->front->next;
    print_queue_front(q);
    free(temp);
}