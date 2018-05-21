#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Init.h"
#include "User.h"

#define NUMBER_OF_MENUS 30

#define MAX_NODE 10

void show(Menu *menu);


//chinh sua nho thay doi so luong NUMBER_OF_MENUS
DataMenu data[NUMBER_OF_MENUS] =
{
	{ "", "", NULL, MEMBER },
	{ "Chuc nang user"		, "", NULL, MEMBER },
	{ "Quan ly doc gia"		, "", NULL, MEMBER },
	{ "Quan ly sach"		, "", NULL, MEMBER },
	{ "Lap phieu muon sach"	, "", NULL, MEMBER },
	{ "Lap phieu tra sach"	, "", NULL, MEMBER },
	{ "Chuc nang thong ke"	, "", NULL, MEMBER },

	{ "Cap nhat thong tin ca nhan"	, "Chuc nang user", NULL, MEMBER },
	{ "Thay doi mat khau"			, "Chuc nang user", NULL, MEMBER },
	{ "Tao nguoi dung"				, "Chuc nang user", NULL, ADMIN },
	{ "Phan quyen nguoi dung"		, "Chuc nang user", NULL, ADMIN },
	{ "Dang xuat"					, "Chuc nang user", logOut, MEMBER },

	{ "Xem danh sach doc gia"			, "Quan ly doc gia", NULL, MEMBER },
	{ "Them doc gia"					, "Quan ly doc gia", NULL, MEMBER },
	{ "Chinh sua thong tin doc gia"		, "Quan ly doc gia", NULL, MEMBER },
	{ "Xoa thong tin doc gia"			, "Quan ly doc gia", NULL, MODERATOR },
	{ "Tim kiem doc gia theo CMND"		, "Quan ly doc gia", NULL, MEMBER },
	{ "Tim kiem doc gia theo ho ten"	, "Quan ly doc gia", NULL, MEMBER },


	{ "Xem danh sach cac sach"		, "Quan ly sach", NULL, MODERATOR },
	{ "Them sach"					, "Quan ly sach", NULL, MODERATOR },
	{ "Chinh sua thong tin sach"	, "Quan ly sach", NULL, MODERATOR },
	{ "Xoa thong tin sach"			, "Quan ly sach", NULL, MODERATOR },
	{ "Tim kiem sach theo ISBN"		, "Quan ly sach", NULL, MEMBER },
	{ "Tim kiem sach theo ten sach"	, "Quan ly sach", NULL, MEMBER },

	{ "So luong sach trong thu vien"	, "Chuc nang thong ke", NULL, MEMBER },
	{ "So luong sach theo the loai "	, "Chuc nang thong ke", NULL, MEMBER },
	{ "So luong doc gia"				, "Chuc nang thong ke", NULL, MEMBER },
	{ "So luong doc gia theo gioi tinh"	, "Chuc nang thong ke", NULL, MEMBER },
	{ "So luong sach dang duoc muon"	, "Chuc nang thong ke", NULL, MEMBER },
	{ "Danh sach doc gia bi tre han"	, "Chuc nang thong ke", NULL, MEMBER },
};

//Sau khi xay dung cay menu thi chi co parent cua MainMenu = NULL
bool isMainMenu(Menu *menu)
{
	return (menu->parent == NULL);
}

//Thu thi menu
void execute(Menu *menu)
{
	//Neu no la leaf => thuc thi
	if (menu->data->enter != NULL)
		menu->data->enter();
	else {
		//Chua phai leaf => show chuc nang
		show(menu);
	}

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

void clearInputBuffer() {
	while ((getchar()) != '\n');
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

	
	system("cls");		//xoa man hinh

	//dang xuat thi ko tiep tuc de quy
	if (menu_cmd->data->enter == logOut) {
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