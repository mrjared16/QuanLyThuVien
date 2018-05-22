#pragma once

#include <stdio.h>

template <class KeyType>
struct Record {
	KeyType record_key;
	int index;
};

int getFileLength(FILE *f) {
	fseek(f, 0L, SEEK_END);
	return ftell(f);
}

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

template <class RecordType>
void readRecord(FILE *f, RecordType &record, int id)
{
	fseek(f, id * sizeof(RecordType), SEEK_SET);
	fread_s(&record, sizeof(RecordType), sizeof(RecordType), 1, f);
}

template <class RecordType>
bool getRecord(RecordType &record, int id, const char *file_name)
{
	FILE *f;
	fopen_s(&f, file_name, "r");
	if (f == NULL)
		return false;
	fseek(f, id * sizeof(RecordType), SEEK_SET);
	if (!fread_s(&record, sizeof(RecordType), sizeof(RecordType), 1, f))
		return false;

	fclose(f);
	return true;
}


//Tra ve thu tu trong record neu tim thay, NOT_FOUND = -1 neu ko tim thay
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
	RecordType record;

	int left = 0, right = getFileLength(f) / sizeof(RecordType) - 1;
	int mid;
	int cmp_result;

	while (left <= right)
	{
		mid = (left + right) / 2;
		readRecord(f, record, mid);
		cmp_result = cmp(key, record.record_key);

		if (cmp_result == 0) {
			fclose(f);
			return mid;
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

	if (insert_location != NULL)
		*insert_location = left;

	fclose(f);
	return NOT_FOUND;
}


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
		if (i == insert_location)
		{
			fwrite(&new_record, sizeof(RecordType), 1, f_tmp);
		}
		if (fread_s(&tmp, sizeof(RecordType), sizeof(RecordType), 1, f_read))
		{
			fwrite(&tmp, sizeof(RecordType), 1, f_tmp);
			i++;
		}
	}

	fclose(f_read);
	fclose(f_tmp);

	remove(file_name);
	rename("tmp", file_name);
	return true;
}


template <class RecordType>
bool deleteRecord(int id, const char *file_name)
{
	FILE *f_read, *f_tmp;

	bool possible_delete = (getNumberRecords<RecordType>(file_name) > id);

	fopen_s(&f_read, file_name, "r");
	if (!possible_delete || f_read == NULL || id == -1) {
		//printf("Xoa khong thanh cong\n");
		if (f_read != NULL)
			fclose(f_read);
		return false;
	}

	fopen_s(&f_tmp, "tmp", "w");

	int i = 0;
	RecordType tmp;

	while (!feof(f_read))
	{
		if (fread_s(&tmp, sizeof(RecordType), sizeof(RecordType), 1, f_read))
		{
			if (i != id)
			{
				fwrite(&tmp, sizeof(RecordType), 1, f_tmp);
			}
			i++;
		}
	}


	fclose(f_read);
	fclose(f_tmp);

	remove(file_name);
	rename("tmp", file_name);
	return true;
}

template <class RecordType>
bool editRecord(RecordType &new_record, int id, const char *file_name)
{
	FILE *f;
	fopen_s(&f, file_name, "r+");
	if (f == NULL)
		return false;

	fseek(f, id * sizeof(RecordType), SEEK_SET);

	if (!fwrite(&new_record, sizeof(RecordType), 1, f))
		return false;

	fclose(f);
	return true;
}

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

	//printf("Thu vien co %d doc gia:\n", n);
	for (int i = 0; i < n; i++)
	{
		//printf("Doc gia thu %d: \n", i);
		fread_s(&buffer, sizeof(RecordType), sizeof(RecordType), 1, f);
		print(buffer, i + 1);
	}

	fclose(f);
	return n;
}