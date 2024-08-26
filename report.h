#ifndef REPORT_H
#define REPORT_H

#include "exam.h"
#include <stdio.h>

typedef struct report Report;

typedef struct condition_log ConditionLog;

// Report* start_report(int report_id, int exam_id, char condition_IA, int timestamp);

Report *create_report(Exam *exam, int report_id, int timestamp);

void condition_report(Report *report, Exam *exam);

void write_report(Report *report);

void report_condition_data(Report *report, int timestamp, int *count_cancer, int *qtd_cancer, int *count_tuberculose, int *qtd_tuberculose, int *count_fibrose, 
int *qtd_fibrose, int *count_derrame, int *qtd_derrame, int *count_embolia, int *qtd_embolia, int *count_covid, int *qtd_covid, 
int *count_pneumonia, int *qtd_pneumonia, int *count_bronquite, int *qtd_bronquite, int *count_healthy, int *qtd_healthy);

void report_destroy(Report *report);

char *get_report_condition(Report *report);

#endif