#pragma once
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "Functions.h"
#include "Init.h"

TheDocGia docgia;
Record<HoTen> name_record;
Record<IdentityCardNumber> icn_record;

bool reader_stop = false;

void reader_cancel() {
	reader_stop = true;
}

extern void runCustomMenu(const char *MSG, const char *label[], void(*func[])(), int n);


bool checkReaderFile(TheDocGia &a, TheDocGia &tmp)
{
	if (compareStringField(a.info.CMND, tmp.info.CMND) == 0)
		return true;

	return false;
}


void changeReaderID()
{
	printf("Nhap ma doc gia moi: ");
	gets_s(docgia.MaDocGia);
}

void changeReaderName()
{
	nhapHoTen(docgia.info);
}

void changeReaderDoB()
{
	nhapNgaySinh(docgia.info);
}

void changeReaderAddress()
{
	nhapDiaChi(docgia.info);
}


void NhapThongTinDocGia(TheDocGia &t) {
	printf("Nhap ma doc gia:  ");
	gets_s(t.MaDocGia);
	NhapThongTinNguoi(t.info);
	printf("Nhap ngay het han:  ");
	NhapNgay(t.NgayHetHan);
	//printf("\n");
	
}

void XuatThongTinDocGia(TheDocGia &t) {
	printf("Ma doc gia: %s\n", t.MaDocGia);
	XuatThongTinNguoi(t.info);
	printf("Ngay het han: %d/%d/%d\n", t.NgayHetHan.ngay, t.NgayHetHan.thang, t.NgayHetHan.nam);
	
}


void printReader(TheDocGia &reader, int stt)
{
	printf("%d/ ", stt);
	XuatThongTinDocGia(reader);
	printf("\n");
}

void printAllReaders() {
	
	int result = printAllRecords(DOCGIA, printReader);
	if (result == 0)
	{
		printf("Chua co doc gia nao!\n");
		return;
	}

	if (result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s\n", DOCGIA);
		return;
	}
}


void searchICNmsg() {
	printf("Nhap CMND can tim: ");
}

void searchNameMsg() {
	printf("Nhap ten doc gia can tim: ");
}

void notFoundReaderMsg() {
	printf("Khong tim thay doc gia!\n");

}


void searchReaderbyIdentityCardNumber()
{
	if (searchObjectbyField<IdentityCardNumber, TheDocGia>
		(docgia, DOCGIA, icn_record, IDCARD_DOCGIA, searchICNmsg, inputStringField, notFoundReaderMsg))
	{
		printf("\nTim thay doc gia!\n\n");
		XuatThongTinDocGia(docgia);
	}
}

void searchReaderbyName()
{
	if (searchObjectbyField<HoTen, TheDocGia>
		(docgia, DOCGIA, name_record, HOTEN_DOCGIA, searchNameMsg, inputStringField, notFoundReaderMsg))
	{
		printf("\nTim thay doc gia!\n\n");
		XuatThongTinDocGia(docgia);
	}
}


bool getReaderbyICN() {
	if (!searchObjectbyField<IdentityCardNumber, TheDocGia>
		(docgia, DOCGIA, icn_record, IDCARD_DOCGIA, searchICNmsg, inputStringField, notFoundReaderMsg))
	{
		return false;
	}

	int search_result = binarySearch<HoTen, Record<HoTen>>
		(docgia.info.Ho_Ten, compareStringField<HoTen>, HOTEN_DOCGIA);
	if (search_result == NOT_FOUND || search_result == FILE_NOT_FOUND)
	{
		printf("Xay ra loi!\n");
		return false;
	}

	getRecord(name_record, search_result, HOTEN_DOCGIA);
	return true;
}

bool getReaderbyName()
{
	if (!searchObjectbyField<HoTen, TheDocGia>
		(docgia, DOCGIA, name_record, HOTEN_DOCGIA, searchNameMsg, inputStringField, notFoundReaderMsg))
	{
		return false;
	}

	int search_result = binarySearch<IdentityCardNumber, Record<IdentityCardNumber>>
		(docgia.info.CMND, compareStringField<IdentityCardNumber>, IDCARD_DOCGIA);
	if (search_result == NOT_FOUND || search_result == FILE_NOT_FOUND)
	{
		printf("Xay ra loi!\n");
		return false;
	}

	getRecord(icn_record, search_result, IDCARD_DOCGIA);
	return true;
}


