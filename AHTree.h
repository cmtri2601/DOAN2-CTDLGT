#pragma once
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

struct AHNode
{
	unsigned char _c;
	int _w;
	bool _NYT;

	AHNode* _parent;
	AHNode* _left;
	AHNode* _right;
};
class AHTree
{
private:
	AHNode* _root;
	AHNode* _NYT;
public:
	AHTree();
	AHTree(AHNode* _root, AHNode* _NYT);
	~AHTree();
	
	AHNode* getRoot() { return _root; }
	AHNode* getNYT() { return _NYT; }
	void print();

	//VỊ TRÍ TÍNH TỪ 1
	int Height();//Chiều cao của cây
	int Height(AHNode* node);//Chiều cao của node truyền vào trong cây
	int Length(int height);//Số node có cùng bậc (cùng chiều cao)
	int Length(AHNode* node);//Vị trí của node trong các node có cùng bậc
	AHNode* Get(int height, int length);//Tìm con trỏ khi biết vị trí 

	void swap(AHNode* x, AHNode* y);//Đổi 2 node
	AHNode* find(char _c);//Tìm node chứa kí tự truyền vào
	AHNode* addNYT(char _c);//thêm vào NYT (thêm kí tự mới)
	AHNode* check(AHNode* node);//check từ nốt đó -> các nốt cha tương ứng -> gốc, trả về node vi phạm tính anh em xa nhất
	void up(AHNode* node);//Các node cha từ node hiện hành đến node gốc bằng tổng 2 node con
	void update(AHNode* node);//hiệu chỉnh cây từ node truyền vào tới tới các node cha ở trên
	
	string path(AHNode* node);//Tìm đường đi từ gốc tới node (trả về chuỗi)
};

//-------------------------------------------------------------------------------------------//

int binary_to_decimal(string in);//Chuyển từ hệ 2 qua hệ 10
string decimal_to_binary(int in);//Chuyển từ hệ 10 qua hệ 2

