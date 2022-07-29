#include "Dictionarygame.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include<unordered_map>
#include <vector>
//cin.fail done
//tryagain done
//hangman done
//validations(handling letters entered before)
//languages

using namespace std;
design::design() {}
void design::font(int f) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = f;                  // Height
	//cfi.FontFamily = FF_DONTCARE;
	//cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"arialbd"); // Choose your font CONSOLAS
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void design::place(short z, short y) {
	COORD x;
	x = { z ,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

level::level() {}

user::user() {
	lvl = 1;
};

Dictionarygame::Dictionarygame()
{
	readfile();
	readuserfile();
	wons.name = "New";
	won = 0;
	diff = "random";
	Mainmenu();
}

void Dictionarygame::Mainmenu() {
	design d;
	d.place(40, 0);
	d.font(25);
	cout << " Welcome to Dictionary Game !" << endl << endl;
	d.place(50, 5);
	cout << "1-Play" << endl;
	d.place(49, 7);
	cout << "2-Options" << endl;
	d.place(50, 9);
	cout << "3-Exit" << endl;

	int num;
	cin >> num;
	while (cin.fail() || num > 3 || num < 1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid entry, Please choose a number from the menu above" << endl;
		cin >> num;
	}
	if (num == 1) play();
	else if (num == 2) options();
	else if (num == 3) return;
}

void Dictionarygame::play() {
	system("cls");
	cout << "1-One player" << endl << "2-Two player" << endl;
	int num;
	cin >> num;
	while (cin.fail() || num > 2 || num < 1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid entry, Please choose a number from the menu above" << endl;
		cin >> num;
	}
	system("cls");
	if (num == 1) {
		if (wons.name == "New") {
			string s = "NewPlayer"; int i = 1;
			unordered_map<string, int>::iterator it = player.find(s);
			while (it != player.end())
			{
				if (i > 1) s.erase(s.size() - 1, s.size());
				s = s +to_string(i);
				it = player.find(s);
				i++;
			}
			player.insert(make_pair(s, 1));
			wons.name = s;
		}
		system("cls");
		cout << "Welcome " << wons.name << "!" << endl;
		choosencategory = choosecategory();
		system("cls");
		if (diff != "random") {
			unordered_map<string, vector<level> >::iterator it = game.find(choosencategory);
			for (int i = 0; i < it->second.size(); i++)
				if (it->second[i].difficulty == diff) wordswithdiff.push_back(it->second[i]);
		}
		gamecycle();
				Sleep(1000);
				system("cls");
				Mainmenu();
			}
	else if (num == 2)
		twoplayerscycle();
}

void Dictionarygame::options() {
	system("cls");
	cout << "1- Change User  2-Change difficulty  3-MainMenu" << endl;
	int num;
	cin >> num;
	while (cin.fail() || num > 3 || num < 1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid entry,Please choose a number from the menu above" << endl;
		cin >> num;
	}
	if (num == 1) selectplayer();
	else if (num==2) choosediffculty();
	else Mainmenu();
	system("cls");
	Mainmenu();
}

void Dictionarygame::readfile() {

	ifstream input;
	level s;
	vector<level>q;
	input.open("Countries.txt");
	while (!input.eof()) {
		input >> s.difficulty >> s.word;
		getline(input, s.defintion);
		q.push_back(s);
	} game.insert(make_pair("Countries", q));
	input.close();
	q.clear();

	input.open("Sports.txt");
	while (!input.eof()) {
		input >> s.difficulty >> s.word;
		getline(input, s.defintion);
		q.push_back(s);
	} game.insert(make_pair("Sports", q));

	input.close();
	q.clear();

	input.open("Animals.txt");
	while (!input.eof()) {
		input >> s.difficulty >> s.word;
		getline(input, s.defintion);
		q.push_back(s);
	} game.insert(make_pair("Animals", q));

	input.close();
	q.clear();

	input.open("Jobs.txt");
	while (!input.eof()) {
		input >> s.difficulty >> s.word;
		getline(input, s.defintion);
		q.push_back(s);
	} game.insert(make_pair("Jobs", q));

	input.close();
	q.clear();

	input.open("Colors.txt");
	while (!input.eof()) {
		input >> s.difficulty >> s.word;
		getline(input, s.defintion);
		q.push_back(s);
	} game.insert(make_pair("Colors", q));

	input.close();
	q.clear();
	input.open("Fruits.txt");
	while (!input.eof()) {
		input >> s.difficulty >> s.word;
		getline(input, s.defintion);
		q.push_back(s);
	} game.insert(make_pair("Fruits", q));

	input.close();
}

string Dictionarygame::choosecategory() {
	cout << "Choose Category:" << endl << " 1)Countries\t 2)Sports\t 3)Animals\t 4)Jobs\t 5)Colors\t 6)Fruits" << endl;
	int category_Index; cin >> category_Index;
	while (cin.fail() || category_Index > 6 || category_Index < 1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid entry, Please choose a number from the menu above" << endl;
		cin >> category_Index;
	}
	switch (category_Index) {
	case 1:return "Countries";
	case 2:return "Sports";
	case 3: return "Animals";
	case 4: return "Jobs";
	case 5: return "Colors";
	case 6: return "Fruits";
	}
}

void Dictionarygame::choosediffculty() {
	cout << "Choose which difficulty to play with ?" << endl;
	cout << "1-Easy" << endl << "2-Medium" << endl << "3-Hard" << endl << "4-MainMenu" << endl;
	int num; cin >> num;
	while (cin.fail() || num > 4 || num < 1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid entry,Please choose a number from the menu above" << endl;
		cin >> num;
	}
	switch (num) {
	case 1:diff = "Easy"; break;
	case 2:diff = "Medium"; break;
	case 3:diff = "Hard"; break;
	case 4: Mainmenu();
	}
}

void Dictionarygame::gamecycle() {
	while (true) {
		random_key = randomword();
		if (random_key.word == "Mastered") {
			cout << "You Mastered this Category" << endl;
			Sleep(2000);
			break;
		}
		else {
			trials = 0;
			cout << "Defintion: " << random_key.defintion << endl;
			cout << "Guess word!" << endl;
			bool istrue = guessWholeWord(random_key.word);
			if (istrue) {
				solvedwords.push_back(random_key.word);
				won++;
				cout << "Total won: " << won << endl;
				if (won % 5 == 0) {
					wons.lvl++;
					cout << "Congratulations! You have upgraded to level " << wons.lvl << "." << endl;
				}
				cout << "1-Next word\t 2-MainMenu" << endl;
				int num; cin >> num;
				while (cin.fail() || num > 2 || num < 1) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Invalid entry,Please choose a number from the menu above" << endl;
					cin >> num;
				}
				if (num == 2)break;
			}
			else {
				initializevector(lettersOfTheWord, random_key.word.size());
				int counter = hint(lettersOfTheWord, random_key.word);
				istrue = guessLetterByLetter(lettersOfTheWord, counter, random_key.word);
				if (istrue == false) {
					cout << "You failed!" << endl<< "The right word is "<<random_key.word<<endl;
					break;
				}
				else {
					solvedwords.push_back(random_key.word);
					won++;
					cout << "Total won: " << won << endl;
						if (won % 5 == 0) {
						wons.lvl++;
						cout << "Congratulations! You have upgraded to level " << wons.lvl << "." << endl;
					}
				}
			}

		}Sleep(1500); 
		system("cls");
	}upgradeprogess();
	saveuser();
}

bool Dictionarygame::checksolve(string choosenword) {
	for (int i = 0; i < solvedwords.size(); i++)
		if (choosenword == solvedwords[i])return true;
	return false;
}

level Dictionarygame::randomword() {
	unordered_map<string, vector <level> >::iterator it;
	level choosen;
	if (diff == "random") {
		it = game.find(choosencategory);
		int k = rand() % (it->second.size());
		while (checksolve(it->second[k].word) && solvedwords.size() != it->second.size())
			k = rand() % (it->second.size());
		if (solvedwords.size() == it->second.size()) {
			choosen.word = "Mastered";
			return choosen;
		}
		choosen.word = it->second[k].word;
		choosen.defintion = it->second[k].defintion;
		choosen.difficulty = it->second[k].difficulty;
		return choosen;
	}
	else {
		int k = rand() % (wordswithdiff.size());
		while (checksolve(wordswithdiff[k].word) && solvedwords.size() != wordswithdiff.size())
			k = rand() % (wordswithdiff.size());
		if (solvedwords.size() == wordswithdiff.size()) {
			choosen.word = "Mastered";
			return choosen;
		}
		choosen.word = wordswithdiff[k].word;
		choosen.defintion = wordswithdiff[k].defintion;
		choosen.difficulty = wordswithdiff[k].difficulty;
		return choosen;
	}

}

void Dictionarygame::initializevector(vector <char>&lettersOfTheWord, int size) {
	lettersOfTheWord.clear();
	for (int i = 0; i < size; i++)
		lettersOfTheWord.push_back('_');
}

void Dictionarygame::displayvector(vector<char>lettersOfTheWord) {
	for (int i = 0; i < lettersOfTheWord.size(); i++)
		cout << lettersOfTheWord[i] << " ";
	cout << endl;
}

int Dictionarygame::updatevector(vector<char>&lettersOfTheWord, char t, string random_key) {
	for (int i = 0; i < random_key.size(); i++)
		if (t == random_key[i]) {
			if (lettersOfTheWord[i] == random_key[i])
				cout << "letter already exists" << endl;
			else
				lettersOfTheWord[i] = t;
		}
	int counter = 0;
	for (int i = 0; i < lettersOfTheWord.size(); i++)
		if (lettersOfTheWord[i] == random_key[i])
			counter++;
	return counter;
}

int Dictionarygame::hint(vector<char>&lettersOfTheWord, string random_key) {
	char t = random_key[rand() % random_key.size()];
	return updatevector(lettersOfTheWord, t, random_key);
}

void Dictionarygame::hangman(int counter) {
	switch (counter)
	{
	case 0:cout << " \t\t\t\t\t\t\t\t\t _________" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         |" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|_____________" << endl;
		break;
	case 1:cout << " \t\t\t\t\t\t\t\t\t_________" << endl;
	    cout << " \t\t\t\t\t\t\t\t\t|         |" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         O  " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|_____________" << endl;
		break;
	case 2:cout << " \t\t\t\t\t\t\t\t\t _________" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         |" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         O  " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         |" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|_____________" << endl;
		break;
	case 3:cout << " \t\t\t\t\t\t\t\t\t_________" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         |" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|       \\ O " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         |" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         " << endl;
	   cout << " \t\t\t\t\t\t\t\t\t|_____________" << endl;
		break;
	case 4:cout << " \t\t\t\t\t\t\t\t\t_________" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         |" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|       \\ O /" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         | " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|_____________" << endl;
		break;
	case 5:cout << " \t\t\t\t\t\t\t\t\t_________" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         |" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|       \\ O / " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         | " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|        / " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|_____________" << endl;
		break;
	case 6:cout << " \t\t\t\t\t\t\t\t\t_________" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         |" << endl;
		cout << " \t\t\t\t\t\t\t\t\t|       \\ O / " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|         | " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|        / \\ " << endl;
		cout << " \t\t\t\t\t\t\t\t\t|_____________" << endl;
		cout << "\t\t\t\t\t\t\t\t\tYou're dead" << endl;
		break;
	}
}

bool Dictionarygame::guessWholeWord(string random_word) {
	string guess;
	for (int i = 0; i < 3; i++) {
		hangman(trials);
		if (i != 0) {
			cout << "You have " << 6 - trials << "trial left " << endl;
		}cin >> guess;
		guess = casesenstivity_string(guess);
		if (guess == random_word) {
			cout << "TRUE!" << endl;
			return true;
		}
		else {
			trials++;
			cout << "try again" << endl;
			Sleep(300);
			system("cls");
			cout << "Defintion: " << random_key.defintion << endl;
			cout << "Guess word!" << endl;

		}
		
	} return false;

}

bool Dictionarygame::guessLetterByLetter(vector<char>&lettersOfTheWord, int counter, string random_word) {
	char t;
	vector <char>missed;
	while (trials <= 6 && counter != random_word.size()) {//trials 3
		system("cls");
		cout << "Defintion: " << random_key.defintion << endl;
		cout << "Guess word!" << endl;
		hangman(trials);
		if (trials == 6) break;
		cout << "You have " << 6 - trials << "trial left " << endl;
		displayvector(lettersOfTheWord);
		cin >> t;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please enter a single letter" << endl;
			cin >> t;
		}
		int b = -1;
		b = random_word.find_first_of(t);
		if (b != -1) {
			counter = updatevector(lettersOfTheWord, t, random_word);
		}
		else if (b == -1 && isupper(t)) {
			t = tolower(t);
			b = random_word.find_first_of(t);
			if (b != -1)
				counter = updatevector(lettersOfTheWord, t, random_word);
		}
		else if (b == -1 && islower(t)) {
			t = toupper(t);
			b = random_word.find_first_of(t);
			if (b != -1)
				counter = updatevector(lettersOfTheWord, t, random_word);
		}

		if (b == -1) {
			missed.push_back(t);
			cout << "try again" << endl;
			trials++;
		}
		Sleep(500);
	}
	return (trials!=6);
}

