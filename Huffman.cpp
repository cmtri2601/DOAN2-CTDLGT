#include "Huffman.h"

const int MAX_NODE = 65536 * 2;
const int MAX_BIT_LEN = 10000;
NODE huffTree[MAX_NODE];
wstring BITCODE[65536];

void Init()
{
	for (int i = 0; i < MAX_NODE; i++)
	{
		huffTree[i].c = i;
		huffTree[i].w = 0;
		huffTree[i].used = false;
		huffTree[i].left = -1;
		huffTree[i].right = -1;
	}
}

void StatisticWeight(string InputFile)
{
	locale loc(locale(), new codecvt_utf8<wchar_t>);//UTF 8
	wifstream fin(InputFile);
	fin.imbue(loc);

	wchar_t c;
	while (1)
	{
		fin.get(c);
		if (fin.eof())
		{
			break;
		}
		huffTree[c].w++; //tăng trọng số của kí tự mới tìm thấy lên 1
	}

	fin.close();
}

//i,j là vị trí 2 node nhỏ nhất, nNode là số lượng các node cần xét (trong lúc tạo cây sẽ phát sinh các node cha)
bool Find_2Min(int& i, int& j, long nNode)
{
	i = -1;
	j = -1;

	for (int k = 0; k < nNode; k++)
		if (huffTree[k].used == false && huffTree[k].w > 0)
		{
			if (i == -1)
			{
				i = k;
			}
			else if (j == -1)
			{
				j = k;
			}
			else
			{
				if (huffTree[i].w > huffTree[j].w)
				{
					if (huffTree[k].w < huffTree[i].w)
					{
						i = k;
					}
				}
				else
				{
					if (huffTree[k].w < huffTree[j].w)
					{
						j = k;
					}
				}
			}
		}
	// nếu 1 trong 2 là -1 tức mảng chỉ còn 1 hoặc 0 phần tử chưa sử dụng, trả về sai
	// sắp xếp lại để [i] nhỏ nhất, [j] nhỏ nhì
	if (i != -1 && j != -1)
	{
		if ((huffTree[i].w > huffTree[j].w) || ((huffTree[i].w == huffTree[j].w) && (huffTree[i].c > huffTree[j].c)))
		{
			int t = i;
			i = j;
			j = t;
		}
		return true;
	}
	else
	{
		return false;
	}
}

long Creat()
{
	int nNode = 65536; //Vị trí node đầu tiên của các node cha (các node lá 0-255)
	int i, j;
	bool find = false;
	while (true)
	{
		find = Find_2Min(i, j, nNode);
		if (!find) {
			break;
		}

		// Gán các thuốc tính cho node cha mới tạo ra từ 2 node nhỏ nhất vừa được tìm thấy: kí tự (lấy kị tự nhỏ hơn), trọng số = tổng, node trái nhỏ hơn, node phải lớn hơn
		huffTree[nNode].c = (huffTree[i].c < huffTree[j].c) ? huffTree[i].c : huffTree[j].c;
		huffTree[nNode].w = huffTree[i].w + huffTree[j].w;
		huffTree[nNode].left = i;
		huffTree[nNode].right = j;

		// Đánh dấu 2 node nhỏ này đã được sử dụng lần tìm tiếp theo 2 node này sẽ không được tìm 
		huffTree[i].used = true;
		huffTree[j].used = true;

		// Đánh dấu node mới chưa được sử dụng, lần tìm tiếp theo node mới sẽ được tính trong mảng
		huffTree[nNode].used = false;
		nNode++; //***
	}
	return nNode - 1; //Vì ở dòng *** trên ta đã +1 cho vị trí node cha cuối cùng, ta phải -1 để trả về vị trí của node gốc
}

//Đệ qui để tạo mã bit cho các node, với BitCode là chuỗi mã bit, nBitCode là số lượng bit trong chuỗi
void BrowseTree(long nNode, wstring BitCode, int& leaf)
{
	//Điều điệu dừng
	if (nNode == -1)
	{
		return;
	}
	//Nếu là node lá thì sẽ gán chuỗi mà bít hiện hành cho node lá đó
	if (huffTree[nNode].left == -1 && huffTree[nNode].right == -1)
	{
		leaf++;
		BITCODE[nNode] = BitCode;
		///wcout << huffTree[nNode].c << L": " << huffTree[nNode].w << L" " << BITCODE[nNode] << L"\n";/////////////////////////
		return;
	}
	//Nếu không phải là node lá thì tiếp tục đi xuống các node con ở dưới...
	else {
		//thêm 0 và chuỗi và đệ qui qua nhánh trái
		BitCode += L'0';
		BrowseTree(huffTree[nNode].left, BitCode, leaf);
		BitCode = BitCode.substr(0, BitCode.size() - 1);

		//thêm 1 và chuỗi và đệ qui qua nhánh phải
		BitCode += L'1';
		BrowseTree(huffTree[nNode].right, BitCode, leaf);
		BitCode = BitCode.substr(0, BitCode.size() - 1);
	}
}

