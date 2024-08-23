#ifndef REPORT_H
#define REPORT_H

#include "exam.h"
#include <stdio.h>

typedef struct report Report;

// Report* start_report(int report_id, int exam_id, char condition_IA, int timestamp);

Report *create_report(Exam *exam, int report_id, int timestamp);

void condition_report(Report *report, Exam *exam);

void write_report(Report *report);

#endif