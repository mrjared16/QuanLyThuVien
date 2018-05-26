// QuanLyThuVien.cpp : Defines the entry point for the console application.
//

#include "Init.h"
#include "User.h"
#include "Menu.h"

//extern User login_user;

int main(int argc, char *arg[]) {
	//User login_user;
	Authentication input;
	int id_user = -1;
	bool login_check = false;
	bool first_try = true;

	do {
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

		login_check = checkLogin(input, id_user);

		//dang nhap thanh cong
		if (login_check)
		{
			//login_user : "Init.h"
			getRecord(login_user, id_user, USER_DATA);
			//getUser(id_user, user);
			runMenu(login_user);
		}
		else {
			printf("Dang nhap that bai. Dang nhap lai!\n\n");
		}
	} while (1);// !login_check);

	//save change: user, docgia, sach
	return 0;
}
