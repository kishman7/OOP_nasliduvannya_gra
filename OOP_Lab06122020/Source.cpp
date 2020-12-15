#include <iostream>
#include <string>
#include <windows.h>
#include <cmath>
#include <ctime> // Бібліотека для rand (генератора випадкових чисел)
#include <wingdi.h>

using namespace std;

class Unit
{
public:
	int hp; // життя
	int dmg; // пошкодження при атаці
	int dodge; // шанс ухилятись у %
	string name; // ім’я учасника
	string teams = "";
public:

	Unit(string tem)
	{
		this->teams = tem;
	}
	Unit() {};
	void attack() {
		cout << "Атакує!" << endl;
	}
	void dodge_attacks() {
		cout << "Ухилятися від атак!" << endl;
	}
	void death() {
		cout << "Вмирати!" << endl;
	}
	
	string ShowUnit() {
		return this->name;
		/*<< "\nЖиття: " << this->hp << "\nПошкодження при атаці: " << this->dmg << "\nШанс ухилитись: " << this->dodge << "%"*/
	}
	void ShowGamer() {
		if (this->hp <= 0)
			cout << this->name << " Dead\n";
		else
		cout<< this->name<< "\tЖиття: " << this->hp << endl;
	}
};

class Swordsman : public Unit {
public:
	Swordsman(string tem):Unit(tem)
	{
		this->hp = 15;
		this->dmg = 5;
		this->dodge = 60;
		this->name = "Мечник";
	}
};

class Archer : public Unit {
public:
	Archer(string tem) :Unit(tem)
	{
		this->hp = 12;
		this->dmg = 4;
		this->dodge = 40;
		this->name = "Лучник";
	}
	
};

class Mage : public Unit {
public:
	Mage(string tem) :Unit(tem)
	{
		this->hp = 8;
		this->dmg = 10;
		this->dodge = 30;
		this->name = "Маг";
	}
	
};

void Teams(Unit* green_team, int n, string);  // прототип функції по створенню команд
void Draka(Unit& green_team, Unit& red_team);  // прототип функції по веденню бою

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(unsigned(time(NULL)));

	
	const int n = 3; // кількість гравців в команді
	int gamer; // учасник гри
	
	Unit *green_team = new Unit[n]; // команда зелених
	Unit *red_team = new Unit[n]; // команда червоних

	Teams(green_team, n, "Green");

	cout << "\nКоманда зелених." << endl;

	for (int i = 0; i < n; i++) // потрібно зробити у вмгляді функції
	{
		green_team[i].ShowGamer();
	}

	Teams(red_team, n, "Red");
	
	cout << "\nКоманда червоних." << endl;
	for (int i = 0; i < n; i++)
	{
		red_team[i].ShowGamer();
	}
	//cout << red_team[0].hp << endl;

	char space = 'y';
	//int start; 
	//cout << "Натисніть 1 для початку бою ->";
	//cin >> start;
	int green_gamer;
	int red_gamer;
	int block; // ймовірність захисту від атаки
	int Count_dead_green = 0; // кількість смертей зелених
	int Count_dead_red = 0; // кількість смертей червоних
	bool enter = true;
	while (enter)
	{
		cout << "\nНатисніть \"y\" для початку бою ->";
		cin >> space;
		if (space == 'y')
		{
			char team;
			cout << "\nХто перший буде атакувати (g - зелені, r - червоні): ";
			cin >> team;
			if (team == 'g')
			{
				cout << "\nАтакує команда зелених!" << endl;
				green_gamer = rand() % 3 ;

					cout << "Оберіть, якого гравця команди червоних Ви хочете атакувати (1 - перший, 2 - другий, 3 - третій) ->";
					int i = 0;
					cin >> i;
					if (i>=1 && i<=3)
					{
						Draka(green_team[green_gamer], red_team[i - 1]);

						for (int i1 = 0; i1 < n; i1++)
						{
							red_team[i1].ShowGamer();
						}
						if (red_team[i - 1].hp <= 0)
						{
							Count_dead_red++;
							if (Count_dead_red == 3)
							{
								cout << "Перемогла команда " << green_team->teams << endl;
							}
						}
					}
					else
					{
						cout << "Ви обрали не вірний номер гравця!!! \n\nПовторіть свій вибір." << endl;
					}
			}
			else if (team == 'r')
			{
				cout << "\nАтакує команда червоних!" << endl;
				red_gamer = rand() % 3;
				
				cout << "Оберіть, якого гравця команди зелених Ви хочете атакувати (1 - перший, 2 - другий, 3 - третій) ->";
				int i = 0;
				cin >> i;
				if (i >= 1 && i <= 3)
				{
					Draka(red_team[red_gamer], green_team[i - 1]);

					for (int i = 0; i < n; i++)
					{
						green_team[i].ShowGamer();
					}
					if (green_team[i - 1].hp <= 0)
					{
						Count_dead_green++;
						if (Count_dead_green == 3)
						{
							cout << "Перемогла команда " << red_team->teams << endl;
						}
					}
				}
				else
				{
					cout << "Ви обрали не вірний номер гравця!!! \n\nПовторіть свій вибір." << endl;
				}
			}
		}
		if (Count_dead_red == 3 || Count_dead_green == 3)
		{
			cout << "\n===== Гру завершено =====" << endl;
			break;
		}
	}
	delete[] green_team;
	delete[] red_team;
	return 0;
}

void Draka(Unit& green_team, Unit & red_team)  // функція по веденню бою
{
	cout << green_team.ShowUnit() << " команди "<< green_team.teams <<" атакує " << red_team.ShowUnit() << " команди " << red_team.teams << endl;
	cout << green_team.ShowUnit() << " команди "<< green_team.teams << " наносить удар!" << endl;
	int block = rand() % 10 + 1;
	if (block >= 1 && block <= 6)
	{
		cout << red_team.ShowUnit() << " команди " << red_team.teams << " ухилився від атаки!" << endl;
	}
	else if (block >= 7 && block <= 10)
	{
		red_team.hp -= green_team.dmg;
		if (red_team.hp <= 0)
		{
			red_team.death();
		}
		else

			cout << red_team.ShowUnit() << " команди " << red_team.teams << " отримав пошкодження і його життя зменшилось на " << green_team.dmg << endl;
	}
}

void Teams(Unit* green_team, int n, string teams) { // функція по створенню команд
	if (n==0)
	{
		return;
	}
		int gamer = rand() % 3 + 1;
		if (gamer == 1)
		{
			green_team[n-1] = *(new Swordsman(teams));
		}
		else if (gamer == 2)
		{
			green_team[n-1] = *(new Archer(teams));
		}
		else if (gamer == 3)
		{
			green_team[n-1] = *(new Mage(teams));
		}
		Teams(green_team, n - 1, teams);
}