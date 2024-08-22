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
        
        int patient_arrival = gen_randint(1, 100);
        // printf("Patient arrival chance: %d\n", patient_arrival);
        if (patient_arrival >= 80)
        {
            Patient *patient = createPatient(id, timestamp);
            id++; 
            pacient_writer(patient);
            q_enqueue(q_patient, patient);


        }
        if(!q_is_empty(q_patient)){
            if(machine_is_available(machine_list))
            {
            Patient *patient = patient_dequeue(q_patient);
            insertPatientOnMachine(machine_list, patient, timestamp);
            }
        }
        
        //pre_diagnosis_manager(machine_list, timestamp, q_patient);

        
        
                 

        timestamp++;
    }
    q_print(q_patient);
    printf("\n----------------\n");
    printMachines(machine_list);
    //print_queue_front(q_patient);

}