#include <iostream>
#include <Windows.h>
#include "Dictionarygame.h"
using namespace std;

int main() {
	SetConsoleTitle("Dictionary Game");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1);
	Dictionarygame game;
	
	system("pause");
	return 0;
}