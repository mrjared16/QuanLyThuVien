#pragma once

//** NHUNG HAM MAU HO TRO DOC GHI FILE VA MOT SO HAM SU DUNG CHUNG KHAC **
//** LUU Y: DO 1 STRUCT CO DO LON KHONG DOI NEN MOI SU DUNG DUOC

#include <stdio.h>

//Kieu du lieu gom 1 khoa chua gia tri, 1 khoa chua vi tri
//Dung de tim kiem du lieu nhanh: 
//- File chua kieu Record dc sap xep => su dung binarysearch
//- Tim dc xong tu index lay ra kieu du lieu can tim
template <class KeyType>
struct Record {
	KeyType record_key;
	int index;
};



//Ham tra ve so luong cua 1 kieu du lieu tu file cho truoc
//file_name: ten file chua kieu du lieu can dem
template <class RecordType>
int getNumberRecords(const char *file_name)
{
	FILE *f;
	fopen_s(&f, file_name, "r");
	if (f == NULL)
		return FILE_NOT_FOUND;
	int result = getFileLength(f) / sizeof(RecordType);
	fclose(f);
	return result;
}


//Ham so sanh cac khoa' tim kiem
template <class Type>
int compareStringField(Type &key, Type &input)
{
	return strcmp(key.key, input.key);
}

//ham nhap khoa' tim kiem
template <class Type>
void inputStringField(Type &input)
{
	gets_s(input.key);
}



//Tra ve do dai cua file, ham ho tro cho binarysearch:
//Do thay doi f gay anh huong den viec doc ghi
//binarysearch su dung random access nen khong can quan tam
int getFileLength(FILE *f) {
	fseek(f, 0L, SEEK_END);	//di ve cuoi file
	return ftell(f);		//tra ve vi tri cua no => do dai file tinh bang byte
}



//Ham ghi 'record' tu stream f o vi tri 'id'
//Ho tro "random access" cho ham binarysearch
template <class RecordType>
void readRecord(FILE *f, RecordType &record, int id)
{
	fseek(f, id * sizeof(RecordType), SEEK_SET);
	fread_s(&record, sizeof(RecordType), sizeof(RecordType), 1, f);
}


//Ham tim kiem gia tri 'key' tu file 'file_name'
//con tro ham 'cmp': ham so sanh 2 gia tri kieu du lieu cua 'key'
//'insert_location': su dung khi ham binarysearch dc dung de tim vi tri 
//					de insert theo thu tu vao 1 file da sap xep
//Ham tra ve thu tu cua gia tri can tim
//NOT_FOUND => ko tim thay, FILE_NOT_FOUND => ko doc duoc file
template <class KeyType, class RecordType>
int binarySearch(KeyType &key, int(*cmp)(KeyType &, KeyType &), const char *file_name, int *insert_location = NULL)
{
	FILE *f;
	fopen_s(&f, file_name, "r");

	if (f == NULL)
	{
		//printf("Khong tim thay file %s\n", file_name);
		return FILE_NOT_FOUND;
	}
	RecordType record;	//bien tam de doc cac record

	int left = 0, right = getFileLength(f) / sizeof(RecordType) - 1;
	int mid;

	int cmp_result;	//ket qua tim kiem: < 0 neu a < b, = 0 neu a = b, > 0 neu a > b

	while (left <= right)
	{
		mid = (left + right) / 2;
		readRecord(f, record, mid);		//record = a[(left+right) / 2]

		cmp_result = cmp(key, record.record_key);

		if (cmp_result == 0) {		//key = record
			fclose(f);
			return mid;				// => mid la gia tri can tim
		}

		//record nam ben trai mid
		if (cmp_result < 0)
		{
			right = mid - 1;
		}
		else {
			left = mid + 1;	//nam ben phai mid
		}
	}

	//neu tim vi tri chen thi luu vi tri chen
	if (insert_location != NULL)
		*insert_location = left;

	fclose(f);
	return NOT_FOUND;	//ko tim thay
}



