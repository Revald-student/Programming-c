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

struct node
{
	struct dictionary dict;

	struct node *next;
};


struct node *inputList()
{
	struct node *newNode = NULL;
	struct node *first = NULL;
	struct node *current = NULL;
	char buff[100];
	char format[28];
	AnsiToOem(" %99[a-z0-9A-ZА-Яа-я!?.,' ]", format);

	printf("Введите 0, чтобы выйти\n");

	for (int i = 0; i < DICTLEN; i = i + 1)
	{
		printf("Слово %i: ", i + 1);
		scanf(format, buff);
		if (buff[0] == '0')
			break;

		newNode = (struct node*)malloc(sizeof(struct node));

		OemToAnsi(buff, buff);

		newNode->dict.word = malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(newNode->dict.word, buff);


		printf("Перевод %i: ", i + 1);
		scanf(format, buff);
		OemToAnsi(buff, buff);

		newNode->dict.translation = malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(newNode->dict.translation, buff);

		printf("Пример в предложении %i: ", i + 1);
		scanf(format, buff);
		OemToAnsi(buff, buff);

		newNode->dict.useInCentence = malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(newNode->dict.useInCentence, buff);

		if ((first == NULL) || (strcmp(first->dict.translation, newNode->dict.translation) >= 0))
		{
			newNode->next = first;
			first = newNode;
			continue;
		}

		current = first;

		while (1)
		{
			if ((current->next == NULL) || (strcmp(current->next->dict.translation, newNode->dict.translation) >= 0))
			{
				newNode->next = current->next;
				current->next = newNode;
				break;
			}
			current = current->next;
		}
	}

	return first;
}

struct node* search_list(struct node *list,char *word)
{
	int flag = 0;
	struct node *current = list;
	while(current != NULL)
	{
		flag = strcmp(current->dict.translation, word);
		if (flag > 0)
			break;
		if (flag == 0)
			return current;
		current = current->next;
	}

	return NULL;
}


int main(void)
{
	setlocale(LC_ALL, "RUS");

	struct node *list = inputList();
	struct node *searchRes = NULL;
	struct node *nextNode = NULL;

	char con_input[100];
	printf("\n\nВведите 0 чтобы выйти\n");

	while (1)
	{
		printf("\nИскомое слово по переводу: ");
		scanf(" %99s", con_input);
		if (con_input[0] == '0')
			break;

		OemToAnsi(con_input, con_input);
		searchRes = search_list(list, con_input);
		if (searchRes == NULL)
			printf("Искомый перевод не найден\n");
		else
			printf("Слово: %s\nПример в предложении: %s\n", searchRes->dict.word, searchRes->dict.useInCentence);
	}

	while(list != NULL)
	{
		free(list->dict.word);
		free(list->dict.useInCentence);
		free(list->dict.translation);
		nextNode = list->next;
		free(list);
		list = nextNode;
	}

	return 0;
}