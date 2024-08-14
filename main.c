#include <stdio.h>
#include "patient.h"

int main()
{
    int timestamp = 0;

    QueuePatient *q = q_create();

    Patient *patient = createPatient(1, "John Doe", timestamp );

    QueuePatient *q_enqueue(QueuePatient *q, Patient *patient);


    q_print(q);

}