#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> 
#include <windows.h>
using namespace std;
const char * FName = "Videoteka.txt";

HANDLE hConsole, hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

struct films
{
	int   id;           // Номер запису 
	char  film[30];     // Назва фільму
	char  countrys[30]; // Назва країни
	float time;         // Тривалість фільму
	char  genre[30];    // Жанр фільму
	int   date;         // Дата випуску фільма
} *shop;

int  menu(); //Функція меню
void config_console(); //Функція для української мови в консолі 
void film_load(); //Заносить дані в файл
void SetColor(int text, int background); //надає колір в консолі
void GotoXY(int X, int Y); //функція переміщення курсора в консолі

int  number(); //Функція яка запитує в функції film_input() скільки потрібно ввести записів в файл
void film_input(); //Запис даних в файл
void film_print(); //Виводить дані на екран

void film_add_k(); //Додавання запису в кінець файлу
void film_add_p(); //Додавання запису на початок файлу
void film_delete_id(); //Видалення даних з файла
void film_sort_genre(); //Сортуванння за жанрами фільмів
void film_list_country(); //Виводить список фільмів, знятих у певних країнах
void film_list_litera(); //Список фільмів, які задаються з клавіатури і починаються з певної літери
void film_list_1992(); //Виводить список фільмів, знятих до 1992 року

int  main()
{
	config_console();
	film_load();

	bool l = true;
	while (l)
	{
		switch (menu())
		{
		case 1: film_input();
			break;
		case 2: film_print(); 
			break;
		case 3: film_add_k();
			break;
		case 4: film_add_p();
			break;
		case 5: film_delete_id();
			break;
		case 6: film_sort_genre();;
			break;
		case 7: film_list_country();
			break;
		case 8: film_list_litera(); 
			break;
		case 9: film_list_1992();
			break;
		case 10: l = false;
		}
		system("pause");
		system("CLS");
	}

	delete[] shop; //Для звільнення динамічно розміщеного масиву //видаляє виділену пам`яті
}

