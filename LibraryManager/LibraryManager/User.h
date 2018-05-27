#pragma once


#include <stdio.h>
#include <string.h>
#include "Functions.h"
#include "Init.h"


User login_user;


//Ham so sanh username
int compareUsername(Authentication &a, Authentication &b)
{
	return strcmp(a.usr, b.usr);
}

//Ham kiem tra ten dang nhap va mat khau trung khop
bool isMatch(Authentication &check, Authentication &user_input)
{
	int cmp_name = strcmp(check.usr, user_input.usr);
	int cmp_password = strcmp(check.pwrd, user_input.pwrd);
	return (cmp_name == 0 && cmp_password == 0);
}

//Ham xuat thong tin user
void XuatThongTinNguoiDung(User &t) {
	printf("ID: %d\n", t.id);

	printf("Username: %s\n", t.usr);

	XuatThongTinNguoi(t.info);

	printf("Trang thai: ");
	if (t.Active) 
		printf("Active\n");
	else 
		printf("Blocked\n");

	printf("Quyen dieu khien: ");

	switch (t.permission) {
		case ADMIN: 
			printf("Admin\n"); 
			break;
		case MODERATOR: 
			printf("Quan ly\n"); 
			break;
		case MEMBER: 
			printf("Chuyen vien\n");
			break;
	}
	printf("\n");

}

//Ham nhap thong tin nguoi dung
void NhapThongTinNguoiDung(User &t, int id, char *username) {

	t.id = id;

	strcpy_s(t.usr, username);

	NhapThongTinNguoi(t.info);

	printf("Nhap trang thai (1 = active, 0 = blocked):  ");
	scanf_s("%d", &t.Active);

	printf("Nhap quyen dieu khien (%d = admin, %d = quan ly, %d = chuyen vien):  ", ADMIN, MODERATOR, MEMBER);
	scanf_s("%d", &t.permission);
	//printf("\n");
}


//Ham nhap username password tham so lay tu cmd line
bool nhapUsernamePassword(Authentication &input, char *usr, char *pwrd)
{
	if (usr == NULL || pwrd == NULL)
		return false;
	strcpy_s(input.usr, usr);
	strcpy_s(input.pwrd, pwrd);
	return true;
}

//Ham nhap username password tu ban phim
bool nhapUsernamePassword(Authentication &input)
{
	printf("Nhap ten:  ");
	gets_s(input.usr);

	printf("Nhap mat khau:  ");
	gets_s(input.pwrd);

	return true;
}


//Ham kiem tra dang nhap, dang nhap thanh cong tra ve 'id_user'
bool checkLogin(Authentication &input, int &id_user) {

	//tim theo username
	int search_result = binarySearch<Authentication, Record<Authentication>>(input, compareUsername, AUTHEN);

	
	if (search_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s\n", AUTHEN);
		return false;
	}

	//Khong tim thay user;
	if (search_result == NOT_FOUND)
	{	
		return false;
	}

	Record<Authentication> result;
	getRecord(result, search_result, AUTHEN);	//lay password ra de so sanh
	
	if (!isMatch(result.record_key, input))		// sai password
		return false;
	
	id_user = result.index;	//id_user chinh la thu tu cua user

	return true;
}

void changePassword()
{
	Record<Authentication> new_record;

	//login_user: "Init.h" 
	
	strcpy_s(new_record.record_key.usr, login_user.usr);
	
	//Tim vi tri cua user
	int search_result = binarySearch<Authentication, Record<Authentication>>(new_record.record_key, compareUsername, AUTHEN);

	//lay user id
	getRecord(new_record, search_result, AUTHEN);

	//Thay doi mat khau
	printf("Nhap mat khau moi: ");
	gets_s(new_record.record_key.pwrd);

	//chinh sua record
	if (editRecord(new_record, search_result, AUTHEN))
		printf("Thay doi mat khau thanh cong!\n");
	else 
		printf("Thay doi mat khau that bai!\n");
}

//ham rong de thoat khoi vong lap de quy => dang xuat
void logOut() {
	//system("cls");
}

//cap nhat user moi vao file
void updateUserInformation(User &user)
{
	if (!editRecord(user, user.id, USER_DATA))
		printf("Chinh sua that bai!\n");
	else
		printf("Chinh sua thanh cong!\n");
}

//hien thi thong tin user de tien chinh sua
void showInformation()
{
	printf("\tTHONG TIN HIEN TAI:\n");
	XuatThongTinNguoiDung(login_user);
	printf("Chon noi dung muon chinh sua\n");
}

//login_user: "Init.h"
void changeName()
{
	nhapHoTen(login_user.info);
	updateUserInformation(login_user);
}

void changeDayofBirth()
{
	nhapNgaySinh(login_user.info);
	updateUserInformation(login_user);
}

void changeIdentityCardNumber()
{
	nhapCMND(login_user.info);
	updateUserInformation(login_user);
}

void changeAddress()
{
	nhapDiaChi(login_user.info);
	updateUserInformation(login_user);
}

//them user moi
void addUser()
{
	//user id
	int index = getNumberRecords<Authentication>(AUTHEN);

	if (index == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s!\n", AUTHEN);
		return;
	}

	User user;
	Authentication input;
	

	//nhap username, password
	nhapUsernamePassword(input);
	NhapThongTinNguoiDung(user, index, input.usr);

	Record<Authentication> user_record;
	user_record.record_key = input;
	user_record.index = index;

	//vi tri de them user moi
	int insert_location = -1;

	int search_result = binarySearch<Authentication, Record<Authentication>>
		(user_record.record_key, compareUsername, AUTHEN, &insert_location);

	if (search_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s", AUTHEN);
		return;
	}

	if (search_result != NOT_FOUND)
	{
		printf("User da ton tai!\n");
		return;
	}
	
	//them user va username password
	if (insertRecord(user_record, insert_location, AUTHEN)
		&& addRecord(user, USER_DATA))
		printf("Them user thanh cong!\n");
	else {
		printf("Them user that bai!\n");
	}

}

void setPermission() {
	Authentication authen_record;

	//login_user: "Init.h" 

	printf("Nhap username can phan quyen: ");
	gets_s(authen_record.usr);

	
	//Tim vi tri cua user
	int search_result = binarySearch<Authentication, Record<Authentication>>(authen_record, compareUsername, AUTHEN);

	printf("\n");
	if (search_result == FILE_NOT_FOUND) {
		printf("Khong tim thay file %s\n", AUTHEN);
		return;
	}

	if (search_result == NOT_FOUND)
	{
		printf("Khong tim thay user \"%s\"\n", authen_record.usr);
		return;
	}

	//lay record ra de doc id cua User
	Record<Authentication> tmp;
	getRecord(tmp, search_result, AUTHEN);

	//doc thong tin user
	User set_permission;
	getRecord(set_permission, tmp.index, USER_DATA);

	//thay doi quyen 
	printf("Nhap quyen dieu khien (%d = admin, %d = quan ly, %d = chuyen vien):  ", ADMIN, MODERATOR, MEMBER);
	scanf_s("%d", &set_permission.permission);

	//chinh sua thong tin user
	if (editRecord(set_permission, tmp.index, USER_DATA))
		printf("Phan quyen thanh cong!\n");
	else
		printf("Phan quyen that bai!\n");
}