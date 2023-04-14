#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 10000
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int wid, hei;
char** maze;
char** mark;
typedef struct {
    int h;
    int w;
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
        printf("Stack 가득참\n");
        exit(1);
    }
    stack->Data[++(stack->top)] = data;
    printf("PUSH [%d,%d]\n", data.h, data.w);
}

Element Pop(Stack* stack) {
    if (IsEmpty(stack)) {
        printf("Is empty Stack\n");
        exit(1);
    }
    else
        printf("POP  [%d,%d]\n", stack->Data[stack->top].h, stack->Data[stack->top].w);
    stack->top--;
    return stack->Data[stack->top];


}
int Deter(Element Cur, char** maze) { // 갈수있는길이 없으면 0반환 있으면 1 반환
    int H = Cur.h, W = Cur.w;

    if (maze[H][W + 1] != '1' && maze[H + 1][W] != '1' && maze[H - 1][W] != '1' && maze[H][W - 1] != '1') {
        return 0;
    }

    else {
        return 1;
    }
}
void print_result() {
    for (int i = 0; i < hei * 2 + 1; i++) {
        for (int j = 0; j < wid * 2 + 1; j++) {
            printf("%c", mark[i][j]);
        }
        printf("\n");
    }
}
void End() {

    for (int i = 0; i < hei * 2 + 1; i++) {
        for (int j = 0; j < wid * 2 + 1; j++) {
            if (mark[i][j] == '2') maze[i][j] = 'O';
        }
        printf("\n");
    }



    for (int i = 0; i < hei * 2 + 1; i++) {
        for (int j = 0; j < wid * 2 + 1; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    exit(1);
}
void A(Stack* stack, int hei, int wid, char** mark) {
    Element Cur;
    Cur.h = 1; // hei
    Cur.w = 1; // wid
    Push(stack, Cur);
    mark[Cur.h][Cur.w] = '2';
    //while (!IsEmpty(stack) || Deter(Cur, maze) != 0) { // Cur.x < wid * 2 + 1 && Cur.x < hei * 2 + 1 

    while (!IsEmpty(stack)) {

        while (Deter(Cur, mark) != 0) {
            while (mark[Cur.h + 1][Cur.w] == '1') {
                if (Cur.h == 2 * hei - 1 && Cur.w == 2 * wid - 1) {
                    printf("\nend\n");
                    End();
                    ;
                }
                Cur.h++;
                Push(stack, Cur);
                mark[Cur.h][Cur.w] = '2';
            }
            while (mark[Cur.h][Cur.w + 1] == '1') {
                if (Cur.h == 2 * hei - 1 && Cur.w == 2 * wid - 1) {
                    printf("\nend\n");
                    End();
                    ;
                }
                Cur.w++;
                Push(stack, Cur);

                mark[Cur.h][Cur.w] = '2';
            }
            while (mark[Cur.h - 1][Cur.w] == '1') {
                if (Cur.h == 2 * hei - 1 && Cur.w == 2 * wid - 1) {
                    printf("\nend\n");
                    End();
                    ;
                }
                Cur.h--;
                Push(stack, Cur);
                mark[Cur.h][Cur.w] = '2';
            }
            while (mark[Cur.h][Cur.w - 1] == '1') {
                if (Cur.h == 2 * hei - 1 && Cur.w == 2 * wid - 1) {
                    printf("\nend\n");
                    End();
                    ;
                }
                Cur.w--;
                Push(stack, Cur);
                mark[Cur.h][Cur.w] = '2';
            }
        }
        while (Deter(Cur, mark) == 0 && stack->top != 0) {
            if (Cur.h == 2 * hei - 1 && Cur.w == 2 * wid - 1) {
                printf("\nend\n");
                End();
            }
            mark[Cur.h][Cur.w] = '7';
            Cur = Pop(stack);
        }
        if (stack->top == 0) {
            Pop(stack);
        }

    }
    printf("No Route\n");
    End();





}
int main() {
    /*파일 입출력은 main 에서 하는게 안전해서 함*/
    /*int ** 이차원 배열에 맞게 안바꿔서 일단 오류 나던거 고침 -> malloc 파트 */
    // opens text files
    FILE* fp;


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

    mark = (char**)malloc((hei * 2 + 1) * sizeof(char*));
    for (int i = 0; i < hei * 2 + 1; i++) {
        mark[i] = (char*)malloc((wid * 2 + 1) * sizeof(char));
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
                mark[row][col] = c;
                col++;
            }
        }
    }
    /*경로는 1, 벽은 0으로 치환*/

    for (int i = 0; i < hei * 2 + 1; i++) {
        for (int j = 0; j < wid * 2 + 1; j++) {
            if (mark[i][j] == ' ') {
                mark[i][j] = '1';
                //printf("%c", maze[i][j]);
            }
            else {
                mark[i][j] = '0';
                //printf("%c", maze[i][j]);
            }
        }
        //printf("\n");
    }
    fclose(fp);

    Stack X;
    SettingStack(&X);
    maze[hei * 2 - 1][wid * 2 - 1] = '1';
    A(&X, hei, wid, mark);

    /* for (int i = 0; i < 10; i++) { //print Stafck X
         printf("{%d,%d}\n", X.Data[i].h, X.Data[i].w);
     }*/    // print maze

}
