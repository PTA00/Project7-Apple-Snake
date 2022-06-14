#include "lib.h"//头文件放lib里
#include "test.h"//每个函数的测试用例放这里


int isExitgame()
{
	int x;
	x = MessageBox(NULL, TEXT("是否要退出游戏"), TEXT("对话框"), MB_YESNO);
	if (x == IDYES)
	{
		return 1;
	}
	else {
		return 0;
	}
}



void GameErrorlnfo(wchar_t info[]) {
	wchar_t text[100];
	wsprintf(text, L"%s", info);
	MessageBox(NULL, text, TEXT("发生错误！"), MB_ICONERROR);

}




void CopyMap(int map2[20][33], int map[20][33])
{

	memcpy(map2, map, sizeof(map));

}

int main(void) {
	system("chcp 65001");//固定，项目编译命令要加上/utf-8
	cls();

	FileNames2Nums_TEST();
}



