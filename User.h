#pragma once
struct ThongTinNguoi {
	char HoTen[50];
	int DoB[3]; // dd/mm/yyyy
	int CMND[9];
	char DiaChi[200];
	char GioiTinh[4];  // Nam/Nu
};
typedef struct User {
	char usr[20];
	char pwrd[20];
	ThongTinNguoi info;
	int Active; // 1 = activated, 0 = blocked
	int perm; // 1 = admin, 2 = quan ly, 3 = chuyen vien, 4 = user
};