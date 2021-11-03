#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<omp.h>

int r = 50, c = 50;

int getNeighbors(int** grid, int lin, int col) {
    int count = 0, column, l, i, j;
  
    for(i=-1; i<2; i++){
        
        column = col;
        l = lin;
      
        if (lin + i < 0){
            l = r;
        }

        else if (lin + i == r){
            l = 0;
        }

        for(j=-1; j<2; j++){

            if (col + j < 0){
                column = c;
            }
            
            else if (col + j == c){
                column = 0;
            }

            if (i == 0 && j == 0){
                
            }
            else{
                count += grid[l+i][column+j];
            }
        }
    }

    return count;
}


int main(){
    int i, j, count, neighbors;
 
    int** grid = (int**)malloc(r * sizeof(int*));
    for (i = 0; i < r; i++)
        grid[i] = (int*)malloc(c * sizeof(int));
  
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            grid[i][j] = 0;

    //GLIDER
    int lin = 1, col = 1;
    grid[lin  ][col+1] = 1;
    grid[lin+1][col+2] = 1;
    grid[lin+2][col  ] = 1;
    grid[lin+2][col+1] = 1;
    grid[lin+2][col+2] = 1;
    
    //R-pentomino
    lin =10; col = 30;
    grid[lin  ][col+1] = 1;
    grid[lin  ][col+2] = 1;
    grid[lin+1][col  ] = 1;
    grid[lin+1][col+1] = 1;
    grid[lin+2][col+1] = 1;

    neighbors = getNeighbors(grid, 10,30);
    printf("%d\n", neighbors);

    return 0;

}