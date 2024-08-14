#include <stdio.h>
#include <stdlib.h>
#include "patient.h"

int main()
{
    int timestamp = 1;
    int id = 0;

    while (timestamp < 10)
    {
 
        char* name = gen_name();

        QueuePatient *q = q_create();
        id++;
        Patient *patient = createPatient(id, timestamp);
        pacient_writer(patient);

        q_enqueue(q, patient);

        q_print(q); 

        
        timestamp++;
    }
    

}