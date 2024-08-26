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

// struct condition_log{
//     int condition_counter;
//     float condition_time;
// };

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
        strcpy(report->condition_IA, "Saude Normal");
    } 

    else if (chance > 30 && chance <= 50) 
    {
        strcpy(report->condition_IA, "bronquite");
    }

    else if (chance > 50 && chance <= 60) 
    {
        strcpy(report->condition_IA, "Pneumonia");
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

char *get_report_condition(Report *report)
{   
    return report->condition_IA;
}

void report_destroy(Report *report){
    free(report);
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

void report_condition_data(Report *report, int timestamp, int *count_cancer, int *qtd_cancer, int *count_tuberculose, int *qtd_tuberculose, 
int *count_fibrose, int *qtd_fibrose, int *count_derrame, int *qtd_derrame, int *count_embolia, int *qtd_embolia, int *count_covid, int *qtd_covid, 
int *count_pneumonia, int *qtd_pneumonia, int *count_bronquite, int *qtd_bronquite, int *count_healthy, int *qtd_healthy) 
{

    if (strcmp(get_report_condition(report), "Saude Normal") == 0) {
    *count_healthy += timestamp;
    *qtd_healthy += 1;

    } else if (strcmp(get_report_condition(report), "Bronquite") == 0) {
    *count_bronquite += timestamp;
    *qtd_bronquite += 1;

    } else if (strcmp(get_report_condition(report), "Penumonia") == 0) {
    *count_pneumonia += timestamp;
    *qtd_pneumonia += 1;

    } else if (strcmp(get_report_condition(report), "COVID") == 0) {
    *count_covid += timestamp;
    *qtd_covid += 1;

    } else if (strcmp(get_report_condition(report), "Embolia pulmonar") == 0) {
    *count_embolia += timestamp;
    *qtd_embolia += 1;

    } else if (strcmp(get_report_condition(report), "Derrame pleural") == 0) {
    *count_derrame += timestamp;
    *qtd_derrame += 1;

    } else if (strcmp(get_report_condition(report), "Fibrose pulmonar") == 0) {
    *count_fibrose += timestamp;
    *qtd_fibrose += 1;

    } else if (strcmp(get_report_condition(report), "Tuberculose") == 0) {
    *count_tuberculose += timestamp;
    *qtd_tuberculose += 1;

    } else if (strcmp(get_report_condition(report), "Cancer de pulmao") == 0) {
    *count_cancer += timestamp;
    *qtd_cancer += 1;
    }
}
