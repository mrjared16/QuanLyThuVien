// QuanLyThuVien.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#define isbn 13
#pragma warning(disable:4996)


struct ThongTinNguoi {
	char HoTen[50];
	int DoB[3]; // dd/mm/yyyy
	int CMND[9];
	char DiaChi[200];
	char GioiTinh[4];
};
typedef struct User {
	char usr[20];
	char pwrd[20];
	char HoTen[50];
	int DoB[3]; // dd/mm/yyyy
	int CMND[9];
	char DiaChi[200];
	char GioiTinh[4]; // Nam/Nu
	int Active; // 1 = activated, 0 = blocked
	int perm; // 1 = admin, 2 = quan ly, 3 = chuyen vien, 4 = user
};
typedef struct TheDocGia {
	char MaDocGia[8]; // MSSV: 7 ki tu
	char HoTen[50];
	int CMND[9];
	int DoB[8];
	char GioiTinh[4];
	char DiaChi[200];
	int NgayLapThe[3];
	int NgayHetHan[3];
};
typedef struct Sach {
	int ISBN[isbn]; // en.wikipedia.org/ISBN
	char TenSach[100];
	char TacGia[50];
	char NXB[50];
	int NamXB[4];
	char TheLoai[20];
	int GiaSach;
	int SoQuyenSach;
};
typedef struct PhieuMuonSach {
	char MaDocGia[100];
	int NgayMuon[3];
	int NgayTraDK[3];
	int NgayTraTT[3];
	int DanhSachISBN[130];
};
void UserList() {
	User admin;
	strcpy(admin.usr, "admin");
	strcpy(admin.pwrd, "admin");
	admin.perm = 1;
	admin.Active = 1;
	FILE *f = fopen("user.txt", "wb");
	fwrite(&admin, sizeof(User), 1, f);
	fclose(f);
}
User Login(FILE *f, bool &loginsuccess) {
	User userlogin;
	printf("Dang nhap:\n");
	printf("Nhap ten:  ");
	gets_s(userlogin.usr);
	printf("Nhap mat khau:  ");
	gets_s(userlogin.pwrd);
	User inputlist;
	while (!feof(f)) {
		loginsuccess = false;
		fread(&inputlist, sizeof(User), 1, f);
		if (!strcmp(inputlist.usr, userlogin.usr) && !strcmp(inputlist.pwrd, userlogin.pwrd)) {
			loginsuccess = true;
			break;
		}
	}
	if (loginsuccess)
		printf("Da dang nhap: %s.\n", userlogin.usr);
	else
		printf("Dang nhap that bai.\n");
	return userlogin;
}
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
void AddUsr(FILE *f) {
	fseek(f, 0L, SEEK_END);
	User New;
	int i = 0;
	printf("Nhap ho va ten:  ");
	gets_s(New.HoTen);
	printf("Nhap ten dang nhap:  ");
	gets_s(New.usr);
	printf("Nhap mat khau:  ");
	gets_s(New.pwrd);
	printf("Nhap ngay thang nam sinh (dd/mm/yyyy):  ");
	for (i = 0; i < 8; i++)
		scanf("%d", &New.DoB[i]);
	printf("Nhap so CMND:  ");
	for (i = 0; i < 9; i++)
		scanf("%d", &New.CMND[i]);
	printf("Nhap dia chi:  ");
	gets_s(New.DiaChi);
	printf("Nhap gioi tinh (Nam/Nu):  ");
	gets_s(New.GioiTinh);
	New.Active = 1;
	while (true) {
		printf("Nhap cap do phan quyen (2 = quan ly, 3 = chuyen vien, 4 = nguoi dung):  ");
		scanf("%d", &i);
		if (i == 1) 
			printf("Loi: Khong the dang ky quyen admin. Vui long nhap lai.\n");
		else {
			New.perm = i;
			break;
		}
	}
	fwrite(&New, sizeof(User), 1, f);
}
int main() {
	//UserList();
	FILE *f = fopen("user.txt", "r+b");
	if (f != NULL) {
		bool loginsuccess = false;
		User userlogin;
		while (!loginsuccess)
			userlogin = Login(f, loginsuccess);
		DanhSachChucNang(userlogin.perm);
		char function;
		printf("Nhap chuc nang muon su dung (1 - 7):  ");
		scanf("%c", &function);
		switch (function) {
			case '7': break;
		}
	}
	else {
		printf("Khong the mo danh sach nguoi dung.\n");
	}
	fclose(f);
	return 0;
}
