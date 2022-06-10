
//下面两个是例子，提交前一定要写好放在这里。

void GameErrorlnfo(wchar_t info[]);

void GameErrorlnfo_TEST() {
	GameErrorlnfo(L"123123");
}

int getFileRowCount(char path[]);

void getFileRowCount_TEST() {
	int r = getFileRowCount("text/getFileRowCount.txt");
	printf("文件行数：%d\n", r);
}

void GameStartSelect_TEST() {
	int r = GameStartSelect();
	cls();
	gotoxy(0, 0);
	printf("选择：%d\n", r);
}