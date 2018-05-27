#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DocGia.h"
#include "Init.h"
#include "Stats.h"
#include "PhieuMuonTraSach.h"
#include "Sach.h"
#include "User.h"

#define NUMBER_OF_MENUS 41

#define MAX_NODE 10

void show(Menu *menu);


//******NOTE****** : Chinh sua SO LUONG menu => nho thay doi so luong NUMBER_OF_MENUS
DataMenu data[NUMBER_OF_MENUS] =
{
	{ "", "", NULL, MEMBER },
	{ "Chuc nang user"		, "", NULL, MEMBER },
		{ "Cap nhat thong tin ca nhan"	, "Chuc nang user", showInformation, MEMBER },
			{ "Thay doi ho ten"		, "Cap nhat thong tin ca nhan", changeName, MEMBER },
			{ "Thay doi ngay sinh"	, "Cap nhat thong tin ca nhan", changeDayofBirth, MEMBER },
			{ "Thay doi dia chi"	, "Cap nhat thong tin ca nhan", changeAddress, MEMBER },
		{ "Thay doi mat khau"			, "Chuc nang user", changePassword, MEMBER },
		{ "Tao nguoi dung"				, "Chuc nang user", addUser, ADMIN },
		{ "Phan quyen nguoi dung"		, "Chuc nang user", setPermission, ADMIN },
		{ "Dang xuat"					, "Chuc nang user", logOut, MEMBER },
	
	{ "Quan ly doc gia"		, "", NULL, MEMBER },
		{ "Xem danh sach doc gia"			, "Quan ly doc gia", printAllReaders, MEMBER },
		{ "Them doc gia"					, "Quan ly doc gia", addReader, MEMBER },
		{ "Chinh sua thong tin doc gia"		, "Quan ly doc gia", NULL, MEMBER },
			{ "Chinh sua doc gia theo CMND"		, "Chinh sua thong tin doc gia", changeReaderInfobyICN, MEMBER },
			{ "Chinh sua doc gia theo ho ten"	, "Chinh sua thong tin doc gia", changeReaderInfobyName, MEMBER },
		{ "Xoa doc gia"						, "Quan ly doc gia", NULL, MODERATOR },
			{ "Xoa doc gia theo CMND"			, "Xoa doc gia", deleteReaderbyICN, MODERATOR },
			{ "Xoa doc gia theo ho ten"			, "Xoa doc gia", deleteReaderbyName, MODERATOR },
		{ "Tim kiem doc gia theo CMND"		, "Quan ly doc gia", searchReaderbyIdentityCardNumber, MEMBER },
		{ "Tim kiem doc gia theo ho ten"	, "Quan ly doc gia", searchReaderbyName, MEMBER },
	
	{ "Quan ly sach"		, "", NULL, MEMBER },
		{ "Xem danh sach cac sach"		, "Quan ly sach", printAllBooks, MODERATOR },
		{ "Them sach"					, "Quan ly sach", addBook, MODERATOR },
		{ "Chinh sua thong tin sach"	, "Quan ly sach", NULL, MODERATOR },
			{ "Chinh sua sach theo ISBN"		, "Chinh sua thong tin sach", changeBookInfobyISBN, MODERATOR },
			{ "Chinh sua sach theo ten sach"	, "Chinh sua thong tin sach", changeBookInfobyName, MODERATOR },
		{ "Xoa sach"					, "Quan ly sach", NULL, MODERATOR },
			{ "Xoa sach theo ISBN"				, "Xoa sach", deleteBookbyISBN, MODERATOR },
			{ "Xoa sach theo ten sach"			, "Xoa sach", deleteBookbyName, MODERATOR },
		{ "Tim kiem sach theo ISBN"		, "Quan ly sach", searchBookbyISBN, MEMBER },
		{ "Tim kiem sach theo ten sach"	, "Quan ly sach", searchBookbyName, MEMBER },

	{ "Lap phieu muon sach"	, "", MuonSach, MEMBER },
	{ "Lap phieu tra sach"	, "", TraSach, MEMBER },
	{ "Chuc nang thong ke"	, "", NULL, MEMBER },
		{ "So luong sach trong thu vien"	, "Chuc nang thong ke", thongKeSach, MEMBER },
		{ "So luong sach theo the loai "	, "Chuc nang thong ke", thongKeSachTheoTheLoai, MEMBER },
		{ "So luong doc gia"				, "Chuc nang thong ke", thongKeDocGia, MEMBER },
		{ "So luong doc gia theo gioi tinh"	, "Chuc nang thong ke", thongKeDocGiaTheoGioiTinh, MEMBER },
		{ "So luong sach dang duoc muon"	, "Chuc nang thong ke", thongKeSachDangMuon, MEMBER },
		{ "Danh sach doc gia bi tre han"	, "Chuc nang thong ke", thongKeTreHan, MEMBER },
};

//Sau khi xay dung cay menu thi chi co parent cua MainMenu = NULL
bool isMainMenu(Menu *menu)
{
	return (menu->parent == NULL);
}

