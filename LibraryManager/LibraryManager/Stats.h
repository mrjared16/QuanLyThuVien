#pragma once
#include <stdio.h>
#include <string.h>
#include "Init.h"
#include "Functions.h"



void thongKeSach()
{
	int n = getNumberRecords<Sach>(SACH);

	if (n == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s!\n", SACH);
		return;
	}
	
	printf("So luong sach thu vien dang co: %d\n", n);
}

bool matchTheLoai(Sach &record, char *theloai)
{
	return (strcmp(record.TheLoai, theloai) == 0);
}

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

	int result = countRecord(the_loai, SACH, matchTheLoai);

	printf("Thu vien dang co %d sach the loai \"%s\" tren %d sach.\n", result, the_loai, n);
}



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

bool matchGioiTinh(TheDocGia &record, int *gioitinh)
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

	int gioitinh;
	printf("Nhap gioi tinh can tim (1 = Nam, 0 = Nu):  ");
	scanf_s("%d", &gioitinh);

	int result = countRecord(&gioitinh, DOCGIA, matchGioiTinh);

	printf("Thu vien dang co %d doc gia %s tren tong so %d doc gia.\n", result, gioitinh == MALE ? "nam" : "nu", n);
}