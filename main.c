#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "machine.h"
#include "exam.h"
#include "report.h"
#include <unistd.h>

int main()
{
    // Initializing the time variables
    int timestamp = 1;            // Current time in the simulation

    // Initializing the ID variables
    int id = 1;                    // ID for new patients
    int report_id = 1;             // ID for new reports

    // Initializing the doctor-related variables
    int doctor_occupied = 0;       // Indicates if the doctor is currently occupied
    int doctor_wait;               // Time the doctor will be busy until

    // Initializing counters
    int patient_count = 0;         // Total number of patients processed
    int sum_report = 0;            // Sum of the time taken to generate reports

    // Variables to count occurrences of each condition in the periodic report
    int count_cancer = 0, count_tuberculose = 0, count_fibrose = 0, count_derrame = 0;
    int count_embolia = 0, count_covid = 0, count_pneumonia = 0, count_bronquite = 0, count_healthy = 0;

    // Variables to accumulate time for each condition
    int qtd_cancer = 0, qtd_tuberculose = 0, qtd_fibrose = 0, qtd_derrame = 0;
    int qtd_embolia = 0, qtd_covid = 0, qtd_pneumonia = 0, qtd_bronquite = 0, qtd_healthy = 0;

    // Initializing the machine linked list
    MachineList *machine_list = createMachineList();

    // Adding 5 machines to the linked list
    initializeMachinesOnList(machine_list);

    // Initializing patient and exam queues
    QueuePatient *q_patient = q_patient_create();
    ExamPriorityQueue *exam_priority_queue = createExamPriorityQueue();

    // Simulation time loop
    while (timestamp <= 43200)
    {
        // Create new patient and add them to the queue
        id = patient_Creation(id, timestamp, q_patient); 
        
        // Check if there are patients waiting and if a machine is available
        if(!q_is_empty(q_patient))
        {
            if(machine_is_available(machine_list))
            {
                // Dequeue a patient and assign them to a machine
                Patient *patient = patient_dequeue(q_patient);
                insertPatientOnMachine(machine_list, patient, timestamp);

                patient_count++; // Increment the patient count
            }
        }
        
        // Check if any exams are completed and move patients to the exam priority queue
        checkExamDuration(exam_priority_queue, machine_list, timestamp, q_patient);

        // Process exams if the doctor is available
        if(!isEmptyExamPriorityQueue(exam_priority_queue))
        {
            if (doctor_occupied == 0)
            {
                // Doctor processes the next exam in the queue
                Exam *exam = dequeueExamPriorityQueue(exam_priority_queue);

                sum_report += (timestamp + 30) - get_exam_timestamp(exam); // Update report sum
                Report *report = create_report(exam, report_id, timestamp + 30);
                write_report(report);

                // Gather condition-specific report data
                int data_time = (timestamp + 30) - get_exam_timestamp(exam);
                report_condition_data(report, data_time, &count_cancer, &qtd_cancer, &count_tuberculose, &qtd_tuberculose, 
                                      &count_fibrose, &qtd_fibrose, &count_derrame, &qtd_derrame, &count_embolia, &qtd_embolia, 
                                      &count_covid, &qtd_covid, &count_pneumonia, &qtd_pneumonia, &count_bronquite, &qtd_bronquite, 
                                      &count_healthy, &qtd_healthy);

                doctor_wait = timestamp;  // Set the time the doctor will be occupied until
                doctor_occupied = 1;      // Mark the doctor as occupied

                report_destroy(report);   // Clean up the report
                report_id++;              // Increment the report ID
            } 
            else
            {
                // Check if the doctor is free after processing the previous exam
                if(doctor_occupied == 1 && timestamp == doctor_wait + 30)
                {
                    Exam *exam = dequeueExamPriorityQueue(exam_priority_queue);

                    sum_report += (timestamp + 30) - get_exam_timestamp(exam);
                    Report *report = create_report(exam, report_id, timestamp + 30);
                    write_report(report);

                    // Gather condition-specific report data
                    int data_time = (timestamp + 30) - get_exam_timestamp(exam);
                    report_condition_data(report, data_time, &count_cancer, &qtd_cancer, &count_tuberculose, &qtd_tuberculose, 
                    &count_fibrose, &qtd_fibrose, &count_derrame, &qtd_derrame, &count_embolia, &qtd_embolia, &count_covid, 
                    &qtd_covid, &count_pneumonia, &qtd_pneumonia, &count_bronquite, &qtd_bronquite,&count_healthy, &qtd_healthy);

                    doctor_wait = timestamp; // Update the doctor's occupied time
                    doctor_occupied = 1;     // Mark the doctor as occupied

                    report_destroy(report);  // Clean up the report
                    report_id++;             // Increment the report ID
                }
            }
        }

        // Calculate the number of finished exams
        int finished_exam = (patient_count - get_exam_priority_queue_size(exam_priority_queue));

        // Log the simulation state every 1200 time units
        if (timestamp % 1200 == 0 && timestamp != 0)
        {
            printf("\n\n------------------- HOSPITAL LOG TIME: %d ----------------------------\n", timestamp);
            
            printf("Number of patients entered:                                     %d\n", patient_count);
            printf("Number of patients on the exam queue:                           %d\n", get_exam_priority_queue_size(exam_priority_queue));
            printf("Number of patients that finished the exam:                      %d\n", finished_exam);
            printf("Percentage of patients that finished the exam and got a report: %.2f%%\n", finished_exam == 0 ? 0 : (double)(report_id * 100) / finished_exam);
            printf("Average time before getting the report:                         %d\n", sum_report == 0 ? 0 : (sum_report / report_id));
        
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

        // Additional log every 7200 time units
        if (timestamp % 7200 == 0)
        {
            printf("-----------------------------------------------------------------------\n");
            printf("Num of exams after 7200:                                        %d\n", finished_exam);
            printf("-----------------------------------------------------------------------\n\n");
        }

        // Simulate time passing (sleep for 1 millisecond)
        usleep(1 * 1000);

        // Increment the timestamp for the next iteration
        timestamp++;
    } 

    // Clean up and free memory
    destroyExamPriorityQueue(exam_priority_queue);
    destroyMachineList(machine_list);
    destroyPatientQueue(q_patient);
    return 0;
}
