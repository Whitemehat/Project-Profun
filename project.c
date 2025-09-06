#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

typedef struct {
    char name[50];
    int age;
    char disease[100];
    char date[20];
}Patient;

Patient *patient = NULL;
int patient_count = 0;

int load_csv(const char *filename)
{
    FILE *fp = fopen("info.csv" , "r");
    if(fp == NULL)
    {
        printf("Failed to open file for reading\n");
        return;
    }
    char text[MAX_LINE];
    if(fgets(text , sizeof(text) , fp) == NULL)
    {
        printf("Empty File!\n");
        fclose(fp);
    }
    while (fgets(text, sizeof(text) , fp)){
        char *name = strtok(line , ",");
        char *age = strtok(NULL , ",");
        char *disease = strtok(NULL , ",");
        char *date = strtok(NULL , ",\n");

        if(name && age && disease && date)
        {
            patients = realloc(patient , (patient-count + 1) * sizeof(Patient))
            if(!patients)
            {
                perror("Memory allocation failed");
                exit(1);
            }
            strcpy(patients[patient_count].name , name);
            patients[patient_count].age = atoi(age);
            strcpy(patients[patient_count].disease , disease);
            strcpy(patients[patient_count].date , date);
            patient_count++;
        }
    }
    fclose(fp);
}

int save_csv(const char *filename)
{
    FILE *fp = fopen(filename , "w");
    if(!fp)
    {
        printf("Failed to saving file");
        return;
    }
    fprintf(fp , "name,age,congenital-disease,date\n");
    for(int i = 0;i < patient_count; i++)
    {
        fprintf(fp, "%s,%d,%s,%s\n",patient[i].name , 
                                    patient[i].age,
                                    patient[i].disease,
                                    patient[i].date);
    }
    fclose(fp);
}

int list_patient()
{
    if(patient_count == 0)
    {
        printf("No patient Yet!");
        return;
    }
    for(int i = 0 ; i < patient_count;i++)
    {
        printf("Patient [%d]
                Name : %s\n
                Age : %d\n
                Disease : %s\n
                Date : %s\n" , i+1 , patients[i].name , patient[i].age , patient[i].disease , patient[i].date);
    }
}

int add_patient()
{
    Patient p;
    printf("Enter name : ");
    scanf(" %[^\n]" , p.name);
    printf("Enter age : ");
    scanf(" %d" , &p.age);
    printf("Enter Disease : ");
    scanf(" %[^\n]" , p.disease);
    printf("Enter date (YYYY-MM-DD) : ");
    scanf(" %[^\n]" , p.date);

    patient = realloc(patient , (patient_count + 1) * sizeof(Patient));
    if(!patients){
        perror("Memmory allocation failed");
        exit(1);
    }
    patients[patient_count++] = p;
    printf("Patient added!\n");
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





int main()
{
    int option;
    load_csv("data.csv");
    while (1){    
        option = display_menu();
        switch (option)
        {
            case 1:
                list_patient();
                break;
            case 2:
                save_csv(filename);
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