// QuanLyThuVien.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma warning(disable:4996)

void DanhSachChucNang(int perm) {
	printf("Danh sach chuc nang:\n");
	printf("1.1 Dang nhap\n");
	printf("1.2 Dang xuat\n");
	printf("1.3 Thay doi mat khau\n");
	printf("1.4 Cap nhat thong tin ca nhan\n");
	if (perm == 1) {
		printf("1.5 Tao nguoi dung\n");
		printf("1.6 Phan quyen nguoi dung\n");
	}
	printf("2.1 Xem danh sach dong gia\n");
	printf("2.2 Them doc gia\n");
	printf("2.3 Chinh sua thong tin mot doc gia\n");
	if (perm <= 2) printf("2.4 Xoa thong tin mot doc gia\n");
	printf("2.5 Tim kiem dong gia theo CMND");
	printf("2.6 TIm kiem sach theo ho ten\n");
	if (perm <= 2) {
		printf("3.1 Xem danh sach cac sanh trong thu vien\n");
		printf("3.2 Them sach\n");
		printf("3.3 Chinh sua thong tin mot quyen sach\n");
		printf("3.4 Xoa thong tin sach\n");
	}
	printf("3.5 Tim kiem sach theo ISBN\n");
	printf("3.6 Tim kiem sach theo ten sach\n");
	printf("4 Lap phieu muon sach\n");
	printf("5 Lap phieu tra sach\n");
	printf("6.1 Thong ke so luong sach trong thu vien\n");
	printf("6.2 Thong ke so luong sach theo the loai\n");
	printf("6.3 Thong ke so luong doc gia\n");
	printf("6.4 Thong ke so luong doc gia theo gioi tinh\n");
	if (perm <= 2) {
		printf("6.5 Thong ke so sach dang duoc muon\n");
		printf("6.6 Thong ke danh sach doc gia bi tre han\n");
	}
	printf("7 Thoat chuong trinh\n");
}


int main(int argc, char *arg[]) {

	Authentication input;
	bool check = false;

	do {
		if (argc == 3)
		{
			inputAuthentication(input, arg[1], arg[2]);
		}
		else {
			inputAuthentication(input);
		}

		check = Login(input);
		if (check)
		{
			printf("Dang nhap thanh cong.\n");
			//do something
			//load nguoi dung, doc gia, sach
			/*
			DanhSachChucNang(userlogin.perm);
			char function;
			printf("Nhap chuc nang muon su dung (1 - 7):  ");
			scanf("%c", &function);
			switch (function) {
				case '7': break;
			}*/
		}
		else {
			printf("Dang nhap that bai. Dang nhap lai!\n\n");
		}
	} while (!check);
	//save change: user, docgia, sach
	return 0;
}
