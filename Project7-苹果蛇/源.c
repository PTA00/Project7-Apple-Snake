#include "lib.h"

/// <summary>
/// zhushi
/// </summary>
/// <returns>fanhui</returns>
int isExitgame()
{
	int x;
	x = MessageBox(NULL, TEXT("�Ƿ�Ҫ�˳���Ϸ"), TEXT("�Ի���"), MB_YESNO);
	if (x == IDYES)
	{
		return 1;
	}
	else { return 0; }

}

/// <summary>
/// ��ʾ�ύ
/// </summary>
void aaaa() {
	printf("%s", "��Ҫ�ݺݵ�͸�ٴ�");
}

int main(void) {
	int r = isExitgame();
    printcf(15, "%d\n", r);
    
}
