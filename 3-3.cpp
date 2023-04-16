#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX_WORD 20
#define MAX_DEF 100
int count = 1;
typedef struct Node {
    char word[MAX_WORD];
    char definition[MAX_DEF];
    struct Node* link;
} Node;

Node* insert(Node* root, char* word, char* definition, int type) {
    if (type == 0) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        strcpy(new_node->word, word);
        strcpy(new_node->definition, definition);
        new_node->link = NULL;

        if (root == NULL) {
            return new_node;
        }

        if (strcmp(word, root->word) < 0) {
            new_node->link = root;
            return new_node;
        }

        Node* cur = root;
        while (cur->link != NULL && strcmp(word, cur->link->word) > 0) {
            cur = cur->link;
        }

        if (cur->link != NULL && strcmp(word, cur->link->word) == 0) {
            // 단어가 이미 있을 경우 정의를 덮어씁니다.
            strcpy(cur->link->definition, definition);
            return root;
        }

        new_node->link = cur->link;
        cur->link = new_node;

        return root;
    }
    else {
    }
}

void SearchWord(Node* root, char* input) {
    Node* p = root;
    int exist = 0;
    while (root != NULL) {
        int same = strcmp(root->word, input);
        if (same == 0) {
            printf("%s\n", root->definition);
            exist = 1;
            break;
        }
        root = root->link;
    }
    root = p;
    if (exist == 0) {
        char defin[MAX_DEF];
        printf("찾을 수 없는 단어입니다. 뜻을 추가하세요(추가하지 않으려면 공백)");
        int a;
        while ((a = getchar() != '\n'));
        printf("\n>");
        fgets(defin, MAX_DEF, stdin);
        defin[strlen(defin) - 1] = '\0';
        if (defin[0] == '\n') {
            printf("단어를 추가하지 않았습니다.\n");
        }
        else {
            root = insert(root, input, defin, 0 );
            printf("%s %s가 추가되었습니다.(총 %d개의 단어)\n",input ,defin, count);
        }
    }
}


void printList(Node* root) {
    while (root != NULL) {
        printf("%s : %s\n", root->word, root->definition);
        root = root->link;
    }
}
int main() {
    clock_t start = clock();
    Node* root = NULL;
    FILE* fp;
    
    char line[MAX_WORD + MAX_DEF + 2];
    char word[MAX_WORD], definition[MAX_DEF];

    fp = fopen("randdict.TXT", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%s : %[^\n]", word, definition);
        root = insert(root, word, definition,0);
        count++;
    }
    fclose(fp);

    clock_t end= clock();
    
    printf("%.3f초가 소요되었습니다. \n", (double)(end - start) / CLOCKS_PER_SEC);
    
    char input[20];
    while (1) {
        printf(">>");
        scanf("%s", input);
        SearchWord(root,input);
        
    }
    
    return 0;
}
