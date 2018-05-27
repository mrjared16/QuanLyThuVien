#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//** FILE
#define NOT_FOUND -1
#define FILE_NOT_FOUND -2

//** CHUNG
#define MALE 1
#define FEMALE 0

#define MAX_LABEL_LENGTH 40	//do dai toi da cua ten menu
#define MSSV_LENGTH 8		//do dai toi da cua ma doc gia
#define MAX_NAME_LENGTH 50
#define MAX_BOOKNAME_LENGTH 50
#define CMND_LENGTH 10

//** SACH
#define isbn 14		//do dai cua isbn = 13 (tinh them NULL)


//** USER

//quyen user
#define MEMBER 1
#define MODERATOR 2
#define ADMIN 3

//trang thai user
#define ACTIVE 1
#define BLOCKED 0


//** PHIEU MUON SACH

//thoi gian cua the doc gia
#define READER_EXPDATE 730	//day

//muon toi da 5 cuon trong vong 7 ngay
#define MAX_SACH_MUON 5
#define MAX_TIME_MUON 7

//qua han dong 5000/ngay; mat sach den 2 lan tien sach
#define PHAT_QUAHAN 5000
#define PHAT_MATSACH 2

//** TEN FILE

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



//bieu dien ngay thang nam
// dd/mm/yyyy
struct Time {
	int ngay;
	int thang;
	int nam;
};

//thong tin dang nhap, gom ten dang nhap va mat khau
//username -> password
struct Authentication {
	char usr[20];
	char pwrd[20];
};


//** CAC KIEU DU LIEU DUNG DE TIM KIEM
struct HoTen {
	char key[50];
};

// so CMND
struct IdentityCardNumber {
	char key[10];
};

// ma isbn
struct ISBN {
	char key[isbn];
};

// ten sach
struct BookName {
	char key[100];
};

//ma doc gia
struct ReaderID {
	char key[8];// MSSV: 7 ki tu
};


// thong tin ca nhan
//ten -> DoB -> CMND -> diachi -> gioi tinh
struct ThongTinNguoi {
	HoTen Ho_Ten;
	Time DoB;
	IdentityCardNumber CMND;
	char DiaChi[200];
	int GioiTinh;  //1 = Nam, 0 = Nu
};

// thong tin nguoi dung
//id -> username -> info -> active -> permission
struct User {
	int id;
	char usr[20];
	ThongTinNguoi info;
	int Active; // 1 = activated, 0 = blocked
	int permission;
};

// thong tin the doc gia
//madocgia (MSSV) -> info -> ngayhethan
struct TheDocGia {
	ReaderID MaDocGia;
	ThongTinNguoi info;
	Time NgayDangKy, NgayHetHan;
};

// thong tin sach
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

// thong tin phieu muon
struct PhieuMuonSach {
	ReaderID MaDocGia;

	Time NgayMuon;
	Time NgayTraDK;

	int soluong_sach;
	ISBN DanhSachISBN[MAX_SACH_MUON];
};

// thong tin phieu tra
struct PhieuTraSach {
	PhieuMuonSach phieu_muon;
	Time NgayTraThucTe;
	
	int so_sach_bimat;
	ISBN ISBN_sach_bimat[MAX_SACH_MUON];
	// tien phat = (ngay tre) * 5000 + sach(ISBN_sach_bi_mat[i]).giaSach (i = 0..so_sach_bimat)
	// ngay tre = ngayTraThucTe - ngayMuon - 7
	int tien_phat; 
};


// thong tin function menu
struct DataMenu {
	char label[MAX_LABEL_LENGTH];
	char parent_label[MAX_LABEL_LENGTH];
	void(*enter)();
	int permission;
};

// cau truc cua menu: cau truc cay
struct Menu {
	Menu *parent;
	Menu **children;	//su dung pointer de do~ lang phi khi Node thuc thi chuc nang => ko co con
	int n_of_children;
	DataMenu *data;
};

struct MainMenu {
	Menu *root;
};


//ham nhap ngay
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

//ham nhap thong tin ca nhan cua user/ doc gia
void NhapThongTinNguoi(ThongTinNguoi &t) {
	
	nhapHoTen(t);
	nhapNgaySinh(t);
	nhapCMND(t);
	nhapDiaChi(t);

	printf("Nhap gioi tinh (1 = Nam, 0 = Nu):  ");
	scanf_s("%d", &t.GioiTinh);
}

//ham xuat thong tin ca nhan cua user/ doc gia
void XuatThongTinNguoi(ThongTinNguoi &t) {
	printf("Ho ten: %s\n", t.Ho_Ten.key);

	printf("Ngay sinh: %d/%d/%d\n", t.DoB.ngay, t.DoB.thang, t.DoB.nam);

	printf("So CMND: %s\n", t.CMND.key);

	printf("Dia chi: %s\n", t.DiaChi);

	printf("Gioi tinh: ");
	if (t.GioiTinh == MALE)
		printf("Nam\n");
	else
		printf("Nu\n");

}

