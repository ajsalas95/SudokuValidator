#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct {                //Data passed into functions
    int row;                    //#of rows
    int column;                 // # of columns
    int lowerRow;               //upper and lower bounds of the 9 subgrids
    int upperRow;
    int lowerColumn;
    int upperColumn;
    int checkedPosition;        //position of the array used to check the soduku solution
} parameters;
void *checkSubGrid(void *d);
void *checkRow(void *d);
void *checkColumn(void *d);

int a[11];                      //array used to check the soduku solution

int main(void) {
    printf("CS149 Sudoku from Alejandro Salas\n");
    int i, j;
    int checked = 0;
    pthread_t tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8, tid9, tid10, tid11;   //thread ids and attribute
    pthread_attr_t attr;
    pthread_attr_init(&attr);                        //initialize the thread attributes
    for(i = 0; i<11; i++){                          //initialize the the array used to check the sudoku solution
        a[i] = 0;
    }
    
    parameters *data = (parameters *) malloc(sizeof(parameters));   //cread the the data structure
    data->row = 9;
    data->column = 9;
    data->lowerColumn = 0;
    data->upperColumn =3;
    data->lowerRow =0;
    data->upperRow =3;
    data->checkedPosition = 0;
    
    int grid[9][9] = {{6,5,3,1,2,8,7,9,4}, {1,7,4,3,5,9,6,8,2}, {9,2,8,4,6,7,5,3,1}, {2,8,6,5,1,4,3,7,9}, {3,9,1,7,8,2,4,5,6},{5,4,7,6,9,3,2,1,8}, {8,6,5,2,3,1,9,4,7},{4,1,2,9,7,5,8,6,3},{7,3,9,8,4,6,1,2,5}};
    
    for(i = 0; i<9; i++){
        for(j = 0; j<9; j++ ) {                             //the sudoku solution
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
    
    //call the 11 threads and update the data structure
    pthread_create(&tid1, &attr, checkRow, (void*) data);
    pthread_join(tid1,NULL);
    data->checkedPosition = 1;
    
    pthread_create(&tid2, &attr, checkColumn, (void*) data);
    pthread_join(tid2,NULL);
    data->checkedPosition = 2;
    
    pthread_create(&tid3, &attr, checkSubGrid, (void*) data);
    pthread_join(tid3,NULL);
    data->checkedPosition = 3;
    data->lowerRow =0;
    data->upperRow =3;
    data->lowerColumn = 3;
    data->upperColumn =6;
    
    pthread_create(&tid4, &attr, checkSubGrid, (void*) data);
    pthread_join(tid4,NULL);
    data->checkedPosition = 4;
    data->checkedPosition = 3;
    data->lowerRow =0;
    data->upperRow =3;
    data->lowerColumn = 6;
    data->upperColumn =9;
    
    pthread_create(&tid5, &attr, checkSubGrid, (void*) data);
    pthread_join(tid5,NULL);
    data->checkedPosition = 5;
    data->checkedPosition = 3;
    data->lowerRow =3;
    data->upperRow =6;
    data->lowerColumn = 0;
    data->upperColumn =3;
    
    pthread_create(&tid6, &attr, checkSubGrid, (void*) data);
    pthread_join(tid6,NULL);
    data->checkedPosition = 6;
    data->lowerRow =3;
    data->upperRow =6;
    data->lowerColumn = 3;
    data->upperColumn =6;
    
    pthread_create(&tid7, &attr, checkSubGrid, (void*) data);
    pthread_join(tid7,NULL);
    data->checkedPosition = 7;
    data->lowerRow =3;
    data->upperRow =6;
    data->lowerColumn = 6;
    data->upperColumn =9;
    
    pthread_create(&tid8, &attr, checkSubGrid, (void*) data);
    pthread_join(tid8,NULL);
    data->checkedPosition = 8;
    data->lowerRow =6;
    data->upperRow =9;
    data->lowerColumn = 0;
    data->upperColumn =3;
    
    pthread_create(&tid9, &attr, checkSubGrid, (void*) data);
    pthread_join(tid9,NULL);
    data->checkedPosition = 9;
    data->lowerRow =6;
    data->upperRow =9;
    data->lowerColumn = 3;
    data->upperColumn =6;
    
    pthread_create(&tid10, &attr, checkSubGrid, (void*) data);
    pthread_join(tid10,NULL);
    data->checkedPosition = 10;
    data->lowerRow =6;
    data->upperRow =9;
    data->lowerColumn = 6;
    data->upperColumn =9;
    
    pthread_create(&tid11, &attr, checkSubGrid, (void*) data);
    pthread_join(tid11,NULL);
    
    for(i=0; i<11; i++) if(a[i] == 1) checked++;                        //check to see if the solution is valid
    if(checked==0) printf("valid Sudoku\n");
    else printf("not valid Sudoku\n");
    free(data);
    return 0;
}
void *checkRow(void *d) {                                               //check each row
    parameters *data = (parameters *) malloc(sizeof(parameters));
    data = d;
    int check[9] = {0,0,0,0,0,0,0,0,0};
    int i, j;
    for(i =0; i<data->column; i++) {
        for(j=0; j<data->row; j++) {
            if (data->grid[i][j] == 1) check[0] = check[0] +1;
            if (data->grid[i][j] == 2) check[1] = check[1] +1;
            if (data->grid[i][j] == 3) check[2] = check[2] +1;
            if (data->grid[i][j] == 4) check[3] = check[3] +1;
            if (data->grid[i][j] == 5) check[4] = check[4] +1;
            if (data->grid[i][j] == 6) check[5] = check[5] +1;
            if (data->grid[i][j] == 7) check[6] = check[6] +1;
            if (data->grid[i][j] == 8) check[7] = check[7] +1;
            if (data->grid[i][j] == 9) check[8] = check[8] +1;
        }
    }
    for(i=0; i<9; i++) {if(check[i]<9 || check[i]>9) {a[data->checkedPosition] = 1;}}
    pthread_exit(0);
}

void *checkColumn(void *d) {                                            //check each column
    parameters *data = (parameters *) malloc(sizeof(parameters));
    data = d;
    int check[9] = {0,0,0,0,0,0,0,0,0};
    int i;
    int j;
    for(i =0; i<data->row; i++) {
        for(j=0; j<data->column; j++) {
            if (data->grid[j][i] == 1) check[0] = check[0] +1;
            if (data->grid[j][i] == 2) check[1] = check[1] +1;
            if (data->grid[j][i] == 3) check[2] = check[2] +1;
            if (data->grid[j][i] == 4) check[3] = check[3] +1;
            if (data->grid[j][i] == 5) check[4] = check[4] +1;
            if (data->grid[j][i] == 6) check[5] = check[5] +1;
            if (data->grid[j][i] == 7) check[6] = check[6] +1;
            if (data->grid[j][i] == 8) check[7] = check[7] +1;
            if (data->grid[j][i] == 9) check[8] = check[8] +1;
        }
    }
    for(i=0; i<9; i++) {if(check[i]<9 || check[i]>9) {a[data->checkedPosition] = 1;}}
    pthread_exit(0);
}

void *checkSubGrid(void *d) {                                           //check the 9 3x3 grids within the soduku
    parameters *data = (parameters *) malloc(sizeof(parameters));
    data = d;
    int check[9] = {0,0,0,0,0,0,0,0,0};
    int subgrid[3][3];
    int i, j;
    for(i=data->lowerRow;i<data->upperRow;i++) {
        for(j=data->lowerColumn; j<data->upperColumn; j++){
            subgrid[i-data->lowerRow][j-data->lowerColumn] = data->grid[i][j];
        }
    }
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if (subgrid[i][j] == 1) check[0] = check[0] +1;
            if (subgrid[i][j] == 2) check[1] = check[1] +1;
            if (subgrid[i][j] == 3) check[2] = check[2] +1;
            if (subgrid[i][j] == 4) check[3] = check[3] +1;
            if (subgrid[i][j] == 5) check[4] = check[4] +1;
            if (subgrid[i][j] == 6) check[5] = check[5] +1;
            if (subgrid[i][j] == 7) check[6] = check[6] +1;
            if (subgrid[i][j] == 8) check[7] = check[7] +1;
            if (subgrid[i][j] == 9) check[8] = check[8] +1;
        }
    }
    for(i=0; i<9; i++) {if(check[i]!=1) {a[data->checkedPosition] = 1;}}
    pthread_exit(0);
}