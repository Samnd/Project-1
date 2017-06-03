#include "stdafx.h"
#include "lophoc.h"
#include <iostream>
#include <stdio.h>

using namespace std;

Lophoc::Lophoc()
{
	maLop = 0;
	maHP = "";
	tenHP = "";
	thu = 0;
	start = 0;
	end = 0;
	kip = "";
	prefer = 0;
}

void Lophoc::SetPrefer(int numb)
{
	prefer = numb;
}
int Lophoc::GetPrefer()
{
	return prefer;
}
void Lophoc::SetMaLop(int numb)
{
	maLop = numb;
}
void Lophoc::SetMaHP(string str)
{
	maHP = str;
}
void Lophoc::SetTenHP(string str)
{
	tenHP = str;
}
void Lophoc::SetThu(int th)
{
	thu = th;
}
void Lophoc::SetStart(int numb)
{
	start = numb;
}
void Lophoc::SetEnd(int numb)
{
	end = numb;
}
int	Lophoc::Getmalop()
{
	return maLop;
}
string Lophoc::GetmaHP()
{
	return maHP;
}
string Lophoc::GetTenHP()
{
	return tenHP;
}
int	Lophoc::Getthu()
{
	return thu;
}
int	Lophoc::Getstart()
{
	return start;
}
int	Lophoc::Getend()
{
	return end;
}
Lophoc::~Lophoc()
{
}
