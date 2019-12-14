#pragma once
#include <iostream>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <string>
#include <cstring>
#include <locale> //dùng tiếng Việt ghi file
#include <codecvt> //possible C++11?
#include <fstream> //
#include <math.h>
#include <time.h>
#include <dirent.h>
#include <direct.h>
#include <windows.h>
using namespace std;

struct NODE {
	wchar_t	c;         // kí tự
	long	w;	       // số lần xuất hiện
	bool	used;	   // đánh dấu node đã xử lý chưa
	int		left;	   // vị trí của node con bên trái trong mảng
	int		right;	   // vị trí của node con bên phải trong mảng
};

void Init(); //Khởi tạo cây huffman
void StatisticWeight(string InputFile); //Thống kê tần số xuất hiện của các kí tự
bool Find_2Min(int& i, int& j, long nNode); //Tìm 2 phần tử nhỏ nhất trong cây mà chưa xử lý
long Creat(); //Khởi tạo cây huffman từ số liệu thống kê tìm được
void BrowseTree(long nNode, wstring BitCode, int& leaf);//Đệ qui tạo các chuỗi bit cho các node trong cây
int InitBitCode(long nRoot);//Tạo mã bit cho các node trong cây, trả về số lượng node lá

//Hệ nhị phân bắt buộc với 16 bit
int binary_to_decimal(wstring in);//Chuyển từ hệ 2 qua hệ 10 
wstring decimal_to_binary(int in);//Chuyển từ hệ 10 qua hệ 2
//Hệ nhị phân không bị ràng buộc bởi số lượng bit
int binary_to_decimal_end(wstring in);//Chuyển từ hệ 2 qua hệ 10 
wstring decimal_to_binary_end(int in);//Chuyển từ hệ 10 qua hệ 2

//-----//
void compress_file(string InputFile, string OutputFile);//nén file
void decompress_file(string InputFile, string OutputFile);//giải nén file
void compress_folder(string InputFolder, string OutputFolder);//nén thư mục
void decompress_folder(string InputFolder, string OutputFolder);//nén thư mục



