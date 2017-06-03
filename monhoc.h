#ifndef MONHOC_H_
#define MONHOC_H_

#include "stdafx.h"
#include <string>

using namespace std;

class monhoc
{
private:
	string maHP;
	string tenHP;
	int TCHP;
public:
	monhoc();
	void SetMaHP(string str);
	void SetTenHP(string str);
	void SetTCHP(int);
	string GetmaHP();
	string GettenHP();
	int GetTCHP();
	~monhoc();

};
#endif