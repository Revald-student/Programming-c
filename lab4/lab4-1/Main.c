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

struct dictionary *inputDict()
{
	struct dictionary *dictArr = (struct dictionary*)malloc(DICTLEN * sizeof(struct dictionary));
	char buff[100];
	char format[28];
	int size = 0;
	AnsiToOem(" %99[a-z0-9A-ZА-Яа-я!?.,' ]", format);

	printf("Введите 0, чтобы выйти\n");

	for (int i = 0; i < DICTLEN; i = i + 1)
	{
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

	qsort(dictArr, size, sizeof(struct dictionary), compare_translation);

	return dictArr;
}

int search_dict(struct dictionary *dict, char *word)
{
	int flag = 0;
	int res = -1;
	for (int i = 0; (i < DICTLEN) && (dict[i].translation != NULL); i = i + 1)
	{
		flag = strcmp(dict[i].translation, word);
		if (flag > 0)
			break;
		if (flag == 0)
		{
			res = i;
			break;
		}
	}
	return res;
}


int main(void)
{
	setlocale(LC_ALL, "RUS");

	struct dictionary *dict = inputDict();
	int res_i = 0;

	char con_input[100];
	printf("\nВведите 0 чтобы выйти\n");

	while(1)
	{
		printf("\nИскомое слово по переводу: ");
		scanf(" %99s", con_input);
		if (con_input[0] == '0')
			break;

		OemToAnsi(con_input,con_input);
		res_i = search_dict(dict, con_input);
		if (res_i < 0)
		{
			printf("Искомый перевод не найден\n");
			continue;
		}
		printf("Слово: %s\nПример в предложении: %s\n", dict[res_i].word, dict[res_i].useInCentence);
	}

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