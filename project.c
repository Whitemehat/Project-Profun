#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int list_patient()
{
    
}

int add_patient_info()
{

}

int search()
{

}

int update()
{

}

int delete()
{

}

int menu()
{
    printf("###########################################\n");
    printf("1. list patient health information\n");
    printf("2. add the patient information\n");
    printf("3. search from name / congential disease\n");
    printf("4. update age / congential disease\n");
    printf("5. delete patient information\n");
    printf("###########################################\n");
}

int display_menu()
{
    int option;
    menu();
    printf("Enter your option : ");
    scanf("%d" , &option);
    return option;
}

int read_csv()
{
    FILE *fp = fopen("info.csv" , "r");
    if(fp == NULL)
    {
        printf("Failed to open file for reading\n");
        exit(1);
    }
    char text[MAX_LINE];
    while(fgets(line , sizeof(text) , fp))
    {
        char *token = strtok(text , ",")
        while(token != NULL)
        {
            printf("%s\t" , token);
            token = strtok(NULL , ",");
        }
        printf("\n");
    }
    fclose(fp);
}

int write_csv(char name , char age , char congential , char date)
{
    FILE *fp = fopen("info.csv" , "w");
    if(fp == NULL)
    {
        printf("Failed to open file to writing");
        exit(1);
    }

}

int main()
{
    int option;
    while (1){    
        option = display_menu();
        switch (option)
        {
            case 1:
                list_patient();
                break;
            case 2:
                add_patient_info();
                break;
            case 3:
                search();
                break;
            case 4:
                update();
                break;
            case 5:
                delete();
                break;
            default:
                printf("Invalid input\n");
        }
    }
    
    return 0;
}