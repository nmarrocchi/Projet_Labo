#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <windef.h>
#include <wincon.h>

using namespace std;

class text_color
{
public:
	enum Color
	{
		Black = 0,
		White = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
		Blue = FOREGROUND_BLUE,
		Green = FOREGROUND_GREEN,
		Red = FOREGROUND_RED,
		Yellow = FOREGROUND_RED | FOREGROUND_GREEN,
		Magenta = FOREGROUND_RED | FOREGROUND_BLUE,
		LightWhite = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
		LightBlue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		LightGreen = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		LightRed = FOREGROUND_RED | FOREGROUND_INTENSITY,
		LightYellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		LightMagenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	};
};


class bg_color
{
public:
	enum Color
	{
		Black = 0,
		White = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED,
		Blue = BACKGROUND_BLUE,
		Green = BACKGROUND_GREEN,
		Red = BACKGROUND_RED,
		Yellow = BACKGROUND_RED | BACKGROUND_GREEN,
		Magenta = BACKGROUND_RED | BACKGROUND_BLUE,
		LightWhite = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY,
		LightBlue = BACKGROUND_BLUE | BACKGROUND_INTENSITY,
		LightGreen = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
		LightRed = BACKGROUND_RED | BACKGROUND_INTENSITY,
		LightYellow = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
		LightMagenta = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	};
};