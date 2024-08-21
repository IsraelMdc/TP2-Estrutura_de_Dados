#ifndef PATIENT_H
#define PATIENT_H

typedef struct patient Patient;
typedef struct queue_patient QueuePatient;
typedef struct queue_node_patient QueueNodePatient;

Patient* createPatient(int id, int timestamp);

QueuePatient *q_create();

void q_enqueue(QueuePatient *q, Patient *patient);

int q_is_empty(QueuePatient *q);

void q_print(QueuePatient *q);

char* gen_name();

void pacient_writer(Patient *patient);


#endif  





