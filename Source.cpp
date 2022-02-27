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
			printf("\n������ �������� ���, ���������� ��� ��� ");
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
	printf("\n�������� ��������\n");
	printf("\n1. ������������ �����\n");
	printf("2. ������ �����\n");
	printf("3. ����� �� ���������\n");
	printf("4. ����������\n");
	printf("5. ��������� 1 ���������\n");
	printf("6. �������� ������\n");
	printf("7. ���������� �� ���������\n");
	printf("8. �����\n");

	printf("\n��� �����: ");
	ch = vvod();
	printf("\n");
	}
	return ch;
}


int readf()
{
	if (fopen_s(&f, "struct.dat", "r+b"))
	{
		printf("������ �������� �����");
		return 1;
	}


	char b[10];
	if (fread(b, 1, 1, f) == 0) {
		printf("���� ����!");
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

	printf("\n������� ����� ������ �� ������� ��������: ");

	int zap;

	while (1)
	{
		zap = vvod();
		if (zap <= k) break;
		else printf("����� ������ �� ����������, ���������� ��� ���: ");
	}


	printf("\n������� ��� ������ ��������\n");
	int ch = -1;
	while (ch < 1 || ch > 5)
	{
		printf("1) ��� �������\n");
		printf("2) �����\n");
		printf("3) ������\n");
		printf("4) ��� �����\n");
		printf("5) ����� �������\n");

		printf("\n��� �����: ");
		ch = vvod();
	}

	switch (ch)
	{
		case 1:
			printf("\n������� ����� ��� �������: ");
			gets_s(mas[zap - 1].imya_mastera);
			printf("���������!\n");
			break;

		case 2:
			printf("\n������� ����� �����: ");
			gets_s(mas[zap - 1].marka);
			printf("���������!\n");
			break;

		case 3: 
			printf("\n������� ����� ������: ");
			mas[zap - 1].probeg = vvod();
			printf("���������!\n");
			break;

		case 4:
			printf("\n������� ����� ��� �����: ");
			gets_s(mas[zap - 1].reg_nomer);
			printf("���������!\n");
			break;
		case 5:
			printf("\n������� ����� ����� �������: ");
			mas[zap - 1].summa_remonta = vvod();
			printf("���������!\n");
			break;
	}

	if (fopen_s(&f, "struct.dat", "w"))
	{
		printf("������ �������� �����");
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
	printf(" | ������ | ��� ������� |    �����    |    ������   |  ��� �����  | ����� ������� |\n");
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
			printf("������ �������� �����");
			return;
		}
				}
	else 
		if (fopen_s(&f, "struct.dat", "a"))
		{
			printf("������ �������� �����");
			return;
		}
		else fprintf(f, "\n");
		

	int ch;
	printf("������� ���������� �������: ");
	ch = vvod();

	for (int i = 0; i < ch; i++)
	{
		printf("\n\n������ %d\n������� ��� ������� ", i + 1);
		gets_s(mas[i].imya_mastera);
		fputs(mas[i].imya_mastera, f);
		fprintf(f, "\n");

		printf("������� ����� ");
		gets_s(mas[i].marka);
		fputs(mas[i].marka, f);
		fprintf(f, "\n");

		printf("������� ������ ");
		mas[i].probeg = vvod();
		fprintf(f, "%d\n", mas[i].probeg);

		printf("������� ��� ����� ");
		gets_s(mas[i].reg_nomer);
		fputs(mas[i].reg_nomer, f);
		fprintf(f, "\n");

		printf("������� ����� ������� ");
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

	printf("������� ����� ������ �������: ");
	int zap;

	while (1)
	{
		zap = vvod();
		if (zap <= k) break;
		else printf("����� ������ �� ����������, ���������� ��� ���: ");
	}
	if (fopen_s(&f, "struct.dat", "w"))
	{
		printf("������ �������� �����");
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
		printf("������ �������� �����");
		return;
	}

	int ch = 0;
	while (ch < 1 || ch > 5) {
		printf("\n1. ��� �������\n");
		printf("2. �����\n");
		printf("3. ������\n");
		printf("4. ��������������� �����\n");
		printf("5. ����� �������\n");

		printf("��� �����: ");
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
		printf("������ �������� �����");
		return;
	}

	printf("\n������� �� ������ ��������� �����������: ");
	int ch = 0;
	while (ch < 1 || ch > 5) {
		printf("\n1. ��� �������\n");
		printf("2. �����\n");
		printf("3. ������\n");
		printf("4. ��������������� �����\n");
		printf("5. ����� �������\n");

		printf("��� �����: ");
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