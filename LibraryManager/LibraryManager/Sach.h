
#pragma once
#include <stdio.h>
#include <string.h>
#include "Functions.h"
#include "Init.h"

void NhapSach(Sach &t) {
	printf("Nhap ma ISBN:  ");
	gets_s( t.book_ISBN.key);
	printf("Nhap ten sach:  ");
	gets_s(t.TenSach.key);
	printf("Nhap tac gia:  ");
	gets_s( t.TacGia);
	printf("Nhap NXB:  ");
	gets_s( t.NXB);
	printf("Nhap nam xuat ban:  ");
	gets_s( t.NamXB);
	printf("Nhap the loai:  ");
	gets_s( t.TheLoai);
	printf("Nhap gia sach:  ");
	scanf_s(" %d", &t.GiaSach);
	printf("Nhap so luong:  ");
	scanf_s(" %d", &t.SoLuong);
	
}

void XuatSach(Sach &t) {
	printf("Ma ISBN: %s\n", t.book_ISBN.key);
	printf("Ten sach: %s\n", t.TenSach.key);
	printf("Tac gia: %s\n", t.TacGia);
	printf("NXB: %s\n", t.NXB);
	printf("Nam xuat ban: %s\n", t.NamXB);
	printf("The loai: %s\n", t.TheLoai);
	printf("Gia sach: %d\n", t.GiaSach);
	printf("So luong: %d\n", t.SoLuong);
	
}

void printBook(Sach &reader, int stt)
{
	printf("%d/ ", stt);
	XuatSach(reader);
	printf("\n");
}

void printAllBooks() {

	int result = printAllRecords(SACH, printBook);
	if (result == 0)
	{
		printf("Chua co quyen sach nao!\n");
		return;
	}

	if (result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s\n", SACH);
		return;
	}
}

void findBookbyISBN()
{
	ISBN book_ISBN;
	printf("Nhap ISBN can tim: ");
	gets_s(book_ISBN.key);

	int search_result = binarySearch<ISBN, Record<ISBN>>(book_ISBN, compareString<ISBN>, ISBN_SACH);

	if (search_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s\n", ISBN_SACH);
		return;
	}

	if (search_result == NOT_FOUND)
	{
		printf("Khong tim thay sach!\n");
		return;
	}

	Record<ISBN> record_result;
	getRecord(record_result, search_result, ISBN_SACH);

	Sach sach_result;
	getRecord(sach_result, record_result.index, SACH);

	printf("\nTim thay sach!\n\n");
	XuatSach(sach_result);
}


void findBookbyName()
{
	BookName Ho_Ten;
	printf("Nhap ten sach can tim: ");
	gets_s(Ho_Ten.key);

	int search_result = binarySearch<BookName, Record<BookName>>(Ho_Ten, compareString<BookName>, TEN_SACH);

	if (search_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s\n", TEN_SACH);
		return;
	}

	if (search_result == NOT_FOUND)
	{
		printf("Khong tim thay sach!\n");
		return;
	}

	Record<BookName> record_result;
	getRecord(record_result, search_result, TEN_SACH);

	Sach sach_result;
	getRecord(sach_result, record_result.index, SACH);

	printf("\nTim thay sach!\n\n");
	XuatSach(sach_result);
}

void addBook()
{
	int index = getNumberRecords<Sach>(SACH);

	Sach sach;

	NhapSach(sach);

	int insert_ISBN_location = -1, insert_BookName_location = -1;

	int search_ISBN_result = binarySearch<ISBN, Record<ISBN>>
		(sach.book_ISBN, compareString<ISBN>, ISBN_SACH, &insert_ISBN_location);

	int search_BookName_result = binarySearch<BookName, Record<BookName>>
		(sach.TenSach, compareString<BookName>, TEN_SACH, &insert_BookName_location);

	if (search_ISBN_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s", ISBN_SACH);
		return;
	}
	if (search_BookName_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s", TEN_SACH);
		return;
	}
	if (search_ISBN_result != NOT_FOUND)
	{
		printf("Sach da ton tai!\n");
		return;
	}

	Record<ISBN> ISBN_record;
	strcpy_s(ISBN_record.record_key.key, sach.book_ISBN.key);
	ISBN_record.index = index;

	Record<BookName> BookName_record;
	strcpy_s(BookName_record.record_key.key, sach.TenSach.key);
	BookName_record.index = index;

	if (insertRecord(ISBN_record, insert_ISBN_location, ISBN_SACH) &&
		insertRecord(BookName_record, insert_BookName_location, TEN_SACH) &&
		addRecord(sach, SACH))
		printf("Them sach thanh cong!\n");
	else
		printf("Them sach that bai!\n");
}
