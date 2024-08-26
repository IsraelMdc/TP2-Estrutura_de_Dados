#include "patient.h"
#include "machine.h"
#include "exam.h"
#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Definition of the Report structure//
struct report {
    int report_id;             // Unique identifier for the report
    int exam_id;               // Identifier of the associated exam
    char condition_IA[20];    // Condition diagnosed by the IA
    int timestamp;            // Timestamp when the report was created
};

// Creates a new report based on the provided exam, report ID, and timestamp
Report *create_report(Exam *exam, int report_id, int timestamp) {
    Report *report = (Report *)malloc(sizeof(Report)); // Allocate memory for the Report structure
    int p = gen_randint(1, 10); // Generate a random integer between 1 and 10

    if (p < 8) {
        // Assign the condition from the exam to the report
        strcpy(report->condition_IA, get_exam_condition(exam));
    } else {
        // Generate a random condition if the random number is 8 or greater
        condition_report(report, exam);
    }
    report->report_id = report_id; // Set the report ID
    report->exam_id = get_exam_id(exam); // Set the exam ID
    report->timestamp = timestamp; // Set the timestamp

    return report; // Return the created report
}

// Generates a condition for the report based on a random chance
void condition_report(Report *report, Exam *exam) {
    int chance = gen_randint(1, 100); // Generate a random integer between 1 and 100

    // Assign a condition based on the random chance
    if (chance <= 30) {
        strcpy(report->condition_IA, "Saude Normal");
    } else if (chance > 30 && chance <= 50) {
        strcpy(report->condition_IA, "Bronquite");
    } else if (chance > 50 && chance <= 60) {
        strcpy(report->condition_IA, "Pneumonia");
    } else if (chance > 60 && chance <= 70) {
        strcpy(report->condition_IA, "COVID");
    } else if (chance > 70 && chance <= 75) {
        strcpy(report->condition_IA, "Embolia pulmonar");
    } else if (chance > 75 && chance <= 80) {
        strcpy(report->condition_IA, "Derrame pleural");
    } else if (chance > 80 && chance <= 85) {
        strcpy(report->condition_IA, "Fibrose pulmonar");
    } else if (chance > 85 && chance <= 90) {
        strcpy(report->condition_IA, "Tuberculose");
    } else {
        strcpy(report->condition_IA, "Cancer de pulmao");
    }
    // If the generated condition is the same as the one from the exam, generate a new condition
    if (strcmp(report->condition_IA, get_exam_condition(exam)) == 0) {
        condition_report(report, exam);
    }
}

// Returns the condition of the report
char *get_report_condition(Report *report) {   
    return report->condition_IA;
}

// Frees the memory allocated for the report
void report_destroy(Report *report) {
    free(report);
}

// Writes the details of the report to a text file
void write_report(Report *report) {
    assert(report != NULL); // Ensure the report is not NULL

    char *filename = "db_report.txt"; // File to write the report to

    // Open the file for appending
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening the file %s", filename); // Print an error message if the file cannot be opened
        return;
    }

    // Write the report details to the file
    fprintf(fp, "Report ID: %d, Exam ID: %d, Condition: %s, Timestamp: %d\n", 
            report->report_id, report->exam_id, report->condition_IA, report->timestamp);

    // Close the file
    fclose(fp);
}

// Updates statistics based on the report's condition
void report_condition_data(Report *report, int timestamp, int *count_cancer, int *qtd_cancer, int *count_tuberculose, int *qtd_tuberculose, 
int *count_fibrose, int *qtd_fibrose, int *count_derrame, int *qtd_derrame, int *count_embolia, int *qtd_embolia, int *count_covid, 
int *qtd_covid, int *count_pneumonia, int *qtd_pneumonia, int *count_bronquite, int *qtd_bronquite, int *count_healthy, int *qtd_healthy) 
{
    // Increment the count and total time for each condition based on the report's condition
    if (strcmp(get_report_condition(report), "Saude Normal") == 0) {
        *count_healthy += timestamp;
        *qtd_healthy += 1;
    } else if (strcmp(get_report_condition(report), "Bronquite") == 0) {
        *count_bronquite += timestamp;
        *qtd_bronquite += 1;
    } else if (strcmp(get_report_condition(report), "Pneumonia") == 0) {
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
