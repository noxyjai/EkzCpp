#pragma once
#include<iostream>
#include<Windows.h>
#include<string>
#include<fstream>
#include<iomanip>
#include<cstdlib> 
#include<vector>
#include<functional>
#include<iterator>
#include<algorithm>
#include <random>
#include<sstream>
using namespace std;

vector<string> categ{"Health","Technol.","Beauty", "Food  ", "Other "};
vector<string> fls{ "expenses","top3k","top3z"};

class Zatrata
{
	string ctg; int d = 0, m = 0, pr = 0;
public:
	Zatrata() {
		
	}
	void AddCateg(string s) {
		ctg = s;
	}
	string GetCateg() {
		return ctg;
	}
	int GetDay() {
		return d;
	}
	int GetMonth() {
		return m;
	}
	int GetPrice() {
		return pr;
	}
	void Gen() {
		d = 1 + rand() % 9; m = 1 + rand() % 3;
		pr = rand() % 100;
		ctg = categ[1 + rand() % 4];
	}
	~Zatrata() {

	}
	friend istream& operator>>(istream& os, Zatrata& c);
	friend ostream& operator<<(ostream& os, Zatrata& c);
};
istream& operator>>(istream& os, Zatrata& c) {
	cout << "\n Enter price: ";
	os >> c.pr;
	cout << "\n Enter month: ";
	os >> c.m;
	cout << "\n Enter day: ";
	os >> c.d;
	
	return os;
}

ostream& operator<<(ostream& os, Zatrata& c) {
	os << setw(8) << setfill(' ') << c.pr
		<< setw(6) << setfill(' ') << c.m
		<< setw(6) << setfill(' ') << c.d << endl;
	return os;
}


class Card
{
	string typ;
	int bal = 200;
	vector<Zatrata> z, bf;
	int ch1 = 0, ch2 = 0;
public:
	Card(){
		cout << " Enter type of card (debit or credit):";
		cin >> typ;
	}
	void HeadTable() {
		cout << setiosflags(ios::left);
		cout << setw(11) << setfill(' ') << "Category"
			<< setw(8) << setfill(' ') << " price"
			<< setw(6) << setfill(' ') << " month"
			<< setw(6) << setfill(' ') << " day" << endl;
	}
	
	void frWeek() {
		cout << " Enter month: ";
		cin >> ch2;
		cout << " Enter day: ";
		cin >> ch1;
		for (size_t i = 0; i < z.size(); i++)
		{
			if (z[i].GetMonth() == ch2) {
				if (z[i].GetDay() >= ch1 && z[i].GetDay() <= ch1 + 7)
					bf.push_back(z[i]);
			}
		}
		sort(bf.begin(), bf.end(), [](Zatrata& a, Zatrata& b) {
			return a.GetPrice() > b.GetPrice(); });
	}
	void frMonth() {
		cout << " Enter month: ";
		cin >> ch2;
		for (size_t i = 0; i < z.size(); i++)
		{
			if (z[i].GetMonth() == ch2)
				bf.push_back(z[i]);
		}
		sort(bf.begin(), bf.end(), [](Zatrata& a, Zatrata& b) {
			return a.GetPrice() > b.GetPrice(); });
	}
	void SpendDay() {
		cout << " Enter month: ";
		cin >> ch2;
		cout << " Enter day: ";
		cin >> ch1;
		
		for (size_t i = 0; i < z.size(); i++)
		{
			if (z[i].GetDay() == ch1 && z[i].GetMonth() == ch2)
				bf.push_back(z[i]);
		}
		FileAdd(1, "expenses of day", bf.size());
	}
	void SpendWeek() {
		frWeek();
		FileAdd(1, "expenses of week", bf.size());
	}
	void SpendMonth() {
		frMonth();
		FileAdd(1, "expenses of month", bf.size());
	}
	void Spend3Week() {
		frWeek();
		FileAdd(2, "top 3 expenses of week", 3);
	}
	void Spend3Month() {
		frMonth();
		FileAdd(2, "top 3 expenses of month", 3);
	}
	void CategWeek() {
		frWeek();
		FileAdd(3, "top 3 category of week", 3);
	}
	void CategMonth() {
		frMonth();
		FileAdd(3, "top 3 category of week", 3);
	}
	void PrintCategory() {
		for (size_t i = 0; i < categ.size(); i++)
			cout << i + 1 << " -> " << categ[i] << endl;
	}
	void AddExpense() {
		PrintCategory();
		cout << " Your choise: ";
		cin >> ch1;
		z.resize(z.size() + 1);
		z[z.size() - 1].AddCateg(categ[ch1-1]);
		cin >> z[z.size() - 1];
		bal -= z[z.size() - 1].GetPrice();
		CheckBalance();
	}
	void Show() {
		cout << setiosflags(ios::left);
		HeadTable();
		for (size_t i = 0; i < z.size(); i++)
		{
			cout << setw(13) << setfill(' ') << z[i].GetCateg() << z[i];
		}
		cout << "\n\n Balance -> " << bal << "\n\n";
	}
	void GenExpense() {
		cout << " Enter count: ";
		cin >> ch1;
		for (size_t i = 0; i < ch1; i++)
		{
			z.resize(z.size() + 1);
			z[z.size() - 1].Gen();
			bal -= z[z.size() - 1].GetPrice();
			CheckBalance();
		}
	}
	void AddMoney() {
		cout << " Enter count of money to add: ";
		cin >> ch1;
		bal += ch1;
	}
	void CheckBalance() {
		if (typ == "debit" && bal < 0) {
				bal += z[z.size() - 1].GetPrice();
				z.pop_back();
				cout << "\n error balance \n";
		}
	}
	void FileAdd(int ind, string s, size_t sz) {
		ofstream fin(fls[ind - 1] + ".txt", ios::app);
		cout << s <<endl; 
		fin << s << endl;
		for (size_t i = 0; i < sz; i++)
		{
			cout << setw(13) << setfill(' ') << bf[i].GetCateg() << bf[i];
			fin << setw(13) << setfill(' ') << bf[i].GetCateg() << bf[i];
		}
		fin.close();
		bf.clear();
	}
	~Card() { }
};