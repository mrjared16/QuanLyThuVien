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
bool Login(Authentication input){
	
	FILE *f;
	fopen_s(&f, LOGIN, "rb");

	if (f == NULL){
		printf("Khong the mo danh sach nguoi dung. ");
		return false;
	}

	Authentication read;
	while (!feof(f)) {

		fread_s(&read, sizeof(Authentication), sizeof(Authentication), 1, f);

		if (   !strcmp(read.usr, input.usr) 
			&& !strcmp(read.pwrd, input.pwrd)) {
			return true;
		}
		//if (feof(f))
			//break;
	}

	fclose(f);
	return false;
}