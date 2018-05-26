
#pragma once
#include <stdio.h>
#include <string.h>
#include "Functions.h"
#include "Init.h"

Sach sach;
Record<BookName> book_name_record;
Record<ISBN> isbn_record;

bool book_stop = false;

void book_cancel() {
	book_stop = true;
}

extern void runCustomMenu(const char *MSG, const char *label[], void(*func[])(), int n);

void changeBookName() {
	printf("Nhap ten sach:  ");
	gets_s(sach.TenSach.key);
}

void changeBookAuthor() {
	printf("Nhap tac gia:  ");
	gets_s(sach.TacGia);
}

void changeNhaXuatBan() {
	printf("Nhap NXB:  ");
	gets_s(sach.NXB);
}

void changeNamXB() {
	printf("Nhap nam xuat ban:  ");
	gets_s(sach.NamXB);
}

void changeTheLoai() {
	printf("Nhap the loai:  ");
	gets_s(sach.TheLoai);
}

void changeGiaSach() {
	printf("Nhap gia sach:  ");
	scanf_s(" %d", &sach.GiaSach);
}

void changeSoLuongSach() {
	printf("Nhap so luong:  ");
	scanf_s(" %d", &sach.SoLuong);
}

bool checkBookFile(Sach &a,Sach &tmp)
{
	if (compareStringField(a.book_ISBN, tmp.book_ISBN) == 0)
		return true;

	return false;
}



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



void searchISBNmsg() {
	printf("Nhap ISBN can tim: ");
}

void searchBookNameMsg() {
	printf("Nhap ten sach can tim: ");
}

void notFoundBookMsg() {
	printf("Khong tim thay sach!\n");

}



void searchBookbyISBN()
{
	if (searchObjectbyField<ISBN, Sach>
		(sach, SACH, isbn_record, ISBN_SACH, searchISBNmsg, inputStringField, notFoundBookMsg))
	{
		printf("\nTim thay sach!\n\n");
		XuatSach(sach);
	}
}

void searchBookbyName()
{
	if (searchObjectbyField<BookName, Sach>
		(sach, SACH, book_name_record, TEN_SACH, searchBookNameMsg, inputStringField, notFoundBookMsg))
	{
		printf("\nTim thay sach!\n\n");
		XuatSach(sach);
	}
}



bool getBookbyISBN() {
	if (!searchObjectbyField<ISBN, Sach>
		(sach, SACH, isbn_record, ISBN_SACH, searchISBNmsg, inputStringField, notFoundBookMsg))
	{
		return false;
	}

	int search_result = binarySearch<BookName, Record<BookName>>
		(sach.TenSach, compareStringField<BookName>, TEN_SACH);
	if (search_result == NOT_FOUND || search_result == FILE_NOT_FOUND)
	{
		printf("Xay ra loi!\n");
		return false;
	}

	getRecord(book_name_record, search_result, TEN_SACH);
	return true;
}

bool getBookbyName()
{
	if (!searchObjectbyField<BookName, Sach>
		(sach, SACH, book_name_record, TEN_SACH, searchBookNameMsg, inputStringField, notFoundBookMsg))
	{
		return false;
	}

	int search_result = binarySearch<ISBN, Record<ISBN>>
		(sach.book_ISBN, compareStringField<ISBN>, ISBN_SACH);
	if (search_result == NOT_FOUND || search_result == FILE_NOT_FOUND)
	{
		printf("Xay ra loi!\n");
		return false;
	}

	getRecord(isbn_record, search_result, ISBN_SACH);
	return true;
}



void updateBookInfo() {
	//update
	updateField(isbn_record, sach.book_ISBN, ISBN_SACH);
	updateField(book_name_record, sach.TenSach, TEN_SACH);
	editRecord(sach, book_name_record.index, SACH);

}



void changeBookInfo()
{
	system("cls");
	XuatSach(sach);

	const char *label[] = { "Thay doi ten sach", "Thay doi tac gia", "Thay doi nha xuat ban",
		"Thay doi nam xuat ban", "Thay doi the loai", "Thay doi gia sach", "Thay doi so luong sach", "Huy chinh sua" };
	void(*func[])() = { changeBookName, changeBookAuthor, changeNhaXuatBan,
		changeNamXB, changeTheLoai, changeGiaSach, changeSoLuongSach, book_cancel };

	runCustomMenu(NULL, label, func, 8);

	updateBookInfo();

	if (book_stop)
	{
		book_stop = false;
		return;
	}
	printf("\nChinh sua thong tin thanh cong!\n\n");
	printf("Nhan phim bat ky de tiep tuc!\n");

	_getch();

	changeBookInfo();

}

void deleteBook()
{
	XuatSach(sach);

	const char *label[] = { "Dong y", "Huy" };
	void(*func[])() = { NULLFunction, book_cancel };

	runCustomMenu("Ban co chac chan muon xoa sach nay? \n", label, func, 2);

	if (book_stop)
	{
		book_stop = false;
		return;
	}
	//delete
	deleteRecord(isbn_record, ISBN_SACH, checkIndexFile);
	deleteRecord(book_name_record, TEN_SACH, checkIndexFile);
	deleteRecord(sach, SACH, checkBookFile);

	printf("Xoa thanh cong!\n");
}



void changeBookInfobyISBN() {

	if (!getBookbyISBN())
		return;
	changeBookInfo();
}

void changeBookInfobyName() {

	if (!getBookbyName())
		return;

	changeBookInfo();
}



void deleteBookbyISBN() {

	if (!getBookbyISBN())
		return;
	deleteBook();
}

void deleteBookbyName() {

	if (!getBookbyName())
		return;
	deleteBook();
}



void addBook()
{
	int index = getNumberRecords<Sach>(SACH);

	Sach sach;

	NhapSach(sach);

	int insert_ISBN_location = -1, insert_BookName_location = -1;

	int search_ISBN_result = binarySearch<ISBN, Record<ISBN>>
		(sach.book_ISBN, compareStringField<ISBN>, ISBN_SACH, &insert_ISBN_location);

	int search_BookName_result = binarySearch<BookName, Record<BookName>>
		(sach.TenSach, compareStringField<BookName>, TEN_SACH, &insert_BookName_location);

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


