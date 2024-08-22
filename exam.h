#ifndef EXAM_H
#define EXAM_H

typedef struct exam Exam;
typedef struct queue_node_exam QueueNodeExam;
typedef struct queue_exam QueueExam;

void exam_condition(Exam *exam);

Exam* createExam(int id, int machine_id, int patient_id,  int timestamp);

void q_exam_enqueue(QueueExam *q, Exam *exam);

QueueExam *q_exam_create();

Exam *q_exam_dequeue(QueueExam *q);

int exam_creation(QueueExam *queue_exam, int id, int machine_id, int patient_id,  int timestamp);

int q_is_empty_exam(QueueExam *q);

#endif
