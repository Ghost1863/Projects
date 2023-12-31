#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include<locale.h>
#include <ctype.h>

#define START_SENTENCE "Course work for option 4.23, created by Malinovskii Aleksandr."
#define BLOCK_SIZE 100
#define LAST_SYMBOL '\n\n'

void InputHandler();
void PrintingReference();

char* get_input(int* input_sentences_number);
char** split_text_by_sentences(char* text, char* splitters,
	int input_sentences_number, int* output_sentences_number);
void printTextAndFreeMemory(char* text, char** splitted_text,
	int* output_sentences_number);
void removeDuplicates(char** splitted_text, int* num_sentences);

int countWordsInSentence(char* sentence);
void deleteEvenSentencesWithEvenWordsNumber(char** splitted_text,
	int* output_sentences_number);

void sortUppercaseWordsInSentence(char** splitted_text,
	int* output_sentence_number);

void replaceLessThanThreeSymbolsWords(char** splitted_text,
	int* output_sentences_number);

void PrintMaxDigitWords(char** splitted_text,
	int* output_sentence_number);

int main()
{
	setlocale(LC_ALL, "Russian");
	InputHandler();

	return 0;
}

void PrintingReference(){
	printf("%s\n%s\n%s\n%s\n%s\n%s\n",
		"0 � ����� ������ ����� ��������� ������������ ���������",
		"1 � ����� ������� ��� ������� 1 �� ������ �������",
		"2 � ����� ������� ��� ������� 2 �� ������ �������",
		"3 � ����� ������� ��� ������� 3 �� ������ �������",
		"4 � ����� ������� ��� ������� 4 �� ������ �������",
		"5 � ����� ������� � ��������, ������� ��������� ���������.");
}

void InputHandler() {
	
	printf("%s\n", START_SENTENCE);
	int user_choice = 0;
	scanf("%d\n", &user_choice);
	int input_sentences_number = 0;
	int output_sentences_number = 0;
	char* text = NULL;
	char** splitted_text = NULL;

	switch (user_choice) {
	case 0: {
		text = get_input(&input_sentences_number);
		splitted_text = split_text_by_sentences(text, ".",
			input_sentences_number, &output_sentences_number);
		printTextAndFreeMemory(text, splitted_text,
			&output_sentences_number);
	
		break;
	}
	case 1: {
		text = get_input(&input_sentences_number);
		splitted_text = split_text_by_sentences(text, ".",
			input_sentences_number, &output_sentences_number);
		
		deleteEvenSentencesWithEvenWordsNumber(splitted_text,
			&output_sentences_number);
		printTextAndFreeMemory(text, splitted_text,
			&output_sentences_number);
		
		break;
	}
	case 2:{
		text = get_input(&input_sentences_number);
		splitted_text = split_text_by_sentences(text, ".",
			input_sentences_number, &output_sentences_number);
		sortUppercaseWordsInSentence(splitted_text, &output_sentences_number);
		for (int i = 0; i < output_sentences_number; i++) {
			free(splitted_text[i]);
		}
		free(text);
		free(splitted_text);

		break;
	}
	case 3:
		text = get_input(&input_sentences_number);
		splitted_text = split_text_by_sentences(text, ".",
			input_sentences_number, &output_sentences_number);
		replaceLessThanThreeSymbolsWords(splitted_text, &output_sentences_number);
		for (int i = 0; i < output_sentences_number; i++) {
			free(splitted_text[i]);
		}
		free(text);
		free(splitted_text);
		break;
	case 4:
		text = get_input(&input_sentences_number);
		splitted_text = split_text_by_sentences(text, ".",
			input_sentences_number, &output_sentences_number);
		PrintMaxDigitWords(splitted_text, &output_sentences_number);
		for (int i = 0; i < output_sentences_number; i++) {
			free(splitted_text[i]);
		}
		free(text);
		free(splitted_text);
		break;
	case 5:
		PrintingReference();
		break;
	default:
		printf("Error: �������� ����");
		break;

	}
}

