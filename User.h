#pragma once

#include "Init.h"

typedef struct User {
	const int id;
	ThongTinNguoi info;
	int Active; // 1 = activated, 0 = blocked
	int perm; // 1 = admin, 2 = quan ly, 3 = chuyen vien, 4 = user
};

struct ListUser {
	User list[MAX_USER];
	int length;
};
//void AddUsr(FILE *f);

bool Login(Authentication *input);

int id(Authentication *usr_pwr) {
	int i = 0;
	return i;
}