//Thu thi menu
void execute(Menu *menu)
{
	system("cls");		//xoa man hinh

	//Neu no la leaf => thuc thi

	if (menu->data->enter != NULL)
		menu->data->enter();
	//else {
		//Chua phai leaf => show chuc nang
	show(menu);
	//}

	//Khong phai main menu => add nut back
	if (!isMainMenu(menu))
		printf("\n0. Back");

	printf("\nNhap cac phim con lai de thoat\n");
}

//Them node vao parent
void addNode(Menu *parent, Menu *node)
{
	if (parent == NULL || node == NULL)
		return;

	//chua khoi tao con => khoi tao
	if (parent->children == NULL)
	{
		parent->children = new Menu*[MAX_NODE];
	}

	//tao lien ket giua node va parent
	node->parent = parent;
	parent->children[parent->n_of_children++] = node;	// tang so luong children

}

//Tao mot node moi sao chep data cho truoc
Menu *newNode(DataMenu &data)
{
	Menu *new_node = new Menu;

	new_node->parent = NULL;
	new_node->children = NULL;
	new_node->n_of_children = 0;

	new_node->data = new DataMenu;
	*(new_node->data) = data;	//copy chu khong su dung truc tiep data
	return new_node;
}

//Kiem tra xem child co phai la con cua parent?
bool isParent(DataMenu *parent, DataMenu &child)
{
	//la parent khi parent_label cua child = label cua parent
	return (strcmp(child.parent_label, parent->label) == 0);
}

//Kiem tra xem User co quyen su dung chuc nang hien tai
bool isAccessPermitted(DataMenu &require, User &user)
{
	return require.permission <= user.permission;
}

//Tim node co data = key
Menu *findParentNode(Menu *cur, DataMenu &key)	//su dung depth first search
{
	if (cur == NULL)
		return NULL;

	if (isParent(cur->data, key))	//tim thay
		return cur;

	for (int i = 0; i < cur->n_of_children; i++)
	{
		Menu *result = findParentNode(cur->children[i], key);
		if (result != NULL)
			return result;
	}

	return NULL;
}

//Lay Menu cua user
void getMenus(MainMenu &l_menu, User &user)
{
	int n = NUMBER_OF_MENUS;


	l_menu.root = newNode(data[0]);

	//node cha lay data tu data[0] => them node tu 1
	for (int i = 1; i < n; i++)
	{
		Menu *find_node = findParentNode(l_menu.root, data[i]);
		//tim thay parent va duoc phep thuc thi chuc nang
		if (find_node != NULL && isAccessPermitted(data[i], user))
			addNode(find_node, newNode(data[i]));	//=>them vao cay
	}
}


void nhanPhim(Menu *menu)
{

	int cmd;
	printf("> ");

	//nhan cmd
	if (!scanf_s("%d", &cmd) || (isMainMenu(menu) && cmd == 0) || cmd > menu->n_of_children) {
		exit(0);
		return;
	}

	//moi lan chi nhan 1 cmd
	clearInputBuffer();

	Menu *menu_cmd;	//menu tiep theo
	switch (cmd)
	{
		//BACK
	case 0:
		menu_cmd = menu->parent;
		break;

	default:
		menu_cmd = menu->children[cmd - 1];
		break;
	}

	//dang xuat thi ko tiep tuc de quy nhan phim
	if (menu_cmd->data->enter == logOut) {
		system("cls");
		return;
	}

	execute(menu_cmd);		//thuc thi
	nhanPhim(menu_cmd);		//tiep tuc nhan phim
}
//Xoa cay menu = de quy tranh memory leaks
void deleteMenus(Menu *menu)
{
	if (menu == NULL)
		return;

	for (int i = 0, n = menu->n_of_children; i < n; i++)
	{
		deleteMenus(menu->children[i]);
	}

	delete[] menu->children;
	delete menu->data;
	delete menu;
}

void show(Menu *menu)
{
	if (menu == NULL || menu->n_of_children == 0)
		return;

	for (int i = 0; i < menu->n_of_children; i++)
	{
		printf("%d. %s\n", i + 1, menu->children[i]->data->label);
	}

}

void runMenu(User &user)
{
	MainMenu main_menu;
	getMenus(main_menu, user);
	execute(main_menu.root);
	nhanPhim(main_menu.root);
	deleteMenus(main_menu.root);
}


void showCustomMenu(const char *MSG, const char *label[], int n)
{
	printf("\n");
	if (MSG != NULL)
		printf("\t%s\n", MSG);
	for (int i = 0; i < n; i++)
	{
		printf("%d. %s\n", i + 1, label[i]);
	}
}

void executeCustomMenu(void(*func[])(), int n)
{
	int cmd;

	while (1)
	{
		printf("\n> ");
		if (!scanf_s("%d", &cmd) || cmd <= 0 || cmd > n)
		{
			clearInputBuffer();
			printf("Cu phap khong hop le. Nhap lai!\n");
		}
		else
			break;
	}
	clearInputBuffer();
	func[cmd - 1]();
}

void runCustomMenu(const char *MSG, const char *label[], void(*func[])(), int n)
{
	showCustomMenu(MSG, label, n);
	executeCustomMenu(func, n);
}