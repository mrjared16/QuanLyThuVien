#include "stdafx.h"

bool Init(ListUser &l_user)
{
	FILE *f;
	fopen_s(&f, DATA_USER, "r+b");
	if (f == NULL)
		return false;
	int i = 0;

	while (!feof(f)) {
		fread(&l_user.list[i++], sizeof(User), 1, f);
	}

	fclose(f);
	return true;
}

bool hopLe(char *test)
{
	return true;
}

bool inputAuthentication(Authentication &input, char *usr, char *pwrd)
{
	if (usr != NULL && pwrd != NULL)
	{
		strcpy_s(input.usr, usr);
		strcpy_s(input.pwrd, pwrd);
	} 
	else {
		printf("DANG NHAP\n");

		printf("Nhap ten:  ");
		gets_s(input.usr);

		printf("Nhap mat khau:  ");
		gets_s(input.pwrd);
	}

	return hopLe(input.usr) && hopLe(input.pwrd);
}