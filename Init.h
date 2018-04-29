#pragma once

#include <string.h>

#define isbn 13
#define MAX_USER 100
#define MAX_SACHMUON 130
#define LOGIN "resource\\user.bin"
#define DATA_USER "resource\\user.dat"
#define MALE 1

struct Time {
	int ngay;
	int thang;
	int nam;
};

struct Authentication {
	char usr[20];
	char pwrd[20];
};

struct ThongTinNguoi {
	char HoTen[50];
	Time DoB; // dd/mm/yyyy
	char CMND[9];
	char DiaChi[200];
	int GioiTinh;  //1 = Nam, 0 = Nu
};


bool inputAuthentication(Authentication &input, char *usr = NULL, char *pwrd = NULL);