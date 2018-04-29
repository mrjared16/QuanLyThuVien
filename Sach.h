#pragma once

#include "Init.h"

typedef struct Sach {
	char ISBN[isbn]; // en.wikipedia.org/ISBN

	char TenSach[100];
	char TacGia[50];
	char NXB[50];

	char NamXB[4];

	char TheLoai[20];
	int GiaSach;

	int SoQuyenSach;
};