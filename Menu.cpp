#include "Menu.h"

void Menu()
{
	bool isExit = false;
	int option; //biến lưu lại lựa chọn người dùng

	wstring wInputFile;
	wstring wCompress;
	wstring wDecompress;

	wstring wInputFolder;
	wstring wCompressFolder;
	wstring wDecompressFolder;

	do
	{
		system("cls");
		wcout << L"CẤU TRÚC DỮ LIỆU & GIẢI THUẬT             Sinh viên: Lý Quỳnh Trâm\n";
		wcout << L"ĐỒ ÁN 2                                              Cao Minh Trí \n";
		wcout << L"      ======================================================\n";
		wcout << L"   MENU  \n\n";
		wcout << L"   1.  Nén file.\n";
		wcout << L"   2.  Giải nén file.\n";
		wcout << L"   3.  Nén thư mục.\n";
		wcout << L"   4.  Giải nén thư mục.\n";
		wcout << L"   0.  Thoát\n\n";


		wcout << L"~  Nhập lựa chọn (0-4): "; wcin >> option;
		while (option != 0 && option != 1 && option != 2 && option != 3 && option != 4)
		{
			wcout << L"~  Lựa chọn không hợp lệ, nhập lại (0-4): "; wcin >> option;
		}

		switch (option)
		{
		case 1:
		{
			system("cls");
			wcout << L"CẤU TRÚC DỮ LIỆU & GIẢI THUẬT             Sinh viên: Lý Quỳnh Trâm\n";
			wcout << L"ĐỒ ÁN 2                                              Cao Minh Trí \n";
			wcout << L"      ======================================================\n";
			wcout << L"Nén file >\n\n";
			wcout << L"Nhập tên file cần nén (hoặc đường dẫn đến file cần nén): ";
			wcin >> wInputFile;
			string InputFile(wInputFile.begin(), wInputFile.end());
			wcout << L"Nhập tên file sau khi được nén: ";
			wcin >> wCompress;
			string Compress(wCompress.begin(), wCompress.end());
			compress_file(InputFile, Compress);
			

			wcout << L"\n\nNhấn một phím bất kì để thoát!\n"; system("pause");

			break;
		}
		
		case 2:
		{
			system("cls");
			wcout << L"CẤU TRÚC DỮ LIỆU & GIẢI THUẬT             Sinh viên: Lý Quỳnh Trâm\n";
			wcout << L"ĐỒ ÁN 2                                              Cao Minh Trí \n";
			wcout << L"      ======================================================\n";
			wcout << L"Giải nén file >\n\n";
			wcout << L"Nhập tên file cần giải nén (hoặc đường dẫn đến file cần giải nén): ";
			wcin >> wCompress;
			string Compress(wCompress.begin(), wCompress.end());
			wcout << L"Nhập tên file sau khi được giải nén: ";
			wcin >> wDecompress;
			string Decompress(wDecompress.begin(), wDecompress.end());
			decompress_file(Compress, Decompress);


			wcout << L"\n\nNhấn một phím bất kì để thoát!\n"; system("pause");

			break;
		}
		
		case 3:
		{
			system("cls");
			wcout << L"CẤU TRÚC DỮ LIỆU & GIẢI THUẬT             Sinh viên: Lý Quỳnh Trâm\n";
			wcout << L"ĐỒ ÁN 2                                              Cao Minh Trí \n";
			wcout << L"      ======================================================\n";
			wcout << L"Nén thư mục >\n\n";
			wcout << L"Nhập đường dẫn đến thư mục cần nén: ";
			wcin >> wInputFolder;
			string InputFolder(wInputFolder.begin(), wInputFolder.end());
			wcout << L"Nhập đường dẫn đến thư mục sau khi được nén: ";
			wcin >> wCompressFolder;
			string CompressFolder(wCompressFolder.begin(), wCompressFolder.end());
			compress_folder(InputFolder, CompressFolder);


			wcout << L"\n\nNhấn một phím bất kì để thoát!\n"; system("pause");

			break;
		}

		case 4:
		{
			system("cls");
			wcout << L"CẤU TRÚC DỮ LIỆU & GIẢI THUẬT             Sinh viên: Lý Quỳnh Trâm\n";
			wcout << L"ĐỒ ÁN 2                                              Cao Minh Trí \n";
			wcout << L"      ======================================================\n";
			wcout << L"Giải nén thư mục >\n\n";
			wcout << L"Nhập đường dẫn đến thư mục cần giải nén: ";
			wcin >> wCompressFolder;
			string CompressFolder(wCompressFolder.begin(), wCompressFolder.end());
			wcout << L"Nhập đường dẫn đến thư mục sau khi được giải nén: ";
			wcin >> wDecompressFolder;
			string DecompressFolder(wDecompressFolder.begin(), wDecompressFolder.end());
			decompress_folder(CompressFolder, DecompressFolder);


			wcout << L"\n\nNhấn một phím bất kì để thoát!\n"; system("pause");

			break;
		}

		case 0:
		{
			isExit = true;
			break;
		}
		}
	} while (!isExit);
}