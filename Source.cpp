#include<stdio.h>
#include<locale.h>
#include<string.h>

FILE *f, *F;
int k = 0;

struct Avtoservis
{
	char reg_nomer[15];
	char marka[50];
	int probeg;
	char imya_mastera[20];
	int summa_remonta;
}car, mas[15];
	
int vvod()
{
	int ch;

	while (1)
	{
		if(scanf_s("%d", &ch) != 1){
			getchar();
			printf("\nВведен неверный тип, попробуйте еще раз ");
				}
		else break;
		
	}
	getchar();
	return ch;
}
int menu()
{
	int ch = 0;
	while(ch < 1 || ch > 8){
	printf("\nВыберете действие\n");
	printf("\n1. Формирование файла\n");
	printf("2. Печать вайла\n");
	printf("3. Поиск по параметру\n");
	printf("4. Добавление\n");
	printf("5. Изменения 1 параметра\n");
	printf("6. Удаление записи\n");
	printf("7. Сортировка по параметру\n");
	printf("8. Выход\n");

	printf("\nВаш выбор: ");
	ch = vvod();
	printf("\n");
	}
	return ch;
}


int readf()
{
	if (fopen_s(&f, "struct.dat", "r+b"))
	{
		printf("Ошибка открытия файла");
		return 1;
	}


	char b[10];
	if (fread(b, 1, 1, f) == 0) {
		printf("Файл пуст!");
		return 1;
	}
	rewind(f);

	k = 0;
	for (int i = 0; !feof(f); i++)
	{
		char a[20];
		int j = 0;

		fgets(a, 30, f);
		for (j = 0; a[j] != '\n'; j++);
		strncpy_s(mas[i].imya_mastera, a, j - 1);

		fgets(a, 30, f);
		for (j = 0; a[j] != '\n'; j++);
		strncpy_s(mas[i].marka, a, j - 1);

		fscanf_s(f, "%d", &mas[i].probeg);
		fgetc(f);
		fgetc(f);

		fgets(a, 30, f);
		for (j = 0; a[j] != '\n'; j++);
		strncpy_s(mas[i].reg_nomer, a, j - 1);

		fscanf_s(f, "%d", &mas[i].summa_remonta);
		fgetc(f);
		fgetc(f);
		k++;
	}
	fclose(f);
}

void changes()
{
	if (readf() == 1)
		return;

	printf("\nВведите какую запись вы хотитет изменить: ");

	int zap;

	while (1)
	{
		zap = vvod();
		if (zap <= k) break;
		else printf("Такой записи не сущесвтует, попробуйте еще раз: ");
	}


	printf("\nВведите что хотите изменить\n");
	int ch = -1;
	while (ch < 1 || ch > 5)
	{
		printf("1) Имя мастера\n");
		printf("2) Марка\n");
		printf("3) Пробег\n");
		printf("4) Рег номер\n");
		printf("5) Сумма ремонта\n");

		printf("\nВаш выбор: ");
		ch = vvod();
	}

	switch (ch)
	{
		case 1:
			printf("\nВведите новое имя мастера: ");
			gets_s(mas[zap - 1].imya_mastera);
			printf("Измененно!\n");
			break;

		case 2:
			printf("\nВведите новую марку: ");
			gets_s(mas[zap - 1].marka);
			printf("Измененно!\n");
			break;

		case 3: 
			printf("\nВведите новый пробег: ");
			mas[zap - 1].probeg = vvod();
			printf("Измененно!\n");
			break;

		case 4:
			printf("\nВведите новый рег номер: ");
			gets_s(mas[zap - 1].reg_nomer);
			printf("Измененно!\n");
			break;
		case 5:
			printf("\nВведите новую сумму ремонта: ");
			mas[zap - 1].summa_remonta = vvod();
			printf("Измененно!\n");
			break;
	}

	if (fopen_s(&f, "struct.dat", "w"))
	{
		printf("Ошибка открытия файла");
		return;
	}

	
	for (int i = 0; i < k; i++)
	{
		fputs(mas[i].imya_mastera, f);
		fprintf(f, "\n");

		fputs(mas[i].marka, f);
		fprintf(f, "\n");

		fprintf(f, "%d\n", mas[i].probeg);

		fputs(mas[i].reg_nomer, f);
		fprintf(f, "\n");

		if (i + 1 != k)
			fprintf(f, "%d\n", mas[i].summa_remonta);
		else fprintf(f, "%d", mas[i].summa_remonta);
			
	}
	fclose(f);
}



