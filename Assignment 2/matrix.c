#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_SIZE 100
#define MAX_LENGTH 200
#define MAX_LINE_LENGTH 701

int act_first_row, act_first_col;
int act_second_row, act_second_col;
int tp_row, tp_col;

double mat1[MAX_SIZE][MAX_SIZE]; //1st matrix
double mat2[MAX_SIZE][MAX_SIZE]; //2nd matrix
double tp_mat2[MAX_SIZE][MAX_SIZE]; //transpose of 2nd matrix
double add1[MAX_SIZE][MAX_SIZE]; //normal add
double add2[MAX_SIZE][MAX_SIZE]; //add first mat with transpose of second mat

bool checkIfDimension(char *line, int length){
    for(int i = 0; i < length; i++){
        if(line[i] == '.'){
            return false;
        }
    }
    return true;
}

double getter(double matrix[MAX_SIZE][MAX_SIZE], int i, int j){
    assert(i <= MAX_SIZE && i >= 0 && j <= MAX_SIZE && j >= 0);
    return matrix[i][j];
}

void setter(double matrix[MAX_SIZE][MAX_SIZE], int i, int j, double value){
    //idk wut i've done
    assert(i <= MAX_SIZE && i >= 0 && j <= MAX_SIZE && j >= 0);
    matrix[i][j] = value;
}

//set all matrix zero
void set_zero(){
    for(int i = 0; i < MAX_SIZE; i++){
        for(int j = 0; j < MAX_SIZE; j++){
            setter(mat1, i, j, 0);
            setter(mat2, i, j, 0);
            setter(tp_mat2, i, j, 0);
            setter(add1, i, j, 0);
            setter(add2, i, j, 0);
        }
    }
}

void read_file(){
    FILE *f = stdin;
    char line[1000];
    char delimiters[] = " \t \0 \n";
    int trackRow = 0, trackFirstMat = 0;

    while(fgets(line, 1000, f) != NULL){
        int row = 0, column = 0;
        assert(strlen(line) <= MAX_LENGTH); //precondition to check if maximum content of a line is less than 701
        int length = strlen(line);

        //if the line is dimension of the matrix
        if(checkIfDimension(line, length)){
            char *token = strtok(line, delimiters);
            row = atoi(token);
            token = strtok(NULL, delimiters);
            column = atoi(token);
            trackRow = 0;
            //set dimensions for the first matrix
            if(mat1[0][0] == 0){
                act_first_row = row;
                act_first_col = column;
                trackFirstMat = act_first_row;
                printf("%d %d\n", act_first_row, act_first_col);
            }
            //set dimensions for the second matrix
            else{
                act_second_row = row;
                act_second_col = column;
                printf("%d %d\n", act_second_row, act_second_col);
            }
        }
        //if the line is entry of matrix
        else{
            if(trackFirstMat != 0){
                int i = 0;                   
                char *token = strtok(line, delimiters);
                setter(mat1, trackRow, i, atof(token));
                printf("%.2f ", mat1[trackRow][i]);
                for(i = 1; i < act_first_col; i++){
                    token = strtok(NULL, delimiters);
                    setter(mat1, trackRow, i, atof(token));
                    printf("%.2f ", getter(mat1, trackRow, i));
                }
                printf("\n");
                --trackFirstMat;
            }
            else{
                int i = 0;
                char *token = strtok(line, delimiters);
                setter(mat2, trackRow, i, atof(token));
                printf("%.2f ", mat2[trackRow][i]);
                for(i = 1; i < act_second_col; i++){
                    token = strtok(NULL, delimiters);
                    setter(mat2, trackRow, i, atof(token));
                    printf("%.2f ", getter(mat2, trackRow, i));
                }
                printf("\n");
            }
            ++trackRow;
        }
    }
    assert(act_first_col >= 0 && act_first_col <= MAX_SIZE && act_first_row >= 0 && act_first_row <= MAX_SIZE && act_second_col >= 0 && act_second_col <= MAX_SIZE && act_second_row >= 0 && act_second_row <= MAX_SIZE);
    printf("\n");
}

void add(double matrix1[MAX_SIZE][MAX_SIZE], double matrix2[MAX_SIZE][MAX_SIZE], double matrix[MAX_SIZE][MAX_SIZE],int row1, int row2, int col1, int col2){
    assert(row1 >= 0 && row1 <= MAX_SIZE && col1 >= 0 && col1 <= MAX_SIZE && row2 >= 0 && row2 <= MAX_SIZE && col2 >= 0 && col2 <= MAX_SIZE);
    int row = (row1 < row2) ? row2 : row1;
    int col = (col1 < col2) ? col2 : col1;

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            double value = matrix1[i][j] + matrix2[i][j];
            setter(matrix, i, j, value);
            printf("%.2f ", getter(matrix, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

void transpose(double matrix[MAX_SIZE][MAX_SIZE], double transpose[MAX_SIZE][MAX_SIZE], int row, int col){
    assert(row >= 0 && row <= MAX_SIZE && col >= 0 && col <= MAX_SIZE);
    tp_col = row; 
    tp_row = col;

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            setter(transpose, j, i, matrix[i][j]);
        }
    }
}
void print(double matrix[MAX_SIZE][MAX_SIZE], int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%.2f ", getter(matrix, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    read_file();
    add(mat1, mat2, add1, act_first_row, act_second_row, act_first_col, act_second_col);
    transpose(mat2, tp_mat2, act_second_row, act_second_col);
    print(tp_mat2, tp_row, tp_col);
    add(mat1, tp_mat2, add2, act_first_row, tp_row, act_first_col, tp_col);

    return 0;
}