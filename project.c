#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Patient *patients = NULL;

//CORE FUNCTION

int check_condition(const char *condition) {
    if (!condition || !condition[0]) return 0;
    char c = condition[0];
    if ('A' <= c && c <= 'Z') c += 32;
    return (c == 'y');
}

int add_patient_core(const char *name, int age, const char *disease, const char *date, int *patient_count) {
    for (int i = 0; i < *patient_count; i++) {
        if (strcmp(patients[i].name, name) == 0) return 0; // exists
    }

    patients = realloc(patients, (*patient_count + 1) * sizeof(Patient));
    if (!patients) return -1;

    strcpy(patients[*patient_count].name, name);
    patients[*patient_count].age = age;
    strcpy(patients[*patient_count].disease, disease);
    strcpy(patients[*patient_count].date, date);

    (*patient_count)++;
    return 1; // success
}

int update_patient_core(const char *name, int new_age, const char *new_disease, const char *new_date, int patient_count) {
    int i = search_patient(name, "y", patient_count);
    if (i == -1) return 0;

    if (new_age != 0) patients[i].age = new_age;
    if (new_disease && strcmp(new_disease, "-") != 0) strcpy(patients[i].disease, new_disease);
    if (new_date && strlen(new_date) > 0) strcpy(patients[i].date, new_date);

    return 1;
}

int delete_patient_core(const char *name, int *patient_count) {
    int i = search_patient(name, "y", *patient_count);
    if (i == -1) return 0;

    for (int j = i; j < *patient_count - 1; j++) patients[j] = patients[j + 1];
    (*patient_count)--;
    patients = realloc(patients, (*patient_count) * sizeof(Patient));
    return 1;
}

int search_patient(const char *keyword, const char *condition, int patient_count) {
    for (int i = 0; i < patient_count; i++) {
        if (strstr(patients[i].name, keyword) || strstr(patients[i].disease, keyword)) {
            if (check_condition(condition)) return i;
        }
    }
    return -1;
}

int compare_date(const void *a, const void *b) {
    const Patient *first = (const Patient *)a;
    const Patient *second = (const Patient *)b;

    int y1, m1, d1, y2, m2, d2;
    sscanf(first->date, "%d-%d-%d", &y1, &m1, &d1);
    sscanf(second->date, "%d-%d-%d", &y2, &m2, &d2);

    if (y1 != y2) return y1 - y2;
    if (m1 != m2) return m1 - m2;
    return d1 - d2;
}


int sort_by_date(Patient *patients, int patient_count) {
    if (patient_count == 0) return 0;
    qsort(patients, patient_count, sizeof(Patient), compare_date);
    return 1;
}

void load_csv(const char *filename, int *patient_count) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return;
    char text[MAX_LINE];

    if (fgets(text, sizeof(text), fp) == NULL) {
        fclose(fp);
        return;
    }

    while (fgets(text, sizeof(text), fp)) {
        char *name = strtok(text, ",");
        char *age = strtok(NULL, ",");
        char *disease = strtok(NULL, ",");
        char *date = strtok(NULL, ",\n");

        if (name && age && disease && date) {
            add_patient_core(name, atoi(age), disease, date, patient_count);
        }
    }
    fclose(fp);
}

void save_csv(const char *filename, int patient_count) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    fprintf(fp, "name,age,congenital-disease,date\n");
    for (int i = 0; i < patient_count; i++) {
        fprintf(fp, "%s,%d,%s,%s\n",
                patients[i].name,
                patients[i].age,
                patients[i].disease,
                patients[i].date);
    }
    fclose(fp);
}

// -------------------- I/O FUNCTIONS --------------------