void print()
{
	if (readf() == 1)
		return;

	printf("\n ----------------------------------------------------------------------------------\n");
	printf(" | Запись | Имя мастера |    Марка    |    Пробег   |  Рег номер  | Сумма ремонта |\n");
	printf(" ----------------------------------------------------------------------------------\n");

	for (int i = 0; i < k; i++)
	{
		printf(" |%4d%14s%14s%14d%14s%14d      |\n", i + 1, mas[i].imya_mastera, mas[i].marka, mas[i].probeg, mas[i].reg_nomer, mas[i].summa_remonta);
	}
	printf(" ----------------------------------------------------------------------------------\n");

}

void form(int num)
{
	
	if (num == 1){
		if (fopen_s(&f, "struct.dat", "w"))
		{
			printf("Ошибка открытия файла");
			return;
		}
				}
	else 
		if (fopen_s(&f, "struct.dat", "a"))
		{
			printf("Ошибка открытия файла");
			return;
		}
		else fprintf(f, "\n");
		

	int ch;
	printf("Введите количество записей: ");
	ch = vvod();

	for (int i = 0; i < ch; i++)
	{
		printf("\n\nЗапись %d\nВведите Имя мастера ", i + 1);
		gets_s(mas[i].imya_mastera);
		fputs(mas[i].imya_mastera, f);
		fprintf(f, "\n");

		printf("Введите марку ");
		gets_s(mas[i].marka);
		fputs(mas[i].marka, f);
		fprintf(f, "\n");

		printf("Введите пробег ");
		mas[i].probeg = vvod();
		fprintf(f, "%d\n", mas[i].probeg);

		printf("Введите рег номер ");
		gets_s(mas[i].reg_nomer);
		fputs(mas[i].reg_nomer, f);
		fprintf(f, "\n");

		printf("Введите сумму ремонта ");
		mas[i].summa_remonta = vvod();
		if(i + 1 != ch)
			fprintf(f, "%d\n", mas[i].summa_remonta);
		else fprintf(f, "%d", mas[i].summa_remonta);
	}

	fclose(f);
}

void deletef()
{
	if (readf() == 1)
		return;

	printf("Введите какую запись удалить: ");
	int zap;

	while (1)
	{
		zap = vvod();
		if (zap <= k) break;
		else printf("Такой записи не сущесвтует, попробуйте еще раз: ");
	}
	if (fopen_s(&f, "struct.dat", "w"))
	{
		printf("Ошибка открытия файла");
		return;
	}


	for (int i = 0; i < k; i++)
	{
		if(i != zap - 1){
			fputs(mas[i].imya_mastera, f);
			fprintf(f, "\n");

			fputs(mas[i].marka, f);
			fprintf(f, "\n");
				
			fprintf(f, "%d\n", mas[i].probeg);

			fputs(mas[i].reg_nomer, f);
			fprintf(f, "\n");

			if (i + 1 == k || (zap == k && i + 2 == k))
				fprintf(f, "%d", mas[i].summa_remonta);
			else 
				fprintf(f, "%d\n", mas[i].summa_remonta);
		}
	}
	fclose(f);
}

