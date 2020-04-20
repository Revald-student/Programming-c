#include <stdio.h>
#include <conio.h>
#define SIZE 100

int main(void)
{
	float mas[SIZE][SIZE];
	int n = 0;
	float num = 0;

	printf("N = ");
	scanf("%d", &n);

	if (n <= 0 || n > SIZE)
	{
		printf("N is out of range!\n");
		_getch();
		return 0;
	}

	printf("Enter numbers by one\n");

	for (int i = 0; i < 2 * n; i = i + 1)
		for (int j = 0; j < 2 * n; j = j + 1)
		{
			printf("[%d, %d] = ", i, j);
			scanf("%f", &num);
			mas[i][j] = num;
		}

	for(int i = 0; i < n; i = i + 1)
		for (int j = 0; j < n; j = j + 1)
		{
			num = mas[i][j];
			mas[i][j] = mas[i + n][j + n];
			mas[i + n][j + n] = num;
		}

	for(int i = 0; i < n; i = i + 1)
		for (int j = 0; j < n; j = j + 1)
		{
			num = mas[i][j + n];
			mas[i][j + n] = mas[i + n][j];
			mas[i + n][j] = num;
		}

	return 0;
}