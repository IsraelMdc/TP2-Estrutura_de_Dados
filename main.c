#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "machine.h"

int main()
{
    int timestamp = 1;
    int id = 0;
    
    MachineList *machine_list = createMachineList();
    initializeMachinesOnList(machine_list);

    

    while (timestamp < 6)
    {

        QueuePatient *q = q_create();
        id++;
        Patient *patient = createPatient(id, timestamp);
        pacient_writer(patient);

        insertPatientOnMachine(machine_list, patient, timestamp);

        q_enqueue(q, patient);

        q_print(q); 

        
        timestamp++;
    }
    printMachines(machine_list);

}