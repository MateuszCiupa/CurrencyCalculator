#include "stack.h"

int main() {
	stack_t stack1, stack2;

	init(&stack1);	
	init(&stack2);

	put(&stack1, "ABC");
	put(&stack1, "BCD");
	put(&stack1, "CDE");

	change_stack(&stack2, stack1);

	print_stack(stack1);
	print_stack(stack2);

	put(&stack2, "PLN");
	put(&stack2, "GBP");

	change_stack(&stack2, stack1);

	print_stack(stack1);
	print_stack(stack2);

	change_stack(&stack2, stack1);

	print_stack(stack1);
	print_stack(stack2);

	free_stack(&stack1);
	free_stack(&stack2);

	return 0;
}
