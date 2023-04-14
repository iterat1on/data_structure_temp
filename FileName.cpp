#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD = 50000
#define NODE_SIZE = 50001

typedef struct Node {
    char word[20];
    char definition[100];
    int ascii_word;
    struct Node* next;
} Node;


void insert(Node** head_ref, char* word, char* definition, int Ascii_word) {
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->word, word);
    strcpy(new_node->definition, definition);
    new_node->ascii_word = Ascii_word; // word를 아스키코드로 바꿔서 Node구조체의 ascii에 대입
     
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%s : %s : %d\n", node->word, node->definition, node->ascii_word);
        node = node->next;
    }
}char* changetoAscii(char* word) {
    char* w = (char*)malloc(sizeof(char) * 100);
    int i = 0;
    while (word[i] != '\0') {
        int ascii = (int)word[i];
        char str[4];
        sprintf(str, "%d", ascii);
        strcat(w, str);
        i++;
    }

    return w;
}

int main() {
   /* Node* head = NULL;
    FILE* fp;
    char word[20], definition[100];
    int Ascii_word;

    fp = fopen("randdict.TXT", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    while (fscanf(fp, "%s : %[^\n]", word, definition) != EOF) {
        
       // printf("%d", Ascii_word);
        insert(&head, word, definition, Ascii_word);
    }
    
    fclose(fp);
    */
    //printList(head);
    char A[20] = "asasgasvsa";
    printf("%s", changetoAscii(A));
    
    return 0;
}
