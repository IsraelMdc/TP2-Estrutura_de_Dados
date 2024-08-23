#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "machine.h"
#include "exam.h"


int main()
{
    //
    int timestamp = 1;
    int id = 1;

    // Initializing the machine linked list
    MachineList *machine_list = createMachineList();

    // Function to add the 5 machines onto the linked list
    initializeMachinesOnList(machine_list);

    // Initializing patient and exam queues
    QueuePatient *q_patient_outs = q_patient_create();
    QueuePatient *q_patient = q_patient_create();
    ExamPriorityQueue *exam_priority_queue = createExamPriorityQueue();

    // time loop of the simulation
    while (timestamp < 100)
    {
        //
        id = patient_Creation(id, timestamp, q_patient); 
        
        //
        if(!q_is_empty(q_patient))
        {
            if(machine_is_available(machine_list))
            {
            Patient *patient = patient_dequeue(q_patient);
            insertPatientOnMachine(machine_list, patient, timestamp);
            
            }
            
        }
        
        //
        checkExamDuration(exam_priority_queue, machine_list, timestamp, q_patient, q_patient_outs);

        //
        

        // increase time
        timestamp++;
    }

    // Test prints
    printf("\n--------LISTA DE PACIENTES--------\n");
    q_print(q_patient);
    printf("\n-------LISTA DE PACIENTES QUE SAIRAM---------\n");
    q_print(q_patient_outs);
    printf("\n-------LISTA DE EXAMES DE PRIORIDADES---------\n");
    q_print_exam(exam_priority_queue);
    printf("\n-------LISTA DE MAQUINAS---------\n");
    printMachines(machine_list);


    return 0;

}