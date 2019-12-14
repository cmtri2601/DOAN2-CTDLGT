#include "Huffman.h"
#include "Menu.h"

int main()
{
	_setmode(_fileno(stdout), _O_U8TEXT);
	_setmode(_fileno(stdin), _O_U8TEXT);

	Menu();

	system("pause");
	return 0;
}
