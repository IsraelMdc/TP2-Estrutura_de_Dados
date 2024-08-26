#include <assert.h>       // For the assert function to handle runtime assertions
#include <stdio.h>        // For input and output functions (e.g., printf, fprintf)
#include <stdlib.h>       // For memory allocation and deallocation functions (e.g., malloc, free)
#include <string.h>       // For string manipulation functions (e.g., strcpy)
#include "exam.h"         // Header file defining the Exam structure and related functions
#include "machine.h"      // Header file defining functions related to machines
#include "patient.h"      // Header file defining functions related to patients

// Define the structure for an exam
struct exam {
    int exam_id;           // Unique identifier for the exam
    int machine_id;        // ID of the machine used for the exam
    int patient_id;        // ID of the patient undergoing the exam
    char condition_IA[20]; // Condition diagnosed by the exam
    int timestamp;         // Timestamp when the exam was conducted
    int gravidade;         // Severity of the condition
};

// Define a node for the priority queue that stores exams
struct exam_node_priority_queue {
    Exam *exam;                      // Pointer to the Exam structure
    ExamNodePriorityQueue *next;    // Pointer to the next node in the queue
};

// Define the priority queue for storing exams
struct exam_priority_queue {
    ExamNodePriorityQueue *front;  // Pointer to the front of the queue
    ExamNodePriorityQueue *rear;   // Pointer to the rear of the queue
};

// Create a new Exam instance
Exam* createExam(int id, int machine_id, int patient_id, int timestamp) {
    Exam* exam = (Exam*)malloc(sizeof(Exam)); // Allocate memory for a new Exam

    exam->exam_id = id;
    exam->machine_id = machine_id;
    exam->patient_id = patient_id;
    exam->timestamp = timestamp;

    assert(exam != NULL); // Ensure memory allocation was successful

    exam_condition(exam); // Set the condition and severity for the exam

    return exam;
}

// Create a new priority queue for exams
ExamPriorityQueue *createExamPriorityQueue() {
    ExamPriorityQueue *queue = (ExamPriorityQueue *)malloc(sizeof(ExamPriorityQueue)); // Allocate memory for the queue
    queue->front = NULL; // Initialize the front of the queue to NULL
    queue->rear = NULL;  // Initialize the rear of the queue to NULL
    return queue;
}

// Add an exam to the priority queue
void enqueueExamPriorityQueue(ExamPriorityQueue *queue, Exam *exam) {
    ExamNodePriorityQueue *node = (ExamNodePriorityQueue *)malloc(sizeof(ExamNodePriorityQueue)); // Allocate memory for a new node
    node->exam = exam;  // Set the exam for the new node
    node->next = NULL;  // Initialize the next pointer to NULL

    if (queue->front == NULL) { // If the queue is empty
        queue->front = node; // Set the new node as the front of the queue
        queue->rear = node;  // Set the new node as the rear of the queue
    } else {
        // Find the appropriate position to insert the new node based on the exam's severity
        ExamNodePriorityQueue *current = queue->front;
        ExamNodePriorityQueue *previous = NULL;

        while (current != NULL && current->exam->gravidade >= exam->gravidade) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) { // Insert the new node at the front if it has the highest severity
            node->next = queue->front;
            queue->front = node;
        } else {
            node->next = previous->next;
            previous->next = node;
        }
    }
}

// Remove and return an exam from the priority queue
Exam *dequeueExamPriorityQueue(ExamPriorityQueue *q) {
    assert(!isEmptyExamPriorityQueue(q)); // Ensure the queue is not empty

    Exam *exam = q->front->exam; // Get the exam at the front of the queue

    ExamNodePriorityQueue *temp = q->front; // Store the front node

    if (q->front != q->rear) { // If there are multiple nodes in the queue
        q->front = q->front->next; // Move the front pointer to the next node
    } else {
        q->front = q->rear = NULL; // If the queue is now empty, set both pointers to NULL
    }

    free(temp); // Free the memory allocated for the old front node
    return exam;
}

// Check if the priority queue is empty
int isEmptyExamPriorityQueue(ExamPriorityQueue *queue) {
    return queue->front == NULL; // Return 1 if empty, 0 otherwise
}

