#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "machine.h"


int main()
{
    int timestamp = 1;
    int id = 1;

    MachineList *machine_list = createMachineList();
    initializeMachinesOnList(machine_list);

    QueuePatient *q_patient = q_create();

    while (timestamp < 100)
    {
        
        id = patient_Creation(id, timestamp, q_patient); 
        
        if(!q_is_empty(q_patient)){
            if(machine_is_available(machine_list))
            {
            Patient *patient = patient_dequeue(q_patient);
            insertPatientOnMachine(machine_list, patient, timestamp);
            }

            
        }
        
        timestamp++;
    }
    q_print(q_patient);
    printf("\n----------------\n");
    printMachines(machine_list);
    //print_queue_front(q_patient);

}