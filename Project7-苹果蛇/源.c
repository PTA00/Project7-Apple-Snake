#include "lib.h"

/// <summary>
/// zhushi
/// </summary>
/// <returns>fanhui</returns>
int isExitgame()
{
	int x;
	x = MessageBox(NULL, TEXT("是否要退出游戏"), TEXT("对话框"), MB_YESNO);
	if (x == IDYES)
	{
		return 1;
	}
	else { return 0; }

}

/// <summary>
/// 演示提交
/// </summary>
void aaaa() {

}

void GameErrorlnfo(wchar_t info[]) {
	wchar_t text[100];
	wsprintf(text, L"%s", info);
	MessageBox(NULL, text, TEXT("发生错误！"), MB_ICONERROR);

}

void GameErrorlnfo_TEST() {
	//void GameErrorlnfo(wchar_t info[]);
	//wchar_t info[100];
	//scanf_s("%ls", info, 100);
	GameErrorlnfo(L"123123");

}

int main(void) {

	GameErrorlnfo_TEST();
}

