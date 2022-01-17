#include"Header.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	
	Card crt;int v = 1;
	typedef void(Card::* PA)();
	vector<PA> fu = { &Card::AddMoney, &Card::AddExpense, &Card::GenExpense,
	&Card::SpendDay,&Card::SpendWeek,&Card::SpendMonth ,
		&Card::Spend3Week,&Card::Spend3Month,
		&Card::CategWeek,&Card::CategMonth };

	while (v) {
		crt.Show();
		cout << "\n 1 -> add money to card \n 2 -> enter new expense"
			<< "\n 3 -> Generate \n 4 -> spend day "
			<< "\n 5 -> spend week\n 6 -> spend month"
			<< "\n 7 -> top 3 spend week \n 8 ->  top 3 spend month"
			<< "\n 9 -> top 3 category week\n 10 -> top 3 category month"
			<< "\n 0 -> exit \n\n Your choise: ";
		cin >> v;

		if (v >= 1 && v <= 10) {
			(crt.*fu[v - 1])();
			system("pause");
		}

		system("cls");
		continue;
	}

	return 0;
}