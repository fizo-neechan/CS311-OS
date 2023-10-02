#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main (int argc, char *argv[]) {

    // cehcking if no input files
    if(argc <= 1){
        printf("Enter input files!");
        exit(-1);
    }

    // files array and loading files from args
    FILE *files[argc];
    for(int i = 1; i < argc; i++){
        files[i-1] = fopen(argv[i], "r");
        // check if files DNE
        if(files[i-1] == NULL){
            printf("File %s not found!... ", argv[i]);
            exit(-2);
        }
    }
    
    bool isEnd = false; //checks if all the files have reached EOF
    int size = 100; // declare line size variable
    char *line = malloc(size); // decalre line to readline into

    // file reading loop until all fptrs are EOF
    while(isEnd == false){
        isEnd = true; // set at every loop to true to see if all are good
        memset(line, '\n', 100); // set line to all \n at beginning of each loop

        // read line from files indicidually
        for(int i = 0; i < argc-1; i++){

            // if any file is EOF then dont read, just continue
            if(feof(files[i])) continue;
            // else set isEnd to run for another iteration
            else isEnd = false;

            // getline from file
            // !warning in compiler but runs, cross checked from documentation that its the better function instead of fgets() and syntax is correct...
            getline(&line, &size, files[i]);
            // print each line
            for(int j = 0; j < size; j++){
                if(line[j] == '\n') break;

                printf("%c", line[j]);
            }
            // add space after line from each file
            printf(" ");
        }
        printf("\n");
    }

    // clean up memory and close files
    for(int i = 1; i < argc; i++){
        fclose(files[i-1]);
    }

    free(line);

    return 0;
}