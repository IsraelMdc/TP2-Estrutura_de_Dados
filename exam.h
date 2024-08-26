#ifndef EXAM_H
#define EXAM_H

// Define the structure for an exam//
typedef struct exam Exam;

// Define the structure for a node in a queue of exams
typedef struct queue_node_exam QueueNodeExam;

// Define the structure for a queue of exams
typedef struct queue_exam QueueExam;

// Define the structure for a priority queue of exams
typedef struct exam_priority_queue ExamPriorityQueue;

// Define the structure for a node in a priority queue of exams
typedef struct exam_node_priority_queue ExamNodePriorityQueue;

// Function prototypes for handling exams

// Create a new Exam instance with the given parameters
Exam* createExam(int id, int machine_id, int patient_id, int timestamp);

// Create a new priority queue for exams
ExamPriorityQueue *createExamPriorityQueue();

// Add an exam to the priority queue
void enqueueExamPriorityQueue(ExamPriorityQueue *queue, Exam *exam);

// Remove and return an exam from the priority queue
Exam *dequeueExamPriorityQueue(ExamPriorityQueue *queue);

// Check if the priority queue is empty
int isEmptyExamPriorityQueue(ExamPriorityQueue *queue);

// Create and add a new exam to the priority queue
void exam_creation(ExamPriorityQueue *exam_priority_queue, int exam_id, int machine_id, int patient_id, int timestamp);

// Get the condition of an exam
char *get_exam_condition(Exam *exam);

// Get the ID of an exam
int get_exam_id(Exam *exam);

// Get the timestamp of an exam
int get_exam_timestamp(Exam *exam);

// Get the size of the priority queue
int get_exam_priority_queue_size(ExamPriorityQueue *q);

// Set the condition and severity of an exam based on a random chance
void exam_condition(Exam *exam);

// Print the contents of the priority queue
void q_print_exam(ExamPriorityQueue *q);

// Write the exam details to a file
void exam_writer(Exam *exam);

// Destroy the priority queue and free all allocated memory
void destroyExamPriorityQueue(ExamPriorityQueue *q);

#endif
