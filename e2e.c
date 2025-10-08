#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// declare main from your program
int main_program(); // rename your main() to main_program in main.c

void e2e_add_patient() {
    // Prepare input (simulate user actions)
    FILE *input = fopen("./E2E/input_add.txt", "w");
    fprintf(input,
        "Agent 32\n"        // username (for login)
        "A$3nt32\n"     // password
        "2\n"            // menu -> add patient
        "Charlie\n"      // name
        "40\n"           // age
        "Asthma\n"       // disease
        "2025-01-01\n"   // date
        "1\n"            // menu -> list patient
        "6\n"            // menu -> exit
    );
    fclose(input);

    // Redirect stdin to input.txt
    freopen("./E2E/input_add.txt", "r", stdin);

    // Redirect stdout to output.txt
    freopen("./E2E/output_add.txt", "w", stdout);

    // Run program
    main_program();

    // Reset stdout/stdin
    freopen("/dev/tty", "w", stdout);
    freopen("/dev/tty", "r", stdin);

    // Verify output 
    FILE *output = fopen("./E2E/output_add.txt", "r");
    char buffer[1024];
    int found_charlie = 0;
    while (fgets(buffer, sizeof(buffer), output)) {
        if (strstr(buffer, "Charlie") != NULL) {
            found_charlie = 1;
            break;
        }
    }
    fclose(output);

    assert(found_charlie == 1);

    printf("E2E add patient test passed!\n");
    
}

void e2e_delete_patient(){
    FILE *fp = fopen("./E2E/input_del.txt" , "w");
    fprintf(fp , 
            "Agent 32\n"
            "A$3nt32\n"
            "5\n" 
            "Charlie\n"
            "y\n"
            "1\n"
            "6\n"         
    );
    fclose(fp);
    
    freopen("./E2E/input_del.txt", "r", stdin);

    freopen("./E2E/output_del.txt", "w", stdout);

    main_program();
    
    freopen("/dev/tty" , "w" , stdout);
    freopen("/dev/tty" , "r" , stdin);

    FILE *output = fopen("./E2E/output_del.txt" , "r");
    char buffer[1024];
    int success = 0;
    while(fgets(buffer , sizeof(buffer) , output)){
        if(strstr(buffer , "Charlie") == NULL){
            success = 1;
            break;
        }
    }
    fclose(output);

    assert(success == 1);
    
    printf("E2E delete test passed!\n");
}

void e2e_search(){
    FILE *input = fopen("./E2E/input_search.txt" , "w");
    fprintf(input ,
            "Agent 32\n"
            "A$3nt32\n"
            "3\n"
            "Peter\n"
            "6\n"
    );
    fclose(input);
    
    freopen("./E2E/input_search.txt", "r" , stdin);
    freopen("./E2E/output_search.txt", "w" , stdout);

    main_program();

    freopen("/dev/tty" , "w" ,stdout);
    freopen("/dev/tty" , "r" ,stdin);
    FILE *output = fopen("./E2E/output_search.txt" , "r");
    char name[1024];
    int found = 0;
    while(fgets(name , sizeof(name) , output)){
        if(strstr(name , "Peter") != NULL){
            found = 1;
            break;
        }
    }
    fclose(output);
    assert(found == 1);

    printf("E2E search test success!\n");
}

void e2e_update(){
    FILE *input = fopen("./E2E/input_update.txt" , "w");
    fprintf(input ,
            "Agent 32\n"
            "A$3nt32\n"
            "4\n"
            "Peter\n"
            "No\n"
            "Yes\n"
            "19\n"
            "-\n"
            "2025-10-07\n"
            "1\n"
            "6\n"            
    );
    fclose(input);

    freopen("./E2E/input_update.txt" , "r" , stdin);
    freopen("./E2E/output_update.txt" , "w" , stdout);

    main_program();

    freopen("/dev/tty" , "w" , stdout);
    freopen("/dev/tty" , "r" , stdin);

    char line[1024];
    int success = 0;
    FILE *output = fopen("./E2E/output_update.txt" , "r");
    while(fgets(line , sizeof(line) , output)){
        if ((strstr(line, "Peter") != NULL) &&
            (strstr(line, "19") != NULL) &&
            (strstr(line, "Flu") != NULL) &&
            (strstr(line, "2025-10-07") != NULL))
            {
                success = 1;
                break;
            }
        
    }
    fclose(output);
    assert(success == 1);
    
    printf("E2E update test success!\n");
    

}

int main() {
    e2e_add_patient();
    e2e_delete_patient();
    e2e_search();
    e2e_update();
    return 0;
}
