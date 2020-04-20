#include <stdio.h>
#include <conio.h>
#define SIZE 100

void shrink(int mas[], int size, int index)
{
	for (int i = index; i < size - 1; i = i + 1)
	{
		mas[i] = mas[i + 1];
	}
}

int main(void)
{
	int max = 0, min = 0, n = 0, inter = 0, maxi = 0;
	int mas[SIZE];

	printf("N = ");
	scanf("%d", &n);

	if (n <= 0 || n > SIZE)
	{
		printf("N out of range!");
		_getch();
		return 0;
	}
	printf("Enter numbers one at a time\n");

	for (int i = 0; i < n; i = i + 1)
	{
		scanf("%d", &inter);
		mas[i] = inter;
	}

	min = mas[0];
	max = mas[0];

	for (int i = 0; i < n; i = i + 1)
	{
		if (mas[i] >= max)
		{
			max = mas[i];
			maxi = i;
		}
		if (mas[i] < min)
			min = mas[i];
	}

	int i = 0;

	while (i < n)
	{
		if (i == maxi)
		{
			mas[i] = min;
			break;
		}
		if (mas[i] == max)
		{
			shrink(mas, n, i);
			n = n - 1;
			maxi = maxi - 1;
		}
		else
			i = i + 1;
	}

	for (int j = 0; j < n; j = j + 1)
	{
		printf("%i ", mas[j]);
	}
	_getch();

	return 0;
}