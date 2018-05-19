#include "stdafx.h"

bool hopLe(char *test)
{
	return true;
}

bool loadUser(ListUser *l_user)
{
	FILE *f;
	fopen_s(&f, DATA_USER, "r+b");
	if (f == NULL)
		return false;
	int i = 0;

	while (!feof(f)) {
		fread(&l_user->list[i++], sizeof(User), 1, f);
	}
	l_user->length = i;
	
	fclose(f);
	return true;
}

bool loadBook(ListSach *l_sach)
{
	FILE *f;
	fopen_s(&f, SACH, "r+b");
	if (f == NULL)
		return false;
	int i = 0;

	while (!feof(f)) {
		fread(&l_sach->list[i++], sizeof(Sach), 1, f);
	}
	l_sach->length = i;

	fclose(f);
	return true;
}

bool inputAuthentication(Authentication *input, char *usr, char *pwrd)
{
	if (usr != NULL && pwrd != NULL)
	{
		strcpy_s(input->usr, usr);
		strcpy_s(input->pwrd, pwrd);
	} 
	else {
		printf("DANG NHAP\n");

		printf("Nhap ten:  ");
		gets_s(input->usr);

		printf("Nhap mat khau:  ");
		gets_s(input->pwrd);
	}

	return hopLe(input->usr) && hopLe(input->pwrd);
}

/*void DanhSachChucNang(int perm) {
	printf("Danh sach chuc nang:\n");
	printf("1.1 Dang nhap\n");
	printf("1.2 Dang xuat\n");
	printf("1.3 Thay doi mat khau\n");
	printf("1.4 Cap nhat thong tin ca nhan\n");
	if (perm == 1) {
		printf("1.5 Tao nguoi dung\n");
		printf("1.6 Phan quyen nguoi dung\n");
	}
	printf("2.1 Xem danh sach dong gia\n");
	printf("2.2 Them doc gia\n");
	printf("2.3 Chinh sua thong tin mot doc gia\n");
	if (perm <= 2) printf("2.4 Xoa thong tin mot doc gia\n");
	printf("2.5 Tim kiem dong gia theo CMND");
	printf("2.6 TIm kiem sach theo ho ten\n");
	if (perm <= 2) {
		printf("3.1 Xem danh sach cac sanh trong thu vien\n");
		printf("3.2 Them sach\n");
		printf("3.3 Chinh sua thong tin mot quyen sach\n");
		printf("3.4 Xoa thong tin sach\n");
	}
	printf("3.5 Tim kiem sach theo ISBN\n");
	printf("3.6 Tim kiem sach theo ten sach\n");
	printf("4 Lap phieu muon sach\n");
	printf("5 Lap phieu tra sach\n");
	printf("6.1 Thong ke so luong sach trong thu vien\n");
	printf("6.2 Thong ke so luong sach theo the loai\n");
	printf("6.3 Thong ke so luong doc gia\n");
	printf("6.4 Thong ke so luong doc gia theo gioi tinh\n");
	if (perm <= 2) {
		printf("6.5 Thong ke so sach dang duoc muon\n");
		printf("6.6 Thong ke danh sach doc gia bi tre han\n");
	}
	printf("7 Thoat chuong trinh\n");
}
*/