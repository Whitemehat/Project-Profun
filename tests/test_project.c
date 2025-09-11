#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../project/project.h"

void test_check_condition(){
    assert(check_condition("y") == 1);
    assert(check_condition("Y") == 1);
    assert(check_condition("Yes") == 1);
    assert(check_condition("yes") == 1);
    assert(check_condition("n") == 0);
    assert(check_condition("N") == 0);
    assert(check_condition("No") == 0);
    assert(check_condition("no") == 0);
    printf("Check_condition() passed!\n");
}

void test_sort_patient(){
    patient_count = 2;
    patients = malloc(sizeof(Patient) * 2);
    strcpy(patients[0].name, "Alice");
    strcpy(patients[0].disease , "Flu");
    strcpy(patients[1].name , "Bob");
    strcpy(patients[1].disease , "Cold");

    assert(sort_patient("Alice") == 0);
    assert(sort_patient("Cold") == 1);
    assert(sort_patient("Unknown") == -1);
    printf("sort_patient() passed!\n");

    free(patients);
}

int main(){
    char filename[] = "data.csv";
    test_check_condition();
    test_sort_patient();
    printf("All tests passed!\n");
    return 0;
}