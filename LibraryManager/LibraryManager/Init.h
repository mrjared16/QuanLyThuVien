#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SACHMUON 100

#define isbn 14

#define MALE 1
#define FEMALE 0

#define MAX_LABEL_LENGTH 40
#define MSSV_LENGTH 8

#define MEMBER 1
#define MODERATOR 2
#define ADMIN 3

#define AUTHEN "user.bin"
#define USER_DATA "user_data.bin"

#define SACH "book.bin"
#define ISBN_SACH "isbn_book.bin"
#define TEN_SACH "name_book.bin"

#define DOCGIA "docgia.bin"
#define IDCARD_DOCGIA "icn_docgia.bin"
#define HOTEN_DOCGIA "name_docgia.bin"

#define NOT_FOUND -1
#define FILE_NOT_FOUND -2

// dd/mm/yyyy
struct Time {
	char ngay;
	char thang;
	int nam;
};

struct HoTen {
	char key[50];
};
struct IdentityCardNumber {
	char key[10];
};

//ten -> DoB -> CMND -> diachi -> gioi tinh
struct ThongTinNguoi {
	HoTen Ho_Ten;
	Time DoB;
	IdentityCardNumber CMND;
	char DiaChi[200];
	char GioiTinh;  //1 = Nam, 0 = Nu
};

//username -> password
struct Authentication {
	char usr[20];
	char pwrd[20];
};

//id -> username -> info -> active -> permission
struct User {
	int id;
	char usr[20];
	ThongTinNguoi info;
	int Active; // 1 = activated, 0 = blocked
	int permission;
};

//madocgia (MSSV) -> info -> ngayhethan
struct TheDocGia {
	char MaDocGia[MSSV_LENGTH]; // MSSV: 7 ki tu
	ThongTinNguoi info;
	Time NgayHetHan;
};

struct ISBN {
	char key[isbn];
};

struct BookName {
	char key[100];
};

//isbn -> ten -> tacgia -> NXB -> theloai -> giasach -> soluong
struct Sach {
	ISBN book_ISBN;// en.wikipedia.org/ISBN

	BookName TenSach;
	char TacGia[50];
	char NXB[50];

	char NamXB[5];

	char TheLoai[20];
	int GiaSach;

	int SoLuong;
};

struct PhieuMuonSach {
	char MaDocGia[MSSV_LENGTH];

	Time NgayMuon;
	Time NgayTraDK;
	Time NgayTraTT;

	int soluong_sach;
	ISBN DanhSachISBN[MAX_SACHMUON];
//	char DanhSachISBN[MAX_SACHMUON][isbn];
};





struct DataMenu {
	char label[MAX_LABEL_LENGTH];
	char parent_label[MAX_LABEL_LENGTH];
	void(*enter)();
	int permission;
};

struct Menu {
	Menu *parent;
	Menu **children;	//su dung pointer de do~ lang phi khi Node thuc thi chuc nang => ko co con
	int n_of_children;
	DataMenu *data;
};

struct MainMenu {
	Menu *root;
};


User login_user;


void XuatThongTinNguoi(ThongTinNguoi &t) {
	printf("Ho ten: %s\n", t.Ho_Ten.key);

	printf("Ngay sinh: %d/%d/%d\n", t.DoB.ngay, t.DoB.thang, t.DoB.nam);

	printf("So CMND: %s\n", t.CMND.key);

	printf("Dia chi: %s\n", t.DiaChi);

	printf("Gioi tinh: ");
	if (t.GioiTinh)
		printf("Nam\n");
	else
		printf("Nu\n");

}

void NhapNgay(Time &date) {
	scanf_s("%d %d %d", &date.ngay, &date.thang, &date.nam);
	while (getchar() != '\n');
}

void nhapHoTen(ThongTinNguoi &input)
{
	printf("Nhap ho ten:  ");
	gets_s(input.Ho_Ten.key);
}

void nhapNgaySinh(ThongTinNguoi &input)
{
	printf("Nhap ngay/thang/nam sinh:  ");
	NhapNgay(input.DoB);
}

void nhapCMND(ThongTinNguoi &input)
{
	printf("Nhap so CMND:  ");
	gets_s(input.CMND.key);
}

void nhapDiaChi(ThongTinNguoi &input)
{
	printf("Nhap dia chi:  ");
	gets_s(input.DiaChi);
}

void NhapThongTinNguoi(ThongTinNguoi &t) {
	
	nhapHoTen(t);
	nhapNgaySinh(t);
	nhapCMND(t);
	nhapDiaChi(t);

	printf("Nhap gioi tinh (1 = Nam, 0 = Nu):  ");
	scanf_s("%d", &t.GioiTinh);
}

template <class Type>
int compareString(Type &key, Type &input)
{
	return strcmp(key.key, input.key);
}


/*
bool NamNhuan(int &t) {
	+if (t % 400 == 0) {
		+return true;
		+
	}
	+else if (t % 100 == 0) {
		+return false;
		+
	}
	+else if (t % 4 == 0) {
		+return true;
		+
	}
	+else {
		+return false;
		+
	}
	+
}
+
+int KhoangCach2Time(Time &a, Time &b) {
	+int dif = 0;
	+int NgayTrongThang[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	+dif += NgayTrongThang[a.thang - 1] - a.ngay + 1;
	+dif += b.ngay;
	+if (a.nam == b.nam) {
		+if (NamNhuan(a.nam))
			+ NgayTrongThang[1]++;
		+for (int i = a.thang; i < b.thang - 1; i++)
			+ dif += NgayTrongThang[i];
		+
	}
	+else {
		+int yr_dif = b.nam - a.nam;
		+for (int i = a.nam + 1; i <= b.nam; i++) {
			+if (NamNhuan(i))
				+ dif += 366;
			+else dif += 365;
			+
		}
		+a.nam = b.nam;
		+if (NamNhuan(a.nam))
			+ NgayTrongThang[1]++;
		+for (int i = a.thang; i < b.thang - 1; i++)
			+ dif += NgayTrongThang[i];
		+
	}
	+printf("So ngay chenh lenh: %d", dif);
	+return dif;
	+
}*/