# define MAX_STACK_SIZE 20

typedef struct {
	int x;
	int y;
}Element;

typedef struct {
	Element* Data;
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