//Ham doc gia tri record o vi tri 'id' trong file 'file_name'
template <class RecordType>
bool getRecord(RecordType &record, int id, const char *file_name)
{
	FILE *f;
	fopen_s(&f, file_name, "r");
	if (f == NULL)
		return false;
	fseek(f, id * sizeof(RecordType), SEEK_SET);	//di den vi tri can doc
	if (!fread_s(&record, sizeof(RecordType), sizeof(RecordType), 1, f))	
	{
		fclose(f);
		return false;	//doc ko thanh cong
	}
	fclose(f);
	return true;
}


//Them record vao file 'file_name'
//su dung mode append nen them vao cuoi
template <class RecordType>
bool addRecord(RecordType &new_record, const char *file_name)
{
	FILE *f;
	fopen_s(&f, file_name, "a");

	if (f == NULL)
	{
		//printf("Xay ra loi!\n");
		return false;
	}

	fwrite(&new_record, sizeof(RecordType), 1, f);
	fclose(f);
	return true;
}


//Ham chen record moi vao vi tri 'insert_location' vao file 'file_name'
//Thuc chat la copy du lieu tu file goc sang file moi,
//den vi tri can chen thi them vao. Sau do khi de file cu
template <class RecordType>
bool insertRecord(RecordType &new_record, int insert_location, const char *file_name)
{
	FILE *f_read, *f_tmp;
	fopen_s(&f_read, file_name, "r");

	if (f_read == NULL) {
		return false;
	}

	fopen_s(&f_tmp, "tmp", "w");

	int i = 0;
	RecordType tmp;

	while (!feof(f_read))
	{
		if (i == insert_location)	//vi tri can ghi de
		{
			fwrite(&new_record, sizeof(RecordType), 1, f_tmp);
		}

		if (fread_s(&tmp, sizeof(RecordType), sizeof(RecordType), 1, f_read))	//doc tu file doc
		{
			fwrite(&tmp, sizeof(RecordType), 1, f_tmp);		// chep vao file moi
			i++;
		}
	}

	fclose(f_read);
	fclose(f_tmp);

	//ghi de file cu
	remove(file_name);
	rename("tmp", file_name);
	return true;
}

//Ham ghi de record tai vi tri 'id'
template <class RecordType>
bool editRecord(RecordType &new_record, int id, const char *file_name)
{
	FILE *f;
	fopen_s(&f, file_name, "r+");
	if (f == NULL) {
		//perror("Error");
		return false;
	}

	fseek(f, id * sizeof(RecordType), SEEK_SET);

	if (!fwrite(&new_record, sizeof(RecordType), 1, f))
	{
		fclose(f);
		return false;
	}
	fclose(f);
	return true;
}


//Ham xoa record thoa dieu kien 'check'
//Tuong tu ham insert
template <class RecordType>
bool deleteRecord(RecordType &record, const char *file_name, bool (*check)(RecordType &type, RecordType &input))
{
	FILE *f_read, *f_tmp;

	fopen_s(&f_read, file_name, "r");
	if (f_read == NULL){ 
		return false;
	}

	fopen_s(&f_tmp, "tmp", "w");

	int i = 0;
	RecordType tmp;

	while (!feof(f_read))
	{
		if (fread_s(&tmp, sizeof(RecordType), sizeof(RecordType), 1, f_read))
		{
			if (check(record, tmp))	//thoa man dieu kien can xoa => bo qua ko ghi vao file moi
			{
				continue;
			}
			fwrite(&tmp, sizeof(RecordType), 1, f_tmp);
		}
	}


	fclose(f_read);
	fclose(f_tmp);

	remove(file_name);
	rename("tmp", file_name);
	return true;
}

//Dem record thoa man dieu kien 'check'
template <class RecordType, class KeyType>
int countRecord(KeyType *key, const char *file_name, bool (*check)(RecordType &record, KeyType *key))
{
	int n = getNumberRecords<RecordType>(file_name);
	if (n == FILE_NOT_FOUND || n == 0)
	{
		return n;
	}

	FILE *f;
	fopen_s(&f, file_name, "r");

	RecordType buffer;

	int count = 0;

	for (int i = 0; i < n; i++)
	{
		fread_s(&buffer, sizeof(RecordType), sizeof(RecordType), 1, f);
		if (check(buffer, key))
			count++;
	}

	fclose(f);
	return count;
}

