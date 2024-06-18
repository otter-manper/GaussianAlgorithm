#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct 
{
    int row;
    int col;
}dimension; 

void add(double **matrix,  dimension space, int row1, int row2, double multiple);
void swap(double **matrix,  dimension space, int row1, int row2);
void multiply(double **matrix,  dimension space, int row1, double multiple);
void gaussianSolve(double **matrix,  dimension space);
void printMatrix(double **matrix,  dimension space);

main(){
    dimension space;
    printf("Enter the row amount: ");
    scanf("%d", &(space.row));
    printf("Enter the column amount: ");
    scanf("%d", &(space.col));
    
    double * * matrix = malloc(sizeof(double*) * space.col);

    for(int i = 0;i < space.col; i++){
        matrix[i] = malloc(sizeof(double) * space.row);
    }

    for (int i = 0; i < space.col; i++)
    {
        for (int j = 0; j < space.row; j++)
        {
            printf("Enter the number for row %d, column %d: ",j+1, i+1);
            scanf("%lf", &matrix[i][j]);
        }
    }

    

    printMatrix(matrix, space);

    printf("\nSolving...\n\n");

    gaussianSolve(matrix, space);

    printMatrix(matrix, space);
    
    for(int i = 0;i < space.col; i++){
        free(matrix[i]);
    }
    free(matrix);
    
}

void gaussianSolve(double **matrix, dimension space){


    //ROW ECHELON FORM
    for(int n = 0;n < space.row;n++){//repeat solve for each row
        
        int i = 0;
        for(i = n;i < space.col;i++){//go down...
            
            if(matrix[i][n] != 0){//...column n and find a non-zero value in row i
                swap(matrix, space, i, n);//swap row i and row n
                break;
            }
        }//end loop. Either non-zero value found and swapped and now in row n, or i has reached the end of the column (i = space.col)
        i = n;
        if (i != space.row-1)//only do the rest if there is space down the column
        {
            
            double multiple = 1.0/matrix[i][n];
            multiply(matrix, space, n, multiple);//set first non-zero number in row n to 1
            for (int j = n + 1; j < space.col; j++)//for each row below row n, add a value such where the values in column n become zero
            {//-value column n row j / column n row n =  multiple
                add(matrix, space, j, n, -(matrix[n][j])/(matrix[n][n]));
            }
            
        }//finished of column n, now column n has some number of 0 below a 1, or all 0s.
        else{
            double multiple = 1.0/matrix[i][n];
            multiply(matrix, space, n, multiple);
        }
    }

    //************************************************************************************************** */
    //
    //          MATRIX IS NOW IN ROW ECHELON FORM
    //
    //************************************************************************************************** */

    printMatrix(matrix, space);

    printf("\nReducing...\n\n");

    //REDUCED ROW ECHELON FORM
    for(int n = 1;n < space.row;n++){//repeat solve for each leading 1 in row
        
        int i;
        for (i = 1; i < space.col && matrix[i][n] == 0; i++)//find that leading 1 (continue down the matrix until you see a non-zero number, which will be 1 because REF)
        {}//The for loop only needs to get the value of i

        if (i == space.col)
        {
            i = i-1;
        }
        

        if (matrix[i][n] != 0)
        {
            
            for (int j = i-1; j >= 0; j--)//Go up column and add to set all values above to 0
            {
                add(matrix, space, j, n, -(matrix[n][j])/(matrix[n][n]));
            }
        }
        
            
    }
  

    return;
    
}

void printMatrix(double **matrix,  dimension space){
    printf("\n");
    for (int i = 0; i < space.row; i++)
    {
        for (int j = 0; j < space.col; j++)
        {
            printf("%lf ", matrix[j][i]);
        }
        printf("\n");
    }
}

void swap(double **matrix,  dimension space, int row1, int row2){

    if(row1 == row2){
        return;
    }
    

    for (int i = 0; i < space.col; i++)
    {
        double temp = matrix[i][row1];

        matrix[i][row1] = matrix[i][row2];

        matrix[i][row2] = temp;
    }
    
    

    
}

void add(double **matrix,  dimension space, int row1, int row2, double multiple){

    

    for (int i = 0; i < space.col; i++)
    {
        matrix[i][row1] += matrix[i][row2] * multiple;
    }

  
}

void multiply(double **matrix,  dimension space, int row1, double multiple){

    

    if (multiple == 0 || multiple == INFINITY || multiple == -INFINITY)
    {
        printf("Multiplication Failed!\n");
        return;
    }
    

    for (int i = 0; i < space.col; i++)
    {
        matrix[i][row1] *= multiple;
    }

   
    
}
