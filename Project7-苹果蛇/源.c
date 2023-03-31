//调试模式:1 关闭:0
#define debug 1

#include "lib.h"//头文件和函数放lib里
#include "test.h"//每个函数的测试用例放这里



int main(void) {
	SetConsoleOutputCP(65001);//设置进程控制台输出代码页
	//已弃用 system("chcp 65001");//固定，项目编译命令要加上/utf-8
	while (1) {
		int re = GameStartSelect();
		gotoNewxy(32, 19);
		DrawChar(5);
		pause();
		//返回1,2,3,4,0
		//printf("%d\n",re);
		switch (re)
		{
		case 0:
			//退出游戏
			if (isExitgame()) {//对话框询问是否退出
				exit(0);
			}
			break;
		case 1:
		case 2:
			//关卡选择
			break;
		case 3:
			//游戏规则
			break;
		case 4:
			//作者介绍
			break;
		}
	}
	
	

}

