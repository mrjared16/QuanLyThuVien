#pragma once
#include <stdio.h>
#include <string.h>
#include "Functions.h"
#include "Init.h"

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

void findReaderbyIdentityCardNumber()
{
	IdentityCardNumber CMND;
	printf("Nhap CMND can tim: ");
	gets_s(CMND.key);

	int search_result = binarySearch<IdentityCardNumber, Record<IdentityCardNumber>>(CMND, compareString<IdentityCardNumber>, IDCARD_DOCGIA);
	
	if (search_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s\n", IDCARD_DOCGIA);
		return;
	}

	if (search_result == NOT_FOUND)
	{
		printf("Khong tim thay doc gia!\n");
		return;
	}

	Record<IdentityCardNumber> record_result;
	getRecord(record_result, search_result, IDCARD_DOCGIA);

	TheDocGia docgia_result;
	getRecord(docgia_result, record_result.index, DOCGIA);

	printf("\nTim thay doc gia!\n\n");
	XuatThongTinDocGia(docgia_result);
}


void findReaderbyName()
{
	HoTen Ho_Ten;
	printf("Nhap ten doc gia can tim: ");
	gets_s(Ho_Ten.key);

	int search_result = binarySearch<HoTen, Record<HoTen>>(Ho_Ten, compareString<HoTen>, HOTEN_DOCGIA);

	if (search_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s\n", HOTEN_DOCGIA);
		return;
	}

	if (search_result == NOT_FOUND)
	{
		printf("Khong tim thay doc gia!\n");
		return;
	}

	Record<HoTen> record_result;
	getRecord(record_result, search_result, HOTEN_DOCGIA);

	TheDocGia docgia_result;
	getRecord(docgia_result, record_result.index, DOCGIA);

	printf("\nTim thay doc gia!\n\n");
	XuatThongTinDocGia(docgia_result);
}


void addReader()
{
	int index = getNumberRecords<TheDocGia>(DOCGIA);

	TheDocGia docgia;

	NhapThongTinDocGia(docgia);

	int insert_CMND_location = -1, insert_HoTen_location = -1;

	int search_CMND_result = binarySearch<IdentityCardNumber, Record<IdentityCardNumber>>
		(docgia.info.CMND, compareString<IdentityCardNumber>, IDCARD_DOCGIA, &insert_CMND_location);

	int search_HoTen_result = binarySearch<HoTen, Record<HoTen>>
		(docgia.info.Ho_Ten, compareString<HoTen>, HOTEN_DOCGIA, &insert_HoTen_location);

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
