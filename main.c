#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "machine.h"
#include "exam.h"
#include "report.h"

void hospital_log(int timestamp, int num_patients, int num_exam, int num_reports, int epq_time, int count_limit)
{
    printf("\n--------HOSPITAL LOG TIME: %d--------\n", timestamp);

    printf("Number of patients entered: %d\n", num_patients);
    printf("Number of patients on the exam queue: %d\n", num_patients - num_exam);
    printf("Number of patients that finished the exam: %d\n", num_exam);
    printf("Percentage of patients that finished the exam and got a report: %.2f%%\n", ((float)num_reports / num_exam * 100));
    printf("Average time before getting the report: %d\n", num_reports == 0 ? 0 : epq_time / num_reports);
    printf("Average time per condition\n");
    //print_average_time_report();    
    printf("Number of patients that waited more than 7200 time units: %d\n\n", count_limit);

    printf("\n----------------------------\n");

}

int main()
{
    // Starting the time variables
    int timestamp = 1;
    int total_time = 200;

    // Starting the id variobles
    int id = 1;
    int report_id = 1;

    // Starting the doctor variables
    int doctor_occupied = 0;
    int cooldown;

    //starting the counts
    float *healthy_time, *bronquite_time, *pneumonia_time, *covid_time, *embolia_time, *derrame_time, *fibrose_time, *tuberculose_time, *cancer_time = 0;
    int *healthy_count, *bronquite_count, *pneumonia_count, *covid_count, *embolia_count, *derrame_count, *fibrose_count, *tuberculose_count, *cancer_count = 0;


    // Initializing the machine linked list
    MachineList *machine_list = createMachineList();

    // Adding the 5 machines into the linked list
    initializeMachinesOnList(machine_list);

    // Initializing patient and exam queues
    QueuePatient *q_patient_outs = q_patient_create();
    QueuePatient *q_patient = q_patient_create();
    ExamPriorityQueue *exam_priority_queue = createExamPriorityQueue();

    // Time loop of the simulation
    while (timestamp < total_time)
    {
        // Printing hospital log 10 times during the simulation
        if (timestamp % total_time/10 == 0 && timestamp != 0)
        {

        }
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

        if(!isEmptyExamPriorityQueue(exam_priority_queue))
        {
            if (doctor_occupied == 0)
            {
                                void average_time_report(Exam *exam, Report *report, 
                float *healthy_time, float *bronquite_time, float *pneumonia_time, float *covid_time, float *embolia_time, float *derrame_time, float *fibrose_time, float *tuberculose_time, float *cancer_time,
                int *healthy_count, int *bronquite_count, int *pneumonia_count, int *covid_count, int *embolia_count, int *derrame_count, int *fibrose_count, int *tuberculose_count, int *cancer_count)
                Exam *exam = dequeueExamPriorityQueue(exam_priority_queue);

                printf("\n--------SAINDO DA LISTA DO EXAME--------\n");
                printf("Patient id %d, report id %d and condition %s saindo da lista\n", get_exam_id(exam), report_id, get_exam_condition(exam));
                printf("\n----------------\n");

                Report *report = create_report(exam, report_id, timestamp);
                write_report(report);

                cooldown = timestamp;
                doctor_occupied = 1;
                report_id++;
            } 
            else
            {
                if(doctor_occupied == 1 && timestamp == cooldown + 30)
                {
                void average_time_report(Exam *exam, Report *report, 
                float *healthy_time, float *bronquite_time, float *pneumonia_time, float *covid_time, float *embolia_time, float *derrame_time, float *fibrose_time, float *tuberculose_time, float *cancer_time,
                int *healthy_count, int *bronquite_count, int *pneumonia_count, int *covid_count, int *embolia_count, int *derrame_count, int *fibrose_count, int *tuberculose_count, int *cancer_count)

                Exam *exam = dequeueExamPriorityQueue(exam_priority_queue);

                printf("\n--------SAINDO DA LISTA DO EXAME--------\n");
                printf("Patient id %d, report id %d and condition %s saindo da lista\n", get_exam_id(exam), report_id, get_exam_condition(exam));
                printf("\n----------------\n");

                Report *report = create_report(exam, report_id, timestamp);
                write_report(report);

                cooldown = timestamp;
                doctor_occupied = 1;
                report_id++;
                }
            }

        }
         
        //
        //id_report = create_report(exam, report_id, timestamp);
        

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
    // printf("\n-------LISTA DE MAQUINAS---------\n");
    // printMachines(machine_list);


    return 0;

}