#ifndef EXAM_H
#define EXAM_H

typedef struct exam Exam;
typedef struct queue_node_exam QueueNodeExam;
typedef struct queue_exam QueueExam;
typedef struct exam_priority_queue ExamPriorityQueue;
typedef struct exam_node_priority_queue ExamNodePriorityQueue;

Exam* createExam(int id, int machine_id, int patient_id,  int timestamp);

ExamPriorityQueue *createExamPriorityQueue();

void enqueueExamPriorityQueue(ExamPriorityQueue *queue, Exam *exam);

Exam *dequeueExamPriorityQueue(ExamPriorityQueue *queue);

int isEmptyExamPriorityQueue(ExamPriorityQueue *queue);

void exam_creation( ExamPriorityQueue *exam_priority_queue, int exam_id, int machine_id, int patient_id,  int timestamp);

char *get_exam_condition(Exam *exam);

int get_exam_id(Exam *exam);

void exam_condition(Exam *exam);

void q_print_exam(ExamPriorityQueue *q);

void exam_writer(Exam *exam);

// QueueExam *q_exam_create();

// void q_exam_enqueue(QueueExam *q, Exam *exam);

// Exam *q_exam_dequeue(QueueExam *q);

// int q_is_empty_exam(QueueExam *q);

#endif
