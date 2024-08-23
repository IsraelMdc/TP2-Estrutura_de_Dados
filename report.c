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

Report* start_report(int report_id, int exam_id, char condition_IA, int timestamp){
    Report *report = (Report*)malloc(sizeof(Report));
    assert(report != NULL);

    report->report_id;
    report->exam_id;
    report->condition_IA;
    report->timestamp;

    return report;
}


void create_report(ExamPriorityQueue *exam_priority_queue){

    double p = (double) rand() / (double)RAND_MAX;



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

    if (report->condition_IA == exam->condition_IA) {
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
   fprintf(fp, "Report ID: %d,Timestamp: %d\n", report->report_id, report->timestamp);

   // close the file
   fclose(fp);

}