int  menu()
{
	system("cls"); //очищення екранну 

	int j, i_input, i;
	int y = 0, a = 0, end_p = 9;

	struct punktu { char name[100]; }; //Структура для пунктів
	struct punktu punkt[100]; //Оголошення зміни puk для структури punktu

	SetColor(9, 15);
	printf("                      ВІДЕОТЕКА\n");
	SetColor(0, 15);
	strcpy(punkt[0].name, "\t* Занесення даних в файл.");
	strcpy(punkt[1].name, "\t* Вивести на екран введені дані (про фільми).");
	strcpy(punkt[2].name, "\t* Додає дані про фільм в кінець файла");
	strcpy(punkt[3].name, "\t* Додає дані про фільм на початок файла");
	strcpy(punkt[4].name, "\t* Видаляє всі дані про фільм, номер якого задано користувачем і виводить на екран оновлений вміст.");
	strcpy(punkt[5].name, "\t* Сортує жанри фільмів за алфавітoм.");
	strcpy(punkt[6].name, "\t* Список фільмів, знятих у певних країнах.");
	strcpy(punkt[7].name, "\t* Виводить список фільмів, які задаються з клавіатури і починаються з певної літери");
	strcpy(punkt[8].name, "\t* Список фільмів знятих до 1992 року.");
	strcpy(punkt[9].name, "\t\n");

	SetColor(4, 15); //Колір - червоний
	printf("%s \n", punkt[0].name);
	SetColor(0, 15); //Колір - чорний
	for (i = 1; i<end_p; i++) //Цикл який виводить на екран пункти меню
		printf("%s \n", punkt[i].name);
	SetColor(4, 15); //Колір - червоний

	printf("\n Переміщатися між пунктами меню стрілками вниз-вверх");
	printf("\n Щоб вибрати пункт меню натисніть клавішу - Enter");
	printf("\n Щоб вийти з програми натисніть клавішу - Esc...");

	while (1)
	{
		i_input = _getch(); //Присвоюємо змінній введену клавішу

		switch (i_input) //Перемикач по змінній введеної клавіші
		{
		case 80:  Beep(400, 50); //клавіші "стрілка вниз" відповідає код-80 -----  Beep(500, 100) звукова функція
			a++; //дозволяє рухатися вниз//Збільшення керуючої змінної меню на 1
			SetColor(0, 15); //Колір чорний
			for (i = 0; i<end_p; i++)
			{
				if (i == a) //Якщо параметр циклу збігається з керуючою змінною меню
				{
					SetColor(0, 15); GotoXY(y, (i)); printf("%s", punkt[(i - 1)].name); //Попередній пункт друкуємо чорним кольором
					SetColor(4, 15); GotoXY(y, i + 1); printf("    -->%s", punkt[i].name); //Курсор "-->" переміщається вниз//Активний пункт друкуємо кольором активного пункту 
				}
			}
			break; //Кінець циклу з параметром,вихід з перемикача

		case 72: Beep(400, 50); //клавіші "стрілка в гору" відповідає код- 72
			a--; //дозволяє рухвтися вгору//Зменшення керуючої змінної меню на 1
			SetColor(0, 15);
			for (i = 0; i<end_p; i++)
			{
				if (i == a)
				{
					SetColor(0, 15); GotoXY(y, i + 2); printf("%s", punkt[i + 1].name);
					SetColor(4, 15); GotoXY(y, i + 1); printf("    -->%s", punkt[i].name); //Курсор "-->" переміщається в гору
				}
			}
			break;

		case 13: SetColor(0, 15); Beep(300, 300); Beep(400, 750); goto sw;;//Переходимо на мітку sw,яка поверне значення керуючої змінної в основну програму

		case 27: Beep(400, 1000 / 2); Beep(375, 1000 / 2); Beep(350, 1000 / 2); Beep(325, 1000); exit(0); // клавіші "Esc" відповідає код- 27 --- відбувається вихід з програми 
		}
	}
	sw:system("cls"); //Очищення екрану
	return a + 1; //Повертаємо значення керуючої змінної +1
}
void config_console()
{
	SetConsoleCP(1251); //встановлює кодову сторінку введення
	SetConsoleOutputCP(1251); //встановлює кодову сторінку виведення даних
}
long file_element() //підраховує кількість записів (структур) в файлі
{
	FILE  *fp;
	if ((fp = fopen(FName, "ab")) == NULL) //створення файла
		printf("Помилка при відкритті файлу.\n");


	fseek(fp, 0, SEEK_END); // fseek() встановлює покажчик поточної позиції в файлі.// SEEK_END пошук з кінця файла
	long i = ftell(fp) / sizeof(struct films); //ftell визначає поточну позицію в потоці даних // long цілий тип
	fclose(fp);
	return i;
}
void film_load() //Заносить дані в файл
{
	delete[] shop; //видаленння динамічного масиву
	FILE  *fp;
	if ((fp = fopen(FName, "rb")) == NULL) {
		printf("Помилка при відкритті файлу.\n");
	}
	shop = new films[file_element()]; //стоворення динамічного масиву
	for (int i = 0; i<file_element(); i++)
	{
		if (fread(&shop[i], sizeof(struct films), 1, fp) != 1) {
			if (feof(fp)) break;
			printf("Помилка зчитування файлу.\n");
		}
	}
	fclose(fp);
}
void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text)); // задаємо атрибути для шрифту консолі, щоб надати колір.
}
void GotoXY(int X, int Y)
{
	COORD coord = { X, Y }; SetConsoleCursorPosition(hStdOut, coord); // COORD задав координати X і Y.
	                                                                  // SetConsoleCursorPosition установлює позицію курсора в консолі
																	  // hStdOut дескриптор вывода
}

