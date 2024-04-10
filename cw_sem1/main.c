#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include<locale.h>
#include <ctype.h>

#define TRUE 1
#define START_SENTENCE "Course work for option 4.23, created by Malinovskii Aleksandr."
#define BLOCK_SIZE 100
#define LAST_SYMBOL '\n\n'

void inputHandler();
void printingReference();

char* getInput();
char** splitTextBySentences(char* text, char* splitters,
	int* output_sentences_number);
void printTextAndFreeMemory(char* text, char** splitted_text,
	int* output_sentences_number);
void freeMemory(char* text, char** splitted_text,
	int* output_sentences_number);

void removeDuplicates(char** splitted_text, int* num_sentences);

int countWordsInSentence(char* sentence);
void deleteEvenSentencesWithEvenWordsNumber(char** splitted_text,
	int* output_sentences_number);

void sortUppercaseWordsInSentence(char** splitted_text,
	int* output_sentence_number);

void replaceLessThanThreeSymbolsWords(char** splitted_text,
	int* output_sentences_number);

int compareWordsLength(const void* a, const void* b);
int compareUppercaseLetters(const void* a, const void* b);

void PrintMaxDigitStrings(char** splitted_text,
	int* output_sentence_number);


int main()
{
	setlocale(LC_ALL, "Russian");
	inputHandler();
	
	return 0;
}

void printingReference() {
	printf("%s\n%s\n%s\n%s\n%s\n%s\n",
		"0 – вывод текста после первичной обязательной обработки",
		"1 – вызов функции под номером 1 из списка задания",
		"2 – вызов функции под номером 2 из списка задания",
		"3 – вызов функции под номером 3 из списка задания",
		"4 – вызов функции под номером 4 из списка задания",
		"5 – вывод справки о функциях, которые реализует программа.");
}

void inputHandler() {

	printf("%s\n", START_SENTENCE);
	char user_choice = 0;
	scanf("%c", &user_choice);
	getchar();

	if (isdigit(!user_choice)) {
		printf("Error: Incorrect Input");
	}

	int output_sentences_number = 0;
	char* text = NULL;
	char** splitted_text = NULL;

	switch (user_choice) {
	case '0': {
		text = getInput();
		splitted_text = splitTextBySentences(text, ".",
			&output_sentences_number);
		printTextAndFreeMemory(text, splitted_text,
			&output_sentences_number);

		break;
	}
	case '1': {
		text = getInput();
		splitted_text = splitTextBySentences(text, ".",
			&output_sentences_number);

		deleteEvenSentencesWithEvenWordsNumber(splitted_text,
			&output_sentences_number);
		printTextAndFreeMemory(text, splitted_text,
			&output_sentences_number);

		break;
	}
	case '2': {
		text = getInput();
		splitted_text = splitTextBySentences(text, ".",
			&output_sentences_number);
		sortUppercaseWordsInSentence(splitted_text, &output_sentences_number);
		freeMemory(text, splitted_text, &output_sentences_number);

		break;
	}
	case '3':
		text = getInput();
		splitted_text = splitTextBySentences(text, ".",
			&output_sentences_number);
		replaceLessThanThreeSymbolsWords(splitted_text, &output_sentences_number);
		freeMemory(text, splitted_text, &output_sentences_number);
		break;
	case '4':
		text = getInput();
		splitted_text = splitTextBySentences(text, ".",
			&output_sentences_number);
		PrintMaxDigitStrings(splitted_text, &output_sentences_number);
		freeMemory(text, splitted_text, &output_sentences_number);
		break;
	case '5':
		printingReference();
		break;
	default:
		printf("Error: Incorrect Input");
		break;

	}
}

//user_choice 0
char* getInput() {
	int length = 0;
	int capacity = BLOCK_SIZE;
	char char_temp = 0;
	char* text = malloc(sizeof(char) * capacity);

	//динамическое выделение памяти под исходный текст
	while ((char_temp = getchar())) {
		// если последние 2 символа - перенос строки, завершаем чтение
		if (char_temp == '\n') {
			if (length > 0 && text[length - 1] == '\n')
				break;
		}
		if (text[0] == '.') {
			printf("Error:Forbidden to start text with '.'\n ");
			break;
		}
		//увеличение вместимости text 
		if (length >= capacity) {
			capacity += BLOCK_SIZE;
			text = realloc(text, capacity * sizeof(char));
		}
		text[length++] = char_temp;
	}
	text[length] = '\0';
	if (text[strlen(text) - 1] != '.')
		text[strlen(text) - 1] = '.';
	return text;
}

void printTextAndFreeMemory(char* text, char** splitted_text,
	int* output_sentences_number) {
	for (int i = 0; i < *output_sentences_number; i++) {
		printf("%s\n", splitted_text[i]);
		free(splitted_text[i]);
	}
	free(text);
	free(splitted_text);
}

