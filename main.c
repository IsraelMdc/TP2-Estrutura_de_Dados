#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "machine.h"
#include "aux.h"

int main()
{
    int timestamp = 1;
    int id = 1;


    MachineList *machine_list = createMachineList();
    initializeMachinesOnList(machine_list);

    QueuePatient *q = q_create();

    while (timestamp < 7)
    {
        int patient_arrival = gen_randit(1, 5);
        
        if (patient_arrival == 1)
        {
            Patient *patient = createPatient(id, timestamp);
            pacient_writer(patient);
            q_enqueue(q, patient);
            
            q_print(q);
            printf("\n--------------------------------");  

            id++;          
        }

        timestamp++;
    }
    printMachines(machine_list);

}