int  number()
{
	int k;
	SetColor(9, 15);
	printf("+--------------------------------------------------------------------+\n");
	SetColor(4, 15);
	printf("|                                  WARNING                           |\n");
	SetColor(0, 15);
	SetColor(9, 15);
	printf("| Функцію 'Занесення даних в файл.' бажано використовувати           |\n| тільки один раз, якщо повторно вибрати її введені дані знищуються. |\n| Щоб додати запис виберіть пункт 'Додати фільм в кінець списку.'    | \n");
	printf("+--------------------------------------------------------------------+\n\n\n");
	SetColor(0, 15);

	printf("\t\t+--------------------------------------+\n");
	printf("\t\t|         Запис даних в файл           |\n");
	printf("\t\t+--------------------------------------+\n\n");

	printf("+------------------------------------------+\n");
	printf("|Cкільки записів, потрібно занести в файл?:|\n");
	printf("+------------------------------------------+\n");
	printf("--> "); scanf("%d", &k);
	return k;
}
void film_input()
{
	int n = 1;
	films video;

	FILE  *fp;
	if ((fp = fopen(FName, "wb")) == NULL) // створення нового файла і запис в файл
		printf("Помилка при відкритті файлу.\n");
	
	int num = number(); //виклик функції number()
	for (int i = 0; i < num; i++) //цикл від 0 до num()
	{
		printf("\nІдентифікаційний номер: ");
		scanf("%d", &video.id);

		printf("Назва фільму: ");
		fflush(stdin);    //stdin Стандартне введення 
					      //fflush() в файл буде примусово фізично записано вміст вихідного буфера 
					      //перед вводом очистить буфер від попередніх символів.
		gets(video.film); //Читає рядок з клавіатури

		printf("Країна: ");
		scanf("%s", video.countrys);
		
		SetColor(4, 15);
		printf("Правильне введеня часу, наприклад - 1.20 !!\n");
		SetColor(0, 15);
		printf("Час: ");
		scanf("%f", &video.time);
		
		printf("Жанр: ");
		scanf("%s", video.genre);

		printf("Рік випуску: ");
		scanf("%d", &video.date);

		if (fwrite(&video, sizeof(struct films), 1, fp) != 1)// записує дані в файл
		{
			printf("Помилка при записі у файл.\n");
		}
		else
		{
			SetColor(4, 15);
			printf("\n+----------------------+\n");
			printf("| Дані занесені в файл |\n");
			printf("+----------------------+\n\n");
			SetColor(0, 15);
			
		}
	  }

	fclose(fp);
	film_load();
}
void film_print()
{
	int count = file_element(); //підраховує кількість структур в файлі
	if (count != 0)
	{
		SetColor(9, 15);
		printf("\n\t+----------------------------------------------------------------------------+\n");
		printf("\t|	                       Список фільмів                                |\n");
		printf("\t+----+-----------------------+--------------+---------+--------------+-------+\n"); 
		printf("\t| Ід |   Назва фільму        |    Країна    |   Час   |     Жанр     |  Рік  |\n");
		printf("\t+----+-----------------------+--------------+---------+--------------+-------+\n");
		SetColor(0, 15);
		for (int i = 0; i<count; i++) //цикл виводу даних
		{
			printf("\t| %-2d",      shop[i].id); 
			printf(" |%-21s",	  shop[i].film);
			printf("  |%-12s",    shop[i].countrys);
			printf("  |%-7.2f",   shop[i].time);
			printf("  |%-12s",    shop[i].genre);
			printf("  |%-5d  |\n", shop[i].date);
		}
		printf("\t+----+-----------------------+--------------+---------+--------------+-------+\n\n"); 
	}
	else printf("\n\n\tФАЙЛ ПОРОЖНІЙ!!!\n\n");
}

