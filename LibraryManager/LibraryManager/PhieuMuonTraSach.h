#pragma once

#include "Init.h"
#include "Sach.h"


void XuatPhieuMuonSach(PhieuMuonSach &t) {
	printf("Ma doc gia: %s\n", t.MaDocGia.key);
	printf("Ngay muon: %d/%d/%d\n", t.NgayMuon.ngay, t.NgayMuon.thang, t.NgayMuon.nam);
	printf("Ngay tra du kien: %d/%d/%d\n", t.NgayTraDK.ngay, t.NgayTraDK.thang, t.NgayTraDK.nam);
	printf("Ma ISBN cac sach muon muon:\n");
	int i = 0;
	for (int i = 0; i < t.soluong_sach; i++)
		printf("%d. %s\n", i + 1, &t.DanhSachISBN[i]);
}

void XuatPhieuTraSach(PhieuTraSach &t) {
	XuatPhieuMuonSach(t.phieu_muon);
	printf("Ngay tra thuc te: ");
	show(t.NgayTraThucTe);
	printf("\n");
	if (t.so_sach_bimat > 0)
	{

	}
	printf("So tien phat: %d\n", t.tien_phat);
}



void notFoundReaderID() {
	printf("Khong tim thay phieu muon! Ban phai muon sach!\n");
}

void input(ReaderID &tmp)
{
	gets_s(tmp.key);
}

void print() {
	printf("Nhap ma doc gia: ");
}


int soNgayQuaHan(Time &ngay_tra, Time &ngay_muon)
{
	int songay_tre = timeDiff(ngay_tra, ngay_muon) - 7;
	if (songay_tre <= 0)
		return 0;
	return songay_tre;
}


bool checkPhieu(PhieuMuonSach &a, PhieuMuonSach &b)
{
	return (compareStringField(a.MaDocGia, b.MaDocGia) == 0);
}

bool nhapPhieuTraSach(PhieuTraSach &phieu_tra)
{
	Record<ReaderID> tmp;
	bool search_result = searchObjectbyField<ReaderID, PhieuMuonSach>
		(phieu_tra.phieu_muon, PHIEUMUON, tmp, READERID_PHIEUMUON, print, input, notFoundReaderID);

	if (!search_result)
		return false;
	XuatPhieuMuonSach(phieu_tra.phieu_muon);

	printf("Nhap ngay tra: ");
	NhapNgay(phieu_tra.NgayTraThucTe);

	phieu_tra.tien_phat = soNgayQuaHan(phieu_tra.NgayTraThucTe, phieu_tra.phieu_muon.NgayMuon) * PHAT_QUAHAN;

	phieu_tra.so_sach_bimat = 0;
	phieu_tra.tien_phat += phieu_tra.so_sach_bimat * PHAT_MATSACH;

	for (int i = 0; i < phieu_tra.phieu_muon.soluong_sach; i++)
	{
		Sach tmp;
		Record<ISBN> tmp_isbn;
		tmp_isbn.record_key = phieu_tra.phieu_muon.DanhSachISBN[i];
		int search_result = searchObjectbyField<ISBN, Sach>
			(tmp, SACH, tmp_isbn, ISBN_SACH, notFoundBookMsg);
		tmp.SoLuong++;
		editRecord(tmp, search_result, SACH);
	}

	deleteRecord(tmp, READERID_PHIEUMUON, checkIndexFile);
	deleteRecord(phieu_tra.phieu_muon, PHIEUMUON, checkPhieu);
	return true;
}

bool NhapPhieuMuonSach(PhieuMuonSach &t) {
	printf("Nhap ma doc gia:  ");
	gets_s(t.MaDocGia.key);

	int insert_location;
	int search_result = binarySearch<ReaderID, Record<ReaderID>>(t.MaDocGia, compareStringField, READERID_PHIEUMUON, &insert_location);

	if (search_result == FILE_NOT_FOUND)
	{
		printf("Xay ra loi!\n");
		return false;
	}
	if (search_result != NOT_FOUND)
	{
		printf("Doc gia vui long tra sach truoc khi co the tiep tuc muon!\n");
		return false;
	}
	search_result = binarySearch<ReaderID, Record<ReaderID>>(t.MaDocGia, compareStringField, ID_DOCGIA);

	if (search_result == FILE_NOT_FOUND)
	{
		printf("Xay ra loi!\n");
		return false;
	}
	if (search_result == NOT_FOUND)
	{
		printf("Khong tim thay doc gia!\n");
		return false;
	}

	printf("Nhap ngay muon:  ");
	NhapNgay(t.NgayMuon);

	printf("Nhap ngay tra du kien:  ");
	NhapNgay(t.NgayTraDK);

	printf("Nhap so sach muon:  ");
	while (1)
	{
		if (!scanf_s(" %d", &t.soluong_sach) || t.soluong_sach <= 0)
		{
			clearInputBuffer();
			printf("So sach khong hop le. Nhap lai!\n");
		}
		else if (t.soluong_sach > MAX_SACH_MUON)
		{
			printf("Ban chi co the muon toi da %d sach!\n", MAX_SACH_MUON);
		}
		else break;
		
	}
	clearInputBuffer();

	printf("Nhap ma ISBN cac sach muon muon:\n");
	for (int i = 0; i < t.soluong_sach; i++)
	{
		while (1)
		{			
			gets_s(t.DanhSachISBN[i].key);
			Sach tmp;
			Record<ISBN> tmp_isbn;
			tmp_isbn.record_key = t.DanhSachISBN[i];
			int search_result = searchObjectbyField<ISBN, Sach>
				(tmp, SACH, tmp_isbn, ISBN_SACH, notFoundBookMsg);
			if (tmp.SoLuong <= 0)
			{
				printf("Vui long nhap quyen sach khac.\n");
			}
			else {
				tmp.SoLuong--;
				editRecord(tmp, search_result, SACH);
				//printf("%s\n", tmp.TenSach.key);
				break;
			}
		}
	}

	Record<ReaderID> tmp;
	tmp.record_key = t.MaDocGia;
	tmp.index = getNumberRecords<Record<ReaderID>>(READERID_PHIEUMUON);
	insertRecord(tmp, insert_location, READERID_PHIEUMUON);
	return true;
}



void MuonSach() {
	PhieuMuonSach t;
	if (!NhapPhieuMuonSach(t))
		return;

	addRecord(t, PHIEUMUON);
	system("cls");
	printf("Lap phieu muon thanh cong\n");
	XuatPhieuMuonSach(t);
}


void TraSach() {
	PhieuTraSach phieu_tra;
	if (!nhapPhieuTraSach(phieu_tra))
		return;

	addRecord(phieu_tra, PHIEUTRA);
	system("cls");
	printf("Lap phieu tra thanh cong\n");
	XuatPhieuTraSach(phieu_tra);
}