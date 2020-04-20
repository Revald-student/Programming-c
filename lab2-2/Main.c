#include <stdio.h>
#include <conio.h>
#define SIZE 100

int main(void)
{
	unsigned int len = 0, maxlen = 0;
	int n, inter = 0;
	int mas[SIZE];

	printf("N = ");
	scanf("%d", &n);

	if (n <= 0 || n >= SIZE)
	{
		printf("N is out of range\n");
		_getch();
		return 0;
	}

	printf("Enter numbers by one\n");
	for (int i = 0; i < n; i = i + 1)
	{
		scanf("%d", &inter);
		mas[i] = inter;
	}

	if (n == 1)
	{
		printf("%d\n", mas[0]);
		_getch();
		return 0;
	}

	inter = mas[0];
	for (int i = 0; i < n; i = i + 1)
	{
		if (inter == mas[i])
			len = len + 1;
		else
		{
			if (len > maxlen)
			{
				maxlen = len;
				inter = mas[i];
			}
			else
			{
				inter = mas[i];
			}
			len = 1;
		}
	}
	if (len > maxlen)
		maxlen = len;
	printf("Max Length = %i\n", maxlen);
	_getch();

	return 0;
}