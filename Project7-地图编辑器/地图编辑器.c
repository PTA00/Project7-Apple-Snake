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
	
	int cc[8] = { 3,4,5,6,7,8,100,101 };//最后一个101代表下一个蛇尾的值

	for (int i = 0; i < 20; i++) {//在地图中寻找蛇尾（最大的数）
		for (int j = 0; j < 33; j++) {
			if (map[i][j] >= cc[7]) {//如果找到更新的蛇尾
				cc[7] = map[i][j] + 1;//那么下一个蛇尾的值就是最大值+1
			}
		}
	}
	
	for (int i = 0; i < 8; i++) {//静态的元素选择按钮，一共8个按钮，间隔1个方格（按钮栏）
		gotoxy(4*i+16, 2);
		DrawChar(cc[i]);
	}
	
	gotoxy(2, 2);//静态的保存按钮（按钮栏）
	printf("保存");
	int time = 0;//“保存”按钮的cd变量

	while (1) {
		DrawMap(map, 2, 5);//绘制地图
		if (time) {//每次循环“保存”按钮的cd减一，cd为0时才能再次点击
			time--;
		}
		Sleep(10);
		int r = ReadConsoleInput(hInput, &inRec, 1, &numRead);//读取控制台输入缓冲区
		if (r == 0) {
			exit(6);//如果读取错误，直接退出程序
		}
		if (inRec.EventType == MOUSE_EVENT) {//读取到的是鼠标类输入
			SHORT x = inRec.Event.MouseEvent.dwMousePosition.X;//原始xy
			SHORT y = inRec.Event.MouseEvent.dwMousePosition.Y;
			int x2 = x / 2 - 1;//以地图左上角为参考点的x2y2
			int y2 = y - 5;

			gotoxy(0, 0);//实时输出鼠标在地图上的坐标（以地图左上角为参考点）
			printf("%3d,%3d 选择：", x2, y2);
			gotoxy(14, 0);//实时输出画笔当前的元素
			DrawChar(select);
			gotoxy(16, 0);//实时输出贪吃蛇身体的下一个值
			printf("%d", cc[7]);

			if (inRec.Event.MouseEvent.dwButtonState == 1) {//左键
				if (x2 < 0 || x2>32 || y2 < 0 || y2>19) {//如果不在地图范围内
					if (y2 == -3) {//如果点到-3行（按钮栏）
						if ((x2 == 0 || x2 == 1)&& time==0) {//点到的是“保存”按钮，并且按钮cd结束
							int r = MessageBox(NULL, TEXT("是否要保存？"), TEXT("对话框"), MB_YESNO);
							time = 10;//设置按钮的cd，防止连续点击，外部每次循环会-1
							if (r != IDYES) {//不保存直接跳出
								continue;
							}
							FILE* fp1 = NULL;
							fp1 = _wfopen(wszFile, L"w");//只写，使用之前对话框选择的路径再次打开文件
							for (int i = 0; i < 20; i++) {//将地图写入文件
								for (int j = 0; j < 33; j++) {
									fprintf(fp1, "%04d", map[i][j]);
								}
								fprintf(fp1, "\n");
							}
							fclose(fp1);//写入完成后关闭文件
							exit(7);//保存完毕，退出程序
						}
						else if (x2>=7 && x2<=21 && x2%2!=0) {//或者点到的是各种元素的按钮，按钮只在奇数列
							select = cc[(x2-7) / 2];//将画笔设置为按钮对应的元素
						}
					}
					continue;//运行到这步说明只是点到了没用的地方，直接跳出
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
			else if (inRec.Event.MouseEvent.dwButtonState == 2) {//右键
				if (x2 < 0 || x2>32 || y2 < 0 || y2>19) {//不在地图范围直接跳出
					continue;
				}
				if (map[y2][x2] == 100 && cc[7]!=101) {//想删除蛇头，但仍有蛇尾存在，直接跳出
					continue;
				}
				else if (map[y2][x2] > 100) {//想删除蛇尾
					if (map[y2][x2] == cc[7] - 1) {//对比当前选择是不是蛇尾的数值
						map[y2][x2] = 1;
						cc[7]--;
					}
				}
				else {//其它元素正常的删除
					map[y2][x2] = 1;
				}
				
			}
		}
	}
	
	
}