#include "AHTree.h"

AHTree::AHTree()
{
	_root = nullptr;
	_NYT = nullptr;
}
AHTree::AHTree(AHNode* _root, AHNode* _NYT)
{
	this->_root = _root;
	this->_NYT = _NYT;
}
AHTree::~AHTree()
{
	delete _root;
	delete _NYT;
}
void AHTree::print()
{
	int height = this->Height();
	for (int i = 1; i <= height; i++)
	{
		int length = this->Length(i);
		for (int j = 1; j <= length; j++)
		{
			cout << "(" << this->Get(i, j)->_c << ";" << this->Get(i, j)->_w << ")  ";
		}
		cout << endl;
	}
}

//-----------------------------------------------------------//
int AHTree::Height(AHNode* node)
{
	int height = 0;
	AHNode* temp = node;
	while (temp != nullptr)
	{
		height++;
		temp = temp->_parent;
	}
	return height;
}
int AHTree::Height()
{
	return this->Height(_NYT);
}
//Hàm đệ qui phụ
int len(AHNode* &root, int height)
{
	if (root == nullptr)
		return 0;
	if (height == 1)
		return 1;
	height--;
	return len(root->_left, height) + len(root->_right, height);
}
int AHTree::Length(int height)
{
	return len(this->_root, height);
}
//Duyệt NLR tìm vị trí của node (với chiều cao cho trước) trong cây;
void len(AHTree& Tree, AHNode* root, AHNode* node, int height, int &pos, int &num)
{
	if (root == nullptr)
		return;
	if (Tree.Height(root) == height)
		pos++;
	if (root == node)
	{
		num = pos;
		return;
	}
	len(Tree, root->_left, node, height, pos, num);
	len(Tree, root->_right, node, height, pos, num);
}
int AHTree::Length(AHNode* node)
{
	int height = this->Height(node);
	int num;
	int pos = 0;
	len(*this, this->_root, node, height, pos, num);
	return num;
}
AHNode* get(AHTree& Tree, AHNode* root, int height, int length)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	if (Tree.Height(root) == height && Tree.Length(root) == length)
		return root;
	else
	{
		if (Tree.Height(root) == height)
			return nullptr;
		else
		{
			if (get(Tree, root->_left, height, length) == nullptr && get(Tree, root->_right, height, length) == nullptr)
				return nullptr;
			else if (get(Tree, root->_left, height, length) == nullptr && get(Tree, root->_right, height, length) != nullptr)
				return get(Tree, root->_right, height, length);
			else
				return get(Tree, root->_left, height, length);
		}
	}
}
AHNode* AHTree::Get(int height, int length)
{
	return get(*this, this->_root, height, length);
}
//-----------------------------------------------------------//
void AHTree::swap(AHNode* x, AHNode* y)
{
	AHNode* temp;

	//Đổi con của cha 
	if (x == x->_parent->_left) //x là con bến trái
	{
		if (y == y->_parent->_left)//y là con bên trái
		{
			x->_parent->_left = y;
			y->_parent->_left = x;
		}
		else//y là con bên phải
		{
			x->_parent->_left = y;
			y->_parent->_right = x;
		}
	}
	else //x là con bên phải
	{
		if (y == y->_parent->_left)//y là con bên trái
		{
			x->_parent->_right = y;
			y->_parent->_left = x;
		}
		else//y là con bên phải
		{
			x->_parent->_right = y;
			y->_parent->_right = x;
		}
	}

	//Đổi cha
	temp = x->_parent;
	x->_parent = y->_parent;
	y->_parent = temp;
}
AHNode* _find(AHTree& Tree, AHNode* root, char _c)
{
	if (root == nullptr)
		return nullptr;
	if (root->_c == _c)
		return root;
	else
	{
		if (_find(Tree, root->_left, _c) == nullptr && _find(Tree, root->_right, _c) == nullptr)
			return nullptr;
		else if (_find(Tree, root->_left, _c) == nullptr && _find(Tree, root->_right, _c) != nullptr)
			return _find(Tree, root->_right, _c);
		else
			return _find(Tree, root->_left, _c);
	}
}
AHNode* AHTree::find(char _c)
{
	return _find(*this, this->_root, _c);
}
AHNode* creatAHNode(unsigned char _c, int _w, bool _NYT, AHNode* _parent, AHNode* _left, AHNode* _right)
{
	AHNode* result = new AHNode;

	result->_c = _c;
	result->_w = _w;
	result->_NYT = _NYT;
	result->_parent = _parent;
	result->_left = _left;
	result->_right = _right;

	return result;
}
AHNode* AHTree::addNYT(char _c)
{
	AHNode* temp = this->find(_c);
	if (temp != nullptr)
	{
		temp->_w++;
		this->up(temp);
		return temp;
	}
	else
	{
		if (_root == _NYT)
		{
			_NYT = creatAHNode(NULL, 0, true, nullptr, nullptr, nullptr);
			AHNode* node_right = creatAHNode(_c, 1, false, nullptr, nullptr, nullptr);
			_root = creatAHNode(NULL, 1, false, nullptr, _NYT, node_right);
			_NYT->_parent = _root;
			node_right->_parent = _root;
			this->up(node_right);
			return node_right;
		}
		else
		{
			AHNode* node_right = creatAHNode(_c, 1, false, nullptr, nullptr, nullptr);
			AHNode* node_parent = creatAHNode(NULL, 1, false, _NYT->_parent, _NYT, node_right);
			_NYT->_parent->_left = node_parent;
			_NYT->_parent = node_parent;
			node_right->_parent = node_parent;
			this->up(node_right);
			return node_right;
		}
	}
}
AHNode* AHTree::check(AHNode* node)
{
	AHNode* error = nullptr;
	int height = this->Height(node);
	for (int i = height; i > 0; i--)
	{
		if (i == height) //tại dòng (của cây) chứa node
		{
			int len_row = this->Length(height);
			int len_node = this->Length(node);
			for (int j = len_node + 1; j <= len_row; j++)
			{
				if (this->Get(i, j)->_w < node->_w)
					error = this->Get(i, j);
			}
		}
		else
		{
			int len_row = this->Length(i);
			for (int j = 1; j <= len_row; j++)
			{
				if (this->Get(i, j)->_w < node->_w)
					error = this->Get(i, j);
			}
		}
	}
	return error;
}
void AHTree::up(AHNode* node)
{
	AHNode* temp = node->_parent;
	while (temp != nullptr)
	{
		temp->_w = temp->_left->_w + temp->_right->_w;
		temp = temp->_parent;
	}
}
void AHTree::update(AHNode* node)
{
	if (node == nullptr)
		return;

	AHNode* error = this->check(node);
	if (error != nullptr)
	{
		this->swap(node, error);
		this->up(error); 
		this->up(node);
		this->update(error);
		this->update(node);
	}
	else
	{
		node = node->_parent;
		this->update(node);
	}
}
string AHTree::path(AHNode* node)
{
	if (node == nullptr)
		return "";

	string result;
	AHNode* path = node;
	while (path->_parent != nullptr)
	{
		if (path == path->_parent->_left)
			result = '0' + result;
		else
			result = '1' + result;
		path = path->_parent;
	}
	return result;
}
int binary_to_decimal(string in)
{
	int result = 0;
	for (int i = 0; i < in.size(); i++)
		result = result * 2 + in[i] - '0';
	return result;
}

string decimal_to_binary(int in)
{
	string temp = "";
	string result = "";
	while (in)
	{
		temp += ('0' + in % 2);
		in /= 2;
	}
	result.append(8 - temp.size(), '0');
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		result += temp[i];
	}
	return result;
}

