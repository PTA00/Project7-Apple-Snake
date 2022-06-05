#include "lib.h"
//现在把这些代码提交到git上，如何做？
int main(void){
	char* aa[10] = { 0 };
	if (getFilesName(aa, "map", "txt", 1) == 0) {
		for (int i = 0; i < 10; i++) {
			printf("%s\n", aa[i]);
		}
	}
}