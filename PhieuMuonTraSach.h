#pragma once

#include "Init.h"


typedef struct PhieuMuonSach {
	char MaDocGia[8];

	Time NgayMuon;
	Time NgayTraDK;
	Time NgayTraTT;

	int SoLuongSach;
	char DanhSachISBN[MAX_SACHMUON][isbn];
};