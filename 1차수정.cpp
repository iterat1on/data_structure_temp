#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** maze;

typedef struct {
    int x;
    int y;
} Element;

typedef struct {
    Element Data[MAX_STACK_SIZE];
    int top;
} Stack;

int IsFull(Stack* stack) {
    if (stack->top == MAX_STACK_SIZE - 1) {
        return 1;
    }
    else return 0;
}

int IsEmpty(Stack* stack) {
    if (stack->top == -1) {
        return 1;
    }
    else return 0;
}

void SettingStack(Stack* stack) {
    stack->top = -1;
}

void Push(Stack* stack, Element data) {
    if (IsFull(stack)) {
        printf("Stack ������\n");
        exit(1);
    }
    stack->Data[++(stack->top)] = data;
}

Element Pop(Stack* stack) {
    if (IsEmpty(stack)) {
        printf("Is empty Stack\n");
        exit(1);
    }
    else
        return stack->Data[stack->top--];
}
/*A �Լ����� Ž���� range �� �Է����� �޾ƾ� �ҵ�? */
void A(Stack* stack, int hei, int wid) {
    Element Cur;
    Cur.x = 1;
    Cur.y = 1;

    while (Cur.x < hei * 2 + 1 && maze[Cur.x + 1][Cur.y] != '1') {
        Push(stack, Cur);
        maze[Cur.x][Cur.y] = '*';
        Cur.x++;
    }
    while (Cur.y < wid * 2 + 1 && maze[Cur.x][Cur.y + 1] != '1') {
        Push(stack, Cur);
        maze[Cur.x][Cur.y] = '*';
        Cur.y++;
    }

    Push(stack, Cur);
}

int main() {
    /*���� ������� main ���� �ϴ°� �����ؼ� ��*/
    /*char ** ������ �迭�� �°� �ȹٲ㼭 �ϴ� ���� ������ ��ħ -> malloc ��Ʈ */
    // opens text files
    FILE* fp;
    int wid, hei;

    char c;
    // opens text files
    fp = fopen("maze1.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(fp, "%d %d", &wid, &hei);
    while ((c = fgetc(fp)) != '\n');
    
    // allocate memory for maze
    maze = (char**)malloc((hei * 2 + 1) * sizeof(char*));
    for (int i = 0; i < hei * 2 + 1; i++) {
        maze[i] = (char*)malloc((wid * 2 + 1) * sizeof(char));
    }

    // read maze from file
    int row = 0, col = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            row++;
            col = 0;
        }
        else {
            if (row < hei * 2 + 1 && col < wid * 2 + 1) {
                maze[row][col] = c;
                col++;
            }
        }
    }
    /*��δ� 1, ���� 0���� ġȯ*/
    for (int i = 0; i < hei * 2 + 1; i++) {
        for (int j = 0; j < wid * 2 + 1; j++) {
            if (maze[i][j] == ' ') {
                maze[i][j] = '1';
                //printf("%c", maze[i][j]);
            }
            else {
                maze[i][j] = '0';
                //printf("%c", maze[i][j]);
            }
        }
        //printf("\n");
    }
    fclose(fp);
    // print maze
    Stack X;
    SettingStack(&X);
    maze[hei * 2 - 1][wid * 2 - 1] = '2';
    A(&X, hei, wid);
    for (int i = 0; i < 10; i++) {
        printf("{%d,%d}\n", X.Data[i].x, X.Data[i].y);
    }
    for (int i = 0; i < hei * 2 + 1; i++) {
        for (int j = 0; j < wid * 2 + 1; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}