#pragma once
#include "Init.h"
#include <stdio.h>
#include <time.h>

//ham chuyen tu kieu Time sang tm
void TimeTotm(Time &input, tm &result)
{
	result.tm_sec = 0;
	result.tm_min = 0;
	result.tm_hour = 0;
	result.tm_mday = input.ngay;
	result.tm_mon = input.thang - 1;
	result.tm_year = input.nam - 1900;
}

//Ham chuyen tu kieu tm sang Time
void tmToTime(tm &input, Time &result)
{
	result.ngay = input.tm_mday;
	result.thang = input.tm_mon + 1;
	result.nam = input.tm_year + 1900;
}

//Them n ngay vao thoi diem input, ket qua luu vao result
//Loi dung ham gmtime_s de chuyen ve time dung cau truc
//=> phai su dung kieu tm lam trung gian
//result = input + n 
void addNDay(Time &input, int n, Time &result)
{
	tm tmp;

	TimeTotm(input, tmp);	

	tmp.tm_mday += (n + 1);

	time_t day = mktime(&tmp);	//chuyen tm sang time_t
	gmtime_s(&tmp, &day);		//chuyen time_t ve tm, luc nay tmp da thanh ngay thang nam hop le

	tmToTime(tmp, result);		//luu ket qua
}


//Khoang cach tu thoi diem b den thoi diem a tinh theo ngay
int timeDiff(Time &t2, Time &t1)
{
	tm tmp1, tmp2;
	TimeTotm(t1, tmp1);
	TimeTotm(t2, tmp2);

	return difftime(mktime(&tmp2), mktime(&tmp1)) / 86400;	//difftime tra ve theo s => chia 86400 de lay ngay
}

//Ham lay ngay thagn nam hien tai
void now(Time &result) {
	time_t now = time(0);
	tm tmp;
	gmtime_s(&tmp, &now);
	tmToTime(tmp, result);
}

void show(Time &t)
{
	printf("%d/%d/%d\n", t.ngay, t.thang, t.nam);
}