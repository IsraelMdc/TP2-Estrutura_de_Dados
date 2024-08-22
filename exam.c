#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exam.h"
#include "machine.h"
#include "patient.h"

struct exam{
    int exam_id;
    int machine_id;
    int patient_id;
    char condition_IA[20];
    int timestamp;
    int gravidade;
};

struct queue_node_exam{
    Exam *exam;
    QueueNodeExam *next;
};

struct queue_exam{
    QueueNodeExam *front;
    QueueNodeExam *rear;
};

QueueExam *q_exam_create()
{
    QueueExam *q = (QueueExam *)malloc(sizeof(QueueExam)); // Allocate memory for the queue structure.
    q->front = q->rear = NULL;                 // Initialize the front and rear pointers to NULL, indicating an empty queue.
    return q;
};

void q_exam_enqueue(QueueExam *q, Exam *exam)
{
   QueueNodeExam *node = (QueueNodeExam *)malloc(sizeof(QueueNodeExam)); // Allocate memory for the new node.

   node->exam = exam; // Set the data for the new node.
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
};

// Function to check whether the queue is empty.
int q_is_empty_exam(QueueExam *q)
{
   return q->front == NULL;
}


Exam *q_exam_dequeue(QueueExam *q)
{
   assert(!q_is_empty_exam(q));

   Exam *exam = q->front->exam; // Store the exam data from the front of the queue.

   QueueNodeExam *temp = q->front; // Store the front node of the queue.

   if(q->front != q->rear) // If the front and rear pointers arent equal, there is more than one node in the queue.
   {
      q->front = q->front->next;   }

   else // Otherwise, update the front pointer to the next node in the queue.
   {
      
      q->front = q->rear = NULL; // Set both the front and rear pointers to NULL to indicate an empty queue.

   }
   
   free(temp); // Free the memory allocated for the front node.
   return exam; // Return the exam data that was dequeued.

}

Exam* createExam(int id, int machine_id, int patient_id,  int timestamp)
{   
    Exam* exam = (Exam*)malloc(sizeof(Exam));

    exam->exam_id = id;
    exam->machine_id = machine_id;
    exam->patient_id = patient_id;
    exam->timestamp = timestamp;

    assert(exam != NULL);

    exam_condition(exam);

    return exam;
}

int exam_creation(QueueExam *queue_exam, int id, int machine_id, int patient_id,  int timestamp){

    Exam *exam = createExam( id, machine_id, patient_id, timestamp);
    id++;

    //exam_writer();
    q_exam_enqueue(queue_exam, exam);

    return id;

}

void exam_condition(Exam *exam)
{
    int chance = gen_randint(0, 100);

    if (chance <= 30) {
        strcpy(exam->condition_IA, "saude normal");
        exam->gravidade = 1;
    } 

    else if (chance > 30 && chance <= 50) 
    {
        strcpy(exam->condition_IA, "bronquite");
        exam->gravidade = 2;
    }

    else if (chance > 50 && chance <= 60) 
    {
        strcpy(exam->condition_IA, "pneumonia");
        exam->gravidade = 3;
    } 

    else if (chance > 60 && chance <= 70) 
    {
        strcpy(exam->condition_IA, "COVID");
        exam->gravidade = 4;
    } 

    else if (chance > 70 && chance <= 75) 
    {
        strcpy(exam->condition_IA, "Embolia pulmonar");
        exam->gravidade = 4;    
    }

    else if (chance > 75 && chance <= 80) 
    {
        strcpy(exam->condition_IA, "Derrame pleural");
        exam->gravidade = 4;    
    }

    else if (chance > 80 && chance <= 85) 
    {
        strcpy(exam->condition_IA, "Fibrose pulmonar");
        exam->gravidade = 5;    
    }
    
    else if (chance > 85 && chance <= 90) 
    {
        strcpy(exam->condition_IA, "Tuberculose");
        exam->gravidade = 5;    
    }
    else if (chance > 90) 
    {
        strcpy(exam->condition_IA, "Cancer de pulmao");
        exam->gravidade = 6;
    }
}