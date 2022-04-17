#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW 4
#define COL 3



typedef struct double_matrice //I had to use this method to return matrices.
{
    int mval;
    struct double_matrice *mcol;
} dmatrice;

void readEquation(dmatrice* matrice);
dmatrice *makeMatrice(int lines, int columns);
void printMatrice(dmatrice* matrice);
void multiplyEq(dmatrice* eq, int k, int row_num);
int pivotDeGauss(dmatrice* matrice);


int main(void)
{
    dmatrice* matrice = makeMatrice(ROW,COL);
    readEquation(matrice);
    printMatrice(matrice);


    printf("\n\n%d", pivotDeGauss(matrice));
    printMatrice(matrice);
    
    return 0;
}


void readEquation(dmatrice* matrice)
{
    FILE* fp = fopen("matrix.txt", "r");
    if(fp == NULL)
    {
        perror("Error: ");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < ROW; i++)
    {
        fscanf(fp, "%dx%dy%dz=%d\n", &matrice[i].mcol[0].mval,  &matrice[i].mcol[1].mval,  &matrice[i].mcol[2].mval,  &matrice[i].mcol[3].mval);

    }


}

dmatrice *makeMatrice(int lines, int columns)
{
    dmatrice *new_matrice = (dmatrice *)(malloc(sizeof(dmatrice)*lines));
    for(int i = 0; i < lines; i++)
    {
        new_matrice[i].mcol = (dmatrice *)(malloc(sizeof(dmatrice)*columns));
    }
    return new_matrice;
}

void printMatrice(dmatrice* matrice)
{
    printf("\n");

    for(int i = 0; i < COL; i++)
    {
        
        for(int j = 0; j < ROW; j++)
        {
            printf("%d ", matrice[i].mcol[j].mval);
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
void multiplyEq(dmatrice* eq, int k, int row_num)
{
    for(int i = 0; i < ROW; i++)
    {
        eq[row_num].mcol[i].mval = eq[row_num].mcol[i].mval * k;
    }
}
void substractEq(dmatrice* eq, int f_row_num, int s_row_num)
{
    for(int i = 0; i < ROW; i++)
    {
        eq[s_row_num].mcol[i].mval -= eq[f_row_num].mcol[i].mval;
    }
}

int pivotDeGauss(dmatrice* matrice)
{
    int lcmVal = 0;

    //for x

    //L1 and L2
    lcmVal = lcm(matrice[0].mcol[0].mval, matrice[1].mcol[0].mval);
    multiplyEq(matrice, (lcmVal/matrice[1].mcol[0].mval), 1);
    substractEq(matrice, 0, 1);

    //L1 and L3
    if(matrice[0].mcol[0].mval > matrice[2].mcol[0].mval)
    {
        lcmVal = lcm(matrice[0].mcol[0].mval, matrice[2].mcol[0].mval);
        multiplyEq(matrice, (lcmVal/matrice[2].mcol[0].mval), 2);
        substractEq(matrice, 0, 2);
    }
    else
    {
        lcmVal = lcm(matrice[0].mcol[0].mval, matrice[2].mcol[0].mval);
        multiplyEq(matrice, (lcmVal/matrice[0].mcol[0].mval), 0);
        substractEq(matrice, 0, 2);
    }
    printMatrice(matrice);
    printf("\n------------------------------------\n");
    //for y
    if(matrice[1].mcol[1].mval > 0 && matrice[2].mcol[1].mval < 0 || (matrice[1].mcol[1].mval < 0 && matrice[2].mcol[1].mval > 0)) 
    {
        multiplyEq(matrice, -1, 2);

    } 
    if(matrice[1].mcol[1].mval > matrice[2].mcol[1].mval)
        {
            lcmVal = lcm(matrice[1].mcol[1].mval, matrice[2].mcol[1].mval);
            multiplyEq(matrice, (lcmVal/matrice[2].mcol[1].mval), 2);
            printf("\n-----------------(o)-------------------\n");
            printMatrice(matrice);

            substractEq(matrice, 1, 2);
        }
        else
        {
            lcmVal = lcm(matrice[1].mcol[1].mval, matrice[2].mcol[1].mval);
            multiplyEq(matrice, (lcmVal/matrice[1].mcol[1].mval), 1);
            substractEq(matrice, 1, 2);
        }

    

    return lcmVal;

}
