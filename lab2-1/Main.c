#include <stdio.h>
#include <conio.h>
#include <math.h>
#define SIZE 100

int main(void)
{
	float mas[SIZE];
	int imin[2];
	float sum = 0, min = 0, num = 0;
	int n, aver;

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
		scanf("%f", &num);
		mas[i] = num;
	}
	if (n == 1)
	{
		printf("%f\n", mas[0]);
		_getch();
		return 0;
	}


	for (int i = 0; i < n; i = i + 1)
		sum = sum + mas[i];
	aver = trunc(sum / n);

	min = mas[0];

	for (int i = 0; i < n; i = i + 1)
	{
		if (mas[i] <= min)
		{
			min = mas[i];
			imin[1] = i;
		}
	}

	for (int i = 0; i < n; i = i + 1)
	{
		if (mas[i] == min)
		{
			imin[0] = i;
			break;
		}
	}

	mas[imin[0]] = aver;
	mas[imin[1]] = aver;

	for (int i = 0; i < n; i = i + 1)
	{
		printf("%f ", mas[i]);
	}
	printf("\n");
	_getch();

	return 0;
}