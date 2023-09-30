#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ROW 9
#define COL 9
#define ROWS 11
#define COLS 11
#define COUNT 10

// 显示游戏菜单
void menu();

// 进入游戏
void enterGame();

// 开始游戏
void startGame();

// 初始化二维数组
// '0'表示没有雷，'1'表示有雷
void init(char array[ROWS][COLS], int row, int col, char c);

// 打印二维数组
void display(char array[ROWS][COLS], int row, int col);

// 布置雷
void setMine(char array[ROWS][COLS], int row, int col);

// 扫雷
void findMine(char show[ROWS][COLS], char data[ROWS][COLS], int row, int col);

// 递归探索
void recurveSearch(char show[ROWS][COLS], char data[ROWS][COLS], int row, int col, int x, int y);

// 判断当前格子外围是否有雷，有雷返回雷的个数，没有雷返回'0'
int getMineCount(char data[ROWS][COLS], int x, int y);

// 判断是否赢了
bool isWin(char show[ROWS][COLS], char data[ROWS][COLS], int row, int col);