//////////////////////////////////////////////////////////0
char* get_input(int* input_sentences_number) {
	int length =0;
	int capacity = BLOCK_SIZE;
	char char_temp = 0;
	char* text = malloc(sizeof(char) * capacity);

	//������������ ��������� ������ ��� �������� �����
	while (char_temp = getchar()) {
		// ���� ��������� 2 ������� - ������� ������, ��������� ������
		if (char_temp == '\n') {
			if (length > 0 && text[length - 1] == '\n')
				break;
		}
		//���������� ����������� text 
		if (length >= capacity) {
			capacity += BLOCK_SIZE;
			text = realloc(text, capacity * sizeof(char));
		}
		//������� �����������
		if (char_temp == '.') {
			(*input_sentences_number)++;
		}
		text[length++] = char_temp;
	}
	text = realloc(text, (length + 2) * sizeof(char));
	text[length++] = '\n';
	text[length] = '\0';
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

char** split_text_by_sentences(char* text, char* splitters,
	int input_sentences_number, int* output_sentences_number) {

	char** splitted_text = malloc(sizeof(char*));
	int sentences_counter = 0;
	int last_ind = 0;

	for (int i = 0; i < (int)strlen(text); i++) {

		if (strchr(splitters, text[i])) {
			sentences_counter++;
			splitted_text = realloc(splitted_text, sentences_counter * sizeof(char*));
			splitted_text[sentences_counter - 1] = malloc((last_ind + 2) * sizeof(char));

			int chr_temp = 0;
			for (int j = last_ind; j >= 0; j--) {
				//���������� ������ � ������� ������ � ������ �����������(���� ��� ����)
				if ((j == last_ind) && (isspace(text[i - j])) || (text[i - j] == '.'))
					continue;
					splitted_text[sentences_counter - 1][chr_temp++] = text[i - j];
			}

			while (isspace(splitted_text[sentences_counter - 1][chr_temp - 1])) {
				chr_temp--;
			}
			splitted_text[sentences_counter - 1][chr_temp] = '\0';
			last_ind = 0;

			continue;
		}
		last_ind++;
	}
	*output_sentences_number = sentences_counter;
	printf("%d ����������� �� ��������� ���������\n", *output_sentences_number);
	//������� ������������� �����������
	removeDuplicates(splitted_text, output_sentences_number);
	printf("%d ����������� ����� ��������� ���������\n\n", *output_sentences_number);
	return splitted_text;
}

void removeDuplicates(char** splitted_text, int* num_sentences) {
	for (int i = 0; i < *num_sentences; i++) {

		for (int j = i + 1; j < *num_sentences; j++) {

			if (_stricmp(splitted_text[i], splitted_text[j]) == 0) {
				free(splitted_text[j]);
				for (int k = j; k < *num_sentences; k++) {
					splitted_text[k] = splitted_text[k + 1];
				}
				(*num_sentences)--;
				j--;
			}
		}
	}
}

////////////////////////////////////////////////////////1
int countWordsInSentence(char* sentence) {
	int counter = 0;
	int inWord = 0;
	for (int i = 0; sentence[i] != '\0'; i++)
	{
		if (!isspace(sentence[i]) && sentence[i] != ',') {
			if (!inWord) {
				inWord = 1;
				counter++;
			}
		}
		else
			inWord = 0;
	}
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

////////////////////////////////////////////////////2
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

		//������ ������������
		char** splitters = malloc(sizeof(char*) * (numWordsInSentence -1));
		splitters[0] = malloc(sizeof(char) * 10);
		int current_splitter = 0;
		for (int j = 0; j < strlen(splitted_text[i]); j++)
		{
			int counter = 0;
			if (isspace(splitted_text[i][j]) || splitted_text[i][j] == ',') {
				while (isspace(splitted_text[i][j]) || splitted_text[i][j] == ',') {
					splitters[current_splitter][counter++] = splitted_text[i][j++];	
				}
				splitters[current_splitter][counter] = '\0';
				if (current_splitter < numWordsInSentence - 2) {
					current_splitter++;
					splitters[current_splitter] = malloc(sizeof(char) * 10);
				}
			}
		}
	
		//������ ���� � �����������
		char** words=malloc(sizeof(char*)*numWordsInSentence);
		char* word = strtok(splitted_text[i], " ,\t\n.");
		int word_counter = 0;
		
		while (word!=NULL)
		{
			words[word_counter] = word;
			word = strtok(NULL, " ,\t\n.");
			word_counter++;
		}
		//���������� ���� �� ����������� ���������� ��������� ����
		qsort(words, numWordsInSentence, sizeof(char*), compareUppercaseLetters);

		for (int k = 0; k < numWordsInSentence; k++) {
			
				printf("%s", words[k]);
				if (k < current_splitter + 1 && numWordsInSentence>1)
				printf("%s", splitters[k]);
		}
		for (int i = 0; i < current_splitter+1; i++)
		{
			free(splitters[i]);
		}
		printf("\n");
		free(words);
		if (numWordsInSentence > 1)
			free(splitters);
	}
}

//////////////////////////////////////////////////////3
void replaceLessThanThreeSymbolsWords(char** splitted_text,
	int* output_sentence_number) {
	for (int i = 0; i < *output_sentence_number; i++)
	{
		int numWordsInSentence = countWordsInSentence(splitted_text[i]);

		//������ ������������
			char** splitters = malloc(sizeof(char*) * (numWordsInSentence - 1));
			splitters[0] = malloc(sizeof(char) * 10);
			int current_splitter = 0;

			for (int j = 0; j < strlen(splitted_text[i]); j++)
			{
				int counter = 0;
				if (isspace(splitted_text[i][j]) || splitted_text[i][j] == ',') {
					while (isspace(splitted_text[i][j]) || splitted_text[i][j] == ',') {
						splitters[current_splitter][counter++] = splitted_text[i][j++];
					}
					splitters[current_splitter][counter] = '\0';
					if (current_splitter < numWordsInSentence - 2) {
						current_splitter++;
						splitters[current_splitter] = malloc(sizeof(char) * 10);
					}
				}
			}
		
		//������ ���� � �����������
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
			if (k < current_splitter + 1 && numWordsInSentence>1)
				printf("%s", splitters[k]);
		}
		for (int i = 0; i < current_splitter + 1; i++)
		{
			free(splitters[i]);
		}
		printf("\n");
		free(words);
		if (numWordsInSentence>1)
			free(splitters);
	}
}
///////////////////////////////////////////////////////4
void PrintMaxDigitWords(char** splitted_text,
	int* output_sentence_number) {
	for (int i = 0; i < *output_sentence_number; i++)
	{
		int numWordsInSentence = countWordsInSentence(splitted_text[i]);
		//������ ���� � �����������
		char** words = malloc(sizeof(char*) * numWordsInSentence);
		char* word = strtok(splitted_text[i], " ,\t\n.");
		int word_counter = 0;

		while (word != NULL)
		{
			words[word_counter] = word;
			word = strtok(NULL, " ,\t\n.");
			word_counter++;
		}

		int max_len = 0;
		int max_ind = 0;
		for (int k = 0; k < numWordsInSentence; k++) {	
			if (strlen(words[k]) > max_len && isdigit(words[k][0]) && isdigit(words[k][strlen(words[k])-1])) {
				max_len = strlen(words[k]);
				max_ind = k;
			}
		}
		printf("%s ",words[max_ind]);
		free(words);
	}
}