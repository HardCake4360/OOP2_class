#include "Utils.h"

void GotoXY(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, COORD{ static_cast<SHORT>(x),static_cast<SHORT>(y) });
}