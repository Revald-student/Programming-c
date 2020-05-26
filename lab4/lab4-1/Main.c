#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <string.h>


#define DICTLEN 6

struct dictionary
{
	char *word;
	char *translation;
	char *useInCentence;
};

int compare_translation(void const *a, void const *b)
{
	struct dictionary *dict_a = (struct dictionary *)a;
	struct dictionary *dict_b = (struct dictionary *)b;

	return strcmp(dict_a->translation, dict_b->translation);
}

void myqsort(struct dictionary *arr, int first, int last)
{
	int size = last - first + 1;
	int left = first, right = last;
	struct dictionary p;
	struct dictionary tmp;
	if (size <= 1)
		return;
	p = arr[(last + first) / 2];
	while (left < right)
	{
		while (strcmp(p.translation, arr[left].translation) > 0 && left < right)
			left = left + 1;
		while (strcmp(p.translation, arr[right].translation) <= 0 && right > left)
			right = right - 1;
		if (left == right)
		{ 
			myqsort(arr, first, left);
			myqsort(arr, right + 1, last);
		}
		else
		{
			tmp = arr[left];
			arr[left] = arr[right];
			arr[right] = tmp;
			left = left + 1;
			right = right - 1;
		}
	}
}

struct dictionary *inputDict()
{
	struct dictionary *dictArr = (struct dictionary*)malloc(DICTLEN * sizeof(struct dictionary));
	char buff[100];
	char format[28];
	int size = 0;
	AnsiToOem(" %99[a-z0-9A-ZА-Яа-я!?.,' ]", format);

	for (int i = 0; i < DICTLEN; i = i + 1)
	{
		printf("Введите 0, чтобы выйти\n");
		printf("Слово %i: ", i + 1);
		scanf(format, buff);
		if (buff[0] == '0')
		{
			while (i < DICTLEN)
			{
				dictArr[i].word = NULL;
				dictArr[i].translation = NULL;
				dictArr[i].useInCentence = NULL;
				i = i + 1;
			}
			break;
		}

		size = i + 1;
			
		OemToAnsi(buff, buff);

		dictArr[i].word = malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(dictArr[i].word, buff);


		printf("Перевод %i: ", i + 1);
		scanf(format, buff);
		OemToAnsi(buff, buff);

		dictArr[i].translation = malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(dictArr[i].translation, buff);

		printf("Пример в предложении %i: ", i + 1);
		scanf(format, buff);
		OemToAnsi(buff, buff);

		dictArr[i].useInCentence = malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(dictArr[i].useInCentence, buff);
	}

	myqsort(dictArr, 0, size - 1);

	return dictArr;
}

struct dictionary* searchStruct(struct dictionary *dict, char *word)
{
	int flag = 0;
	for (int i = 0; (i < DICTLEN) && (dict[i].translation != NULL); i = i + 1)
	{
		flag = strcmp(dict[i].translation, word);
		if (flag > 0)
			break;
		if (flag == 0)
		{
			return &dict[i];
		}
	}
	return NULL;
}

int freeStruct(struct dictionary *dict)
{
	for (int i = 0; i < DICTLEN; i = i + 1)
	{
		if (dict[i].word == NULL)
			break;
		free(dict[i].word);
		free(dict[i].useInCentence);
		free(dict[i].translation);
	}
	free(dict);
	return 0;
}

void showStruct(struct dictionary *dict)
{
	printf("\nВсе записи в словаре:\n");
	for (int i = 0; i < DICTLEN && dict[i].word != NULL; i = i + 1)
	{
		printf("Слово %i: %s\n", i + 1, dict[i].word);
		printf("Перевод %i: %s\n", i + 1, dict[i].translation);
		printf("Пример в предложении %i: %s\n", i + 1, dict[i].useInCentence);
	}
}

int main(void)
{
	setlocale(LC_ALL, "RUS");

	struct dictionary *dict = inputDict();
	struct dictionary *searchRes = NULL;

	showStruct(dict);

	char con_input[100];
	printf("\nВведите 0 чтобы выйти\n");

	while(1)
	{
		printf("\nИскомое слово по переводу: ");
		scanf(" %99s", con_input);
		if (con_input[0] == '0')
			break;

		OemToAnsi(con_input,con_input);
		searchRes = searchStruct(dict, con_input);
		if (searchRes == NULL)
		{
			printf("Искомый перевод не найден\n");
			continue;
		}
		printf("Слово: %s\nПример в предложении: %s\n", searchRes->word, searchRes->useInCentence);
	}

	freeStruct(dict);

	return 0;
}