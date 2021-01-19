/*
https://mudongliang.github.io/2017/02/20/cva_argva_listva_startva_end.html
*/

#include <stdio.h>
#include <stdarg.h>

void print_args(int count, ...);

int main(int argc, char* argv[]) {
	print_args(5,1,2,3,4,5);
	return 0; 
}

void print_args(int count, ...) {
	int i, value;
	va_list arg_ptr;
	va_start(arg_ptr, count);
	for(i=0; i<count; i++) {
		value = va_arg(arg_ptr, int);
		printf("position %d = %d\n", i+1, value);
	}
	va_end(arg_ptr);
}