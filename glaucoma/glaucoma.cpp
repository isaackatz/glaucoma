// glaucoma.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <clocale>
using namespace std;

vector<double> input(int a, const char* b)
{
	cout << b << endl;
	vector<double> output;
	double c = 0;
	for (int i = 0; i < a; i++)
	{
		cout << "[" << i << "]: ";
		cin >> c;
		output.push_back(c);
	}

	cout << endl;

	return output;
}

vector<double> sdvig(vector<double> t, vector<double>tau, int stad)
{
	vector<double> T;

	for (int i = stad; i < 5; i++)
	{
		double sum = 0;
		for (int j = stad; j < i; j++)
		{
			sum += t[j];
		}
		T.push_back(tau[i] + sum);

	}

	return T;
}

double ist_vozr(vector<double> dolya, vector<double>T, double tc, int stad)
{
	double ist_vozr = tc;
	double sum = 0;
	for (int i = stad; i < 5; i++)
	{
		ist_vozr -= T[i] * dolya[i];
	}

	return ist_vozr;
}


double find_svns(float i_vozr, vector<double> t, vector<double> tau)
{
	double svns = 0;
	
	cout << "Введите номер стадии, на которой найден пациент: ";
	
	int n; //номер стадии
	
	cin >> n;

	double tproh = 0; //время прохода

	for (int i = 0; i < n; i++)
	{
		tproh += t[i];
	}

	double tn = i_vozr + tproh + tau[n - 1]; //время наступления стадии без лечения


	return svns;
}


int main()
{
	setlocale(0, "");

	bool start = true;

	ofstream fout;

	vector<double> dolya1 = { 0 };
	vector<double> dolya = { 0 }; //массив долей стадий
	vector<double> t = { 0 }; //массив времени прохождения стадии
	vector<double> tau = { 0 }; //массив времени пребывания на стадии
	vector<double> T1 = { 0 }, T0 = { 0 }; //временные сдвиги
	double i_vozr0, i_vozr1; //истинные возраста стадий

	while (start) {
		cout << "Введите средний возраст заболеваемости глаукомой по России: ";
		double tc; //Средний возраст 
		cin >> tc;

		dolya = input(5, "Введите доли для стадий (включая нулевую): ");

		for (int i = 1; i < 5; i++)
		{
			dolya1.push_back(dolya[i] / (1 - dolya[0]));
		}
		cout << endl;

		t = input(4, "Время прохождения стадий без лечения: ");
		tau = input(4, "Время, прошедшее от начала i-й стадии до обнаружения (от 0 до 3-й): ");
		tau.insert(tau.end(), 0);

		T1 = sdvig(t, tau, 1);
		T1.insert(T1.begin(), 0);
		T0 = sdvig(t, tau, 0);

		i_vozr0 = ist_vozr(dolya, T0, tc, 0); //определение истинного возраста нулевой стадии
		i_vozr1 = ist_vozr(dolya1, T1, tc, 1); //определение истинного возраста первой стадии

		cout << "Истинный возраст заболевания нулевой стадией: " << i_vozr0 << endl;
		cout << "Истинный возраст заболевания первой стадией: " << i_vozr1 << endl;
		cout << i_vozr1 - i_vozr0 << endl; //покажет время перехода на следующую стадию

		cout << "Хотите продолжить? Да - 1, Нет - 0: ";

		bool choice;
		cin >> choice;

		if(!choice)
		{
			start = false;
		}

		cout << endl << "---" << endl;

	}

	fout.open("result.txt");

	fout << i_vozr0 << endl;
	fout << i_vozr1 << endl;

	for (double elem : t)
	{
		fout << elem << " ";
	}

	fout.close();

	return 0;
}