void findf()
{
	if (readf() == 1)
		return;

	if (fopen_s(&f, "struct.dat", "rb"))
	{
		printf("Ошибка открытия файла");
		return;
	}

	int ch = 0;
	while (ch < 1 || ch > 5) {
		printf("\n1. Имя мастера\n");
		printf("2. Марка\n");
		printf("3. Пробег\n");
		printf("4. Регистрационный номер\n");
		printf("5. Сумма ремонта\n");

		printf("Ваш выбор: ");
		ch = vvod();
	}
	
	switch (ch)
		{
		case 1:
			printf("\n");
			for (int i = 0; i < k; i++)
			{
				printf("%d | %s\n", i + 1, mas[i].imya_mastera);
			}
			break;
		case 2:
			printf("\n");
			for (int i = 0; i < k; i++)
			{
				printf("%d | %s\n", i + 1, mas[i].marka);
			}
			break;
		case 3:
			printf("\n");
			for (int i = 0; i < k; i++)
			{
				printf("%d | %d\n", i + 1, mas[i].probeg);
			}
			break;
		case 4:
			printf("\n");
			for (int i = 0; i < k; i++)
			{
				printf("%d | %s\n", i + 1, mas[i].reg_nomer);
			}
			break;
		case 5:
			printf("\n");
			for (int i = 0; i < k; i++)
			{
				printf("%d | %d\n", i + 1, mas[i].summa_remonta);
			}
			break;
		}

	fclose(f);

}

void sort()
{
	if (readf() == 1)
		return;

	if (fopen_s(&f, "struct.dat", "w"))
	{
		printf("Ошибка открытия файла");
		return;
	}

	printf("\nВведите по какому параметру сортировать: ");
	int ch = 0;
	while (ch < 1 || ch > 5) {
		printf("\n1. Имя мастера\n");
		printf("2. Марка\n");
		printf("3. Пробег\n");
		printf("4. Регистрационный номер\n");
		printf("5. Сумма ремонта\n");

		printf("Ваш выбор: ");
		ch = vvod();
	}

	switch (ch)
	{
	case 1:
		for (int i = 0; i < k - 1; i++) {
			for (int j = 0; j < k - 1 - i; j++) {
				if (strcmp(mas[j].imya_mastera, mas[j + 1].imya_mastera) > 0) {
					car = mas[j];
					mas[j] = mas[j + 1];
					mas[j + 1] = car;
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < k - 1; i++) {
			for (int j = 0; j < k - 1 - i; j++) {
				if (strcmp(mas[j].marka, mas[j + 1].marka) > 0) {
					car = mas[j];
					mas[j] = mas[j + 1];
					mas[j + 1] = car;
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < k - 1; i++) {
			for (int j = 0; j < k - 1 - i; j++) {
				if (mas[j].probeg > mas[j + 1].probeg) {
					car = mas[j];
					mas[j] = mas[j + 1];
					mas[j + 1] = car;
				}
			}
		}
		break;
	case 4:
		for (int i = 0; i < k - 1; i++) {
			for (int j = 0; j < k - 1 - i; j++) {
				if (strcmp(mas[j].reg_nomer, mas[j + 1].reg_nomer) > 0) {
					car = mas[j];
					mas[j] = mas[j + 1];
					mas[j + 1] = car;
				}
			}
		}
		break;
	case 5:
		for (int i = 0; i < k - 1; i++) {
			for (int j = 0; j < k - 1 - i; j++) {
				if (mas[j].summa_remonta > mas[j + 1].summa_remonta) {
					car = mas[j];
					mas[j] = mas[j + 1];
					mas[j + 1] = car;
				}
			}
		}
		break;
	}

	for (int i = 0; i < k; i++)
	{
		fputs(mas[i].imya_mastera, f);
		fprintf(f, "\n");

		fputs(mas[i].marka, f);
		fprintf(f, "\n");

		fprintf(f, "%d\n", mas[i].probeg);

		fputs(mas[i].reg_nomer, f);
		fprintf(f, "\n");

		if (i + 1 != k)
			fprintf(f, "%d\n", mas[i].summa_remonta);
		else fprintf(f, "%d", mas[i].summa_remonta);

	}

	fclose(f);
	print();
}

int main()
{
	setlocale(LC_ALL, "rus");

	while (1){
		switch (menu())
		{
			case 1:
				form(1);
				break;
	
			case 2: 
				print();
				break;
				
			case 3: 
				findf();
				break;
	
			case 4: 
				form(4);
				break;
		
			case 5:
				changes();
				break;
	
			case 6: 
				deletef();
				break;
		
			case 7:
				sort();
				break;
		
			case 8: 
				return 0;
		}
	}
}