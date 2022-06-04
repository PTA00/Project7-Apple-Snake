#include <stdio.h>
#include <Windows.h>

#pragma warning(disable : 4996)

/**
 * 更改文字颜色
 */
void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);//更改文字颜色
}

/**
 * 光标移动到(x,y)位置
 */
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);//使光标到这个（x，y）的位置，需要调用#include<windows.h>
}

/**
 * 隐藏控制台光标
 */
void HideCursor(){
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

/**
 * 设置控制台的宽高
 */
void setcmdHW(int width,int height) {
    char chCmd[32];
    sprintf(chCmd, "mode con cols=%d lines=%d", width, height);
    system(chCmd);
}

/**
 * 清空控制台
 */
void cls() {
    system("cls");
}

/**
 * 暂停，按任意键继续
 */
void pause() {
    system("pause");
}