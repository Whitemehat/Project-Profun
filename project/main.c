#include "project.h"
#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int Authen = 0;
    int option;
    char filename[] = "data.csv";
    int attemp = 0;
    load_csv(filename);
    while(Authen == 0 && attemp < 3){
        if(attemp != 0)
        {
            for(int i = 10 ; i > 0;i--)
            {
            printf("wait %d second\n" , i);
            sleep(1);
            }
        }
        Authen = login();
        attemp++;
    }
    system("clear");
    while (Authen == 1){
        option = display_menu();
        system("clear");
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
                Authen = 0;
                break;
            default:
                printf("Invalid input\n");
                break;
        }
        
    }
    return 0;
}