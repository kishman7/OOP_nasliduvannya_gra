#include <iostream>
#include <string>
#include <windows.h>
#include <cmath>
#include <ctime> // ��������� ��� rand (���������� ���������� �����)
#include <wingdi.h>

using namespace std;

class Unit
{
public:
	int hp; // �����
	int dmg; // ����������� ��� �����
	int dodge; // ���� ��������� � %
	string name; // ��� ��������
	string teams = "";
public:

	Unit(string tem)
	{
		this->teams = tem;
	}
	Unit() {};
	void attack() {
		cout << "�����!" << endl;
	}
	void dodge_attacks() {
		cout << "��������� �� ����!" << endl;
	}
	void death() {
		cout << "�������!" << endl;
	}
	
	string ShowUnit() {
		return this->name;
		/*<< "\n�����: " << this->hp << "\n����������� ��� �����: " << this->dmg << "\n���� ���������: " << this->dodge << "%"*/
	}
	void ShowGamer() {
		if (this->hp <= 0)
			cout << this->name << " Dead\n";
		else
		cout<< this->name<< "\t�����: " << this->hp << endl;
	}
};

class Swordsman : public Unit {
public:
	Swordsman(string tem):Unit(tem)
	{
		this->hp = 15;
		this->dmg = 5;
		this->dodge = 60;
		this->name = "������";
	}
};

class Archer : public Unit {
public:
	Archer(string tem) :Unit(tem)
	{
		this->hp = 12;
		this->dmg = 4;
		this->dodge = 40;
		this->name = "������";
	}
	
};

class Mage : public Unit {
public:
	Mage(string tem) :Unit(tem)
	{
		this->hp = 8;
		this->dmg = 10;
		this->dodge = 30;
		this->name = "���";
	}
	
};

void Teams(Unit* green_team, int n, string);  // �������� ������� �� ��������� ������
void Draka(Unit& green_team, Unit& red_team);  // �������� ������� �� ������� ���

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(unsigned(time(NULL)));

	
	const int n = 3; // ������� ������� � ������
	int gamer; // ������� ���
	
	Unit *green_team = new Unit[n]; // ������� �������
	Unit *red_team = new Unit[n]; // ������� ��������

	Teams(green_team, n, "Green");

	cout << "\n������� �������." << endl;

	for (int i = 0; i < n; i++) // ������� ������� � ������ �������
	{
		green_team[i].ShowGamer();
	}

	Teams(red_team, n, "Red");
	
	cout << "\n������� ��������." << endl;
	for (int i = 0; i < n; i++)
	{
		red_team[i].ShowGamer();
	}
	//cout << red_team[0].hp << endl;

	char space = 'y';
	//int start; 
	//cout << "�������� 1 ��� ������� ��� ->";
	//cin >> start;
	int green_gamer;
	int red_gamer;
	int block; // ��������� ������� �� �����
	int Count_dead_green = 0; // ������� ������� �������
	int Count_dead_red = 0; // ������� ������� ��������
	bool enter = true;
	while (enter)
	{
		cout << "\n�������� \"y\" ��� ������� ��� ->";
		cin >> space;
		if (space == 'y')
		{
			char team;
			cout << "\n��� ������ ���� ��������� (g - �����, r - ������): ";
			cin >> team;
			if (team == 'g')
			{
				cout << "\n����� ������� �������!" << endl;
				green_gamer = rand() % 3 ;

					cout << "������, ����� ������ ������� �������� �� ������ ��������� (1 - ������, 2 - ������, 3 - �����) ->";
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
								cout << "��������� ������� " << green_team->teams << endl;
							}
						}
					}
					else
					{
						cout << "�� ������ �� ����� ����� ������!!! \n\n�������� ��� ����." << endl;
					}
			}
			else if (team == 'r')
			{
				cout << "\n����� ������� ��������!" << endl;
				red_gamer = rand() % 3;
				
				cout << "������, ����� ������ ������� ������� �� ������ ��������� (1 - ������, 2 - ������, 3 - �����) ->";
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
							cout << "��������� ������� " << red_team->teams << endl;
						}
					}
				}
				else
				{
					cout << "�� ������ �� ����� ����� ������!!! \n\n�������� ��� ����." << endl;
				}
			}
		}
		if (Count_dead_red == 3 || Count_dead_green == 3)
		{
			cout << "\n===== ��� ��������� =====" << endl;
			break;
		}
	}
	delete[] green_team;
	delete[] red_team;
	return 0;
}

void Draka(Unit& green_team, Unit & red_team)  // ������� �� ������� ���
{
	cout << green_team.ShowUnit() << " ������� "<< green_team.teams <<" ����� " << red_team.ShowUnit() << " ������� " << red_team.teams << endl;
	cout << green_team.ShowUnit() << " ������� "<< green_team.teams << " �������� ����!" << endl;
	int block = rand() % 10 + 1;
	if (block >= 1 && block <= 6)
	{
		cout << red_team.ShowUnit() << " ������� " << red_team.teams << " �������� �� �����!" << endl;
	}
	else if (block >= 7 && block <= 10)
	{
		red_team.hp -= green_team.dmg;
		if (red_team.hp <= 0)
		{
			red_team.death();
		}
		else

			cout << red_team.ShowUnit() << " ������� " << red_team.teams << " ������� ����������� � ���� ����� ���������� �� " << green_team.dmg << endl;
	}
}

void Teams(Unit* green_team, int n, string teams) { // ������� �� ��������� ������
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