void add_patient_io(int *patient_count) {
    char name[50], disease[100], date[20];
    int age;

    printf("Enter name : ");
    scanf(" %[^\n]", name);
    int i = search_patient(name, "y", *patient_count);
    if (i != -1) {
        printf("Already has this Patient!\n");
        return;
    }

    printf("Enter age : ");
    scanf("%d", &age);
    if (age > 122) {
        printf("Too high from history. Ask the Admin for adding.\n");
        return;
    }

    printf("Enter disease : ");
    scanf(" %[^\n]", disease);
    printf("Enter date (YYYY-MM-DD) : ");
    scanf(" %[^\n]", date);

    int result = add_patient_core(name, age, disease, date, patient_count);
    if (result == 1) printf("Patient added!\n");
}

void update_patient_io(int patient_count) {
    char name[50], condition[4], disease[100], date[20];
    int age;

    printf("Enter Patient name for Update: ");
    scanf(" %[^\n]", name);

    int i = search_patient(name, "y", patient_count);
    if (i == -1) {
        printf("Patient not found!\n");
        return;
    }
    printf("%s\n%d\n%s\n%s\n" , patients[i].name , patients[i].age , patients[i].disease , patients[i].date);
    printf("Yes / No : ");
    scanf(" %[^\n]", condition);
    if (!check_condition(condition)) return;

    printf("Enter new age (0 for no change) : ");
    scanf("%d", &age);
    printf("Enter new disease (- for no change): ");
    scanf(" %[^\n]", disease);
    printf("Enter new date (- for no change): ");
    scanf(" %[^\n]", date);

    update_patient_core(name, age, disease, strcmp(date, "-") == 0 ? NULL : date, patient_count);
    printf("Update Successfully!\n");
}

void delete_patient_io(int *patient_count) {
    char name[50], condition[4];
    printf("Enter the patient name to delete: ");
    scanf(" %[^\n]", name);

    int i = search_patient(name, "y", *patient_count);
    if (i == -1) {
        printf("Patient not found!\n");
        return;
    }

    printf("Yes / No : ");
    scanf(" %[^\n]", condition);
    if (!check_condition(condition)) {
        printf("Not Deleted\n");
        return;
    }

    delete_patient_core(name, patient_count);
    printf("Deleted successfully!\n");
}

void search_io(int patient_count) {
    char keyword[50];
    printf("Enter name or disease to search : ");
    scanf(" %[^\n]", keyword);
    int i = search_patient(keyword, "y", patient_count);
    if (i != -1) {
        printf("Patient [%d]\nName : %s\nAge : %d\nDisease : %s\nDate : %s\n",
               i + 1, patients[i].name, patients[i].age, patients[i].disease, patients[i].date);
    } else {
        printf("No match found!\n");
    }
}

void list_patient(int patient_count) {
    if (patient_count == 0) {
        printf("No patient Yet!\n");
        return;
    }
    for (int i = 0; i < patient_count; i++) {
        printf("Patient [%d] , Name : %s , Age : %d , Disease : %s , Date : %s\n",
               i + 1, patients[i].name, patients[i].age, patients[i].disease, patients[i].date);
    }
}

bool menu() {
    printf("###########################################\n");
    printf("1. list patient health information\n");
    printf("2. add the patient information\n");
    printf("3. search from name / congenital disease\n");
    printf("4. update age / congenital disease\n");
    printf("5. delete patient information\n");
    printf("6. Unit Test\n");
    printf("7. E2E Test\n");
    printf("0. Exit Program\n");
    printf("###########################################\n");
    return true;
}

int display_menu() {
    int option;
    menu();
    printf("Enter your option : ");
    if(scanf("%d" , &option) != 1){
        return -1;
    }
    return option;
}

int login() {
    char user[64], password[64];
    int attemp = 0;
    while (attemp < 3) {
        printf("Username : ");
        if (fgets(user, sizeof(user), stdin) == NULL) return 0;
        user[strcspn(user, "\n")] = '\0';

        printf("Password : ");
        if (fgets(password, sizeof(password), stdin) == NULL) return 0;
        password[strcspn(password, "\n")] = '\0';

        if (strcmp(user, "Agent 32") == 0 && strcmp(password, "A$3nt32") == 0) return 1;

        printf("[*] attempt [%d] !Username or Password incorrect!\n", attemp + 1);
        attemp++;
    }
    return 0;
}
