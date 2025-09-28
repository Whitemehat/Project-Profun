#ifndef PROJECT_H
#define PROJECT_H

#define MAX_LINE 1024

typedef struct{
    char name[50];
    int age;
    char disease[100];
    char date[20];
}Patient;

extern Patient *patients;
extern int patient_count;

int login();
int sort_patient(const char *keyword);
int check_condition(char *condition);
int compare_date(const void *a, const void *b);
void sort_by_date();
void load_csv(const char *filename);
void save_csv(const char *filename);
void sort_date();
void list_patient();
void add_patient();
void search();
void update_patient();
void delete_patient();
int display_menu();

#endif