void updateReaderInfo() {
	//update
	updateField(icn_record, docgia.info.CMND, IDCARD_DOCGIA);
	updateField(name_record, docgia.info.Ho_Ten, HOTEN_DOCGIA);
	editRecord(docgia, name_record.index, DOCGIA);

}


void changeReaderInfo()
{
	system("cls");
	XuatThongTinDocGia(docgia);

	const char *label[] = { "Thay doi ma doc gia", "Thay doi ho ten", "Thay doi ngay sinh", "Thay doi dia chi", "Huy chinh sua"};
	void(*func[])() = { changeReaderID, changeReaderName, changeReaderDoB, changeReaderAddress, reader_cancel };

	runCustomMenu(NULL, label, func, 5);
	
	updateReaderInfo();

	if (reader_stop)
	{
		reader_stop = false;
		return;
	}
	printf("\nChinh sua thong tin thanh cong!\n\n");
	printf("Nhan phim bat ky de tiep tuc!\n");

	_getch();
	
	changeReaderInfo();

}

void deleteReader()
{
	XuatThongTinDocGia(docgia);

	const char *label[] = { "Dong y", "Huy" };
	void(*func[])() = { NULLFunction, reader_cancel };

	runCustomMenu("Ban co chac chan muon xoa doc gia nay? \n", label, func, 2);

	if (reader_stop)
	{
		reader_stop = false;
		return;
	}
	//delete
	deleteRecord(icn_record, IDCARD_DOCGIA, checkIndexFile);
	deleteRecord(name_record, HOTEN_DOCGIA, checkIndexFile);
	deleteRecord(docgia, DOCGIA, checkReaderFile);

	printf("Xoa thanh cong!\n");
}


void changeReaderInfobyICN() {

	if (!getReaderbyICN())
		return;
	changeReaderInfo();
}

void changeReaderInfobyName() {

	if (!getReaderbyName())
		return;

	changeReaderInfo();
}


void deleteReaderbyICN() {

	if (!getReaderbyICN())
		return;
	deleteReader();
}

void deleteReaderbyName() {

	if (!getReaderbyName())
		return;
	deleteReader();
}


void addReader()
{
	int index = getNumberRecords<TheDocGia>(DOCGIA);

	TheDocGia new_docgia;

	NhapThongTinDocGia(new_docgia);

	int insert_CMND_location = -1, insert_HoTen_location = -1;

	int search_CMND_result = binarySearch<IdentityCardNumber, Record<IdentityCardNumber>>
		(new_docgia.info.CMND, compareStringField<IdentityCardNumber>, IDCARD_DOCGIA, &insert_CMND_location);

	int search_HoTen_result = binarySearch<HoTen, Record<HoTen>>
		(new_docgia.info.Ho_Ten, compareStringField<HoTen>, HOTEN_DOCGIA, &insert_HoTen_location);

	if (search_CMND_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s", IDCARD_DOCGIA);
		return;
	}
	if (search_HoTen_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s", HOTEN_DOCGIA);
		return;
	}
	if (search_CMND_result != NOT_FOUND)
	{
		printf("Doc gia da ton tai!\n");
		return;
	}

	Record<IdentityCardNumber> CMND_record;
	strcpy_s(CMND_record.record_key.key, new_docgia.info.CMND.key);
	CMND_record.index = index;

	Record<HoTen> HoTen_record;
	strcpy_s(HoTen_record.record_key.key, new_docgia.info.Ho_Ten.key);
	HoTen_record.index = index;

	if (insertRecord(CMND_record, insert_CMND_location, IDCARD_DOCGIA) &&
		insertRecord(HoTen_record, insert_HoTen_location, HOTEN_DOCGIA) &&
		addRecord(new_docgia, DOCGIA))
		printf("Them doc gia thanh cong!\n");
	else
		printf("Them doc gia that bai!\n");
}
