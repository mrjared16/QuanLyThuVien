#include "stdafx.h"
#define MODE_ISBN 0
#define MODE_TEN 1

void danhSachSach(ListSach *l_sach)
{
	for (int i = 0; i < l_sach->length; i++)
	{
		printf("%d. %s\n", i + 1, l_sach->list[i].TenSach);
	}
}

// tim kiem
Sach *timKiemSach(ListSach *l_sach, char *key, int mode)
{
	for (int i = 0; i < l_sach->length; i++)
	{
		int cmp;
		switch (mode) {
			case MODE_ISBN:
				cmp = strcmp(l_sach->list[i].ISBN, key);
				break;
			case MODE_TEN:
				cmp = strcmp(l_sach->list[i].TenSach, key);
				break;
		}

		if (cmp == 0)
		{
			//printf("Da tim thay\n");
			// do something
			return &l_sach->list[i];
		}
	}
	//printf("Khong tim thay. Tim lai?\n");
	// do something
	return NULL;
}

void inThongTinSach(Sach *sach)
{
	printf("Ma ISBN: %s - Ten sach: %s\n", sach->ISBN, sach->TenSach);
	printf("Tac gia: %s - Nha xuat ban: %s - Nam xuat ban: %s\n", sach->TacGia, sach->NXB, sach->NamXB);
	printf("The loai: %s - Gia sach: %d (dong) - So quyen con lai: %d\n", sach->TheLoai, sach->GiaSach, sach->SoLuong);
}

// them sach
bool tonTaiSach(ListSach *l_sach, Sach *s)
{
	Sach *search_result = timKiemSach(l_sach, s->ISBN, MODE_ISBN);
	if (search_result == NULL)
		return false;
	return true;
}

bool themSach(ListSach *l_sach, Sach *sach)
{
	if (tonTaiSach(l_sach, sach))
		return false;

	l_sach->list[l_sach->length++] = *sach;
	return true;
}

