#ifndef PATIENT_H
#define PATIENT_H

typedef struct patient Patient;
typedef struct queue_patient QueuePatient;
typedef struct queue_node_patient QueueNodePatient;

Patient* createPatient(int id, const char* name, int timestamp);

QueuePatient *q_create();

QueuePatient *q_enqueue(QueuePatient *q, Patient *patient);

Patient* q_dequeue(QueuePatient *q);

int q_is_empty(QueuePatient *q);

void q_print(QueuePatient *q);

#endif  





