#include <stdio.h>
#include <stdlib.h>

// matrix struct
struct Matrix {
    int rows;
    int cols;
    int **matrix;
};

// multiplication function
// !for some reason it gives error on calling by reference or as ptr, therefore some memory leaks may bethere
struct Matrix matmul(struct Matrix m1, struct Matrix m2){
    // make net matric for multiplication
    struct Matrix mult;

    // give rows and cols
    mult.rows = m1.rows;
    mult.cols = m2.cols;

    // allocate memory for 2D matrix
    mult.matrix = malloc(mult.rows);
    for(int  i = 0; i < mult.rows; i++){
        mult.matrix[i] = malloc(mult.cols);
    }

    // multiplication, same as always :)
    for(int i = 0; i < m1.rows; i++)
        for(int j = 0; j < m2.cols; j++){
            mult.matrix[i][j] = 0; //setting initial to zero, so that things can be added
            for(int k = 0; k < m1.cols; k++)
                mult.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
        }

    return mult;
}


int main (int argc, char *argv[]) {

    // cehcking if both files are inputted
    // * another way done in q2, both are fine but 2nd is better less amount of checks
    if(argv[0] == NULL || argv[1] == NULL) {
        printf("Input filenames are empty! Please enter filenames...");
        exit(-1);
    }

    // loading both files
    FILE *iFile1 = fopen(argv[1], "r");
    FILE *iFile2 = fopen(argv[2], "r");
    // cehcking if file DNE
    if (iFile1 == NULL || iFile2 == NULL){
        printf("Input files donot exist! Please enter a valid filename...");
        exit(-2);
    }

    // declaring initial 2 matrixes
    struct Matrix mat1, mat2;
    // declaring line reader, max of 10 digit numbers can be done
    char line[10];

    // reading initial line for dims of matrixes
    fscanf(iFile1, "%s", line);
    mat1.rows = atoi(line);
    fscanf(iFile1, "%s", line);
    mat1.cols = atoi(line);

    fscanf(iFile2, "%s", line);
    mat2.rows = atoi(line);
    fscanf(iFile2, "%s", line);
    mat2.cols = atoi(line);

    // cehcking for multiplicity
    if(mat1.cols != mat2.rows){
        printf("Matrices are not multiplicable!");
        exit(-4);
    }

    // allocating memory to both matrixes
    mat1.matrix = malloc(mat1.rows);
    for(int i = 0; i < mat1.rows; i++){
        mat1.matrix[i] = malloc(mat1.cols);
        for(int j = 0; j < mat1.cols; j++){
            fscanf(iFile1, "%s", line);
            mat1.matrix[i][j] = atoi(line);
        }
    }

    mat2.matrix = malloc(mat2.rows);
    for(int i = 0; i < mat2.rows; i++){
        mat2.matrix[i] = malloc(mat2.cols);
        for(int j = 0; j < mat2.cols; j++){
            fscanf(iFile1, "%s", line);
            mat2.matrix[i][j] = atoi(line);
        }
    }
    

    // multiplying
    struct Matrix mult = matmul(mat1, mat2);
    // printing matrix product

    // checking if output file or console
    if(argc == 4){
        FILE *outfile;
        outfile = fopen(argv[3], "w"); // output file in write mode, creates if DNE, erases if exists

        fprintf(outfile, "%d %d\n", mult.rows, mult.cols);
        for(int i = 0; i < mult.rows; i++){
            for(int j = 0; j < mult.cols; j++){
                fprintf(outfile, "%d", mult.matrix[i][j]);
            }
            fprintf(outfile, "\n"); //newline
        }
    } else {
        printf("%d %d\n", mult.rows, mult.cols);
        for(int i = 0; i < mult.rows; i++){
            for(int j = 0; j < mult.cols; j++){
                printf("%d", mult.matrix[i][j]);
            }
            printf("\n");
        }
    }



    // cleanup close files and deallocate memory
    fclose(iFile1);
    fclose(iFile2);
    
    for(int i = 0; i < mat1.rows; i++) free((void *) mat1.matrix[i]);
    for(int i = 0; i < mat2.rows; i++) free((void *) mat2.matrix[i]);
    for(int i = 0; i < mult.rows; i++) free((void *) mult.matrix[i]);
    free((void *) mat1.matrix);
    free((void *) mat2.matrix);
    free((void *) mult.matrix);

    return 0;
}