
//下面两个是例子，提交前一定要写好放在这里。

void GameErrorlnfo_TEST() {
	GameErrorlnfo(L"123123");
}

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

void FileNames2Nums_TEST() {
	char* strs[5] = { "111",NULL,"","A","555" };
	int cou = 5;
	int* rn = FileNames2Nums(strs, &cou);
	for (int i = 0; i < cou; i++) {
		printf("%d=%d\n", i, rn[i]);
	}
}