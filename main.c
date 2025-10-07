#include "project.h"
#include <stdio.h>

//int main()
int main_program()
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
        switch (option) {
            case 1:
                list_patient(patient_count);
                break;
            case 2:
                add_patient_io(&patient_count);
                break;
            case 3:
                search_io(patient_count);
                break;
            case 4:
                update_patient_io(patient_count);
                break;
            case 5:
                delete_patient_io(&patient_count);
                break;
            case 6:
                save_csv("data.csv", patient_count);
                printf("Exit program\n");
                return 0;
            default:
                printf("Invalid option!\n");
                break;
        }
    }

    return 0;
}
