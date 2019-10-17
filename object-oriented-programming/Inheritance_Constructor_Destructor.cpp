/*
;|**********************************************************************;
;* Project           : CPP-Language_practise
;*
;* Program name      : Inheritance_Constructor_Destructor.cpp
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 17/10/2019
;*
;* Version           : internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Introduce what is Inheritance, Constructor, Destructor
;*
;* Revision History  :
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 17102019    lst97       1      First release
;*
;* Known Issue       :
;*
;* TODO              :
;*
;|**********************************************************************;
*/

#include "stdio.h"
#include "stdlib.h"

struct DateInfo {
private:
	int year, month, day;

public:
	DateInfo() {
		this->year = 1997;
		this->month = 1;
		this->day = 1;
	}

	DateInfo(int year, int month, int day) {
		this->year = year;
		this->month = month;
		this->day = day;
	}

	void m_fnSetDay(int day) {
		this->day = day;
		return;
	}
	void m_fnSetMonth(int month) {
		this->month = month;
		return;
	}
	void m_fnSetYear(int year) {
		this->year = year;
		return;
	}

	int m_getDay() {
		return day;
	}
	int m_getMonth() {
		return month;
	}
	int m_getYear() {
		return year;
	}

	void m_fnPrintDateInfo() {
		printf("ClassView DateInfo: %d-%d-%d\n\n", year, month, day);
		return;
	}

	~DateInfo() {
		printf("DateInfo Class Exit!\n");
	}
};

struct TimeInfo:DateInfo {
private:
	int hour, minute, second;

public:
	TimeInfo() {
		this->hour = 12;
		this->minute = 5;
		this->second = 30;
	}

	void m_fnSetHour(int hour) {
		this->hour = hour;
		return;
	}
	void m_fnSetMinute(int minute) {
		this->minute = minute;
		return;
	}
	void m_fnSetSecond(int second) {
		this->second = second;
		return;
	}

	int m_getHour() {
		return hour;
	}
	int m_getMinute() {
		return minute;
	}
	int m_getSecond() {
		return second;
	}

	void m_fnPrintDateInfo() {
		printf("ClassView DateInfo: %d-%d-%d\n\n", hour, minute, second);
		return;
	}

	~TimeInfo() {
		printf("TimeInfo Class Exit!\n");
	}
};

int main(int argc, char* argv[]) {
	int classSize;
	int year, month, day;

	// Either choose one constructor
	//DateInfo cDateInfo;
	//year = cDateInfo.m_getYear();
	//month = cDateInfo.m_getMonth();
	//day = cDateInfo.m_getDay();
	//printf("Default DateInfo: %d-%d-%d\n\n", year, month, day);

	TimeInfo cTimeInfo;
	DateInfo cDateInfo(2016, 3, 14);
	year = cDateInfo.m_getYear();
	month = cDateInfo.m_getMonth();
	day = cDateInfo.m_getDay();
	printf("Default DateInfo: %d-%d-%d\n\n", year, month, day);

	cDateInfo.m_fnSetYear(2099);
	cDateInfo.m_fnSetMonth(9);
	cDateInfo.m_fnSetDay(9);
	cDateInfo.m_fnPrintDateInfo();

	classSize = sizeof(cDateInfo);
	printf("sizeof(cDateInfo) = %d\n\n", classSize);

	typedef TimeInfo *PTimeInfo;
	typedef DateInfo *PDateInfo;

	PDateInfo pDateInfo = &cDateInfo;
	PTimeInfo pTimeInfo = &cTimeInfo;

	printf("Pointer Access:\nDateInfo: %d-%d-%d\nTimeInfo: %02d:%02d:%02d\n", 
		*((int*)pDateInfo + 0), *((int*)pDateInfo + 1), *((int*)pDateInfo + 2),
		*((int*)pTimeInfo + 3), *((int*)pTimeInfo + 4), *((int*)pTimeInfo + 5)
	);

	classSize = sizeof(cTimeInfo);
	printf("sizeof(cTimeInfo) = %d\n\n", classSize);

	return 0;
}
