#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(void)
{
	FILE *input, *output;
	int val = 0, len = 0, size = 4, count = 0;
	int *arr = (int *)malloc(size * sizeof(int));

	if ((input = fopen("input.txt", "r")) == NULL)
	{
		printf("Error, file input.txt does not exist\n");
		_getch();
		return 0;
	}

	while (fscanf(input, "%d", &val) != EOF)
	{
		if (len == size)
		{
			size = size * 2;
			arr = (int *)realloc(arr, size * sizeof(int));

			if (arr == NULL)
			{
				printf("Bad alloc\n");
				_getch();
				return 0;
			}
		}
		if (val == 0)
			count = count + 1;
		arr[len] = val;
		len = len + 1;
	}
	
	fclose(input);

	if (size == len)
	{
		size = size + 1;
		arr = (int *)realloc(arr, size * sizeof(int));
		if (arr == NULL)
		{
			printf("Bad alloc\n");
			_getch();
			return 0;
		}
	}
	arr[len] = count;

	output = fopen("output.txt", "w");

	for (int i = 0; i <= len; i = i + 1)
	{
		fprintf(output, "%d ", arr[i]);
	}

	fclose(output);
	free(arr);
	return 0;
}