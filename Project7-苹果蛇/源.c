#include "lib.h"//头文件放lib里
#include "test.h"//每个函数的测试用例放这里



int main(void) {
	system("chcp 65001");//固定，项目编译命令要加上/utf-8
	cls();

	FileNames2Nums_TEST();
}



void CopyMap(int map2[20][33], int map[20][33])
{

	memcpy(map2, map, sizeof(map));

}