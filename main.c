# define _CRT_SECURE_NO_WARNINGS
# define MAX_STACK_SIZE 20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char** maze; // 미로 데이터 숫자로 바꿔서 저장
int wid, hei;

typedef struct {
	int x;
	int y;
}Element;

typedef struct {
	Element Data[MAX_STACK_SIZE];
	int top;
}Stack;

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
	stack->Data[++(stack->top)] = data;
}

Element Pop(Stack* stack) {
	if (IsEmpty(stack)) {
		printf("Is empty Stack\n");
		exit(1);
	}
	else
		return stack->Data[stack->top];
}

int check(char string) {
	if (string == EOF) {
		exit(1);
	}
	else if (string == ' ') {
		return 0;
	}
	else {
		return 1;
	}

}


int make_maze() {
	char file_name[20];
	printf("길을 찾을 미로의 파일명을 입력하시오: ");
	scanf("%s", &file_name);
	FILE* File = fopen(file_name, "r");
	if (File == NULL) {
		printf("잘못된 파일명 입니다.");
	}
	else {
		fscanf(File, "%d %d", &wid, &hei);
		wid = wid * 2 + 1; hei = hei * 2 + 1;
		int i = 0;

		maze = malloc(hei * sizeof(*maze));
		for (i = 0; i < hei; i++) {
			maze[i] = malloc(wid * sizeof(**maze));
		}
		fseek(File, 2, SEEK_CUR);
		for (int h = 0; h < hei; h++) {
			for (int w = 0; w < wid; w++) {
				char b = fgetc(File);
				maze[h][w] = check(b);

			} fseek(File, 2, SEEK_CUR);
		}

	}fclose(File);

}

void A(Stack* stack) {
	Element Cur;
	Cur.x = 1;
	Cur.y = 1;
	Element* p = &Cur;
			
		for (; maze[Cur.x++][Cur.y] != 1;) {
			Push(stack, Cur);
			//maze[Cur.x][Cur.y] = '2';
		}
		for (; maze[Cur.x][Cur.y++] != (1);) {
			Push(stack, Cur);
			//maze[Cur.x][Cur.y] = '2';
		}

		printf("%d", Cur.x);


}
int main() {
	Stack X;
	SettingStack(&X);
	make_maze();
	maze[wid - 1][hei - 1] = 2;
	A(&X);

	for (int i = 0; i < 10;i++) {
		printf("{%d,%d}\n", X.Data[i].x, X.Data[i].y);
	}

	for (int i = 0; i < hei; i++) {
		for (int j = 0; j < wid; j++) {
			printf("%d", maze[i][j]);
		}printf("\n");
	}
}
