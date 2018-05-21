#pragma once

#define MAX_SACHMUON 100

#define isbn 13

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
#define IDCARD "IDCARD_docgia.bin"
#define HOTEN "name_docgia.bin"

#define NOT_FOUND -1
#define FILE_NOT_FOUND -2

// dd/mm/yyyy
struct Time {
	char ngay;
	char thang;
	int nam;
};

//ten -> DoB -> CMND -> diachi -> gioi tinh
struct ThongTinNguoi {
	char HoTen[50];
	Time DoB;
	char CMND[10];
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

//isbn -> ten -> tacgia -> NXB -> theloai -> giasach -> soluong
struct Sach {
	char ISBN[isbn]; // en.wikipedia.org/ISBN

	char TenSach[100];
	char TacGia[50];
	char NXB[50];

	char NamXB[4];

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
	char DanhSachISBN[MAX_SACHMUON][isbn];
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
