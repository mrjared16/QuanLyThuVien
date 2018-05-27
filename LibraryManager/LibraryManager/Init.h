#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NOT_FOUND -1
#define FILE_NOT_FOUND -2

//khai bao chung
#define MALE 1
#define FEMALE 0

#define MAX_LABEL_LENGTH 40
#define MSSV_LENGTH 8

#define isbn 14


//user
#define MEMBER 1
#define MODERATOR 2
#define ADMIN 3

#define ACTIVE 1
#define BLOCKED 0


//phieu muon sach
#define READER_EXPDATE 730	//day

#define MAX_SACH_MUON 5
#define MAX_TIME_MUON 7

#define PHAT_QUAHAN 5000
#define PHAT_MATSACH 2


#define AUTHEN "res/user.bin"
#define USER_DATA "res/user_data.bin"

#define SACH "res/book.bin"
#define ISBN_SACH "res/book_isbn.bin"
#define TEN_SACH "res/book_name.bin"

#define DOCGIA "res/docgia.bin"
#define IDCARD_DOCGIA "res/docgia_icn.bin"
#define HOTEN_DOCGIA "res/docgia_name.bin"
#define ID_DOCGIA "res/docgia_id.bin"


#define PHIEUMUON "res/dsphieumuon.bin"
#define PHIEUTRA "res/dsphieutra.bin"
#define READERID_PHIEUMUON "res/dsphieumuon_rid.bin"



// dd/mm/yyyy
struct Time {
	int ngay;
	int thang;
	int nam;
};

//username -> password
struct Authentication {
	char usr[20];
	char pwrd[20];
};

struct HoTen {
	char key[50];
};

struct IdentityCardNumber {
	char key[10];
};

struct ISBN {
	char key[isbn];
};

struct BookName {
	char key[100];
};

struct ReaderID {
	char key[MSSV_LENGTH];// MSSV: 7 ki tu
};


//ten -> DoB -> CMND -> diachi -> gioi tinh
struct ThongTinNguoi {
	HoTen Ho_Ten;
	Time DoB;
	IdentityCardNumber CMND;
	char DiaChi[200];
	char GioiTinh;  //1 = Nam, 0 = Nu
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
	ReaderID MaDocGia;
	
	ThongTinNguoi info;
	Time NgayDangKy;
	Time NgayHetHan;
	
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
	ReaderID MaDocGia;

	Time NgayMuon;
	Time NgayTraDK;

	int soluong_sach;
	ISBN DanhSachISBN[MAX_SACH_MUON];
};


struct PhieuTraSach {
	PhieuMuonSach phieu_muon;
	Time NgayTraThucTe;
	
	int so_sach_bimat;
	ISBN ISBN_sach_bimat[MAX_SACH_MUON];
	// tien phat = (ngay tre) * 5000 + sach(ISBN_sach_bi_mat[i]).giaSach (i = 0..so_sach_bimat)
	// ngay tre = ngayTraThucTe - ngayMuon - 7
	int tien_phat; 
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


template <class Type>
int compareStringField(Type &key, Type &input)
{
	return strcmp(key.key, input.key);
}


template <class Type>
void inputStringField(Type &input)
{
	gets_s(input.key);
}
