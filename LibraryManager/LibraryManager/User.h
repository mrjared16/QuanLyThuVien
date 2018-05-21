#pragma once

#include <stdio.h>
#include <string.h>
#include "Functions.h"
#include "Init.h"

#define LOGIN "resource\\user.bin"
#define DATA_USER "resource\\user.dat"


int isMatch(Authentication &check, Authentication &user_input)
{
	int cmp_name = strcmp(check.usr, user_input.usr);
	int cmp_password = strcmp(check.usr, user_input.usr);
	if (cmp_name == 0 && cmp_password == 0)
		return 0;
	return cmp_name;
}

//Ham kiem tra dang nhap, dang nhap thanh cong tra ve id user
//Dang nhap that bai tra ve LOGIN_FAILED
bool checkLogin(Authentication &input, int &id_user) {

	int find_result = binarySearch<Authentication, Record<Authentication>>(input, isMatch, AUTHEN );

	
	if (find_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s\n", AUTHEN);
		return false;
	}

	if (find_result == NOT_FOUND)
	{		
		return false;
	}

	Record<Authentication> result;
	getRecord(result, find_result, AUTHEN);
	id_user = result.index;

	return true;
}

//Ham nhap username password tham so lay tu cmd line
bool inputAuthentication(Authentication &input, char *usr, char *pwrd)
{
	if (usr == NULL || pwrd == NULL)
		return false;
	strcpy_s(input.usr, usr);
	strcpy_s(input.pwrd, pwrd);
	return true;
}

//Ham nhap username password tu ban phim
bool inputAuthentication(Authentication &input)
{
	printf("DANG NHAP\n");

	printf("Nhap ten:  ");
	gets_s(input.usr);

	printf("Nhap mat khau:  ");
	gets_s(input.pwrd);

	return true;
}

//ham rong de thoat khoi vong lap de quy => dang xuat
void logOut() {

}
