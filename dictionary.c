#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTHOF_STRING 20

typedef struct {
    char word[MAX_LENGTHOF_STRING];
    char meaning[MAX_LENGTHOF_STRING];
}Element;

typedef struct node {
    Element data;
    struct node* next;
}Node;




int main() {

}