void freeMemory(char* text, char** splitted_text,
	int* output_sentences_number) {
	for (int i = 0; i < *output_sentences_number; i++) {
		free(splitted_text[i]);
	}
	free(text);
	free(splitted_text);
}

char** splitTextBySentences(char* text, char* splitters,
	int* output_sentences_number) {

	char** splitted_text = malloc(sizeof(char*));
	int sentences_counter = 0;
	int last_ind = 0;
	int was_letter_printed = 0;
	for (int i = 0; i < (int)strlen(text); i++) {

		if (strchr(splitters, text[i])) {

			sentences_counter++;
			splitted_text = realloc(splitted_text, sentences_counter * sizeof(char*));
			splitted_text[sentences_counter - 1] = malloc((last_ind + 2) * sizeof(char));

			int chr_temp = 0;
			for (int j = last_ind; j >= 0; j--) {
				//пропускаем пробелы и запятые в начале предложения(если они есть)
				if (!isspace(text[i - j]) && text[i - j] != ',')
					was_letter_printed = TRUE;
				if ((!was_letter_printed) && (isspace(text[i - j]) || text[i - j] == ','))
					continue;

				//обработка корректного ввода разделителей
			/*	if (isspace(text[i - j]) && isspace(text[i - j - 1]) ||
					text[i - j] == ',' && text[i - j - 1] == ',')
					continue;*/
				splitted_text[sentences_counter - 1][chr_temp++] = text[i - j];
			}

			while (isspace(splitted_text[sentences_counter - 1][chr_temp - 1])) {
				chr_temp--;
			}
			splitted_text[sentences_counter - 1][chr_temp] = '\0';
			last_ind = 0;
			continue;
		}
		was_letter_printed = 0;
		last_ind++;
	}

	*output_sentences_number = sentences_counter;
	//убираем повторяющиеся и пустые предложения 
	removeDuplicates(splitted_text, output_sentences_number);
	return splitted_text;
}

void removeDuplicates(char** splitted_text, int* num_sentences) {
	//removing duplicate sentences
	for (int i = 0; i < *num_sentences; i++) {
		for (int j = i + 1; j < *num_sentences; j++) {
			if (strcmp(splitted_text[i], splitted_text[j]) == 0) {
				free(splitted_text[j]);
				for (int k = j; k < *num_sentences; k++) {
					splitted_text[k] = splitted_text[k + 1];
				}
				(*num_sentences)--;
				j--;
			}
		}
	}
	//deleting void sentences(with no letters)
	for (int i = 0; i < *num_sentences; i++)
	{
		if (splitted_text[i][0] == '.') {
			free(splitted_text[i]);
			for (int k = i; k < *num_sentences; k++) {
				splitted_text[k] = splitted_text[k + 1];
			}
			(*num_sentences)--;
			i--;
		}
	}
}


//user_choice 1
int countWordsInSentence(char* sentence) {
	int counter = 0;
	int inWord = 0;
	for (int i = 0; sentence[i] != '\0'; i++)
	{
		if (!isspace(sentence[i]) && sentence[i] != ',') {
			if (!inWord) {
				inWord = TRUE;
				counter++;
			}
		}
		else
			inWord = 0;
	}
	if (isspace(sentence[strlen(sentence) - 2]) || sentence[strlen(sentence) - 2] == ',')
		counter--;
	return counter;
}

void deleteEvenSentencesWithEvenWordsNumber(char** splitted_text,
	int* output_sentences_number) {
	int initial_sentence_number = *output_sentences_number;
	int index = 0;
	for (int i = 0; i < initial_sentence_number; i++) {
		if ((i % 2 == 0) && (countWordsInSentence(splitted_text[i - index]) % 2 == 0)) {
			free(splitted_text[i - index]);
			for (int k = i - index; k < *output_sentences_number; k++) {
				splitted_text[k] = splitted_text[k + 1];
			}
			index++;
			(*output_sentences_number)--;
		}
	}
}

//user_choice 2
int countUppercaseLetters(char* word) {
	int counter = 0;
	for (int i = 0; word[i] != '\0'; i++) {
		if (isupper(word[i]))
			counter++;
	}
	return counter;
}

int compareUppercaseLetters(const void* a, const void* b) {
	return countUppercaseLetters(*(char**)a) - countUppercaseLetters(*(char**)b);
}