//Tham số truyền vào là vị trí node gốc, trả về số lượng node lá
int InitBitCode(long nRoot)
{
	//khởi tạo 

	wstring BitCode;
	//xây dựng mã bit
	int leaf = 0;
	BrowseTree(nRoot, BitCode, leaf);
	return leaf;
}

//Bắt buộc 16bit
int binary_to_decimal(wstring in)
{
	int result = 0;
	for (int i = 0; i < in.size(); i++)
		result = result * 2 + in[i] - '0';
	return result;
}

wstring decimal_to_binary(int in)
{
	wstring temp = L"";
	wstring result = L"";
	while (in)
	{
		temp += ('0' + in % 2);
		in /= 2;
	}
	result.append(16 - temp.size(), '0');
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		result += temp[i];
	}
	return result;
}
//Không bắt buộc 16bit
int binary_to_decimal_end(wstring in)
{
	in = L"1" + in; //tránh những trường hợp ntn 00011010 => 100011010
	int result = 0;
	for (int i = 0; i < in.size(); i++)
		result += int(in[i] - '0') * pow(2, in.size() - i - 1);
	return result;
}
wstring decimal_to_binary_end(int in)
{
	wstring result = L"";
	while (in)
	{
		result = wchar_t('0' + in % 2) + result;
		in /= 2;
	}
	result = result.substr(1);
	return result;
}

//-------------------------------------------------------------------//
void compress_file(string InputFile, string OutputFile)
{
	//Tính thời gian chạy
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	//Cài đặt UTF8, mở các file
	locale loc(locale(), new codecvt_utf8<wchar_t>);//UTF 8

	wchar_t c;
	wstring binary;
	wstring sub;

	wifstream fin(InputFile);
	fin.imbue(loc);
	wofstream fout(OutputFile);
	fout.imbue(loc);

	wcout << L"Đang xử lí dữ liệu...\n";

	//Xây dựng cây và tạo bảng mã
	Init();
	//wcout << L"Khởi tạo cây xong.\n";
	StatisticWeight(InputFile);
	//wcout << L"Thống kê tân suất xong.\n";
	long nNode = Creat();
	//wcout << L"Tạo cây xong.\n";
	int nLeaf = InitBitCode(nNode);
	//wcout << L"Tạo xong bảng mã bit.\n";

	//Ghi số lượng các node lá vào file
	fout << nLeaf;
	///wcout << nLeaf; //////
	//Ghi bảng mã vào file out 
	for (int i = 0; i < 65536; i++)
	{
		if (huffTree[i].left == -1 && huffTree[i].right == -1 && huffTree[i].w > 0)
		{
			fout << (wchar_t)huffTree[i].c;
			///wcout << huffTree[i].c;//////
			fout << huffTree[i].w;
			///wcout << huffTree[i].w; //////
			fout << L" "; //Thêm khoảng trắng ở giữa để tránh trường hợp 2 số nguyên ở cạnh nhau
		}
	};
	//Lấy lần lượt các kí tự và ghi mã tương ứng vào file
	while (1)
	{
		fin.get(c);
		if (fin.eof())
		{
			break;
		}
		binary += BITCODE[c];
		while (binary.size() >= 16)
		{
			sub = binary.substr(0, 16);
			fout << (wchar_t)binary_to_decimal(sub);
			///wcout << sub;////////
			binary = binary.substr(16);
		}
	}

	//Xử lý phần sót lại
	if (binary.size() < 16 && binary.size() > 0)
	{
		fout << (wchar_t)binary_to_decimal_end(binary);
		///wcout << binary;////////
	}
	///wcout << L"\n"; /////

	fin.close();
	fout.close();
	wcout << L"Nén thành công!\n";

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	wcout << L"Thời gian nén: " << cpu_time_used << L"(s)\n";
}

