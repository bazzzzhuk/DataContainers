#include<iostream>
using namespace std;

#define DELIMITER cout << "===============================================\n";
#define HW

void elevator(int floor);
unsigned long long int factorial(int n);
unsigned long long int power(int a, int n);
unsigned long long int fibona44i(int n);
unsigned long long int fibona44i_inside(int  n, unsigned long long int  f_prev_2, unsigned long long int f_prev_1);


void main()
{
	setlocale(LC_ALL, "");
	int a, n;
#ifdef HW
	DELIMITER
	cout << "Enter factorial of number: "; cin >> n;
	cout << "Rezult: " << factorial(n) << endl;
	DELIMITER
	cout << "Введите основание: "; cin >> a;
	cout << "Введите показатель степени: "; cin >> n;
	cout << "Rezult: " << power(a, n) << endl;
	DELIMITER
	cout << "Введите количество чисел в ряде Фибоначии: "; cin >> n;
	cout << n << "-ое число в последовательности Фибоначчи: " << fibona44i(n) << endl;
	DELIMITER
#endif // HW
	cout << "Enter level: "; cin >> n;
	elevator(n);
	DELIMITER
}

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	elevator(floor - 1);
	cout << "Вы на " << floor << " этаже" << endl;
}
//>>----->
unsigned long long int factorial(int n)
{
	if (n == 0) return 1;//доходим до дна, до стартовой единицы
	return n * factorial(n - 1);
}
//>>----->
unsigned long long int power(int a, int n)
{
	if (n == 1)return a;
	return a * power(a, n - 1);//"а" оставляем как основание и циклом со дна собираем перемножая
}
//>>----->
unsigned long long int fibona44i_inside(int n, unsigned long long int f_prev_2, unsigned long long int f_prev_1)
{//не нашёл решения впихнуть всё в одну функцию, но и так красиво
	if (n == 0)return f_prev_2;//Возвращаем ноль - считать нечего
	if (n == 1)return f_prev_1;//Возвращаем единицу не считая или в Debugger'e: (fibona44i_inside will return {возвращаемое число} unsigned __int64)
	return fibona44i_inside(n - 1, f_prev_1, f_prev_1 + f_prev_2);//переворачиваем
}
unsigned long long int fibona44i(int n)
{
	return fibona44i_inside(n, 0, 1);//начальная инициализация
}
