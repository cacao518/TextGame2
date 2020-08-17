#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <stdio.h>
#include <cstdio>
#include <bitset>
#include <thread>
#include <Windows.h>
#include <mutex> 
#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include <Windows.h>
#include <unordered_map>
#include <locale>
#include <string>


enum OBJTYPE { BACKGROUND, TERRAIN, ITEMBOX, VEHICLE, PLAYER, ENEMY,BOSS, BULLET, UI, TYPE_END };

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 


extern const int MapWidth;
extern const int MapHeight;