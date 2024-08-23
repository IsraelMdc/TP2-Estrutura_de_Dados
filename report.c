#include "patient.h"
#include "machine.h"
#include "exam.h"
#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct report{
    int report_id;
    int exam_id;
    char condition_IA[20];
    int timestamp;

};

// Report* start_report(int report_id, int exam_id, char condition_IA, int timestamp)
// {
//     Report *report = (Report*)malloc(sizeof(Report));
//     assert(report != NULL);

//     report->report_id;
//     report->exam_id;
//     report->condition_IA;
//     report->timestamp;

//     return report;
// }


Report *create_report(Exam *exam, int report_id, int timestamp)
{
    Report *report = (Report *)malloc(sizeof(Report));
    int p = gen_randint(1, 10);

    if (p < 8)
    {
        strcpy(report->condition_IA, get_exam_condition(exam));
    }
    else
    {
        condition_report(report, exam);
    }
    report->report_id = report_id;
    report->exam_id = get_exam_id(exam);
    report->timestamp = timestamp;

    return report;
}

void condition_report(Report *report, Exam *exam)
{
    int chance = gen_randint(1, 100);

    if (chance <= 30) 
    {
        strcpy(report->condition_IA, "saude normal");
    } 

    else if (chance > 30 && chance <= 50) 
    {
        strcpy(report->condition_IA, "bronquite");
    }

    else if (chance > 50 && chance <= 60) 
    {
        strcpy(report->condition_IA, "pneumonia");
    } 

    else if (chance > 60 && chance <= 70) 
    {
        strcpy(report->condition_IA, "COVID");
    } 

    else if (chance > 70 && chance <= 75) 
    {
        strcpy(report->condition_IA, "Embolia pulmonar"); 
    }

    else if (chance > 75 && chance <= 80) 
    {
        strcpy(report->condition_IA, "Derrame pleural"); 
    }

    else if (chance > 80 && chance <= 85) 
    {
        strcpy(report->condition_IA, "Fibrose pulmonar");
    }
    
    else if (chance > 85 && chance <= 90) 
    {
        strcpy(report->condition_IA, "Tuberculose");
    }
    else if (chance > 90) 
    {
        strcpy(report->condition_IA, "Cancer de pulmao");
    }
    if (report->condition_IA == get_exam_condition(exam)) {
        condition_report(report, exam);
    }
}

void write_report(Report *report)
{
   assert(report != NULL);

   char *filename = "db_report.txt";

   // open the file for writing
   FILE *fp = fopen(filename, "a");
   if (fp == NULL)
   {
      printf("Error opening the file %s", filename);
      return;
   }

   // write to the text file
   fprintf(fp, "Report ID: %d, Exam ID: %d, Condition: %s, Timestamp: %d\n", report->report_id, report->exam_id, report->condition_IA, report->timestamp);

   // close the file
   fclose(fp);

}

// int priority_queue_out(Exam *exam, int timestamp){
//     int exam_timestamp = get_exam_timestamp(exam);

//     return timestamp - exam_timestamp;
// }

void average_time_report(Exam *exam, int timestamp, 
float *healthy_time, float *bronquite_time, float *pneumonia_time, float *covid_time, float *embolia_time, float *derrame_time, float *fibrose_time, float *tuberculose_time, float *cancer_time,
int *healthy_count, int *bronquite_count, int *pneumonia_count, int *covid_count, int *embolia_count, int *derrame_count, int *fibrose_count, int *tuberculose_count, int *cancer_count)
{
    int exam_timestamp = get_exam_timestamp(exam);
    char condition_IA[20] = get_exam_condition(exam);

    if (condition_IA == "saude normal")
    {
        healthy_time += exam_timestamp;
        healthy_count++;
    }
    else if (condition_IA == "bronquite")
    {
        bronquite_time += exam_timestamp;
        bronquite_count++;
    }
    else if (condition_IA == "pneumonia")
    {
        pneumonia_time += exam_timestamp;
        pneumonia_count++;
    }
    else if (condition_IA == "COVID")
    {
        covid_time += exam_timestamp;
        covid_count++;
    }
    else if (condition_IA == "Embolia pulmonar")
    {
        embolia_time += exam_timestamp;
        embolia_count++;
    }
    else if (condition_IA == "Derrame pleural")
    {
        derrame_time += exam_timestamp;
        derrame_count++;
    }
    else if (condition_IA == "Fibrose pulmonar")
    {
        fibrose_time += exam_timestamp;
        fibrose_count++;
    }
    else if (condition_IA == "Tuberculose")
    {
        tuberculose_time += exam_timestamp;
        tuberculose_count++;
    }
    else if (condition_IA == "Cancer de pulmao")
    {
        cancer_time += exam_timestamp;
        cancer_count++;
    }
}

void print_average_time_report(float healthy_time, float bronquite_time, float pneumonia_time, float covid_time, float embolia_time, float derrame_time, float fibrose_time, float tuberculose_time, float cancer_time, int healthy_count, int bronquite_count, int pneumonia_count, int covid_count, int embolia_count, int derrame_count, int fibrose_count, int tuberculose_count, int cancer_count)
{
    printf("Average time for healthy patients: %f\n", healthy_time / healthy_count);
    printf("Average time for bronquite patients: %f\n", bronquite_time / bronquite_count);
    printf("Average time for pneumonia patients: %f\n", pneumonia_time / pneumonia_count);
    printf("Average time for COVID patients: %f\n", covid_time / covid_count);
    printf("Average time for embolia patients: %f\n", embolia_time / embolia_count);
    printf("Average time for derrame patients: %f\n", derrame_time / derrame_count);
    printf("Average time for fibrose patients: %f\n", fibrose_time / fibrose_count);
    printf("Average time for tuberculose patients: %f\n", tuberculose_time / tuberculose_count);
    printf("Average time for cancer patients: %f\n", cancer_time / cancer_count);
}
