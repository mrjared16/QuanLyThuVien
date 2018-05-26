#pragma once
#include "Init.h"
#include <stdio.h>
#include <time.h>

void TimeTotm(Time &input, tm &result)
{
	result.tm_sec = 0;
	result.tm_min = 0;
	result.tm_hour = 0;
	result.tm_mday = input.ngay;
	result.tm_mon = input.thang - 1;
	result.tm_year = input.nam - 1900;
}

void tmToTime(tm &input, Time &result)
{
	result.ngay = input.tm_mday;
	result.thang = input.tm_mon + 1;
	result.nam = input.tm_year + 1900;
}

void addNDay(Time &input, int n, Time &result)
{
	tm tmp;

	TimeTotm(input, tmp);

	tmp.tm_mday += (n + 1);

	time_t day = mktime(&tmp);
	gmtime_s(&tmp, &day);

	tmToTime(tmp, result);
}

int timeDiff(Time &a, Time &b)
{
	tm tmpa, tmpb;
	TimeTotm(a, tmpa);
	TimeTotm(b, tmpb);

	return difftime(mktime(&tmpa), mktime(&tmpb)) / 86400;
}

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