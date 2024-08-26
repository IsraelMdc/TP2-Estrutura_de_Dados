#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "machine.h"
#include "exam.h"
#include "report.h"

int main()
{
    // Starting the time variables
    int timestamp = 1;
    int total_time = 43200;

    // Starting the id variobles
    int id = 1;
    int report_id = 1;

    // Starting the doctor variables
    int doctor_occupied = 0;
    int doctor_wait;

    //starting the counts
    int patient_count = 0;
    int sum_report = 0;

    // Variables to make the periodical report
    // int count_report = 0;
    int count_cancer = 0;
    int count_tuberculose = 0;
    int count_fibrose = 0;
    int count_derrame = 0;
    int count_embolia = 0;
    int count_covid = 0;
    int count_pneumonia = 0;
    int count_bronquite = 0;
    int count_healthy = 0;

    int qtd_cancer = 0;
    int qtd_tuberculose = 0;
    int qtd_fibrose = 0;
    int qtd_derrame = 0;
    int qtd_embolia = 0;
    int qtd_covid = 0;
    int qtd_pneumonia = 0;
    int qtd_bronquite = 0;
    int qtd_healthy = 0;

    // Initializing the machine linked list
    MachineList *machine_list = createMachineList();

    // Adding the 5 machines into the linked list
    initializeMachinesOnList(machine_list);

    // Initializing patient and exam queues
    QueuePatient *q_patient_outs = q_patient_create();
    QueuePatient *q_patient = q_patient_create();
    ExamPriorityQueue *exam_priority_queue = createExamPriorityQueue();

    // Time loop of the simulation
    while (timestamp <= total_time)
    {

        id = patient_Creation(id, timestamp, q_patient); 
        
        //
        if(!q_is_empty(q_patient))
        {
            if(machine_is_available(machine_list))
            {
            Patient *patient = patient_dequeue(q_patient);
            insertPatientOnMachine(machine_list, patient, timestamp);

            patient_count++;
            
            }
            
        }
        
        //
        checkExamDuration(exam_priority_queue, machine_list, timestamp, q_patient, q_patient_outs);

        if(!isEmptyExamPriorityQueue(exam_priority_queue))
        {
            if (doctor_occupied == 0)
            {
                Exam *exam = dequeueExamPriorityQueue(exam_priority_queue);

                // printf("\n--------SAINDO DA LISTA DO EXAME--------\n");
                // printf("Patient id %d, report id %d and condition %s saindo da lista\n", get_exam_id(exam), report_id, get_exam_condition(exam));
                // printf("\n----------------\n");

                sum_report += (timestamp + 30) - get_exam_timestamp(exam);
                Report *report = create_report(exam, report_id, timestamp + 30);
                write_report(report);

                // getting time difference for the condition calculations
                int data_time = (timestamp + 30) - get_exam_timestamp(exam);

                //
                report_condition_data(report, data_time, &count_cancer, &qtd_cancer, &count_tuberculose, &qtd_tuberculose, 
                &count_fibrose, &qtd_fibrose, &count_derrame, &qtd_derrame, &count_embolia, &qtd_embolia, &count_covid, 
                &qtd_covid, &count_pneumonia, &qtd_pneumonia,&count_bronquite, &qtd_bronquite, &count_healthy, &qtd_healthy);

                doctor_wait = timestamp;
                doctor_occupied = 1;

                report_destroy(report);
                report_id++;
            } 
            else
            {
                if(doctor_occupied == 1 && timestamp == doctor_wait + 30)
                {

                Exam *exam = dequeueExamPriorityQueue(exam_priority_queue);

                sum_report += (timestamp + 30) - get_exam_timestamp(exam);

                // printf("\n--------SAINDO DA LISTA DO EXAME--------\n");
                // printf("Patient id %d, report id %d and condition %s saindo da lista\n", get_exam_id(exam), report_id, get_exam_condition(exam));
                // printf("\n----------------\n");

                Report *report = create_report(exam, report_id, timestamp + 30);
                write_report(report);
                // getting time difference for the condition calculations
                int data_time = (timestamp + 30) - get_exam_timestamp(exam);
                //
                report_condition_data(report, data_time, &count_cancer, &qtd_cancer, &count_tuberculose, &qtd_tuberculose, 
                &count_fibrose, &qtd_fibrose, &count_derrame, &qtd_derrame, &count_embolia, &qtd_embolia, &count_covid, 
                &qtd_covid, &count_pneumonia, &qtd_pneumonia,&count_bronquite, &qtd_bronquite, &count_healthy, &qtd_healthy);

                doctor_wait = timestamp;
                doctor_occupied = 1;
                report_destroy(report);
                report_id++;

                }
            }

        }
        int finished_exam = (patient_count - get_exam_priority_queue_size(exam_priority_queue));

        if (timestamp % 100 == 0 && timestamp != 0)
        {

            printf("\n\n------------------- HOSPITAL LOG TIME: %d ----------------------------\n", timestamp);
            
            printf("Number of patients entered:                                     %d\n", patient_count);
            printf("Number of patients on the exam queue:                           %d\n", get_exam_priority_queue_size(exam_priority_queue));
            printf("Number of patients that finished the exam:                      %d\n", finished_exam);
            printf("Percentage of patients that finished the exam and got a report: %.2f%%\n", finished_exam == 0 ? 0 : (double)(report_id * 100) / finished_exam);
            printf("Average time before getting the report:                         %d\n", sum_report == 0 ? 0 : (sum_report/ report_id));
        
            printf("\n------------------ AVERAGE TIME PER CONDITION ------------------------\n");
            
            printf("Average time for Saude normal to leave the queue:               %.2f\n", qtd_healthy == 0 ? 0 : (double)count_healthy / qtd_healthy);
            printf("Average time for Bronquite to leave the queue:                  %.2f\n", qtd_bronquite == 0 ? 0 : (double)count_bronquite / qtd_bronquite);
            printf("Average time for Pneumonia to leave the queue:                  %.2f\n", qtd_pneumonia == 0 ? 0 : (double)count_pneumonia / qtd_pneumonia);
            printf("Average time for COVID to leave the queue:                      %.2f\n", qtd_covid == 0 ? 0 : (double)count_covid / qtd_covid);
            printf("Average time for Embolia to leave the queue:                    %.2f\n", qtd_embolia == 0 ? 0 : (double)count_embolia / qtd_embolia);
            printf("Average time for Derrame to leave the queue:                    %.2f\n", qtd_derrame == 0 ? 0 : (double)count_derrame / qtd_derrame);
            printf("Average time for Fibrose to leave the queue:                    %.2f\n", qtd_fibrose == 0 ? 0 : (double)count_fibrose / qtd_derrame);
            printf("Average time for Tuberculose to leave the queue:                %.2f\n", qtd_tuberculose == 0 ? 0 : (double)count_tuberculose / qtd_tuberculose);
            printf("Average time for Cancer to leave the queue:                     %.2f\n", qtd_cancer == 0 ? 0 : (double)count_cancer / qtd_cancer);
            printf("-----------------------------------------------------------------------\n");

        }
        if (timestamp % 7200 == 0)
        {   printf("-----------------------------------------------------------------------\n");

            printf("Num of exams after 7200:                                        %d\n", finished_exam);

            printf("-----------------------------------------------------------------------\n\n");
        }

        // increase time
        timestamp++;
    }

    // // Test prints
    // printf("\n--------LISTA DE PACIENTES--------\n");
    // q_print(q_patient);
    // printf("\n-------LISTA DE PACIENTES QUE SAIRAM---------\n");
    // q_print(q_patient_outs);
    // printf("\n-------LISTA DE EXAMES DE PRIORIDADES---------\n");
    // q_print_exam(exam_priority_queue);
    // // printf("\n-------LISTA DE MAQUINAS---------\n");
    // // printMachines(machine_list);


    return 0;

}