﻿#include <stdio.h>
#include <string.h>
#include "locale.h"
#include <stdlib.h>

int const size = 100;

struct person
{
	char num[100];
	char name[100];
};

void exit(FILE* Phonebook)
{
	fclose(Phonebook);
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

int addPerson(int personNum, person* people)
{
	char name[100];
	char num[100];
	addName(name);
	addNum(num);
	person personVal;
	strcpy(personVal.name, name);
	strcpy(personVal.num, num);
	people[personNum] = personVal;
	printf("\nКонтакт успешно добавлен\n");
	return personNum + 1;
}

void saveNote(int peopleSchetchic, person* people)
{
	FILE* Phonebook;
	if ((Phonebook = fopen("Phonebook.txt", "w")) == NULL)
	{
		printf("error\n");
	}
	else
	{
		for (int i = 0; i < peopleSchetchic; i++)
		{
			fprintf(Phonebook, "%s\t%s\n", people[i].name, people[i].num);
		}
	}
	fclose(Phonebook);
	printf("\n\nСохранение прошло успешно \n");
}

void Print(FILE* Phonebook)
{
	char s[100];
	int k = 0;
	if ((Phonebook = fopen("Phonebook.txt", "r")) == NULL)
	{
		printf("error\n");
	}
	else
		while (fgets(s, 100, Phonebook))
		{
			printf("%s", s);
			k++;
		}
	printf("Количество строк: %d\n", k);
	fclose(Phonebook);
	printf("Все данные были распечатаны\n");
}

person* numSearch(char personName, char* nameFinder, person* people)
{
	int strSizeFinder = strlen(nameFinder);
	for (int i = 0; i < personName; i++)
	{
		bool equal = true;
		person personVal = people[i];
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

void printNumSearch(char personName, person* people)
{
	char nameFinder[100];
	printf("Введите номер контакта: ");
	scanf("%s", nameFinder);
	person* personVal = numSearch(personName, nameFinder, people);
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

person* nameSearch(int personNum, char* numFinder, person* people)
{
	int strSizeFinder = strlen(numFinder);
	for (int i = 0; i < personNum; i++)
	{
		bool equal = true;
		person personVal = people[i];
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

void printNameSearch(int personNum, person* people)
{
	char numFinder[100];
	printf("Введите имя контакта: ");
	scanf("%s", numFinder);
	person* personVal = nameSearch(personNum, numFinder, people);
	if (personVal == nullptr)
	{
		printf("Увы, такого контакта здесь нет\n");
		return;
	}
	printf("%s\t%s\n", personVal->name, personVal->num);
}

int load(person* people)
{
	int personSchetchic = 0;
	FILE* Phonebook;
	int i = 0;
	if ((Phonebook = fopen("Phonebook.txt", "r")) == NULL)
	{
		Phonebook = fopen("Phonebook.txt", "w");
		fclose(Phonebook);
		Phonebook = fopen("Phonebook.txt", "r");
	}
	char name[100];
	char num[100];
	while (fscanf(Phonebook, "%s", name) != EOF)
	{
		person personVal;
		fscanf(Phonebook, "%s", num);
		strcpy(personVal.name, name);
		strcpy(personVal.num, num);
		people[personSchetchic] = personVal;
		personSchetchic++;
	}
	return personSchetchic;
}

bool nameSearchTest(int personNum, char* numFinder, person* test)
{
	person* res = nameSearch(personNum, numFinder, test);
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

bool numSearchTest(int personName, char* nameFinder, person* test)
{
	person* res = numSearch(personName, nameFinder,test);
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
	person peopleTest1[2] = {{"qw","435345"}, {"sdfsd","436564" }};
	char numTestFinder[] = "sdfsd";
	if (!numSearchTest(2, numTestFinder, peopleTest1))
	{
		printf("Error");
		return 1;
	}

	person peopleTest2[2] = { {"qw","435345"}, {"sdfsd","436564" } };
	char nameTestFinder[] = "436564";
	if (!nameSearchTest(2, nameTestFinder, peopleTest2))
	{
		printf("Error");
		return 1;
	}

	person people[100];
	FILE* Phonebook;
	Phonebook = fopen("Phonebook.txt", "r+t");
	setlocale(LC_ALL, "Russian");
	printf("Это телефонный справочник\n");
	int schetchic = load(people);
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
		case '0': {exit(Phonebook); return 0;}
		case '1': {schetchic = addPerson(schetchic,people);break;}
		case '2': {Print(Phonebook);break;}
		case '3': {printNumSearch(schetchic, people);break;}
		case '4': {printNameSearch(schetchic, people);break;}
		case '5': {saveNote(schetchic, people);break;}
		case '6': {printf(" 0 - выйти\n 1 - добавить запись (имя и телефон)\n 2 - распечатать все имеющиеся записи\n 3 - найти имя по телефону \n 4 - найти телефон по имени \n 5 - сохранить текущие данные в файл \n");break;}
		case '\n': {break;}
		default: {printf("Я не знаю такой команды, вызовите инструкцию\n");}
		}
	}
	fclose(Phonebook);
	return 0;
}
