#include "function_pointers.h"

/**
 * print_name - Prints a name using a given function pointer.
 * @name: Name of the person to print.
 * @f: Pointer to the function used to print the name.
 *
 * Return: Nothing.
 */
void print_name(char *name, void (*f)(char *))
{
	if (name != NULL && f != NULL)
		f(name);
}
