// QuanLyThuVien.cpp : Defines the entry point for the console application.
//

#include "Init.h"
#include "User.h"
#include "Menu.h"


int main(int argc, char *arg[]) {
	
	Authentication input;
	int id_user = -1;
	bool login_check = false;
	bool first_try = true;	//kiem tra lan nhap dau, chi lan nhap dau moi co the nhap tu cmd line

	do {
		//lay username password tu cmd line hoac do nguio dung nhap vao
		if (argc == 3 && first_try)
		{
			//dang nhap tu cmd line
			nhapUsernamePassword(input, arg[1], arg[2]);
			first_try = false;
		}
		else {
			//dang nhap lai tu ban phim
			printf("DANG NHAP\n");
			nhapUsernamePassword(input);
		}

		login_check = checkLogin(input, id_user);	//kiem tra dang nhap

		//dang nhap thanh cong
		if (login_check)
		{
			//login_user : "Init.h"
			getRecord(login_user, id_user, USER_DATA);	//lay thong tin cua user

			if (login_user.Active != BLOCKED)
			{
				runMenu(login_user);	//chay cac ham khoi tao menu theo user va xuat menu
			}
			else {
				printf("Tai khoan cua ban da bi khoa! Vui long dang nhap bang tai khoan khac.\n");
			}
		}
		else {
			printf("Dang nhap that bai. Dang nhap lai!\n\n");
		}
	} while (1);


	return 0;
}
