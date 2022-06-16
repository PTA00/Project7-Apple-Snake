
//下面两个是例子，提交前一定要写好放在这里。

void GameErrorlnfo_TEST() {
	GameErrorlnfo(L"123123");
}

void getFileRowCount_TEST() {
	int r = getFileRowCount("text/getFileRowCount.txt");
	printf("文件行数：%d\n", r);
}

void LevelSelect_TEST();	//调用关卡
void GameStartSelect_TEST() {
	int r = GameStartSelect();
	cls();
	gotoxy(0, 0);
	printf("选择：%d\n", r);
	if (r == 1 || r == 2) {
		cls();
		LevelSelect_TEST();
	}
}

void FileNames2Nums_TEST() {
	char* strs[5] = { "111",NULL,"","A","555" };
	int cou = 5;
	int* rn = FileNames2Nums(strs, &cou);
	for (int i = 0; i < cou; i++) {
		printf("%d=%d\n", i, rn[i]);
	}
}

void LevelSelect_TEST() {
#define maxgq 27	//关卡最大数
	int level_sz[maxgq] = { 0 };
	for (int i = 0; i < maxgq; i++) {
		level_sz[i] = i + 1;
	}
	int r = LevelSelect(level_sz, maxgq);
	printf("返回 %d ", r);
	if (r == 0) {
		cls();
		GameStartSelect_TEST();
	}
}