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

struct exam_node_priority_queue{
    Exam *exam;
    ExamNodePriorityQueue *next;

};
struct exam_priority_queue
{
    ExamNodePriorityQueue *front;
    ExamNodePriorityQueue *rear;
};

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

ExamPriorityQueue *createExamPriorityQueue()
{
    ExamPriorityQueue *queue = (ExamPriorityQueue *)malloc(sizeof(ExamPriorityQueue)); // Allocate memory for the priority queue structure.
    queue->front = NULL; // Initialize the front pointer to NULL, indicating an empty queue.
    return queue;
}

void enqueueExamPriorityQueue(ExamPriorityQueue *queue, Exam *exam)
{
    ExamNodePriorityQueue *node = (ExamNodePriorityQueue *)malloc(sizeof(ExamNodePriorityQueue)); // Allocate memory for the new node.
    node->exam = exam; // Set the data for the new node.
    node->next = NULL; // Set the next pointer for the new node to NULL.

    if (queue->front == NULL) // If the queue is empty, set the front pointer to the new node.
    {
        queue->front = node;
    }
    else // Otherwise, find the appropriate position to insert the new node based on the exam's gravity.
    {
        ExamNodePriorityQueue *current = queue->front;
        ExamNodePriorityQueue *previous = NULL;

        while (current != NULL && current->exam->gravidade >= exam->gravidade)
        {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) // If the new node has the highest gravity, insert it at the front of the queue.
        {
            node->next = queue->front;
            queue->front = node;
        }
        else // Otherwise, insert the new node after the previous node.
        {
            node->next = previous->next;
            previous->next = node;
        }
    }
}

Exam *dequeueExamPriorityQueue(ExamPriorityQueue *q)
{
    assert(!isEmptyExamPriorityQueue(q));

    Exam *exam = q->front->exam; // Store the exam data from the front of the queue.

    ExamNodePriorityQueue *temp = q->front; // Store the front node of the queue.

    if(q->front != q->rear) // If the front and rear pointers arent equal, there is more than one node in the queue.
    {
        q->front = q->front->next;   
    }

    else // Otherwise, update the front pointer to the next node in the queue.
    { 
        q->front = q->rear = NULL; // Set both the front and rear pointers to NULL to indicate an empty queue.
    }

    free(temp); // Free the memory allocated for the front node.
    return exam; 
}

int isEmptyExamPriorityQueue(ExamPriorityQueue *queue)
{
    return queue->front == NULL;
}

void exam_creation( ExamPriorityQueue *exam_priority_queue, int exam_id, int machine_id, int patient_id,  int timestamp){


    Exam *exam = createExam(exam_id, machine_id, patient_id, timestamp);
    exam_id++;
    exam_writer(exam);
    enqueueExamPriorityQueue(exam_priority_queue, exam);
}

char *get_exam_condition(Exam *exam)
{
    return exam->condition_IA;
}

int get_exam_id(Exam *exam)
{
    return exam->exam_id;
}

int get_exam_timestamp(Exam *exam)
{
    return exam->timestamp;
}

void exam_condition(Exam *exam)
{
    int chance = gen_randint(1, 100);

    if (chance <= 30) {
        strcpy(exam->condition_IA, "Saude Normal");
        exam->gravidade = 1;
    } 

    else if (chance > 30 && chance <= 50) 
    {
        strcpy(exam->condition_IA, "Bronquite");
        exam->gravidade = 2;
    }

    else if (chance > 50 && chance <= 60) 
    {
        strcpy(exam->condition_IA, "Pneumonia");
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
int get_exam_priority_queue_size(ExamPriorityQueue *q)
{
    assert(q != NULL);
    int size = 0;
    ExamNodePriorityQueue *current = q->front;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

void q_print_exam(ExamPriorityQueue *q)
{   
    assert(q != NULL);
    printf("Queue contents:\n");
    ExamNodePriorityQueue *current = q->front;
    while (current != NULL)
    {
        printf("Exam id %d, Machine id %d, Patient id %d, Condition %s, Timestamp %d, Gravidade %d\n", current->exam->exam_id, current->exam->machine_id, current->exam->patient_id, current->exam->condition_IA, current->exam->timestamp, current->exam->gravidade);
        current = current->next;
    }
}

void exam_writer(Exam *exam)
{
   assert(exam != NULL);

   char *filename = "db_exam.txt";

   // open the file for writing
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return;
    }
    // write to the text file
    fprintf(fp,"Exam id %d, Machine id %d, Patient id %d, Condition %s, Timestamp %d, Gravidade %d\n", exam->exam_id, exam->machine_id, exam->patient_id, exam->condition_IA, exam->timestamp, exam->gravidade);

    // close the file
    fclose(fp);

}