void film_add_k()
{
	int n = 1;
	
	FILE  *fp;
	if ((fp = fopen(FName, "ab")) == NULL) //ab - відкриває і додає дані в кінець файла
		printf("Помилка при відкритті файлу.\n");
	
	film_print();
	printf("+------------------------------------------+\n");
	printf("|     Додавання запису,в кінець файла      |\n");
	printf("+------------------------------------------+\n");
	
	films video;

	while (n != 0)
	{
		printf("Ідентифікаційний номер: ");
		scanf("%d", &video.id);

		printf("Назва фільму: ");
		fflush(stdin);
		gets(video.film);

		printf("Країна: ");
		scanf("%s", &video.countrys);

		SetColor(4, 15);
		printf("Правильне введеня часу, наприклад - 1.20 !!\n");
		SetColor(0, 15);
		printf("Час: ");
		scanf("%f", &video.time);

		printf("Жанр: ");
		scanf("%s", video.genre);

		printf("Рік випуску: ");
		scanf("%d", &video.date);

		if (fwrite(&video, sizeof(struct films), 1, fp) != 1) // занесення даних в файл
			printf("Помилка при записі у файл.\n");

		do {
			SetColor(4, 15);
			printf("\nВведіть 0 щоб зупинити, 1 продовжити: ");
			SetColor(0, 15);
			scanf("%d", &n);
		} while (!(n == 0 || n == 1)); //умова для продовження або закінчення вводу даних
	}

	fclose(fp);
	film_load();
	printf("\n\t+-----------------------+\n");
	printf("\t| Оновлений вміст файла |\n");
	printf("\t+-----------------------+\n");
	film_print();
}
void film_add_p()
{
	int n = 1;

	FILE  *fp;
	if ((fp = fopen(FName, "rb+")) == NULL) //ab - відкриває і додає дані в кінець файла
		printf("Помилка при відкритті файлу.\n");

	film_print();
	printf("+------------------------------------------+\n");
	printf("|     Додавання запису,на початок файла    |\n");
	printf("+------------------------------------------+\n");

	films video;

	while (n != 0)
	{
		printf("Ідентифікаційний номер: ");
		scanf("%d", &video.id);

		printf("Назва фільму: ");
		fflush(stdin);
		gets(video.film);

		printf("Країна: ");
		scanf("%s", &video.countrys);

		SetColor(4, 15);
		printf("Правильне введеня часу, наприклад - 1.20 !!\n");
		SetColor(0, 15);
		printf("Час: ");
		scanf("%f", &video.time);

		printf("Жанр: ");
		scanf("%s", video.genre);

		printf("Рік випуску: ");
		scanf("%d", &video.date);

		if (fwrite(&video, sizeof(struct films), 1, fp) != 1) // занесення даних в файл
			printf("Помилка при записі у файл.\n");

		do {
			SetColor(4, 15);
			printf("\nВведіть 0 щоб зупинити, 1 продовжити: ");
			SetColor(0, 15);
			scanf("%d", &n);
		} while (!(n == 0 || n == 1));  //умова для продовження або закінчення вводу даних
	}

	fclose(fp);
	film_load();
	printf("\n\t+-----------------------+\n");
	printf("\t| Оновлений вміст файла |\n");
	printf("\t+-----------------------+\n");
	film_print();
}
void film_delete_id()
{
	FILE *f;
	FILE *p;
	films vudal;
	int k = 0;
	int s, n=1;
	
	printf("\n\t+-----------------------------------------------+\n");
	printf("\t|Введіть номер запису який потрібно видалити: "); scanf("%d", &s);
	printf("\t+-----------------------------------------------+\n");
	f = fopen(FName, "rb");
	p = fopen("baza1.txt", "wb");
	if (s != 0)
	{
		printf("\n\t+------------------------+\n");
		  printf("\t| Запис номер %d видалено |\n",s);
		  printf("\t+------------------------+\n\n");
	}
											   //Функція fread () читає з потоку, що адресується покажчиком f , 1 об'єктів довжиною sizeof(films) байт і розміщує їх в масиві &video.
	while (fread(&vudal, sizeof(films), 1, f)) //зчитує інформацію з файла головного файла	                                       
	if (s != vudal.id)												
	{                                        //Функція fwrite () записує в поток, що адресується покажчиком f , 1 об'єктів довжиною sizeof(films) байт і розміщує їх в масиві &video.
		fwrite(&vudal, sizeof(films), 1, p); // дані які виконуються під умову записуються в тимчасовий файл - p
	} 
	fclose(f);
	fclose(p);

	f = fopen(FName, "wb");
	p = fopen("baza1.txt", "rb+");
	while (fread(&vudal, sizeof(films), 1, p)) //зчитування даних з тимчасового файла - p
	{
		fwrite(&vudal, sizeof(films), 1, f); //запис даних з файла - p в головний файл 
	}
	
	fclose(f);
	fclose(p);
	
	film_load();
	film_print();
	printf("\t+-----------------------+\n");
	printf("\t| Оновлений вміст файла |\n");
	printf("\t+-----------------------+\n");

	if (-1 == remove("baza1.txt")) //Видалення файла для зменшення пам'яті
			printf("Помилка видалення baza1.txt\n");
}
void film_sort_genre()
{
	/*Сортування відбувається бульбашковим методом*/
	int s = file_element(); //підраховує кількість записів
	films sor;
	for (int i = s - 1; i >= 0; i--)
		for (int j = 0; j < i; j++)
			if (shop[j].genre[0] > shop[j + 1].genre[0])
			{
				sor = shop[j];
				shop[j] = shop[j + 1];
				shop[j + 1] = sor;
			}
	printf("\n\t+----------------------------------------+\n");
	printf("\t| Посортувано жанри фільмів за алфавітом |\n");
	printf("\t+----------------------------------------+\n");
	film_print();
}
void film_list_country()
{
	int count = file_element(), exist = 0; //підраховує кількість записів в файлі
	char country[10];

	printf("+------------------------------------------+\n");
	printf("|  Список фільмів, знятих у певних країнах |\n");
	printf("+------------------------------------------+\n");
	printf("\nВведіть назву країни: "); scanf("%s", country);

	for (int i = 0; i < count; i++)
		if (!strcmp(country, shop[i].countrys)) exist++; //strcmp порівнює дві строки і повертає результат залежний від результату порівняння 

	if (exist == 0) {
		printf("Інформацію не знайдено!\n");
		return;
	}
	SetColor(9, 15);
	printf(" \n\tСписок фільмів, введеної країни;\n");
	SetColor(0, 15);
	printf("\n\t+-----------------------+\n");
	printf("\t|        Фільми         |\n");
	printf("\t+-----------------------+\n");
	for (int i = 0; i < count; i++)
	{
		if (!strcmp(country, shop[i].countrys)) { printf(" \t| %-21s |\n", shop[i].film); }
	}
	printf("\t+-----------------------+\n");
}
void film_list_litera()
{
	int count = file_element(), exist = 0;
	char lit[30];
	
	printf("+----------------------------------------------------+\n");
	printf("|  Список фільмів, які починаються на введену літеру |\n");
	printf("+----------------------------------------------------+\n");
	
	printf("\nВведіть довільну літеру: "); scanf("%s", lit);
	
	for (int i = 0; i < count; i++)
		if (strncmp(lit, shop[i].film,strlen(lit))==0) exist++; //strncmp - порівнює в лексикографічному порядку не більше декількох символів 
	                                                            //з двох рядків,  і повертає ціле значення, залежне від результату порівняння
	
	if (exist == 0) 
	{
		printf("\n\t+------------------------+\n");
		printf("\t| Інформацію не знайдено!|\n");
		printf("\t+------------------------+\n\n");
		return;
	}

	printf("\n\t+-----------------------+\n");
	printf("\t|        Фільми         |\n");
	printf("\t+-----------------------+\n");
	for (int i = 0; i < count; i++)
	{
	if (strncmp(lit, shop[i].film, strlen(lit))==0 ) { printf("\t| %-21s |\n", shop[i].film); }
	}
	printf("\t+-----------------------+\n");
}
void film_list_1992()
{
	int count = file_element();
	if (count != 0)
	{
		int exist = 0;
		SetColor(9, 15);
		printf("\t+--------------------------------------------+\n");
		printf("\t|  Список фільмів, знятих до 1992 року       |\n");
		printf("\t+--------------------------------------------+\n");
		SetColor(0, 15);
		for (int i = 0; i < count; i++)
			if (shop[i].date <= 1992) exist++; //знаходження інформації

		if (exist == 0)
		{
			printf("\n\t+------------------------+\n");
			printf("\t|Інформацію не знайдено! |\n"); //умова якщо інофрмації немає
			printf("\t+------------------------+\n\n");
			return;
		}
		
		printf("\t+----------------------+\n");
		printf("\t|        Фільм         |\n");
		printf("\t+----------------------+\n");
		for (int i = 0; i<count; i++)
			if (shop[i].date <= 1992)
			{
				printf("\t|%22s|\n", shop[i].film);
			}
		printf("\t+----------------------+\n\n");
	}
	else
	{
		printf("Файл порожній!!!\n");
	}
}