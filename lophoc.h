#ifndef LOPHOC_H_
#define LOPHOC_H_

#include <string>

class Lophoc
{
private:
	int maLop;
	string maHP;
	int thu;
	int start;
	int end;
public:
	Lophoc();
	SetLopHoc();
	Getmalop();
	GetmaHP();
	Getthu();
	Getstart();
	Getend();
	~Lophoc();
	
};
#endif