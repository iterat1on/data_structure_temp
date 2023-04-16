#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD 20
#define MAX_DEF 100

typedef struct DictArr {
    char word[MAX_WORD];
    char definition[MAX_DEF];
    struct DictArr* ArrP;
}DictArr;



void printDictArr(DictArr* ArrP, int length) {
    for (int i = 0; i < length; i++) {
        printf("%s : ", ArrP[i].word);
        printf("%s\n", ArrP[i].definition);
    }
}

void swap(DictArr* x, DictArr* y) {
    DictArr temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(DictArr arr[], int n) {
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (strcmp(arr[min].word, arr[j].word) > 0) {
                min = j;
            }
        }
        swap(&arr[min], &arr[i]);
    }
}


int main() {
    clock_t start = clock();
    FILE* fp;
    char line[MAX_WORD + MAX_DEF + 2];
    char word[MAX_WORD], definition[MAX_DEF];

    fp = fopen("randdict_utf8.TXT", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }


    DictArr* ArrP = (DictArr*)malloc(sizeof(DictArr) * 50000);
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%s : %[^\n]", word, definition);
        strcpy(ArrP[i].word, word);
        strcpy(ArrP[i].definition, definition);
        i++;
    }

    selectionSort(ArrP, i);
    //printDictArr(ArrP, i);


    fclose(fp);
    clock_t end = clock();
    printf("%.3f초가 소요되었습니다. \n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}