void decompress_file(string InputFile, string OutputFile)
{
	//Tính thời gian chạy
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	//Cài đặt UTF8, mở các file
	locale loc(locale(), new codecvt_utf8<wchar_t>);//UTF 8

	wchar_t c;		//Lấy kí tự
	int nLeaf;		//Lấy số lá
	long weight;	//Lấy trọng số các lá
	long current;	//Lấy vị trí hiện hành trên cây khi xét dãy bit
	wstring binary;	//Lấy dãy bit 
	wstring sub;	//Trích của dãy bit

	wifstream fin(InputFile);
	fin.imbue(loc);
	wofstream fout(OutputFile);
	fout.imbue(loc);

	wcout << L"Đang xử lí dữ liệu...\n";

	//Xây dựng cây và tạo bảng mã
	Init();
	//wcout << L"Khởi tạo cây xong.\n";

	fin >> nLeaf;
	//wcout << nLeaf;//////
	for (int i = 0; i < nLeaf; i++)
	{
		fin.get(c);
		fin >> weight;
		huffTree[c].w = weight;
		///wcout << L"\n" << i + 1 << L".";//////////////
		///wcout << huffTree[c].c << huffTree[c].w;/////////////////////////
		fin.get(c);//Lấy khoảng trắng
	}
	//wcout << L"Thống kê tân suất xong.\n";
	long nNode = Creat();
	//wcout << L"Tạo cây xong.\n";
	nLeaf = InitBitCode(nNode);
	//wcout << L"Tạo xong bảng mã bit.\n";

	current = nNode;
	while (1)
	{
		fin.get(c);
		if (fin.eof())
		{
			break;
		}
		binary += decimal_to_binary(c);
		while (binary.size() > 16)
		{
			sub = binary.substr(0, 1);
			//wcout << sub;////////
			if (sub == L"0")
				current = huffTree[current].left;
			else
				current = huffTree[current].right;
			if (huffTree[current].left == -1 && huffTree[current].right == -1)
			{
				fout << huffTree[current].c;
				current = nNode; //Sau khi tìm được kí tự thì cho quay lại node gốc để tìm kí tự mới
			}
			binary = binary.substr(1);
		}
	}
	//Xử lý phần sót lại
	binary = decimal_to_binary_end(binary_to_decimal(binary));
	//wcout << binary << L"\n";/////////////
	while (!binary.empty())
	{
		sub = binary.substr(0, 1);
		if (sub == L"0")
			current = huffTree[current].left;
		else
			current = huffTree[current].right;
		if (huffTree[current].left == -1 && huffTree[current].right == -1)
		{
			fout << huffTree[current].c;
			current = nNode; //Sau khi tìm được kí tự thì cho quay lại node gốc để tìm kí tự mới
		}
		binary = binary.substr(1);
	}

	fin.close();
	fout.close();
	wcout << L"Giải nén thành công!\n";

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	wcout << L"Thời gian giải nén: " << cpu_time_used << L"(s)\n";
}
void compress_folder(string InputFolder, string OutputFolder)
{
	//Tính thời gian chạy
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	DIR* dirin;
	struct dirent* filein;
	//DIR *dirout;
	//struct dirent *fileout;

	dirin = opendir(InputFolder.c_str());
	CreateDirectory(OutputFolder.c_str(), NULL);

	wcout << L"Các file trong thư mục: \n";

	while ((filein = readdir(dirin)) != NULL)
	{
		if (filein->d_namlen == 1 || filein->d_namlen == 2)
			continue;
		wcout << L"  - " << filein->d_name << L"\n";
		string file_input = (string)InputFolder + (string)filein->d_name;
		string file_compress = (string)OutputFolder + (string)filein->d_name;
		compress_file(file_input, file_compress);
	}

	closedir(dirin);
	wcout << L"Nén thư mục thành công!\n";
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	wcout << L"Thời gian giải nén: " << cpu_time_used << L"(s)\n";
}

void decompress_folder(string InputFolder, string OutputFolder)
{
	//Tính thời gian chạy
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	DIR* dirin;
	struct dirent* filein;
	//DIR *dirout;
	//struct dirent *fileout;

	dirin = opendir(InputFolder.c_str());
	CreateDirectory(OutputFolder.c_str(), NULL);

	wcout << L"Các file trong thư mục: \n";

	while ((filein = readdir(dirin)) != NULL)
	{
		if (filein->d_namlen == 1 || filein->d_namlen == 2)
			continue;
		wcout << L"  - " << filein->d_name << L"\n";
		string file_input = (string)InputFolder + (string)filein->d_name;
		string file_compress = (string)OutputFolder + (string)filein->d_name;
		decompress_file(file_input, file_compress);
	}

	closedir(dirin);
	wcout << L"Giải nén thư mục thành công!\n";
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	wcout << L"Thời gian giải nén: " << cpu_time_used << L"(s)\n";
}