string Dictionarygame::casesenstivity_string(string guess) {
	guess[0] = toupper(guess[0]);
	for (int i = 1; i < guess.size(); i++)
		guess[i] = tolower(guess[i]);

	return guess;
}

bool Dictionarygame::twoplayers(string word)
{
	cout << "Guess word!" << endl;
	initializevector(lettersOfTheWord, word.size());

	bool istrue = guessWholeWord(word);
	if (istrue)
		return true;
	else
	{
		int counter = hint(lettersOfTheWord, word);
		displayvector(lettersOfTheWord);
		istrue = guessLetterByLetter(lettersOfTheWord, counter, word);
		if (istrue == false) {
			cout << "You failed!" << endl;
			cout << "The word is:" << word;
			return false;
		}
		else
			return true;
	}
}

void Dictionarygame::twoplayerscycle() {
	string player1, player2;
	cout << "Enter Player 1 name:" << endl;
	cin >> player1;
	cout << "Enter Player 2 name:" << endl;
	cin >> player2;
	unordered_map <string, int> players; //for players names and score
	players.insert(make_pair(player1, 0));
	players.insert(make_pair(player2, 0));
	unordered_map <string, int> p1;  //for scoreboard
	unordered_map <string, int>p2;
	int num= 1;
	while (num==1)
	{
		level lvl;
		cout << "Player 1's turn , Enter the word " << endl;
		cin >> lvl.word;
		lvl.word = casesenstivity_string(lvl.word);
		cout << "Enter the definition:" << endl;
		cin >> lvl.defintion;
		system("cls");
		cout << lvl.defintion << endl;
		if (twoplayers(lvl.word))
		{
			p1.insert(make_pair(lvl.word, 1));
			players[player1]++;
			cout << "Right guess" << endl;
		}
		else
		{
			p1.insert(make_pair(lvl.word, 0));
			players[player2]++;
			cout << "Wrong guess" << endl;
		}

		system("cls");
		cout << "Player 2's turn , Enter the word " << endl;
		cin >> lvl.word;
		lvl.word = casesenstivity_string(lvl.word);
		cout << "Enter the definition:" << endl;
		cin >> lvl.defintion;
		system("cls");
		cout << lvl.defintion << endl;
		if (twoplayers(lvl.word))
		{
			p2.insert(make_pair(lvl.word, 1));
			players[player2]++;

			cout << "Right guess" << endl;
		}
		else
		{
			p2.insert(make_pair(lvl.word, 0));
			players[player1]++;

			cout << "Wrong guess" << endl;
		}
		cout << "Do you want to continue ? Press 1 for (YES) 2 for (NO) ";
		cin >> num;
		while (cin.fail() || num > 2 || num < 1) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please choose a number from the menu above" << endl;
			cin >> num;
		}
		system("cls");
	}
	if (players[player1] > players[player2])
	{
		cout << "The winner is " << " " << player1 << " " << "with" << " " << players[player1] << " " << "points" << endl;
		cout << player2 << " " << "has lost with " << " " << players[player2] << " " << "points" << endl;

	}
	else if (players[player1] < players[player2])
	{
		cout << "The winner is " << " " << player2 << " " << "with" << " " << players[player2] << " " << "points" << endl;
		cout << player1 << " " << "has lost with " << " " << players[player1] << " " << "points" << endl;

	}
	else
	{
		cout << "The two players tied" << " " << "with" << " " << players[player1] << " " << "points" << endl;
	}

	cout << player1 << endl;
	unordered_map<string, int>::iterator it = p1.begin();

	for (it = p1.begin(); it != p1.end(); it++)
	{
		cout << it->first << "\t";
		if (it->second == 1)cout << "Succeeded" << endl;
		else cout << "Failed" << endl;
	}

	cout << player2 << endl;
	for (it = p2.begin(); it != p2.end(); it++)
	{
		cout << it->first << "\t";
		if (it->second == 1)cout << "Succeeded" << endl;
		else cout << "Failed" << endl;
	}
}

