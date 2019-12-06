#include "AHTree.h"

int main()
{
	AHTree tree;
	AHNode* temp;

	temp = tree.getNYT();
	cout << "Path NYT: " << tree.path(temp) << " - " << binary_to_decimal(tree.path(temp)) << "\n";
	system("pause");

	tree.update(tree.addNYT('a'));
	//tree.print(); system("pause");
	tree.update(tree.addNYT('b'));
	//tree.print(); system("pause");
	tree.update(tree.addNYT('a'));
	//tree.print(); system("pause");
	tree.update(tree.addNYT('c'));
	//tree.print(); system("pause");
	tree.update(tree.addNYT('b'));
	//tree.print(); system("pause");
	tree.update(tree.addNYT('d'));
	//tree.print(); system("pause");
	tree.update(tree.addNYT('c'));
	
	//tree.update(tree.addNYT('a'));
	//tree.update(tree.addNYT('b'));
	//tree.update(tree.addNYT('a'));
	//tree.update(tree.addNYT('a'));
	//tree.update(tree.addNYT('a'));//4a 1b
	//tree.update(tree.addNYT('f'));
	//tree.update(tree.addNYT('b'));
	//tree.update(tree.addNYT('b'));
	//tree.update(tree.addNYT('b'));
	//tree.update(tree.addNYT('b'));
	//tree.update(tree.addNYT('d'));//4a 5b 1d 1f
	//tree.update(tree.addNYT('a'));
	//tree.update(tree.addNYT('c'));
	//tree.update(tree.addNYT('a'));
	//tree.update(tree.addNYT('a'));
	//tree.update(tree.addNYT('e'));//7a 5b 1c 1d 1e 1f
	//tree.update(tree.addNYT('g'));
	//tree.update(tree.addNYT('d'));
	//tree.update(tree.addNYT('c'));
	//tree.update(tree.addNYT('c'));
	//tree.update(tree.addNYT('a'));//8a 5b 3c 2d 1e 1f 1g

	tree.print();
	system("pause");
	
	temp = tree.find('d');
	cout << "Path d: " << tree.path(temp) << " - " << binary_to_decimal(tree.path(temp)) << "\n";
	temp = tree.find('b');
	cout << "Path b: " << tree.path(temp) << " - " << binary_to_decimal(tree.path(temp)) << "\n";
	temp = tree.getRoot();
	cout << "Path root: " << tree.path(temp) << " - " << binary_to_decimal(tree.path(temp)) << "\n";
	temp = tree.getNYT();
	cout << "Path NYT: " << tree.path(temp) << " - " << binary_to_decimal(tree.path(temp)) << "\n";
	system("pause");
	return 0;
}