// Create and add a new exam to the priority queue
void exam_creation(ExamPriorityQueue *exam_priority_queue, int exam_id, int machine_id, int patient_id, int timestamp) {
    Exam *exam = createExam(exam_id, machine_id, patient_id, timestamp); // Create a new exam
    exam_id++; // Increment exam ID for future exams
    exam_writer(exam); // Write the exam details to a file
    enqueueExamPriorityQueue(exam_priority_queue, exam); // Add the exam to the priority queue
}

// Get the condition of an exam
char *get_exam_condition(Exam *exam) {
    return exam->condition_IA;
}

// Get the ID of an exam
int get_exam_id(Exam *exam) {
    return exam->exam_id;
}

// Get the timestamp of an exam
int get_exam_timestamp(Exam *exam) {
    return exam->timestamp;
}

// Set the condition and severity of an exam based on a random chance
void exam_condition(Exam *exam) {
    int chance = gen_randint(1, 100); // Generate a random integer between 1 and 100

    if (chance <= 30) {
        strcpy(exam->condition_IA, "Saude Normal");
        exam->gravidade = 1;
    } else if (chance > 30 && chance <= 50) {
        strcpy(exam->condition_IA, "Bronquite");
        exam->gravidade = 2;
    } else if (chance > 50 && chance <= 60) {
        strcpy(exam->condition_IA, "Pneumonia");
        exam->gravidade = 3;
    } else if (chance > 60 && chance <= 70) {
        strcpy(exam->condition_IA, "COVID");
        exam->gravidade = 4;
    } else if (chance > 70 && chance <= 75) {
        strcpy(exam->condition_IA, "Embolia pulmonar");
        exam->gravidade = 4;
    } else if (chance > 75 && chance <= 80) {
        strcpy(exam->condition_IA, "Derrame pleural");
        exam->gravidade = 4;
    } else if (chance > 80 && chance <= 85) {
        strcpy(exam->condition_IA, "Fibrose pulmonar");
        exam->gravidade = 5;
    } else if (chance > 85 && chance <= 90) {
        strcpy(exam->condition_IA, "Tuberculose");
        exam->gravidade = 5;
    } else {
        strcpy(exam->condition_IA, "Cancer de pulmao");
        exam->gravidade = 6;
    }
}

// Get the size of the priority queue
int get_exam_priority_queue_size(ExamPriorityQueue *q) {
    assert(q != NULL); // Ensure the queue is not NULL
    int size = 0;
    ExamNodePriorityQueue *current = q->front; // Start from the front of the queue
    while (current != NULL) {
        size++; // Increment the size count
        current = current->next; // Move to the next node
    }
    return size;
}

// Print the contents of the priority queue
void q_print_exam(ExamPriorityQueue *q) {
    assert(q != NULL); // Ensure the queue is not NULL
    printf("Queue contents:\n");
    ExamNodePriorityQueue *current = q->front; // Start from the front of the queue
    while (current != NULL) {
        // Print details of the current exam
        printf("Exam id %d, Machine id %d, Patient id %d, Condition %s, Timestamp %d, Gravidade %d\n",
               current->exam->exam_id, current->exam->machine_id, current->exam->patient_id,
               current->exam->condition_IA, current->exam->timestamp, current->exam->gravidade);
        current = current->next; // Move to the next node
    }
}

void exam_writer(Exam *exam)
{
   // Ensure that the exam pointer is not NULL
   assert(exam != NULL);

   // Define the filename for storing exam data
   char *filename = "db_exam.txt";

   // Open the file in append mode; create it if it does not exist
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        // Print an error message if the file cannot be opened
        printf("Error opening the file %s", filename);
        return;
    }
    
    // Write the exam details to the file
    fprintf(fp, "Exam id %d, Machine id %d, Patient id %d, Condition %s, Timestamp %d, Gravidade %d\n",
            exam->exam_id, exam->machine_id, exam->patient_id, exam->condition_IA, exam->timestamp, exam->gravidade);

    // Close the file after writing
    fclose(fp);
}

void destroyExamPriorityQueue(ExamPriorityQueue *q)
{
    // Ensure that the priority queue pointer is not NULL
    assert(q != NULL);
    
    // Continuously remove elements from the queue until it is empty
    while (!isEmptyExamPriorityQueue(q))
    {
        dequeueExamPriorityQueue(q);
    }
    
    // Free the memory allocated for the priority queue itself
    free(q);
}

