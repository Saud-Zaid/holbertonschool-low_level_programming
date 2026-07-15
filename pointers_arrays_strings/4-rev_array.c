#include "main.h"

/**
 * reverse_array - reverses the content of an array
 * @a: array of integers
 * @n: number of elements in the array
 *
 * Return: void
 */
void reverse_array(int *a, int n)
{
	int left = 0;
	int right = n - 1;
	int temp;

	while (left < right)
	{
		temp = a[left];
		a[left] = a[right];
		a[right] = temp;
		left++;
		right--;
	}
}
