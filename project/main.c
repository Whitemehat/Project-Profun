#include "project.h"
#include "stdio.h"
int main()
{
    int option;
    char filename[] = "data.csv";
    load_csv(filename);
    while (1){    
        option = display_menu();
        switch (option)
        {
            case 1:
                list_patient();
                break;
            case 2:
                add_patient();
                save_csv(filename);
                break;
            case 3:
                search();
                break;
            case 4:
                update_patient();
                save_csv(filename);
                break;
            case 5:
                delete_patient();
                save_csv(filename);
                break;
            case 6:
                return 0;
            default:
                printf("Invalid input\n");
        }
    }
    return 0;
}