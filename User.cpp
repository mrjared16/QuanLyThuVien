#include "stdafx.h"
/*void AddUsr(FILE *f) {
	fseek(f, 0L, SEEK_END);
	User New;
	int i = 0;
	printf("Nhap ho va ten:  ");
	gets_s(New.info.HoTen);
	printf("Nhap ten dang nhap:  ");
	gets_s(New.usr);
	printf("Nhap mat khau:  ");
	gets_s(New.pwrd);
	printf("Nhap ngay thang nam sinh (dd/mm/yyyy):  ");
	for (i = 0; i < 8; i++)
		scanf("%d", &New.info.DoB[i]);
	printf("Nhap so CMND:  ");
	for (i = 0; i < 9; i++)
		scanf("%d", &New.info.CMND[i]);
	printf("Nhap dia chi:  ");
	gets_s(New.info.DiaChi);
	printf("Nhap gioi tinh (Nam/Nu):  ");
	gets_s(New.info.GioiTinh);
	New.Active = 1;
	while (true) {
		printf("Nhap cap do phan quyen (2 = quan ly, 3 = chuyen vien, 4 = nguoi dung):  ");
		scanf("%d", &i);
		if (i == 1)
			printf("Loi: Khong the dang ky quyen admin. Vui long nhap lai.\n");
		else {
			New.perm = i;
			break;
		}
	}
	fwrite(&New, sizeof(User), 1, f);
}
*/

/*void UserList() {
	User admin;
	strcpy(admin.usr, "admin");
	strcpy(admin.pwrd, "admin");
	admin.perm = 1;
	admin.Active = 1;
	FILE *f = fopen("user.txt", "wb");
	fwrite(&admin, sizeof(User), 1, f);
	fclose(f);
}
*/
void NhapNgay(Time &date) {
	scanf_s("%d %d %d", &date.ngay, &date.thang, &date.nam);
}

void NhapThongTinNguoi(ThongTinNguoi &t) {
	printf("Nhap ho ten:  ");
	scanf(" %[^\n]%*c", t.HoTen);
	printf("Nhap ngay/thang/nam sinh:  ");
	NhapNgay(t.DoB);
	printf("Nhap so CMND:  ");
	scanf(" %[^\n]%*c", t.CMND);
	printf("Nhap dia chi:  ");
	scanf(" %[^\n]%*c", t.DiaChi);
	printf("Nhap gioi tinh (1 = Nam, 0 = Nu):  ");
	scanf(" %d", &t.GioiTinh);
}

void XuatThongTinNguoi(ThongTinNguoi &t) {
	printf("Ho ten: %s\n", t.HoTen);
	printf("Ngay sinh: %d/%d/%d\n", t.DoB.ngay, t.DoB.thang, t.DoB.nam);
	printf("So CMND: %s\n", t.CMND);
	printf("Dia chi: %s\n", t.DiaChi);
	printf("Gioi tinh: ");
	if (t.GioiTinh) printf("Nam\n");
	else printf("Nu\n");
}

void NhapThongTinDocGia(TheDocGia &t) {
	printf("Nhap ma doc gia:  ");
	scanf("%[^\n]%*c", t.MaDocGia);
	NhapThongTinNguoi(t.info);
	printf("Nhap ngay het han:  ");
	NhapNgay(t.NgayHetHan);
	printf("\n");
}

void XuatThongTinDocGia(TheDocGia &t) {
	printf("Ma doc gia: %s\n", t.MaDocGia);
	XuatThongTinNguoi(t.info);
	printf("Ngay het han: %d/%d/%d", t.NgayHetHan.ngay, t.NgayHetHan.thang, t.NgayHetHan.nam);
}

void NhapThongTinNguoiDung(User &t) {
	printf("Nhap ID:  ");
	scanf("%d", &t.id);
	NhapThongTinNguoi(t.info);
	printf("Nhap trang thai (1 = active, 0 = blocked):  ");
	scanf(" %d", &t.Active);
	printf("Nhap quyen dieu khien (1 = admin, 2 = quan ly, 3 = chuyen vien):  ");
	scanf(" %d", &t.perm);
	printf("\n");
}

long ThongKeDocGia() {
	FILE *f = fopen("docgia.bin", "rb");
	fseek(f, 0L, SEEK_END);
	long eof = ftell(f);
	fclose(f);
	long N = eof / sizeof(TheDocGia);
	printf("So luong doc gia: %ld\n", N);
	return N;
}

int ThongKeDocGia_GioiTinh() {
	printf("Nhap gioi tinh can tim (1 = Nam, 0 = Nu):  ");
	int gt;
	scanf(" %d", &gt);
	int num = 0;
	TheDocGia dg;
	FILE *f = fopen("docgia.bin", "rb");
	while (!feof(f)) {
		fread(&dg, sizeof(TheDocGia), 1, f);
		if (feof(f)) break;
		if (gt == dg.info.GioiTinh) {
			num++;
		}
	}
	fclose(f);
	printf("So luong doc gia ");
	if (gt == 1) printf("Nam:  ");
	else printf("Nu:  ");
	printf("%d\n", num);
	return num;
}

void XuatThongTinNguoiDung(User &t) {
	printf("ID: %d\n", t.id);
	XuatThongTinNguoi(t.info);
	printf("Trang thai: ");
	if (t.Active) printf("Active\n");
	else printf("Blocked\n");
	printf("Quyen dieu khien: ");
	switch (t.perm) {
	case 1: printf("Admin\n"); break;
	case 2: printf("Quan ly\n"); break;
	case 3: printf("Chuyen vien\n"); break;
	}
	printf("\n");
}

bool Login(Authentication *input){
	
	FILE *f;
	fopen_s(&f, LOGIN, "rb");

	if (f == NULL){
		printf("Khong the mo danh sach nguoi dung. ");
		return false;
	}

	Authentication read;
	while (!feof(f)) {

		fread_s(&read, sizeof(Authentication), sizeof(Authentication), 1, f);

		if (   !strcmp(read.usr, input->usr) 
			&& !strcmp(read.pwrd, input->pwrd)) {
			return true;
		}
		//if (feof(f))
			//break;
	}

	fclose(f);
	return false;
}