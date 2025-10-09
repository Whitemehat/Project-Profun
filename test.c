#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "project.h"

void test_check_condition() {
    assert(check_condition("Yes") == 1);
    assert(check_condition("y") == 1);
    assert(check_condition("No") == 0);
    assert(check_condition("n") == 0);
    assert(check_condition("") == 0);
}

void test_add_patient() {
    int count = 0;
    patients = NULL;

    int r = add_patient_core("Alice", 30, "Flu", "2024-01-01", &count);
    assert(r == 1);
    assert(count == 1);
    assert(strcmp(patients[0].name, "Alice") == 0);

    // duplicate
    r = add_patient_core("Alice", 31, "Cold", "2024-02-01", &count);
    assert(r == 0);
    assert(count == 1);

    r = add_patient_core("Bob", 25, "Cold", "2024-02-01", &count);
    assert(r == 1);
    assert(count == 2);

    free(patients);
}

void test_update_patient() {
    int count = 2;
    patients = malloc(count * sizeof(Patient));
    strcpy(patients[0].name, "Alice");
    patients[0].age = 30;
    strcpy(patients[0].disease, "Flu");
    strcpy(patients[0].date, "2024-01-01");

    strcpy(patients[1].name, "Bob");
    patients[1].age = 25;
    strcpy(patients[1].disease, "Cold");
    strcpy(patients[1].date, "2024-02-01");

    // Update Alice
    int r = update_patient_core("Alice", 35, "Covid", "2024-05-05", count);
    assert(r == 1);
    assert(patients[0].age == 35);
    assert(strcmp(patients[0].disease, "Covid") == 0);
    assert(strcmp(patients[0].date, "2024-05-05") == 0);

    // Non-existing patient
    r = update_patient_core("Charlie", 40, "Asthma", "2024-06-01", count);
    assert(r == 0);

    free(patients);
}

void test_delete_patient() {
    int count = 2;
    patients = malloc(count * sizeof(Patient));
    strcpy(patients[0].name, "Alice");
    strcpy(patients[1].name, "Bob");

    int r = delete_patient_core("Alice", &count);
    assert(r == 1);
    assert(count == 1);
    assert(strcmp(patients[0].name, "Bob") == 0);

    r = delete_patient_core("Charlie", &count);
    assert(r == 0);
    assert(count == 1);

    free(patients);
}

void test_search_patient() {
    int count = 3;
    patients = malloc(count * sizeof(Patient));
    strcpy(patients[0].name, "Alice");
    strcpy(patients[0].disease, "Flu");
    strcpy(patients[1].name, "Bob");
    strcpy(patients[1].disease, "Cold");
    strcpy(patients[2].name, "Peter Tamo");
    strcpy(patients[2].disease, "Flu");

    int test = search_patient("Alice", "y", count, 0);
    assert(test == 0);

    test = search_patient("Bob", "y", count, 1);
    assert(test == 1);

    test = search_patient("Peter Tamo", "y", count, 2);
    assert(test == 2);

    test = search_patient("Unknown", "y", count, 0);
    assert(test == -1);

    test = search_patient("Peter", "y", count, 2);
    assert(test == -1);

    test = search_patient("Alice", "n", count, 0);
    assert(test == -1);

    free(patients);
}

void test_sort_by_date() {
    int count = 3;
    patients = malloc(count * sizeof(Patient));
    strcpy(patients[0].date, "2023-12-01");
    strcpy(patients[1].date, "2021-01-05");
    strcpy(patients[2].date, "2022-07-20");

    sort_by_date(patients, count);

    assert(strcmp(patients[0].date, "2021-01-05") == 0);
    assert(strcmp(patients[1].date, "2022-07-20") == 0);
    assert(strcmp(patients[2].date, "2023-12-01") == 0);

    free(patients);
}

void test_load_and_save_csv() {
    int count = 2;
    patients = malloc(count * sizeof(Patient));

    strcpy(patients[0].name, "Alice");
    patients[0].age = 30;
    strcpy(patients[0].disease, "Flu");
    strcpy(patients[0].date, "2024-01-01");

    strcpy(patients[1].name, "Bob");
    patients[1].age = 25;
    strcpy(patients[1].disease, "Cold");
    strcpy(patients[1].date, "2024-02-01");

    save_csv("test.csv", count);

    free(patients);
    patients = NULL;
    int new_count = 0;
    load_csv("test.csv", &new_count);

    assert(new_count == 2);
    assert(strcmp(patients[0].name, "Alice") == 0);
    assert(patients[0].age == 30);

    remove("test.csv");
    free(patients);
}

int main() {
    test_check_condition();
    printf("test_check_condition passed!\n");
    test_add_patient();
    printf("test_add_patient passed!\n");
    test_update_patient();
    printf("test_update_patient passed!\n");
    test_delete_patient();
    printf("test_delete_patient passed!\n");
    test_search_patient();
    printf("test_search_patient passed!\n");
    test_sort_by_date();
    printf("test_sort_by_date passed!\n");
    test_load_and_save_csv();
    printf("test_load_and_save_csv passed!\n");

    printf("All tests passed!\n");
    return 0;
}
