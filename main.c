#include "project.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int patient_count = 0;
    load_csv("data.csv", &patient_count);

    if (!login()) {
        printf("Login failed!\n");
        return 0;
    }

    int option;
    while (1) {
        option = display_menu();
        system("clear");
        switch (option) {
            case 1:
                list_patient(patient_count);
                
                break;
            case 2:
                add_patient_io(&patient_count);
                save_csv("data.csv", patient_count);
                
                break;
            case 3:
                search_io(patient_count);
                save_csv("data.csv", patient_count);
                
                break;
            case 4:
                update_patient_io(patient_count);
                save_csv("data.csv", patient_count);
                
                break;
            case 5:
                delete_patient_io(&patient_count);
                save_csv("data.csv", patient_count);
                
                break;
            case 6:
                save_csv("data.csv", patient_count);
                printf("Exit program\n");
                free(patients);
                return 0;
            default:
                printf("Invalid option!\n");
                break;
        }
        sort_by_date(patients , patient_count);
    }

    return 0;
}