//Dem record thoa man dieu kien 'check'
template <class RecordType>
int countRecord(const char *file_name, bool(*check)(RecordType &record, int &count))
{
	int n = getNumberRecords<RecordType>(file_name);
	if (n == FILE_NOT_FOUND || n == 0)
	{
		return n;
	}

	FILE *f;
	fopen_s(&f, file_name, "r");

	RecordType buffer;

	int count = 0;

	for (int i = 0; i < n; i++)
	{
		fread_s(&buffer, sizeof(RecordType), sizeof(RecordType), 1, f);
		check(buffer, count);
	}

	fclose(f);
	return count;
}

//Doc va in tat ca cac record, tra ve so luong record
//print: Ham mau de in 1 record
template <class RecordType>
int printAllRecords(const char *file_name, void(*print)(RecordType &record, int index))
{
	int n = getNumberRecords<RecordType>(file_name);
	if (n == FILE_NOT_FOUND || n == 0)
	{
		return n;
	}

	FILE *f;
	fopen_s(&f, file_name, "r");

	RecordType buffer;

	for (int i = 0; i < n; i++)
	{
	
		fread_s(&buffer, sizeof(RecordType), sizeof(RecordType), 1, f);

		print(buffer, i + 1);
	}

	fclose(f);
	return n;
}


template <class Field, class Object>
bool searchObjectbyField(Object &obj_result, const char *obj_file, Record<Field> &field_record, const char *field_file,
	void(*printRequest)(), void(*inputField)(Field &), void(*notFoundMsg)())
{
	Field search_field;
	printRequest();
	inputField(search_field);
	int search_result = binarySearch<Field, Record<Field>>(search_field, compareStringField<Field>, field_file);

	if (search_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s\n", field_file);
		return false;
	}

	if (search_result == NOT_FOUND)
	{
		notFoundMsg();
		return false;
	}

	getRecord(field_record, search_result, field_file);

	getRecord(obj_result, field_record.index, obj_file);
	return true;
}

template <class Field, class Object>
int searchObjectbyField(Object &obj_result, const char *obj_file, Record<Field> field_record, const char *field_file,
	void(*notFoundMsg)())
{
	int search_result = binarySearch<Field, Record<Field>>(field_record.record_key, compareStringField<Field>, field_file);

	if (search_result == FILE_NOT_FOUND)
	{
		printf("Khong tim thay file %s\n", field_file);
		return NOT_FOUND;
	}

	if (search_result == NOT_FOUND)
	{
		notFoundMsg();
		return NOT_FOUND;
	}
	getRecord(field_record, search_result, field_file);

	getRecord(obj_result, field_record.index, obj_file);
	return field_record.index;
}


//Ham kieu tra cac file chua kieu record
//Khi xoa record, index cac record phia sau record bi xoa se giam di 1
template<class T>
bool checkIndexFile(T &a, T&tmp)
{
	if (a.index == tmp.index)
		return true;
	if (a.index < tmp.index)
		tmp.index--;
	return false;
}

//Ham cap nhat 'file_name'
//'field_record' la gia tri ban dau
//'obj_field' la gia tri sau khi thay doi
template <class Field>
void updateField(Record<Field> &field_record, Field &obj_field, const char *file_name)
{
	//nothing change
	if (compareStringField(field_record.record_key, obj_field) == 0)	//ko thay doi
	{
		return;
	}
	

	deleteRecord(field_record, file_name, checkIndexFile);	//xoa gia tri cu

	field_record.record_key = obj_field;	//gan gia tri moi

	int insert;
	int search_result = binarySearch<Field, Record<Field>>(obj_field, compareStringField<Field>, file_name, &insert);

	insertRecord(field_record, insert, file_name);	//them gia tri moi vao vi tri thich hop
}

//Ham rong
void NULLFunction() {

}

//Ham xoa buffer input
//tranh loi khi nhap xuat so va chuoi
void clearInputBuffer() {
	while ((getchar()) != '\n');
}