void sortUppercaseWordsInSentence(char** splitted_text,
	int* output_sentence_number) {

	for (int i = 0; i < *output_sentence_number; i++)
	{
		int numWordsInSentence = countWordsInSentence(splitted_text[i]);

		//массив разделителей
		//оставляем место для разделителя после последнего слова
		char** splitters = malloc(sizeof(char*) * (numWordsInSentence));
		splitters[0] = calloc(10,sizeof(char));
		int current_splitter = 0;
		for (int j = 0; j < strlen(splitted_text[i]); j++)
		{
			int counter = 0;
			if (isspace(splitted_text[i][j]) || splitted_text[i][j] == ',') {
				while (isspace(splitted_text[i][j]) || splitted_text[i][j] == ',') {
					splitters[current_splitter][counter++] = splitted_text[i][j++];
				}
				splitters[current_splitter][counter] = '\0';
				if (current_splitter < numWordsInSentence - 1) {
					current_splitter++;
					splitters[current_splitter] = calloc(10,sizeof(char));
				}
			}
		}

		//массив слов в предложении
		char** words = malloc(sizeof(char*) * numWordsInSentence);
		char* word = strtok(splitted_text[i], " ,\t\n.");
		int word_counter = 0;

		while (word != NULL)
		{
			words[word_counter] = word;
			word = strtok(NULL, " ,\t\n.");
			word_counter++;
		}
		//сортировка слов по возрастанию количества заглавных букв
		qsort(words, numWordsInSentence, sizeof(char*), compareUppercaseLetters);
		for (int k = 0; k < numWordsInSentence; k++) {
			printf("%s", words[k]);
			if (k < current_splitter + 1 && (strchr(splitters[k], ' ')
			|| strchr(splitters[k], ',') || strchr(splitters[k], '\t') || strchr(splitters[k], '\n')))
				printf("%s", splitters[k]);
				
		}
		printf(".\n");
		for (int i = 0; i < current_splitter + 1; i++)
			free(splitters[i]);

		free(words);
		free(splitters);
	}
}

//user_choice 3

void replaceLessThanThreeSymbolsWords(char** splitted_text,
	int* output_sentence_number) {
	for (int i = 0; i < *output_sentence_number; i++)
	{
		int numWordsInSentence = countWordsInSentence(splitted_text[i]);

		//массив разделителей
		//оставляем место для разделителя после последнего слова
		char** splitters = malloc(sizeof(char*) * (numWordsInSentence));
		splitters[0] = calloc(10, sizeof(char));
		int current_splitter = 0;
		for (int j = 0; j < strlen(splitted_text[i]); j++)
		{
			int counter = 0;
			if (isspace(splitted_text[i][j]) || splitted_text[i][j] == ',') {
				while (isspace(splitted_text[i][j]) || splitted_text[i][j] == ',') {
					splitters[current_splitter][counter++] = splitted_text[i][j++];
				}
				splitters[current_splitter][counter] = '\0';
				if (current_splitter < numWordsInSentence - 1) {
					current_splitter++;
					splitters[current_splitter] = calloc(10, sizeof(char));
				}
			}
		}

		//массив слов в предложении
		char** words = malloc(sizeof(char*) * numWordsInSentence);
		char* word = strtok(splitted_text[i], " ,\t\n.");
		int word_counter = 0;

		while (word != NULL)
		{
			words[word_counter] = word;
			word = strtok(NULL, " ,\t\n.");
			word_counter++;
		}

		for (int k = 0; k < numWordsInSentence; k++) {
			if (strlen(words[k]) > 3)
				printf("%s", words[k]);
			else
				printf("Less Then 3");
			if (k < current_splitter + 1 && (strchr(splitters[k], ' ')
				|| strchr(splitters[k], ',') || strchr(splitters[k], '\t')|| strchr(splitters[k],'\n')))
				printf("%s", splitters[k]);
		}
		
		for (int i = 0; i < current_splitter + 1; i++)
			free(splitters[i]);
		printf(".\n");
		free(words);
		free(splitters);
	}
}

//user_choice 4
int compareWordsLength(const void* a, const void* b) {
	return strlen(*(char**)b) - strlen(*(char**)a);
}

void PrintMaxDigitStrings(char** splitted_text,
	int* output_sentence_number) {
	char** max_strings = malloc(sizeof(char*) * *output_sentence_number);
	int first_ind = 0;
	int last_ind = 0;

	for (int i = 0; i < *output_sentence_number; i++) {
		for (int j = 0; j < strlen(splitted_text[i]); j++)
		{
			if (isdigit(splitted_text[i][j])) {
				first_ind = j;
				break;
			}
		}
		for (int k = strlen(splitted_text[i]); k >= 0; k--)
		{
			if (isdigit(splitted_text[i][k])) {
				last_ind = k;
				break;
			}
		}
		if (!isdigit(splitted_text[i][first_ind]) && !isdigit(splitted_text[i][last_ind]))
			printf("Warning:Sentence %d has no digits\n", i);

		char* string = malloc(sizeof(char) * (last_ind - first_ind + 2));
		strncpy(string, splitted_text[i] + first_ind, last_ind - first_ind + 1);
		string[last_ind - first_ind + 1] = '\0';
		max_strings[i] = string;
	}

	qsort(max_strings, *output_sentence_number, sizeof(char*), compareWordsLength);

	for (int i = 0; i < *output_sentence_number; i++)
	{
		if (isdigit(max_strings[i][0]))
			printf("%s\n", max_strings[i]);
		free(max_strings[i]);
	}
	free(max_strings);
}
