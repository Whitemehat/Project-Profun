#ifndef PATIENT_H
#define PATIENT_H

#include <stdbool.h>

#define MAX_LINE 1024

typedef struct {
    char name[50];
    int age;
    char disease[100];
    char date[20];
} Patient;

extern Patient *patients;

// Core functions (unit-testable)
int check_condition(const char *condition);
int add_patient_core(const char *name, int age, const char *disease, const char *date, int *patient_count);
int update_patient_core(const char *name, int new_age, const char *new_disease, const char *new_date, int patient_count);
int delete_patient_core(const char *name, int *patient_count);
int search_patient(const char *keyword, const char *condition, int patient_count);
int sort_by_date(Patient *patients, int patient_count);
void load_csv(const char *filename, int *patient_count);
void save_csv(const char *filename, int patient_count);

// I/O functions
void add_patient_io(int *patient_count);
void update_patient_io(int patient_count);
void delete_patient_io(int *patient_count);
void search_io(int patient_count);
void list_patient(int patient_count);
bool menu();
int display_menu();
int login();

#endif
