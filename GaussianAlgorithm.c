#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct dimension
{
    int row;
    int col;
};

struct fraction
{
    int numer;
    int denom;
};

struct fraction multifrac(struct fraction, struct fraction);
struct fraction addifrac(struct fraction, struct fraction);
struct fraction reciprocal(struct fraction);
struct fraction reduce(struct fraction);

void add(double **matrix, struct dimension space, int row1, int row2, double multiple);
void swap(double **matrix, struct dimension space, int row1, int row2);
void multiply(double **matrix, struct dimension space, int row1, double multiple);
void gaussianSolve(double **matrix, struct dimension space);
void printMatrix(double **matrix, struct dimension space);

main(){
    struct dimension space;
    printf("Enter the row amount: ");
    scanf("%d", &space.row);
    printf("Enter the column amount: ");
    scanf("%d", &space.col);
    
    double * * matrix = malloc(sizeof(double) * space.col);

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

    printf("%lf\n",matrix[0][0]);

    printMatrix(matrix, space);

    printf("\nSolving...\n\n");

    gaussianSolve(matrix, space);

    printMatrix(matrix, space);
    
    for(int i = 0;i < space.col; i++){
        free(matrix[i]);
    }
    free(matrix);
}

void gaussianSolve(double **matrix, struct dimension space){
    for(int n = 0;n < space.row;n++){//repeat solve for each row
        int i = 0;
        for(i = n;i < space.col;i++){//go down...
            printf("%lf",matrix[n][i]);
            if(matrix[n][i] != 0){//...column n and find a non-zero value in row i
                swap(matrix, space, i, n);//swap row i and row n
                break;
            }
        }//end loop. Either non-zero value found and swapped and now in row n, or i has reached the end of the column (i = space.col)
        i = n;
        if (i != space.col)//only do the rest if there is space down the column
        {
            printf("\n==\nI = %d\n==\n",i);
            double multiple = 1.0/matrix[i][n];
            multiply(matrix, space, n, multiple);//set first non-zero number in row n to 1
            for (int j = n + 1; j < space.col; j++)//for each row below row n, add a value such where the values in column n become zero
            {//-value column n row j / column n row n =  multiple
                add(matrix, space, j, n, -(matrix[n][j])/(matrix[n][n]));
            }
            
        }//finished of column n, now column n has some number of 0 below a 1, or all 0s.
        
    }

    //Reduced Row Echelon Form:

    //TODO

    
}
//TODO:
//Change to fractions
//GUI
//Ncurses


void printMatrix(double **matrix, struct dimension space){
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

void swap(double **matrix, struct dimension space, int row1, int row2){

    printMatrix(matrix, space);

    printf("\nSwapping...\n");

    for (int i = 0; i < space.col; i++)
    {
        double temp = matrix[i][row1];

        matrix[i][row1] = matrix[i][row2];

        matrix[i][row2] = temp;
    }
    
    printMatrix(matrix, space);

    
}

void add(double **matrix, struct dimension space, int row1, int row2, double multiple){

    printMatrix(matrix, space);

    printf("\nAdding...%lf\n", multiple);

    for (int i = 0; i < space.col; i++)
    {
        matrix[i][row1] += matrix[i][row2] * multiple;
    }

    printMatrix(matrix, space);
}

void multiply(double **matrix, struct dimension space, int row1, double multiple){

    printMatrix(matrix, space);

    printf("\nMultiplying...%lf\n", multiple);

    if (multiple == 0 || multiple == INFINITY || multiple == -INFINITY)
    {
        printf("Multiplication Failed!\n");
        return;
    }
    

    for (int i = 0; i < space.col; i++)
    {
        matrix[i][row1] *= multiple;
    }

    printMatrix(matrix, space);
    
}

struct fraction multifrac(struct fraction tar1, struct fraction tar2){
    
    struct fraction goal;

    goal.denom = tar1.denom * tar2.denom;

    goal.numer = tar1.numer * tar2.numer;
    
    return goal;
}
struct fraction addifrac(struct fraction, struct fraction);


struct fraction reciprocal(struct fraction target){
    struct fraction goal;
    goal.numer = target.denom;
    goal.denom = target.numer;
    return goal;
}

struct fraction reduce(struct fraction target){
    int gcf = 1;

    int bed = min(target.numer,target.denom);

    for (int i = 0; i < bed; i++)
    {
        if (target.numer % i == 0 && target.denom % i == 0)
        {
            gcf = i;
        }
        
    }

    struct fraction goal;

    goal.numer = target.numer/gcf;
    goal.denom = target.denom/gcf;
    return goal;
}