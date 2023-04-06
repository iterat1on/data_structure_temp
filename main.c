# define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
# define MAX_STACK_SIZE 100

int wid, hei;

typedef Element;
typedef struct {
	int arr[MAX_STACK_SIZE];
	int top;
}Stack;

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

void Push(Stack* stack, int data) {
	stack->arr[++(stack->top)] = data;
}

int Pop(Stack* stack) {
	if (IsEmpty(stack)) {
		printf("Is empty Stack\n");
		return 0;
	}
	else
		return stack->arr[stack->top];
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
		char** size;
		size = malloc(hei * sizeof(*size));
		for (i = 0; i < hei; i++) {
			size[i] = malloc(wid * sizeof(**size));
		}
		fseek(File, 2, SEEK_CUR);
		for (int h = 0; h < hei; h++) {
			for (int w = 0; w < wid; w++) {
				char b = fgetc(File);
				size[h][w] = check(b);


			} fseek(File, 2, SEEK_CUR);
		}
		for (int i = 0; i < hei; i++) {
			for (int j = 0; j < wid; j++) {
				printf("%d", size[i][j]);
			}printf("\n");
		}
	}fclose(File);

}

int main() {
	make_maze();
	
	
	
	
	
}