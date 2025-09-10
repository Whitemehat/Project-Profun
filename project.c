#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 1024

typedef struct {
    char name[50];
    int age;
    char disease[100];
    char date[20];
}Patient;

Patient *patients = NULL;
int patient_count = 0;

int sort_patient(const char *keyword){
    int i;
    for(i = 0 ;i < patient_count;i++)
    {
        if(strstr(patients[i].name , keyword) || strstr(patients[i].disease , keyword))
        {
            return i;
        }
    }
    return -1;
}

int check_condition(char *condition){
    int state = 0;
    char c = condition[0];
    if('A' <= c && c <= 'Z')
    {
        c = c + 32;
    }
    return (c == 'y');

}

void load_csv(const char *filename)
{
    FILE *fp = fopen(filename , "r");
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
        return;
    }
    while (fgets(text, sizeof(text) , fp)){
        char *name = strtok(text , ",");
        char *age = strtok(NULL , ",");
        char *disease = strtok(NULL , ",");
        char *date = strtok(NULL , ",\n");

        if(name && age && disease && date)
        {
            patients = realloc(patients , (patient_count + 1) * sizeof(Patient));
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

void save_csv(const char *filename)
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
        fprintf(fp, "%s,%d,%s,%s\n",patients[i].name , 
                                    patients[i].age,
                                    patients[i].disease,
                                    patients[i].date);
    }
    fclose(fp);
}

void list_patient()
{
    if(patient_count == 0)
    {
        printf("No patient Yet!");
        return;
    }
    for(int i = 0 ; i < patient_count;i++)
    {
        printf("Patient [%d] , Name : %s , Age : %d , Disease : %s , Date : %s\n\n" , 
            i+1 , patients[i].name , patients[i].age , patients[i].disease , patients[i].date);
    }
}

void add_patient()
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

    patients = realloc(patients , (patient_count + 1) * sizeof(Patient));
    if(!patients){
        perror("Memmory allocation failed");
        exit(1);
    }
    patients[patient_count++] = p;
    printf("Patient added!\n");
}

void search()
{
    char keyword[50];
    printf("Enter name or disease to search : ");
    scanf(" %[^\n]" , keyword);
    int i = sort_patient(keyword);
    if(i != -1)
    {
        printf("Patient [%d]\nName : %s\nAge : %d\nDisease : %s\nDate : %s\n" , 
        i+1 , patients[i].name , patients[i].age , patients[i].disease , patients[i].date); 
    }   
    else{
        printf("No match found!");
    }
}

void update_patient()
{
    char name[50];
    char condition[4];
    printf("Enter Pateint name for Update: ");
    scanf(" %[^\n]" , name);
    int i = sort_patient(name);
    if(i == -1)
    {
        printf("Patient not found!");
        return;
    }
    printf("Patient [%d]\nName : %s\n" , i+1 , patients[i].name);
    printf("Yes / no : ");
    scanf(" %[^\n]" , condition);
    if(check_condition(condition))
    {
        int new_age;
        char new_disease[50];
        printf("Enter new age (0 for no change) : ");
        scanf("%d" , &new_age);
        printf("Enter new disease (- for no change): ");
        scanf(" %[^\n]" , new_disease);
        if(new_age != 0)
        {
            patients[i].age = new_age;
        }
        if(strcmp(new_disease , "-") != 0)
        {
            strcpy(patients[i].disease , new_disease);
        }
        for(int i = 0;i<5;i++)
        {
            printf(".");
            fflush(stdout);
            usleep(500000);
        }
        printf("Updated!\n");
    }
}

void delete_patient()
{
    char name[50];
    printf("Enter the patient name to delete: ");
    scanf(" %[^\n]" , name);
    int i = sort_patient(name);
    if(i != -1)
    {
        for(int j = i;j < patient_count-1;j++)
        {
            patients[j] = patients[j+1];
        }
        patient_count--;
        patients = realloc(patients , patient_count * sizeof(Patient));
        printf("Deleted successfully!");
        return;
    }
    else{
        printf("Patient not found!");
    }
}

void menu()
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
    char filename[9] = "data.csv";
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
            default:
                printf("Invalid input\n");
        }
        sleep(2);
    }
    
    return 0;
}