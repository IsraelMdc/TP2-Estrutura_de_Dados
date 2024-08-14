#include "patient.h"
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

QueuePatient *q_enqueue(QueuePatient *q, Patient *patient)
{
   QueueNodePatient *node = (QueueNodePatient *)malloc(sizeof(QueueNodePatient)); // Allocate memory for the new node.
   node->patient = patient; // Set the data for the new node.
   node->next = NULL; // Set the next pointer for the new node to NULL.
    
   if (q->rear == NULL) // If the queue is empty, set both the front and rear pointers to the new node.
   {
      q->front = q->rear = node;
   }
   else // Otherwise, add the new node to the end of the queue and update the rear pointer.
   {
      q->rear->next = node;
      q->rear = node;
   }

   return q;
}

// Function to dequeue and return a float value from the queue.
Patient* q_dequeue(QueuePatient *q)
{
   assert(!q_is_empty(q));

   Patient *patient = q->front->patient;
   QueueNodePatient *p = q->front; // Store for removal

   if (q->front != q->rear)
      q->front = q->front->next;
   else
      q->front = q->rear = NULL;

   free(p);
   return patient;
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

Patient* createPatient(int id, const char* name, int timestamp)
{   
    Patient* patient = (Patient*)malloc(sizeof(Patient));
    
    assert(patient != NULL);

    patient->id = id;

    strncpy(patient->name, name, sizeof(patient->name) - 1);

    patient->name[sizeof(patient->name) - 1] = '\0';
    patient->timestamp = timestamp;

    return patient;
}


