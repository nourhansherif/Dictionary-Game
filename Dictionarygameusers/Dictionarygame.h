#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<unordered_map>
#include <vector>
using namespace std;

class design {
public:
	design();
	void font();
	void place(short z, short y);
};
class user
{
public:
	string name;
	int lvl;
	user();
};
class level {
public:
	string difficulty;
	string word;
	string defintion;
	level();
};
class Dictionarygame
{
	string diff;
	unordered_map<string, vector<level> > game;
	string choosencategory;
	level random_key;
	vector<char> lettersOfTheWord;
	vector<level> wordswithdiff;
	vector <string> solvedwords;
	user wons;
	int won;
	int trials;
	unordered_map<string, int> player;
public:
	Dictionarygame();
	void Mainmenu();
	void play();
	void options();
	void readfile();
	void readuserfile();
	void upgradeprogess();
	void saveuser();
	void selectplayer();
	void newplayer();
	string choosecategory();
    void choosediffculty();
	bool checksolve(string choosenword);
	void gamecycle();
	level randomword();
	void initializevector(int size);
	void displayvector(vector<char>lettersOfTheWord);
	int updatevector(int counter ,char t, string random_word);
	int hint(string random_word);
	void hangman(int counter);
	bool guessWholeWord(string random_word);
	bool guessLetterByLetter(int counter, string random_word);
	string casesenstivity_string(string guess);
	bool twoplayers(string word);
	void twoplayerscycle();
	~Dictionarygame();
};

