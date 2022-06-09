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
				exit(3);
			}
			map[h][l] = r;
			l++;
		}
		h++;
		count++;
	}

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inRec;
	DWORD numRead;
	int select = 1;
	while (1) {
		DrawMap(map, 2, 5);
		Sleep(20);
		int r = ReadConsoleInput(hInput, &inRec, (DWORD)1, &numRead);
		if (r == 0) {
			exit(6);
		}
		r = inRec.EventType;
		if (r == MOUSE_EVENT) {
			SHORT x = inRec.Event.MouseEvent.dwMousePosition.X;
			SHORT y = inRec.Event.MouseEvent.dwMousePosition.Y;
			gotoxy(0, 0);
			printf("%3d,%3d  选择：", x/2-1, y-5);
			DrawChar(select);

			if (inRec.Event.MouseEvent.dwButtonState == 1) {

			}
			else if (inRec.Event.MouseEvent.dwButtonState == 2) {

			}
		}
	}
	
	fclose(fp);
}