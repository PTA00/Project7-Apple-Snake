//调试模式，如要关闭请注释掉
#define debug

#include "lib.h"//头文件和函数放lib里
#include "test.h"//每个函数的测试用例放这里

int main(void) {
	SetConsoleOutputCP(65001);//设置进程控制台输出代码页
	//已弃用 system("chcp 65001");//固定，项目编译命令要加上/utf-8
	cls();
	GameStartSelect();

}

