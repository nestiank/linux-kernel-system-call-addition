#include<linux/syscalls.h>
#include<linux/kernel.h>
#include<linux/linkage.h>

#define ERROR_CODE 2147483647
int stack[50];
int top = 0;
void print_stack(void);

SYSCALL_DEFINE1(oslab_push, int, input)
{
	int i;

	// Overflow Prevention
	if (top >= 50) {
		printk("oslab_push(): Stack overflow occured.\n");

		return;
	}

	// Existence Check
	for (i = 0; i < top; i++) {
		if (stack[i] == input) {
			printk("oslab_push(): Input already exists.\n");

			return;
		}
	}

	// Stack Push
	stack[top++] = input;
	printk("oslab_push(): Push %d\n", input);
	print_stack();

	return;
}
SYSCALL_DEFINE0(oslab_pop)
{
	int output;

	// Underflow Prevention
	if (top <= 0) {
		printk("oslab_pop(): Stack underflow occured.\n");
		return ERROR_CODE;
	}

	// Stack Pop
	output = stack[--top];
	printk("oslab_pop(): Pop %d\n", output);
	print_stack();

	return output;
}
void print_stack(void)
{
	int i;

	printk("Stack Top ----------\n");
	if (top == 0) printk("(Stack Empty)\n");
	for (i = top - 1; i >= 0; i--) {
		printk("%d\n", stack[i]);
	}
	printk("Stack Bottom -------\n");

	return;
}