void Dictionarygame::readuserfile()
{
	ifstream input;
	user p;
	input.open("Users.txt");
	int begin = input.tellg();
	input.seekg(0, ios::end);
	int end = input.tellg();
	if (end - begin != 0) {
		input.seekg(0);
		while (!input.eof()) {
			input >> p.name >> p.lvl;
			player.insert(make_pair(p.name, p.lvl));
		}
	}
	input.close();
}
void Dictionarygame::newplayer() {
	unordered_map<string, int>::iterator it;
	user p;
	cout << "Enter Name:";
	cin >> p.name;
	it = player.find(p.name);
	if (it == player.end()) {
		player.insert(make_pair(p.name, 1));
		wons.name = p.name;
		wons.lvl = 1;
	}
	else {
		cout << "This player already exist do you want to continue with that name? Press 1 for (YES), 2 for (NO) !" << endl;
		int num;
		cin >> num;
		while (cin.fail() || num > 2 || num < 1) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid entry,Please choose a number from the menu above" << endl;
			cin >> num;
		}
		if (num == 1)
		{
			wons.name = it->first;
			wons.lvl = it->second;
		}
		else if (num == 2) {
			cout << "Enter another name: ";
			cin >> p.name;
		}
	}
	saveuser();
}
void  Dictionarygame::selectplayer() {
	int num;
	user p;
	unordered_map<string, int>::iterator it;
	cout << "Press 1 to Select Player , 2 to Add New Player ! " << endl;
	cin >> num;
	while (cin.fail() || num > 2 || num < 1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid entry,Please choose a number from the menu above" << endl;
		cin >> num;
	}
	if (num == 2)
		newplayer();

	else if (num == 1) {
		if (player.empty()) {
			cout << "No saved players please add a new one " << endl;
			newplayer();
		}
		else {
			for (it = player.begin(); it != player.end(); it++) {
				cout << it->first << " " << it->second << endl;
			}
			cin >> p.name;
			it = player.find(p.name);
			if (it == player.end()) {
				cout << "Player doesn't exist, Do you want to create one with that name? \n Press 1 for (YES), 2 for (NO) ! " << endl;
				int c;
				cin >> c;
				while (cin.fail() || c> 2 || c < 1) {
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Invalid entry,Please choose a number from the menu above" << endl;
					cin >> c;
				}
				if (c == 1) {
					player.insert(make_pair(p.name, 1));
				}
				else
				{
					cout << "Enter another name: ";
					cin >> p.name;
				}

			}
			else {
				wons.name = it->first;
				wons.lvl = it->second;
			}
		}
	}
}

void Dictionarygame::upgradeprogess()
{
	unordered_map<string, int>::iterator it;
	it = player.find(wons.name);
	it->second = wons.lvl;
}

void Dictionarygame::saveuser() {
	ofstream output;
	unordered_map<string, int>::iterator it;
	output.open("Users.txt", ios::trunc);
	for (it = player.begin(); it != player.end(); it++)
		output << it->first << "\t" << it->second << endl;

	output.close();
}

Dictionarygame::~Dictionarygame()
{
	cout << "Thank You For Playing ' _ '" << endl;
}
