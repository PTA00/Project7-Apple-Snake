#include "lib.h"//头文件放lib里
#include "test.h"//每个函数的测试用例放这里

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



void GameErrorlnfo(wchar_t info[]) {
	wchar_t text[100];
	wsprintf(text, L"%s", info);
	MessageBox(NULL, text, TEXT("发生错误！"), MB_ICONERROR);
}

/// <summary>
/// 获取文本文件的行数
/// </summary>
/// <param name="path">文本文件的路径</param>
/// <returns>返回行数，如果有错误返回0</returns>
int getFileRowCount(char path[]) {
	FILE* fp;
	int flag = 0, file_row = 0, count = 0;
	if ((fp = fopen(path, "r")) == NULL) {
		return 0;
	}
	while (!feof(fp)) {
		flag = fgetc(fp);
		if (flag == '\n') {
			count++;
		}
	}
	file_row = count + 1; //加上最后一行
	//printf("row = %d\n", file_row);
	fclose(fp);
	return file_row;
}



int main(void) {
	getFileRowCount_TEST();
	
}

