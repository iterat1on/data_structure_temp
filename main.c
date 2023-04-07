# define _CRT_SECURE_NO_WARNINGS

#include "head.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** maze; // 미로 데이터 숫자로 바꿔서 저장
int wid, hei;




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
		for (int i = 0; i < hei; i++) {
			for (int j = 0; j < wid; j++) {
				printf("%d", maze[i][j]);
			}printf("\n");
		}
	}fclose(File);

}

void move(Stack * stack) {
	if () {

	}
	
}

int main() {
	Stack X, Y;
	SettingStack(&X);
	SettingStack(&Y);
	make_maze();
	
}
