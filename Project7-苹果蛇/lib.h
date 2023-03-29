#include <stdio.h>
#include <Windows.h>
#include <io.h>
#include <conio.h>

#pragma warning(disable : 4996)

/**
 * 更改文字颜色
 */
void Color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);//更改文字颜色
}

/**
 * 光标移动到(x,y)位置
 */
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);//使光标到这个（x，y）的位置
}

/**
 * 隐藏控制台光标
 */
void HideCursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

/**
 * 禁用控制台编辑和插入
 */
void DisbleQuickEditMode() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;//移除快速编辑模式
    mode &= ~ENABLE_INSERT_MODE;//移除插入模式
    mode |= ENABLE_MOUSE_INPUT;//启用鼠标输入
    SetConsoleMode(hStdin, mode);
}


/**
 * 设置控制台的宽高
 */
void setcmdHW(int width, int height) {
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

/**
 * 获取指定目录下的所有文件名
 * 参数：字符串数组，搜索路径，文件后缀名，最大数量
 * 返回值：-1=未找到，0=正常
 */
int getFilesName(char* arr[], char* path, char* suffix, int count) {
    char pathstr[MAX_PATH];
    sprintf(pathstr, "%s/*.%s", path, suffix);

    struct _finddata_t fa;
    int fHandle = _findfirst(pathstr, &fa);
    if (fHandle == -1) {
        return -1;//异常返回：当前目录下没有文件
    }
    int i = 0;
    do {
        arr[i] = (char*)malloc(MAX_PATH);
        if (arr[i]) {
            strcpy(arr[i], fa.name);
        }
        i++;
        //printf("调试输出：找到文件:%s\n", fa.name);
    } while ((_findnext(fHandle, &fa) == 0) && (i < count));
    _findclose(fHandle);
    return 0;
}

/**
 * 获取指定目录下，指定类型文件的数量
 * 参数：搜索路径，文件后缀名
 * 返回值：指定类型文件的数量
 */
int getFilesNum(char* path, char* suffix) {
    char pathstr[MAX_PATH];
    sprintf(pathstr, "%s/*.%s", path, suffix);

    struct _finddata_t fa;
    int fHandle = _findfirst(pathstr, &fa);
    if (fHandle == -1) {
        return 0;
    }
    int i = 0;
    do {
        i++;
    } while ((_findnext(fHandle, &fa) == 0));
    _findclose(fHandle);

    return i;
}

//简化名称：sas
#define sas(a, b) StrAndStr(a, b)
/**
 * 拼接字符串（加强版）
 * 参数：字符串a，字符串b（可以为常量）
 * 返回值：字符串指针，0为异常
 */
char* StrAndStr(char* a, char* b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    if (strlen(a) == 0 || strlen(b) == 0) {
        return 0;
    }
    char* s = (char*)malloc(strlen(a) + strlen(b) + 1);
    if (s) {
        return strcat(strcpy(s, a), b);
    }
}

//简化名称：printcf
#define printcf(color, _Format, ...) printColorf(color, _Format, __VA_ARGS__)
/**
 * printf 炫彩版
 * 参数：颜色，格式字符串，参数列表
 * 
 * 0   =   黑色    * 8   =   灰色
 * 1   =   蓝色    * 9  =   淡蓝色
 * 2   =   绿色    * 10  =   淡绿色
 * 3   =   湖蓝色  * 11  =   淡浅绿色
 * 4   =   红色    * 12  =   淡红色
 * 5   =   紫色    * 13  =   淡紫色
 * 6   =   黄色    * 14  =   淡黄色
 * 7   =   白色    * 15   =   亮白色
 */
void printColorf(int color, char const* const _Format, ...) {   
    Color(color);
    va_list args;
    va_start(args, _Format);
    vprintf(_Format, args);
    va_end(args);
    Color(7);
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


/// <summary>
/// 绘制字符（元素）
/// </summary>
/// <param name="number">代表元素的数字</param>
void DrawChar(int number) {
    switch (number) {

    case 1:
        printcf(51, "  ");
        break;
    case 3:
        printcf(60, "♥");
        break;
    case 4:
        printcf(48, "※");
        break;
    case 5:
        printcf(52, "★");
        break;
    case 6:
        printcf(136, "\u2588\u2588");
        break;
    case 7:
        printcf(48, "●");
        break;
    case 8:
        printcf(127, "□");
        break;
    case 100:
        printcf(234, "%s", "■");
    default:
        if (number > 199 || number < 1) {
            exit(4);
        }
        if (number > 100 && number < 200) {
            printcf(42, "%s", "■");
        }
        break;
    }
}

/// <summary>
/// 打开文件对话框
/// </summary>
/// <param name="path">宽字符文件路径</param>
/// <returns>返回0为用户关闭了对话框或取消选择</returns>
int FileDialog(wchar_t path[]) {
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.hwndOwner = GetConsoleWindow();
    ofn.lStructSize = sizeof(ofn); // 结构大小
    ofn.lpstrFile = path; // 路径
    ofn.nMaxFile = MAX_PATH; // 路径大小
    ofn.lpstrFilter = L"Text(*.txt)\0*.txt\0\0"; // 文件类型
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    return GetOpenFileName(&ofn);
}

/// <summary>
/// 绘制地图，从xy位置开始绘制
/// </summary>
/// <param name="map">地图二维数组</param>
/// <param name="x">x位置</param>
/// <param name="y">y位置</param>
void DrawMap(int map[20][33], int x, int y) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 33; j++) {
            gotoxy(j * 2 + x, i + y);
            DrawChar(map[i][j]);
            //printf("%d,", map[i][j]);
        }
        if (i == 19) {
            return;
        }
        printf("\n");
    }
}

