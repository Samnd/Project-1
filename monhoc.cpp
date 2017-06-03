#include "stdafx.h"
#include "monhoc.h"
#include <string>

using namespace std;

monhoc::monhoc()
{
	maHP = "";
	tenHP = "";
}

void monhoc::SetMaHP(string str)
{
	maHP = str;
}

void monhoc::SetTenHP(string str)
{
	tenHP = str;
}

void monhoc::SetTCHP(int tinchi)
{
	TCHP = tinchi;
}
string monhoc::GetmaHP()
{
	return maHP;
}

string monhoc::GettenHP()
{
	return tenHP;
}
int monhoc::GetTCHP()
{
	return TCHP;
}
monhoc::~monhoc()
{

}
