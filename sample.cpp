#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


int main (void){
    FILE* fp;
    int dim1, dim0, row, col;

    char c;
    // opens text files
    fp = fopen("maze2.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(fp, "%d %d", &dim0, &dim1);
    while ((c = fgetc(fp)) != '\n');
    //save txt as 2d array
    char** maze = (char**)malloc((dim1 * 2 + 1) * sizeof(char*));
    for (int i = 0; i < dim1 * 2 + 1; i++) {
        maze[i] = (char*)malloc((dim0 * 2 + 1) * sizeof(char));
    }

    row = col = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            row++;
            col = 0;
        }
        else {
            maze[row][col] = c;
            col++;
        }
    }
    fclose(fp);

    // fill the blank with '1' and others to '0'
    for (int i = 0; i < dim1 * 2 + 1; i++) {
        for (int j = 0; j < dim0 * 2 + 1; j++) {
            if (maze[i][j] == ' ') {
                maze[i][j] = '1';
                printf("%c", maze[i][j]);
            }
            else {
                maze[i][j] = '0';
                printf("%c", maze[i][j]);
            }
        }
        printf("\n");
    }

    // free memory allocated for 2D maze array
    for (int i = 0; i < dim1 * 2 + 1; i++) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}
