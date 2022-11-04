#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define n 9

int solver(int grid[n][n],int row,int column);
int checker(int grid[n][n],int row,int column,int N);
void printer(int array[n][n]);

int main(int argc,char *argv[])
{
    int input[81],counter=0,counter_2=0;
    FILE *fp;
    
    if(argc>=2)
    {
        fp=fopen(argv[1],"r+");
    }

    else 
    {
        char name[100];
        printf("Enter the sudoku file you want to solve ");
        scanf("%s",name);
        fp=fopen(name,"r+");
    }
    int grid[n][n],row=0,column=0,val;
    char extract[1];

    extract[0]=fgetc(fp);
    
    while(extract[0]!=EOF)
    {
        if(!isspace(extract[0]))
        {
            char string[2];
            string[1]='\0';
            string[0]=extract[0];   
            val=atoi(string);
            input[counter]=val;
            counter++;
            
        }
    extract[0]=fgetc(fp);
    }
    
    for (row=0; row < n; row++)
	{
		for (column=0;column < n; column++)
        {
            grid[row][column]=input[counter_2];
            counter_2++;
        }
    }
   
     if (solver(grid, 0, 0)==1)
		printer(grid);
	else
		printf("No solution exists");

    fclose(fp);
    return 0;
}

int solver(int grid[n][n],int row,int column)
{
    if (row == n - 1 && column == n)
		return 1;
	if (column == n)
	{
		row++;
		column = 0;
	}

	if (grid[row][column] > 0)
		return solver(grid, row, column + 1);

	for (int num = 1; num <= n; num++)
	{
		if (checker(grid, row, column, num)==1)
		{
			grid[row][column] = num;
			if (solver(grid, row, column + 1)==1)
				return 1;
		}
	
				grid[row][column] = 0;
	}
	return 0;
}


int checker(int grid[n][n],int row,int col,int num)
{
   for (int x = 0; x <= 8; x++)
		if (grid[row][x] == num)
			return 0;
	for (int x = 0; x <= 8; x++)
		if (grid[x][col] == num)
			return 0;
	int row_2 = row - row % 3,
				col_2 = col - col % 3;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (grid[i +row_2][j +col_2] == num)
				return 0;

	return 1;
}

void printer(int array[n][n])
{
    FILE *fpt;
    fpt=fopen("Sudokosolver.txt","w+");
    printf("The solved answer is in sudokosolver\n");
    fprintf(fpt,"\n New Solved \n");
    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
        {
			fprintf(fpt,"%d ",array[i][j]);
        }
        fprintf(fpt,"\n");
	}
}