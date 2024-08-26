#include "patient.h"
#include "machine.h"
#include "exam.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Definition of the Patient structure
struct patient
{
   int id;           // Unique identifier for the patient
   char name[100];   // Name of the patient
   int timestamp;    // Timestamp of the patient's arrival
};

// Definition of the QueuePatient structure
struct queue_patient
{
   QueueNodePatient *front; // Pointer to the front of the queue
   QueueNodePatient *rear;  // Pointer to the rear of the queue
};

// Definition of a node in the patient queue
struct queue_node_patient
{
   Patient *patient;       // Pointer to the patient data
   QueueNodePatient *next; // Pointer to the next node in the queue
};

// Definition of the createQueue function
QueuePatient *q_patient_create()
{
   QueuePatient *q = (QueuePatient *)malloc(sizeof(QueuePatient)); // Allocate memory for the queue structure
   q->front = q->rear = NULL; // Initialize the front and rear pointers to NULL, indicating an empty queue
   return q;
}

// Definition of the enqueue function
void q_enqueue(QueuePatient *q, Patient *patient)
{
   QueueNodePatient *node = (QueueNodePatient *)malloc(sizeof(QueueNodePatient)); // Allocate memory for a new node
   node->patient = patient; // Set the data for the new node
   node->next = NULL; // Set the next pointer of the new node to NULL
    
   if (q->rear == NULL) // If the queue is empty
   {
      q->front = node; // Set the front pointer to the new node
      q->rear = node;  // Set the rear pointer to the new node
   }
   else // If the queue is not empty
   {
      q->rear->next = node; // Add the new node to the end of the queue
      q->rear = node;       // Update the rear pointer
   }
}

// Definition of the dequeue function
Patient *patient_dequeue(QueuePatient *q)
{
   assert(!q_is_empty(q)); // Ensure the queue is not empty

   Patient *patient = q->front->patient; // Store the patient data from the front of the queue

   QueueNodePatient *temp = q->front; // Store the front node of the queue

   if (q->front != q->rear) // If there is more than one node in the queue
   {
      q->front = q->front->next; // Update the front pointer
   }
   else // If the queue has only one node
   {
      q->front = q->rear = NULL; // Set both front and rear pointers to NULL
   }
   
   free(temp); // Free the memory allocated for the front node
   return patient; // Return the patient data that was dequeued
}

// Definition of the printQueue function
void q_print(QueuePatient *q)
{
   assert(q != NULL); // Ensure the queue is not NULL
   printf("Queue contents:\n");
   QueueNodePatient *p = q->front;
   
   while (p != NULL) // Traverse the queue
   {
      printf("Patient ID: %d, Name: %s, Timestamp: %d\n", p->patient->id, p->patient->name, p->patient->timestamp);
      p = p->next; // Move to the next node
   }
}

// Definition of the patient_writer function
void pacient_writer(Patient *patient)
{
   assert(patient != NULL); // Ensure the patient is not NULL

   char *filename = "db_patient.txt"; // File to write patient data

   // Open the file for writing
   FILE *fp = fopen(filename, "a");
   if (fp == NULL)
   {
      printf("Error opening the file %s", filename); // Error message if file cannot be opened
      return;
   }
   // Write patient data to the file
   fprintf(fp, "Patient ID: %d, Name: %s, Timestamp: %d\n", patient->id, patient->name, patient->timestamp);

   // Close the file
   fclose(fp);
}

// Definition of the createPatient function
Patient* createPatient(int id, int timestamp)
{   
   Patient* patient = (Patient*)malloc(sizeof(Patient)); // Allocate memory for the new patient
   assert(patient != NULL); // Ensure memory allocation was successful

   char *name_patient = gen_name(); // Generate a name for the patient
   patient->id = id; 
   strncpy(patient->name, name_patient, sizeof(patient->name) - 1); // Copy the name to the patient structure
   patient->name[sizeof(patient->name) - 1] = '\0'; // Null-terminate the name

   patient->timestamp = timestamp; // Set the timestamp
   return patient;
}

// Definition of the patient_Creation function
int patient_Creation(int id, int timestamp, QueuePatient *q_patient)
{
   int patient_arrival = gen_randint(1, 100); // Generate a random integer to determine if a patient arrives
   if (patient_arrival >= 80) // If the generated number indicates patient arrival
   {
      Patient *patient = createPatient(id, timestamp); // Create a new patient
      id++; // Increment the patient ID
      pacient_writer(patient); // Write patient data to a file
      q_enqueue(q_patient, patient); // Enqueue the patient
   }
   return id; // Return the updated patient ID
}

// Definition of the gen_name function
char* gen_name()
{
   char* name = (char*)malloc(100 * sizeof(char)); // Allocate memory for the name string

   // Arrays of possible first and last names
   char *first[] = {"John", "Jane", "Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Henry"};
   char *last[] = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor"};

   strcpy(name, first[rand() % 10]); // Select a random first name
   strcat(name, " "); // Add a space
   strcat(name, last[rand() % 10]); // Add a random last name

   return name; // Return the generated name
}

// Definition of the gen_randint function
int gen_randint(int initial_number, int final_number)
{
   return initial_number + rand()%(final_number - initial_number + 1); // Generate a random integer in the specified range
}

// Definition of the q_is_empty function
int q_is_empty(QueuePatient *q)
{
   return q->front == NULL; // Check if the queue is empty
}

// Definition of the print_queue_front function
void print_queue_front(QueuePatient *q)
{
   assert(q != NULL); // Ensure the queue is not NULL
   printf("Patient ID: %d, Name: %s, Timestamp: %d\n", q->front->patient->id, q->front->patient->name, q->front->patient->timestamp); // Print the front patient
}

// Definition of the print_patient function
void print_patient(Patient *patient)
{
   printf("Patient ID: %d, Name: %s, Timestamp: %d\n", patient->id, patient->name, patient->timestamp); // Print patient details
}

// Definition of the destroyPatientQueue function
void destroyPatientQueue(QueuePatient *q)
{
   while (!q_is_empty(q)) // While the queue is not empty
   {
      patient_dequeue(q); // Dequeue each patient
   }
   free(q); // Free the queue memory //
}
