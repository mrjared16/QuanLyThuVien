#include "stdafx.h"
#define MODE_ISBN 0
#define MODE_TEN 1

void NhapNgay(Time &date) {
	scanf_s("%d %d %d", &date.ngay, &date.thang, &date.nam);
}

void NhapSach(Sach &t) {
	printf("Nhap ma ISBN:  ");
	scanf(" %[^\n]%*c", t.ISBN);
	printf("Nhap ten sach:  ");
	scanf(" %[^\n]%*c", t.TenSach);
	printf("Nhap tac gia:  ");
	scanf(" %[^\n]%*c", t.TacGia);
	printf("Nhap NXB:  ");
	scanf(" %[^\n]%*c", t.NXB);
	printf("Nhap nam xuat ban:  ");
	scanf(" %[^\n]%*c", t.NamXB);
	printf("Nhap the loai:  ");
	scanf(" %[^\n]%*c", t.TheLoai);
	printf("Nhap gia sach:  ");
	scanf(" %d", &t.GiaSach);
	printf("Nhap so luong:  ");
	scanf(" %d", &t.SoLuong);
}

void XuatSach(Sach &t) {
	printf("Ma ISBN: %s", t.ISBN);
	printf("Ten sach: %s", t.TenSach);
	printf("Tac gia: %s", t.TacGia);
	printf("NXB: %s", t.NXB);
	printf("Nam xuat ban: %s", t.NamXB);
	printf("The loai: %s", t.TheLoai);
	printf("Gia sach: %d", t.GiaSach);
	printf("So luong: %d", t.SoLuong);
}

void danhSachSach(ListSach *l_sach)
{
	for (int i = 0; i < l_sach->length; i++)
	{
		printf("%d. %s\n", i + 1, l_sach->list[i].TenSach);
	}
}

void NhapPhieuMuonSach(PhieuMuonSach &t) {
	printf("Nhap ma doc gia:  ");
	scanf(" %[^\n]%*c", t.MaDocGia);
	printf("Nhap ngay muon:  ");
	NhapNgay(t.NgayMuon);
	printf("Nhap ngay tra du kien:  ");
	NhapNgay(t.NgayTraDK);
	printf("Nhap ngay tra thuc te:  ");
	NhapNgay(t.NgayTraTT);
	printf("Nhap so sach muon:  ");
	scanf(" %d", &t.SoLuongSach);
	printf("Nhap ma ISBN cac sach muon muon:\n");
	for (int i = 0; i < t.SoLuongSach; i++)
		scanf(" %[^\n]%*c", &t.DanhSachISBN[i]);
}

void XuatPhieuMuonSach(PhieuMuonSach &t) {
	printf("Ma doc gia: %s\n", t.MaDocGia);
	printf("Ngay muon: %d/%d/%d\n", t.NgayMuon.ngay, t.NgayMuon.thang, t.NgayMuon.nam);
	printf("Ngay tra du kien: %d/%d/%d\n", t.NgayTraDK.ngay, t.NgayTraDK.thang, t.NgayTraDK.nam);
	printf("Ngay tra thuc te: %d/%d/%d\n", t.NgayTraTT.ngay, t.NgayTraTT.thang, t.NgayTraTT.nam);
	printf("Ma ISBN cac sach muon muon:\n");
	int i = 0;
	for (int i = 0; i < t.SoLuongSach; i++)
		printf("%s\n", &t.DanhSachISBN[i]);
}

// tim kiem
Sach *timKiemSach(ListSach *l_sach, char *key, int mode)
{
	for (int i = 0; i < l_sach->length; i++)
	{
		int cmp;
		switch (mode) {
			case MODE_ISBN:
				cmp = strcmp(l_sach->list[i].ISBN, key);
				break;
			case MODE_TEN:
				cmp = strcmp(l_sach->list[i].TenSach, key);
				break;
		}

		if (cmp == 0)
		{
			//printf("Da tim thay\n");
			// do something
			return &l_sach->list[i];
		}
	}
	//printf("Khong tim thay. Tim lai?\n");
	// do something
	return NULL;
}

void inThongTinSach(Sach *sach)
{
	printf("Ma ISBN: %s - Ten sach: %s\n", sach->ISBN, sach->TenSach);
	printf("Tac gia: %s - Nha xuat ban: %s - Nam xuat ban: %s\n", sach->TacGia, sach->NXB, sach->NamXB);
	printf("The loai: %s - Gia sach: %d (dong) - So quyen con lai: %d\n", sach->TheLoai, sach->GiaSach, sach->SoLuong);
}

// them sach
bool tonTaiSach(ListSach *l_sach, Sach *s)
{
	Sach *search_result = timKiemSach(l_sach, s->ISBN, MODE_ISBN);
	if (search_result == NULL)
		return false;
	return true;
}

bool themSach(ListSach *l_sach, Sach *sach)
{
	if (tonTaiSach(l_sach, sach))
		return false;

	l_sach->list[l_sach->length++] = *sach;
	return true;
}

int ThongKeSach() {
	int N = 0;
	Sach s;
	FILE *f = fopen("book.bin", "rb");
	while (!feof(f)) {
		fread(&s, sizeof(Sach), 1, f);
		if (feof(f)) break;
		N += s.SoLuong;
	}
	printf("So luong sach: %ld\n", N);
	return N;
}

int ThongKeSach_TheLoai() {
	printf("Nhap the loai muon tim kiem:  ");
	char tl[20];
	scanf(" %[^\n]%*c", tl);
	int num = 0;
	Sach s;
	FILE *f = fopen("book.bin", "rb");
	while (!feof(f)) {
		fread(&s, sizeof(Sach), 1, f);
		if (feof(f)) break;
		if (!strcmp(tl, s.TheLoai))
			num += s.SoLuong;
	}
	fclose(f);
	printf("So luong sach theo the loai '%s' la  %d", tl, num);
	return num;
}