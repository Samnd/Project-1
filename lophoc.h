#ifndef LOPHOC_H_
#define LOPHOC_H_

#include <string>
#include <string.h>

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
	void SetLopHoc();
	int Getmalop();
	string GetmaHP();
	int Getthu();
	int Getstart();
	int Getend();
	~Lophoc();
	
};
#endif
