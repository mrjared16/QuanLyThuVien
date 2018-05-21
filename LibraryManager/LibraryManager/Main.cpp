// QuanLyThuVien.cpp : Defines the entry point for the console application.
//

#include "Init.h"
#include "User.h"
#include "Menu.h"

int main(int argc, char *arg[]) {
	User user;
	Authentication input;
	int id_user = -1;
	bool login_check = false;
	bool first_try = true;

	do {
		if (argc == 3 && first_try)
		{
			//dang nhap tu cmd line
			inputAuthentication(input, arg[1], arg[2]);
			first_try = false;
		}
		else {
			//dang nhap lai tu ban phim
			inputAuthentication(input);
		}

		login_check = checkLogin(input, id_user);

		//dang nhap thanh cong
		if (login_check)
		{
			getRecord(user, id_user, USER_DATA);
			//getUser(id_user, user);
			runMenu(user);
		}
		else {
			printf("Dang nhap that bai. Dang nhap lai!\n\n");
		}
	} while (1);// !login_check);

	//save change: user, docgia, sach
	return 0;
}
