#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<omp.h>

int r = 50, c = 50;

int getNeighbors(int** grid, int lin, int col) {
    int count = 0, column, l, i, j;
  
    for(i=-1; i<2; i++){
        
        l = lin + i;
      
        if (lin + i < 0){
            l = r - 1;
        }

        else if (lin + i == r){
            l = 0;
        }

        for(j=-1; j<2; j++){
            column = col + j;
            if (col + j < 0){
                column = c - 1;
            }
            
            else if (col + j == c){
                column = 0;
            }

            if (i == 0 && j == 0){
                
            }
            else{
                count += grid[l][column];
            }
        }
    }

    return count;
}

int new_cell_status(int** grid, int l, int col){
    int neighbors = getNeighbors(grid, l, col);
//     printf("[%d][%d] %d\n",l,col, neighbors);
    if(grid[l][col] == 1){
        if(neighbors != 2 && neighbors != 3){
            return 0;
            // printf("[%d][%d]Morreu! Vizinhos: %d\n", l, col, neighbors);
        }
    }

    else if(grid[l][col] == 0){
        if(neighbors == 3){
           return 1;
            // printf("[%d][%d]Viveu! Vizinhos: %d\n", l, col, neighbors);
        }
    }

    return grid[l][col];
}

int alive_population(int** grid){
    int total = 0, i, j;

    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            if(grid[i][j] == 1){
                // printf("[%d][%d]Vivo \n", i, j);
                total++;
            }
        }
    }

    return total;
}

int** new_round(int** grid){
    int i,j, population;

    int** new_grid = (int**)malloc(r * sizeof(int*));
    for (i = 0; i < r; i++)
        new_grid[i] = (int*)malloc(c * sizeof(int));

    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            new_grid[i][j] = new_cell_status(grid,i,j);
        }
    }

    return new_grid;
}

int** game_of_life(int** grid, int n){
    int i, population;

    int** new_grid = (int**)malloc(r * sizeof(int*));
    for (i = 0; i < r; i++)
        new_grid[i] = (int*)malloc(c * sizeof(int));

    population = alive_population(grid);
    printf("Geracao 1: %d\n", population);
    new_grid = new_round(grid);
    for(i=0; i<n-1; i++){
        population = alive_population(new_grid);
        printf("Geracao %d: %d\n", i+1, population);
        new_grid = new_round(new_grid);
    }

    return new_grid;
}


int main(){
    int i, j, count, neighbors, population;
 
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

    int** new_grid = (int**)malloc(r * sizeof(int*));
    for (i = 0; i < r; i++)
        new_grid[i] = (int*)malloc(c * sizeof(int));

    new_grid = game_of_life(grid, 5);
    population = alive_population(new_grid);
    printf("%d\n", population);
    return 0;

}