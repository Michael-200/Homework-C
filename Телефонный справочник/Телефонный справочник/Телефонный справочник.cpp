﻿#include <stdio.h>
#include <string.h>
#include "locale.h"
#include <stdlib.h>

int const size = 100;

struct Person
{
	char num[100];
	char name[100];
};

void exit(FILE* phonebook)
{
	fclose(phonebook);
}

void addNum(char* num)
{
	printf("Введите номер контакта: ");
	scanf("%s", num);
}

void addName(char* name)
{
	printf("Введите имя контакта: ");
	scanf("%s", name);
}

int addPerson(int personNum, Person* people)
{
	Person personVal;
	addName(personVal.name);
	addNum(personVal.num);
	people[personNum] = personVal;
	printf("\nКонтакт успешно добавлен\n");
	return personNum + 1;
}

void saveNote(int peopleCounter, Person* people)
{
	FILE* phonebook = fopen("Phonebook.txt", "w");
	if (phonebook == nullptr)
	{
		printf("error\n");
	}
	else
	{
		for (int i = 0; i < peopleCounter; i++)
		{
			fprintf(phonebook, "%s\t%s\n", people[i].name, people[i].num);
		}
	}
	fclose(phonebook);
	printf("\n\nСохранение прошло успешно \n");
}

void Print(FILE* phonebook)
{
	char s[100];
	int k = 0;
	if ((phonebook = fopen("Phonebook.txt", "r")) == nullptr)
	{
		printf("error\n");
	}
	else
	{
		while (fgets(s, 100, phonebook))
		{
			printf("%s", s);
			k++;
		}
	}
	printf("Количество строк: %d\n", k);
	fclose(phonebook);
	printf("Все данные были распечатаны\n");
}

Person* numSearch(char personName, char* nameFinder, Person* people)
{
	int strSizeFinder = strlen(nameFinder);
	for (int i = 0; i < personName; i++)
	{
		bool equal = true;
		Person personVal = people[i];
		int sizePersonNum = strlen(personVal.num);
		if (sizePersonNum != strSizeFinder)
		{
			continue;
		}
		for (int j = 0; j < strSizeFinder; j++)
		{
			if (nameFinder[j] != personVal.num[j])
			{
				equal = false;
			}
		}
		if (equal)
		{
			return &people[i];
		}
	}
	return nullptr;
}

void printNumSearch(char personName, Person* people)
{
	char nameFinder[100];
	printf("Введите номер контакта: ");
	scanf("%s", nameFinder);
	Person* personVal = numSearch(personName, nameFinder, people);
	if (personVal == nullptr)
	{
		printf("\nУвы, такого контакта здесь нет\n");
		return;
	}
	printf("%s\t%s\n", personVal->name, personVal->num);
}

int min(int x, int y)
{
	return x > y ? y : x;
}

Person* nameSearch(int personNum, char* numFinder, Person* people)
{
	int strSizeFinder = strlen(numFinder);
	for (int i = 0; i < personNum; i++)
	{
		bool equal = true;
		Person personVal = people[i];
		int sizePersonName = strlen(personVal.name);
		if (sizePersonName != strSizeFinder)
		{
			continue;
		}
		for (int j = 0; j < strSizeFinder; j++)
		{
			if (numFinder[j] != personVal.name[j])
			{
				equal = false;
			}
		}
		if (equal)
		{
			return &people[i];
		}
	}
	return nullptr;
}

void printNameSearch(int personNum, Person* people)
{
	char numFinder[100];
	printf("Введите имя контакта: ");
	scanf("%s", numFinder);
	Person* personVal = nameSearch(personNum, numFinder, people);
	if (personVal == nullptr)
	{
		printf("Увы, такого контакта здесь нет\n");
		return;
	}
	printf("%s\t%s\n", personVal->name, personVal->num);
}

int load(Person* people)
{
	int personCounter = 0;
	FILE* phonebook = fopen("Phonebook.txt", "r");
	int i = 0;
	if (phonebook == nullptr)
	{
		phonebook = fopen("Phonebook.txt", "w");
		fclose(phonebook);
		phonebook = fopen("Phonebook.txt", "r");
	}
	char name[100];
	char num[100];
	while (fscanf(phonebook, "%s", name) != EOF)
	{
		Person personVal;
		fscanf(phonebook, "%s", num);
		strcpy(personVal.name, name);
		strcpy(personVal.num, num);
		people[personCounter] = personVal;
		personCounter++;
	}
	return personCounter;
}

bool nameSearchTest(int personNum, char* numFinder, Person* test)
{
	Person* res = nameSearch(personNum, numFinder, test);
	int n = strlen(numFinder);
	for (int i = 0; i <= n; i++)
	{
		if (numFinder[i] != res->name[i])
		{
			return false;
		}
	}
	return true;
}

bool numSearchTest(int personName, char* nameFinder, Person* test)
{
	Person* res = numSearch(personName, nameFinder,test);
	int n = strlen(nameFinder);
	for (int i = 0; i <= n; i++)
	{
		if (nameFinder[i] != res->num[i])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	Person peopleTest1[2] = {{"qw","435345"}, {"sdfsd","436564" }};
	char numTestFinder[] = "sdfsd";
	if (!numSearchTest(2, numTestFinder, peopleTest1))
	{
		printf("Error");
		return 1;
	}

	Person peopleTest2[2] = { {"qw","435345"}, {"sdfsd","436564" } };
	char nameTestFinder[] = "436564";
	if (!nameSearchTest(2, nameTestFinder, peopleTest2))
	{
		printf("Error");
		return 1;
	}

	Person people[100];
	FILE* phonebook = fopen("Phonebook.txt", "r+t");
	setlocale(LC_ALL, "Russian");
	printf("Это телефонный справочник\n");
	int counter = load(people);
	char act = '0';
	while (true)
	{
		if (act != '\n')
		{
			printf("\nВызов инструкции осуществляется по номеру 6\nВведите номер команды: ");
		}
		scanf("%c", &act);
		switch (act)
		{
		case '0': {exit(phonebook); return 0;}
		case '1': {counter = addPerson(counter,people);break;}
		case '2': {Print(phonebook);break;}
		case '3': {printNumSearch(counter, people);break;}
		case '4': {printNameSearch(counter, people);break;}
		case '5': {saveNote(counter, people);break;}
		case '6': {printf(" 0 - выйти\n 1 - добавить запись (имя и телефон)\n \
							2 - распечатать все имеющиеся записи\n 3 - найти имя по телефону \n \
							4 - найти телефон по имени \n 5 - сохранить текущие данные в файл \n");break;}
		case '\n': {break;}
		default: {printf("Я не знаю такой команды, вызовите инструкцию\n");}
		}
	}
	fclose(phonebook);
	return 0;
}
