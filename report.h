#ifndef REPORT_H
#define REPORT_H

#include "exam.h"
#include <stdio.h>

typedef struct report Report;

// Creates a new report.
Report *create_report(Exam *exam, int report_id, int timestamp);

// Generates a condition for the report.
void condition_report(Report *report, Exam *exam);

// Writes the report to a file.
void write_report(Report *report);

// Updates statistical data based on the report's condition.
void report_condition_data(Report *report, int timestamp, int *count_cancer, int *qtd_cancer, int *count_tuberculose, int *qtd_tuberculose, 
int *count_fibrose, int *qtd_fibrose, int *count_derrame, int *qtd_derrame, int *count_embolia, int *qtd_embolia, int *count_covid, 
int *qtd_covid, int *count_pneumonia, int *qtd_pneumonia, int *count_bronquite, int *qtd_bronquite, int *count_healthy, int *qtd_healthy);

// Frees the memory allocated for the report.
void report_destroy(Report *report);

// Returns the condition of the report.
char *get_report_condition(Report *report);

#endif