/// <summary>
/// 游戏界面
/// </summary>
/// <returns>开始游戏 1，关卡选择 2，游戏规则 3，作者介绍 4，退出游戏，esc 0，</returns>
int GameStartSelect() {
    int will_x = 33;	//地图空间长值
    int will_y = 20;	//地图空间宽值
    int i, j;
    //标题没想好
    setcmdHW(will_x * 2 + 20, will_y + 10);		//控制台大小
    for (i = 0; i <= will_x + 1; i++)
    {
        for (j = 0; j <= will_y + 1; j++)
        {
            gotoxy(i * 2 + 8, j + 2);
            if (i == 0 || i == will_x + 1) {
                printf("□");
            }
            else if (j == 0 || j == will_y + 1) {
                printf("□");
            }
            if (j != 0 && j != 21 && i == 0) {		//不重要
                gotoxy(6, j + 2);					//不重要
                printcf(11, "%d", j);				//不重要
            }										//不重要
            //Sleep(1);
        }
        if (i != 0 && i != 34) {					//不重要
            if (i % 2 == 0)								//不重要
                gotoxy(i * 2 + 8, 0);				//不重要
            else									//不重要
                gotoxy(i * 2 + 8, 1);				//不重要
            printcf(11, "%d", i);					//不重要
        }											//不重要
    }
    gotoxy(12, 4);
    printcf(12, "ESC 退！退！退！");
    gotoxy(will_x + 27, will_y - 1);
    printcf(14, "上下键控制选择");
    gotoxy(will_x + 27, will_y + 1);
    printcf(14, "回车确定");
    char xz;
    const int co1 = 15, co2 = 8;//选项的两种颜色
    const int js_x = will_x + 5; //选项的x值
    int re_do = 1;
    int re_enter = 0;
    do {
        int opTion_co[4] = { co2,co2,co2,co2 };
        switch (re_do)
        {
        case 1: opTion_co[0] = co1; break;
        case 2: opTion_co[1] = co1; break;
        case 3: opTion_co[2] = co1; break;
        case 4: opTion_co[3] = co1; break;
        }
        gotoxy(js_x, 14);
        printcf(opTion_co[0], "开始游戏");
        gotoxy(js_x, 16);
        printcf(opTion_co[1], "关卡选择");
        gotoxy(js_x, 18);
        printcf(opTion_co[2], "游戏规则");
        gotoxy(js_x, 20);
        printcf(opTion_co[3], "作者介绍");
        gotoxy(js_x - 28, 22);
        //printf("当前选择值：%d", re_do);				//不重要
        HideCursor();
        xz = _getch();
        switch (xz)
        {
        case 72: case 'w': case 'W':
            if (re_do == 1)
                re_do = 1;
            else
                re_do--;
            continue;
        case 80: case 's': case 'S':
            if (re_do == 4)
                re_do = 4;
            else
                re_do++;
            continue;
        case 27:re_do = 0; break;
        case 13:re_enter = 1; break;
        }
    } while (re_do != 0 && re_enter == 0);
    return re_do;
}

