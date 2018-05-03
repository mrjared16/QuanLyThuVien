// QuanLyThuVien.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma warning(disable:4996)


ListSach l_sach;
ListUser l_user;

int main(int argc, char *arg[]) {

	Authentication input;
	bool check = false;

	do {
		if (argc == 3)
		{
			inputAuthentication(&input, arg[1], arg[2]);
		}
		else {
			inputAuthentication(&input);
		}

		check = Login(&input);
		if (check)
		{
			printf("Dang nhap thanh cong.\n");
			//do something
			//load nguoi dung, doc gia, sach
		}
		else {
			printf("Dang nhap that bai. Dang nhap lai!\n\n");
		}
	} while (!check);
	//save change: user, docgia, sach
	return 0;
}
