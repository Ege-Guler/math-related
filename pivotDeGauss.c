/*
    pivotDeGauss.c

    This program uses Gaussian elimination method to solve a system of 3 equations.

    Shout out to "https://github.com/oguzalpcakmak" for "dmatrix *makematrix(int cols, int rows);" function

    I haven't yet finished working on this project.

    Ege Guler - Galatasaray University
    04/17/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW 3
#define COL 4



typedef struct double_matrix //I had to use this method to return matrixs.
{
    int mval;
    struct double_matrix *mcol;
} dmatrix;

void readEquation(dmatrix* matrix); // reads system from "system.txt"
dmatrix *makematrix(int cols, int rows); //creates matrix
void printmatrix(dmatrix* matrix); //prints matrix
void multiplyEq(dmatrix* eq, int k, int row_num); //multiplies equation with constant
int lcm(int f_num, int s_num); // Calculates largest common factor
void pivotDeGauss(dmatrix* matrix);//Gaussian elimination method
int determinant(dmatrix* matrix);//Calculates determinant of 3x3 matrix


int main(void)
{
    dmatrix* matrix = makematrix(ROW, COL);
    readEquation(matrix);
    printmatrix(matrix);
    int systemDeterminant = determinant(matrix);
    printf("\nDeterminant of this system is: %d\n", systemDeterminant);
    if(determinant == 0)
    {
        printf("\nThis program is unable to solve systems with infinite or no solution\n");
        exit(EXIT_FAILURE);
    }
    
    

    pivotDeGauss(matrix);

    
    return 0;
}


void readEquation(dmatrix* matrix)
{
    FILE* fp = fopen("system.txt", "r");
    if(fp == NULL)
    {
        perror("Error: ");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < ROW; i++)
    {
        fscanf(fp, "%dx%dy%dz=%d\n", &matrix[i].mcol[0].mval,  &matrix[i].mcol[1].mval,  &matrix[i].mcol[2].mval,  &matrix[i].mcol[3].mval);

    }


}

dmatrix *makematrix(int rows, int cols)
{
    dmatrix *new_matrix = (dmatrix *)(malloc(sizeof(dmatrix)*rows));
    for(int i = 0; i < rows; i++)
    {
        new_matrix[i].mcol = (dmatrix *)(malloc(sizeof(dmatrix)*cols));
    }
    return new_matrix;
}

void printmatrix(dmatrix* matrix)
{
    printf("\n");

    for(int i = 0; i < ROW; i++)
    {
        
        for(int j = 0; j < COL; j++)
        {
            printf("%d ", matrix[i].mcol[j].mval);
        }
        printf("\n\n");
    }

}

int lcm(int f_num, int s_num)
{
    int max = (f_num > s_num) ? f_num : s_num;

    while(true)
    {
        if(max % f_num == 0 && max % s_num == 0)
        {
            break;
        }
        ++max;
    }

    return max;
}
void multiplyEq(dmatrix* eq, int k, int row_num)
{
    for(int i = 0; i < COL; i++)
    {
        eq[row_num].mcol[i].mval = eq[row_num].mcol[i].mval * k;
    }
}
void substractEq(dmatrix* eq, int f_row_num, int s_row_num)
{
    for(int i = 0; i < COL; i++)
    {
        eq[s_row_num].mcol[i].mval -= eq[f_row_num].mcol[i].mval;
    }
}

void pivotDeGauss(dmatrix* matrix)
{
    int lcmVal = 0;

    //for x

    //L1 and L2 (eliminates x in 2nd equation)

    if(matrix[0].mcol[0].mval < 0)
    {
        multiplyEq(matrix, -1, 0);
    }
    if(matrix[1].mcol[0].mval < 0)
    {
        multiplyEq(matrix, -1, 1);
    }
    if(matrix[0].mcol[0].mval > matrix[1].mcol[0].mval) // checks whether coefficient of x in 1st equation is greater than 2nd equation's
    {

        //some math
        lcmVal = lcm(matrix[0].mcol[0].mval, matrix[1].mcol[0].mval);
        multiplyEq(matrix, (lcmVal/matrix[1].mcol[0].mval), 1);

        if(lcmVal != matrix[0].mcol[0].mval)
        {
            multiplyEq(matrix, (lcmVal/matrix[0].mcol[0].mval), 0);

        }
        substractEq(matrix, 0, 1);
    } 
    else // vice versa
    {
        lcmVal = lcm(matrix[0].mcol[0].mval, matrix[1].mcol[0].mval);
        multiplyEq(matrix, (lcmVal/matrix[0].mcol[0].mval), 0);

        if(lcmVal != matrix[1].mcol[0].mval)
        {
            multiplyEq(matrix, (lcmVal/matrix[1].mcol[0].mval), 1);

        }
        substractEq(matrix, 0, 1);

    }
    printf("\n----L1 and L2-----\n");
    printmatrix(matrix);
    printf("\n");


    //L1 and L3 (eliminates x in 3rd equation)
    if(matrix[0].mcol[0].mval < 0)
    {
        multiplyEq(matrix, -1, 0);
    }
    if(matrix[2].mcol[0].mval < 0)
    {
        multiplyEq(matrix, -1, 2);
    }
    if(matrix[0].mcol[0].mval > matrix[2].mcol[0].mval) // same thing mentioned above
    {
        lcmVal = lcm(matrix[0].mcol[0].mval, matrix[2].mcol[0].mval);
        multiplyEq(matrix, (lcmVal/matrix[2].mcol[0].mval), 2);

        if(lcmVal != matrix[0].mcol[0].mval)
        {
            multiplyEq(matrix, (lcmVal/matrix[0].mcol[0].mval), 0);

        }

        substractEq(matrix, 0, 2);
    }
    else
    {
        lcmVal = lcm(matrix[0].mcol[0].mval, matrix[2].mcol[0].mval);
        multiplyEq(matrix, (lcmVal/matrix[0].mcol[0].mval), 0);

        if(lcmVal != matrix[2].mcol[0].mval)
        {
            multiplyEq(matrix, (lcmVal/matrix[2].mcol[0].mval), 2);

        }
        substractEq(matrix, 0, 2);
    }

    printf("\n----L1 and L3-----\n");
    printmatrix(matrix);

    

    //I repeat same process for y

    if(matrix[1].mcol[1].mval < 0)
    {
        multiplyEq(matrix, -1, 1);
    }
    if(matrix[2].mcol[1].mval < 0)
    {
        multiplyEq(matrix, -1, 2);
    }

    if(matrix[1].mcol[1].mval > matrix[2].mcol[1].mval)
        {
            lcmVal = lcm(matrix[1].mcol[1].mval, matrix[2].mcol[1].mval);
            multiplyEq(matrix, (lcmVal/matrix[2].mcol[1].mval), 2);

            if(lcmVal != matrix[1].mcol[1].mval)
            {
                multiplyEq(matrix, (lcmVal/matrix[1].mcol[1].mval), 1);

            }
        


        substractEq(matrix, 1, 2);
        }
    else
    {
        lcmVal = lcm(matrix[1].mcol[1].mval, matrix[2].mcol[1].mval);
        multiplyEq(matrix, (lcmVal/matrix[1].mcol[1].mval), 1);

        if(lcmVal != matrix[2].mcol[1].mval)
        {
            multiplyEq(matrix, (lcmVal/matrix[2].mcol[1].mval), 2);

        }
        substractEq(matrix, 1, 2);
    }
    printf("\n----L2' and L3'-----\n");
    printmatrix(matrix);

    // In the end you get an equation which looks like 0x + 0y + az = b, I had to calculate x and y but haven't wrote this part.
    
    

}
int determinant(dmatrix* m)
{
    return m[0].mcol[0].mval * (m[1].mcol[1].mval * m[2].mcol[2].mval - m[1].mcol[2].mval * m[2].mcol[1].mval) - m[1].mcol[0].mval * (m[0].mcol[1].mval * m[2].mcol[2].mval- m[0].mcol[2].mval * m[2].mcol[1].mval) + m[2].mcol[0].mval * (m[0].mcol[1].mval * m[1].mcol[2].mval - m[1].mcol[1].mval * m[0].mcol[2].mval);
}