/// <summary>
/// 文件名数组转换至序号数组，过滤不合法文件名
/// </summary>
/// <param name="filenames">文件名数组</param>
/// <param name="count">文件数组长度（文件数量）</param>
/// <returns>动态创建的新序号数组（长度可能缩小）</returns>
int* FileNames2Nums(char* filenames[], int* count) {
    int* names = (int*)calloc(*count, sizeof(int*));
    if (names == NULL) {
        exit(8);//申请内存失败退出
    }
    int n = 0;
    for (int i = 0; i < *count; i++) {
        if (filenames[i] == NULL) {//空串跳过
            continue;
        }
        int r = atoi(filenames[i]);
        if (r == 0) {//非数字跳过
            continue;
        }
        names[i] = r;
        n++;
    }
    int* names2 = (int*)calloc(n, sizeof(int*));
    if (names2 == NULL) {
        exit(8);//申请内存失败退出
    }
    int n2 = 0;
    for (int i = 0; i < *count && n2 < n; i++) {
        if (names[i] == 0) {//前面筛选不合法的跳过
            continue;
        }
        names2[n2] = names[i];
        n2++;
    }
    free(names);
    *count = n;
    return names2;
}

/// <summary>
/// 错误信息对话框（可自定义）
/// </summary>
/// <param name="info">自定义的错误信息（宽字符）</param>
void GameErrorlnfo(wchar_t info[]) {
    wchar_t text[100];
    wsprintf(text, L"%s", info);
    MessageBox(NULL, text, TEXT("发生错误！"), MB_ICONERROR);
}

/// <summary>
/// 是否退出对话框
/// </summary>
/// <returns>选是返回1，选否返回0</returns>
int isExitgame() {
    int x;
    x = MessageBox(NULL, TEXT("是否要退出游戏"), TEXT("对话框"), MB_YESNO);
    if (x == IDYES) {
        return 1;
    }
    else {
        return 0;
    }
}

/// <summary>
/// 绘制debug边框（显示边界、行号列号）
/// </summary>
void drawDebugBox() {
    int will_x = 33;	//地图空间长值
    int will_y = 20;	//地图空间宽值
    int i, j;
    setcmdHW(will_x * 2 + 20, will_y + 10);		//控制台大小

    for (i = 0; i <= will_x + 1; i++)
    {
        for (j = 0; j <= will_y + 1; j++)
        {
            gotoxy(i * 2 + 8, j + 2);
            if (i == 0 || i == will_x + 1) {
                printf("□");
            }
            else if (j == 0 || j == will_y + 1) {
                printf("□");
            }
            if (j != 0 && j != 21 && i == 0) {
                gotoxy(6, j + 2);
                printcf(11, "%d", j);
            }
        }
        if (i != 0 && i != 34) {
            if (i % 2 == 0) {
                gotoxy(i * 2 + 8, 0);
            }
            else {
                gotoxy(i * 2 + 8, 1);
            }
            printcf(11, "%d", i);
        }
    }
}