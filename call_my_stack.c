#include<unistd.h>
#include<stdio.h>

#define my_stack_push 335
#define my_stack_pop 336
#define ERROR_CODE 2147483647

int main()
{
	int i, result, n = 3;

	// Stack Push
	for (i = 1; i <= n; i++) {
		syscall(my_stack_push, i);
		printf("Push %d\n", i);
	}

	// Duplicate Check Test
	syscall(my_stack_push, n);
	printf("Push failed (Duplication)\n");

	// Stack Pop
	for (i = 1; i <= n + 1; i++) {
		result = syscall(my_stack_pop);
		if (result == ERROR_CODE) printf("Pop failed (Underflow)\n");
		else printf("Pop %d\n", result);
	}
	
	return 0;
}
