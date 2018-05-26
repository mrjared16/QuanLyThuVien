#pragma once
#include "Init.h"

typedef struct PhieuMuonTraSach {
	char MaDocGia[8];

	Time NgayMuon;
	Time NgayTraDK;
	Time NgayTraTT;

	int SoLuongSach;
	char DanhSachISBN[100][13];
};

bool NamNhuan(int &t) {
	if (t % 400 == 0) {
		return true;
	}
	else if (t % 100 == 0) {
		return false;
	}
	else if (t % 4 == 0) {
		return true;
	}
	else {
		return false;
	}
}

int KhoangCach2Time(Time &a, Time &b) {
	int dif = 0;
	int NgayTrongThang[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	dif += NgayTrongThang[a.thang - 1] - a.ngay + 1;
	dif += b.ngay;
	if (a.nam == b.nam) {
		if (NamNhuan(a.nam))
			NgayTrongThang[1]++;
		for (int i = a.thang; i < b.thang - 1; i++)
			dif += NgayTrongThang[i];
	}
	else {
		int yr_dif = b.nam - a.nam;
		for (int i = a.nam + 1; i <= b.nam; i++) {
			if (NamNhuan(i))
				dif += 366;
			else dif += 365;
		}
		a.nam = b.nam;
		if (NamNhuan(a.nam))
			NgayTrongThang[1]++;
		for (int i = a.thang; i < b.thang - 1; i++)
			dif += NgayTrongThang[i];
	}
	//printf("So ngay chenh lenh: %d", dif);
	return dif;
}

void NhapPhieuMuonSach(PhieuMuonTraSach &t) {
	printf("Nhap ma doc gia:  ");
	gets_s(t.MaDocGia);
	printf("Nhap ngay muon:  ");
	NhapNgay(t.NgayMuon);
	printf("Nhap ngay tra du kien:  ");
	NhapNgay(t.NgayTraDK);
	/*printf("Nhap ngay tra thuc te:  ");
	NhapNgay(t.NgayTraTT);*/
	printf("Nhap so sach muon:  ");
	scanf_s(" %d", &t.SoLuongSach);
	printf("Nhap ma ISBN cac sach muon muon:\n");
	for (int i = 0; i < t.SoLuongSach; i++)
		gets_s(t.DanhSachISBN[i]);
}

void XuatPhieuMuonSach(PhieuMuonTraSach &t) {
	printf("Ma doc gia: %s\n", t.MaDocGia);
	printf("Ngay muon: %d/%d/%d\n", t.NgayMuon.ngay, t.NgayMuon.thang, t.NgayMuon.nam);
	printf("Ngay tra du kien: %d/%d/%d\n", t.NgayTraDK.ngay, t.NgayTraDK.thang, t.NgayTraDK.nam);
	printf("Ngay tra thuc te: %d/%d/%d\n", t.NgayTraTT.ngay, t.NgayTraTT.thang, t.NgayTraTT.nam);
	printf("Ma ISBN cac sach muon muon:\n");
	int i = 0;
	for (int i = 0; i < t.SoLuongSach; i++)
		printf("%s\n", &t.DanhSachISBN[i]);
}

void MuonSach() {
	PhieuMuonTraSach t;
	NhapPhieuMuonSach(t);
	FILE *f;
	fopen_s(&f, "PhieuMuonSach.bin", "ab");
	fwrite(&t, sizeof(PhieuMuonTraSach), 1, f);
	fclose(f);
}

void TraSach() {
	PhieuMuonTraSach t[100];
	int n = 0;
	char MDG[8];
	printf("Nhap ma doc gia:  ");
	gets_s(MDG);
	FILE *f;
	fopen_s(&f, "PhieuMuonSach.bin", "rb");

	while (!feof(f)) {
		fread(&t[n], sizeof(PhieuMuonTraSach), 1, f);
		if (feof(f)) break;
		n++;
	}
	for (int i = 0; i < n; i++) {
		if (!strcmp(MDG, t[i].MaDocGia)) {
			printf("Nhap ngay tra thuc te:  ");
			NhapNgay(t[i].NgayTraTT);
			int dif = KhoangCach2Time(t[i].NgayMuon, t[i].NgayTraTT);
			XuatPhieuMuonSach(t[i]);
			if (dif > 7)
				printf("Sach bi muon qua han %d ngay, bi phat %d dong.\n", dif - 5, (dif - 5) * 5000);
			break;
		}
	}
	fclose(f);
}