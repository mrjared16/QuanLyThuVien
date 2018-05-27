#pragma once
#include <stdio.h>
#include <string.h>

#include "Init.h"
#include "Functions.h"
#include "PhieuMuonTraSach.h"

bool countBook(Sach &sach, int &count)
{
	count += sach.SoLuong;
	return true;
}

//Ham thong ke so luong sach co trong thu vien
void thongKeSach()
{
	int n = getNumberRecords<Sach>(SACH);

	if (n == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s!\n", SACH);
		return;
	}
	
	int loai = countRecord<Sach>(SACH, countBook);
	printf("So luong sach thu vien dang co: %d\n", n);
	printf("So luong tong cong: %d\n", loai);
}


//check xem sach co dung the loai can tim hay khong
bool checkTheLoai(Sach &record, char *theloai)
{
	return (strcmp(record.TheLoai, theloai) == 0);
}

//Ham thong ke sach theo the loai dc nhap tu ban phim
void thongKeSachTheoTheLoai()
{
	int n = getNumberRecords<Sach>(SACH);

	if (n == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s!\n", SACH);
		return;
	}

	if (n == 0)
	{
		printf("Thu vien chua co quyen sach nao\n");
		return;
	}

	char the_loai[20];
	printf("Nhap the loai can thong ke: ");
	gets_s(the_loai);

	int result = countRecord(the_loai, SACH, checkTheLoai);

	printf("Thu vien dang co %d sach the loai \"%s\" tren %d sach.\n", result, the_loai, n);
}


//Ham thong ke so luong doc gia cua thu vien
void thongKeDocGia()
{
	int n = getNumberRecords<TheDocGia>(DOCGIA);

	if (n == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s!\n", DOCGIA);
		return;
	}

	printf("So luong doc gia cua thu vien: %d\n", n);
}


//Ham kiem tra xem doc gia co phai gioi tinh dang can tim hay khong
bool checkGioiTinh(TheDocGia &record, int *gioitinh)
{
	return (record.info.GioiTinh == *gioitinh);
}

void thongKeDocGiaTheoGioiTinh()
{
	int n = getNumberRecords<TheDocGia>(DOCGIA);

	if (n == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s!\n", DOCGIA);
		return;
	}

	if (n == 0)
	{
		printf("Thu vien chua co doc gia nao\n");
		return;
	}

	int gioitinh = MALE;
	int result = countRecord(&gioitinh, DOCGIA, checkGioiTinh);

	printf("Thu vien dang co %d doc gia:\n", n);
	printf("Nam: %d\n", result);
	printf("Nu:  %d\n", n - result);
}


//Ham thong ke so sach dang duoc muon
void thongKeSachDangMuon() {
	PhieuMuonSach t;
	int all = countRecord<Sach>(SACH, countBook);
	int sum = 0;
	FILE *f;
	fopen_s(&f, PHIEUMUON, "rb");
	while (!feof(f)) {
		if (fread(&t, sizeof(PhieuMuonSach), 1, f))
		{
			sum += t.soluong_sach;
		}
	}
	fclose(f);
	printf("So luong sach dang duoc muon la %d tren tong so %d sach trong thu vien.\n", sum, all);
}



//Ham thong ke so luong sach bi tre han
void thongKeTreHan() {
	PhieuMuonSach t;
	int all = getNumberRecords<PhieuMuonSach>(PHIEUMUON);
	int sum = 0;
	Time today;
	now(today);
	FILE *f;
	fopen_s(&f, PHIEUMUON, "rb");
	
	while (!feof(f)) {
		if (fread(&t, sizeof(PhieuMuonSach), 1, f)) {
			if (soNgayQuaHan(today, t.NgayMuon) > 0) {	//bi tre han (Ham o "PhieuMuonTraSach.h")
				if (sum == 0)
				{
					printf("Danh sach ma doc gia cua cac doc gia bi tre han: ");
				}
				sum++;
				printf("%d. %s\n", sum, t.MaDocGia.key);
			}
		}
	}
	fclose(f);

	printf("\nSo doc gia dang bi tre han la %d tren tong so %d doc gia dang muon sach.\n", sum, all);
}