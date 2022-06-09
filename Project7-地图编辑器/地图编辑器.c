#include "../Project7-苹果蛇/lib.h"


int main(void) {
	system("chcp 65001");
	cls();
	SetConsoleTitle(L"地图编辑器");
	setcmdHW((33+2)*2, 20+6);
	HideCursor();
	DisbleQuickEditMode();

	wchar_t wszFile[MAX_PATH] = { 0 };
	char szFile[MAX_PATH] = { 0 };
	wchar_t title[MAX_PATH + 6] = { 0 };

	if (FileDialog(wszFile)) {
		WideCharToMultiByte(CP_UTF8, 0, wszFile, -1, szFile, MAX_PATH, NULL, FALSE);
		wsprintf(title, L"地图编辑器：%s", wszFile);
		SetConsoleTitle(title);
	}
	else {
		exit(0);
	}
	

	FILE* fp = NULL;
	fp = _wfopen(wszFile, L"r");
	if(!fp){
		exit(1);
	}

	char str[33 * 4 + 2] = { 0 };
	int map[20][33] = { 0 };
	int h = 0;
	int l = 0;
	int count = 0;
	while (fgets(str, 33*4+2, fp) != NULL && count<20) {
		
		if (strlen(str) != 33 * 4+1) {
			fclose(fp);
			exit(2);
		}
		l = 0;
		char aa[5] = { 0 };
		for (int i = 0; i < 33; i++) {
			aa[0] = str[i * 4];
			aa[1] = str[i * 4 + 1];
			aa[2] = str[i * 4 + 2];
			aa[3] = str[i * 4 + 3];

			int r = atoi(aa);
			if (r == 0) {
				fclose(fp);
				exit(3);
			}
			map[h][l] = r;
			l++;
		}
		h++;
		count++;
	}

	fclose(fp);

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inRec;
	DWORD numRead;
	int select = 1;
	
	int cc[8] = { 3,4,5,6,7,8,100,101 };
	int temp = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 33; j++) {
			if (map[i][j] > temp) {
				temp = map[i][j];
			}
		}
	}
	if (temp > 100) {
		cc[7] = temp + 1;
	}
	
	for (int i = 0; i < 8; i++) {
		gotoxy(4*i+16, 2);
		DrawChar(cc[i]);
	}
	
	gotoxy(2, 2);
	printf("保存");
	int time = 0;
	while (1) {
		DrawMap(map, 2, 5);
		if (time) {
			time--;
		}
		Sleep(10);
		int r = ReadConsoleInput(hInput, &inRec, 1, &numRead);
		if (r == 0) {
			exit(6);
		}
		r = inRec.EventType;
		if (r == MOUSE_EVENT) {
			SHORT x = inRec.Event.MouseEvent.dwMousePosition.X;
			SHORT y = inRec.Event.MouseEvent.dwMousePosition.Y;
			int x2 = x / 2 - 1;
			int y2 = y - 5;
			gotoxy(0, 0);
			printf("%3d,%3d 选择：", x2, y2);
			gotoxy(14, 0);
			DrawChar(select);
			gotoxy(16, 0);
			printf("%d", cc[7]);


			if (inRec.Event.MouseEvent.dwButtonState == 1) {
				
				if (x2 < 0 || x2>32 || y2 < 0 || y2>19) {
					if (y2 == -3) {
						if ((x2 == 0 || x2 == 1)&& time==0) {
							int r;
							r = MessageBox(NULL, TEXT("是否要保存？"), TEXT("对话框"), MB_YESNO);
							time = 10;
							if (r != IDYES) {
								continue;
							}
							//SetConsoleTitle(L"正在保存...");
							FILE* fp1 = NULL;
							fp1 = _wfopen(wszFile, L"w");
							//char savestr[33 * 4 + 2] = { 0 };
							for (int i = 0; i < 20; i++) {
								for (int j = 0; j < 33; j++) {
									fprintf(fp1, "%04d", map[i][j]);
								}
								fprintf(fp1, "\n");
							}
							fclose(fp1);
							exit(7);
						}
						else if (x2>=7 && x2<=21 && x2%2!=0) {
							select = cc[(x2-7) / 2];
						}
					}
					continue;
				}
				if (map[y2][x2] != 1) {
					continue;
				}
				if (select == 100) {
					int one = 0;
					for (int i = 0; i < 20; i++) {
						for (int j = 0; j < 33; j++) {
							if (map[i][j] == 100) {
								one++;
							}
						}
					}
					if (one > 0) {
						continue;
					}
					map[y2][x2] = 100;
				}
				else if (select > 100) {
					int temp = 0;
					if (x2 + 1 >= 0 && x2 + 1 <= 32) {
						if (map[y2][x2 + 1] == cc[7] - 1) {
							temp = 1;
						}
					}
					if (x2 - 1 >= 0 && x2 - 1 <= 32) {
						if (map[y2][x2 - 1] == cc[7] - 1) {
							temp = 1;
						}
					}
					if (y2 + 1 >= 0 && y2 + 1 <= 19) {
						if (map[y2 + 1][x2] == cc[7] - 1) {
							temp = 1;
						}
					}
					if (y2 - 1 >= 0 && y2 - 1 <= 19) {
						if (map[y2 - 1][x2] == cc[7] - 1) {
							temp = 1;
						}
					}
					if (temp == 1) {
						map[y2][x2] = cc[7];
						cc[7]++;
					}
					
				}
				else {
					map[y2][x2] = select;
				}
			}
			else if (inRec.Event.MouseEvent.dwButtonState == 2) {
				if (x2 < 0 || x2>32 || y2 < 0 || y2>19) {
					continue;
				}
				if (map[y2][x2] == 100 && cc[7]!=101) {
					continue;
				}
				else if (map[y2][x2] > 100) {
					int temp = 0;
					for (int i = 0; i < 20 && temp==0; i++) {
						for (int j = 0; j < 33; j++) {
							if (map[i][j] == cc[7] - 1) {
								if (i == y2 && j == x2) {
									map[y2][x2] = 1;
									cc[7]--;
								}
							}
						}
					}
				
				
				}
				else {
					map[y2][x2] = 1;
				}
				
			}
		}
	}
	
	
}