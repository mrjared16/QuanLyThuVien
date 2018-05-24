#pragma once
#include <stdio.h>
#include <string.h>
#include "Functions.h"
#include "Init.h"


template<class T>
bool check1(T &a, T&tmp)
{
	if (compareStringField(a.info.CMND, tmp.info.CMND) == 0)
		return true;

	return false;
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
	TheDocGia result;
	Record<IdentityCardNumber> icn_result;
	if (searchObjectbyField<IdentityCardNumber, TheDocGia>
		(result, DOCGIA, icn_result, IDCARD_DOCGIA, searchICNmsg, inputStringField, notFoundReaderMsg))
	{
		printf("\nTim thay doc gia!\n\n");
		XuatThongTinDocGia(result);
	}
}


void searchReaderbyName()
{
	TheDocGia result;
	Record<HoTen> name_result;
	if (searchObjectbyField<HoTen, TheDocGia>
		(result, DOCGIA, name_result, HOTEN_DOCGIA, searchNameMsg, inputStringField, notFoundReaderMsg))
	{
		printf("\nTim thay doc gia!\n\n");
		XuatThongTinDocGia(result);
	}
}



void chinhSuaThongTinDocGia() {
	TheDocGia docgia_result;
	Record<HoTen> record_result;
	Record<IdentityCardNumber> cmnd_record;

	if (!searchObjectbyField<HoTen, TheDocGia>
		(docgia_result, DOCGIA, record_result, HOTEN_DOCGIA, searchNameMsg, inputStringField, notFoundReaderMsg))
	{
		return;
	}
	printf("\nTim thay doc gia!\n\n");
	
	int search_result = binarySearch<IdentityCardNumber, Record<IdentityCardNumber>>
		(docgia_result.info.CMND, compareStringField<IdentityCardNumber>, IDCARD_DOCGIA);
	if (search_result == NOT_FOUND || search_result == FILE_NOT_FOUND)
	{
		printf("Xay ra loi!\n");
		return;
	}

	getRecord(cmnd_record, search_result, IDCARD_DOCGIA);
	
	//change info
	printf("Nhap CMND:  ");
	gets_s(docgia_result.info.CMND.key);
	printf("Nhap Ho Ten: ");
	gets_s(docgia_result.info.Ho_Ten.key);
	//end change info

	//update
	updateField(cmnd_record, docgia_result.info.CMND, IDCARD_DOCGIA);
	updateField(record_result, docgia_result.info.Ho_Ten, HOTEN_DOCGIA);
	editRecord(docgia_result, record_result.index, DOCGIA);
}

void xoaDocGia() {
	TheDocGia docgia_result;
	Record<HoTen> record_result;
	Record<IdentityCardNumber> cmnd_record;

	if (!searchObjectbyField<HoTen, TheDocGia>
		(docgia_result, DOCGIA, record_result, HOTEN_DOCGIA, searchNameMsg, inputStringField, notFoundReaderMsg))
	{
		return;
	}
	printf("\nTim thay doc gia!\n\n");

	int search_result = binarySearch<IdentityCardNumber, Record<IdentityCardNumber>>
		(docgia_result.info.CMND, compareStringField<IdentityCardNumber>, IDCARD_DOCGIA);
	if (search_result == NOT_FOUND || search_result == FILE_NOT_FOUND)
	{
		printf("Xay ra loi!\n");
		return;
	}
	getRecord(cmnd_record, search_result, IDCARD_DOCGIA);

	//delete
	deleteRecord(cmnd_record, IDCARD_DOCGIA, checkIndexFile);
	deleteRecord(record_result, HOTEN_DOCGIA, checkIndexFile);
	deleteRecord(docgia_result, DOCGIA, check1);
}


void addReader()
{
	int index = getNumberRecords<TheDocGia>(DOCGIA);

	TheDocGia docgia;

	NhapThongTinDocGia(docgia);

	int insert_CMND_location = -1, insert_HoTen_location = -1;

	int search_CMND_result = binarySearch<IdentityCardNumber, Record<IdentityCardNumber>>
		(docgia.info.CMND, compareStringField<IdentityCardNumber>, IDCARD_DOCGIA, &insert_CMND_location);

	int search_HoTen_result = binarySearch<HoTen, Record<HoTen>>
		(docgia.info.Ho_Ten, compareStringField<HoTen>, HOTEN_DOCGIA, &insert_HoTen_location);

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
	strcpy_s(CMND_record.record_key.key, docgia.info.CMND.key);
	CMND_record.index = index;

	Record<HoTen> HoTen_record;
	strcpy_s(HoTen_record.record_key.key, docgia.info.Ho_Ten.key);
	HoTen_record.index = index;

	if (insertRecord(CMND_record, insert_CMND_location, IDCARD_DOCGIA) &&
		insertRecord(HoTen_record, insert_HoTen_location, HOTEN_DOCGIA) &&
		addRecord(docgia, DOCGIA))
		printf("Them doc gia thanh cong!\n");
	else
		printf("Them doc gia that bai!\n");
}
