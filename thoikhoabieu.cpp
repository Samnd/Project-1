#include "stdafx.h"
#include "thoikhoabieu.h"
#include <iostream>

using namespace std;

thoikhoabieu::thoikhoabieu()
{
	tiet1 = 0;
	tiet2 = 0;
	tiet3 = 0;
	tiet4 = 0;
	tiet5 = 0;
	tiet6 = 0;
	tiet7 = 0;
	tiet8 = 0;
	tiet9 = 0;
	tiet10 = 0;
	tiet11 = 0;
	tiet12 = 0;
}
void thoikhoabieu::Setvalue(int giatri, int vitri)
{
	if (vitri == 1)	tiet1 = giatri;
	else if (vitri == 2) tiet2 = giatri;
	else if (vitri == 3) tiet3 = giatri;
	else if (vitri == 4) tiet4 = giatri;
	else if (vitri == 5) tiet5 = giatri;
	else if (vitri == 6) tiet6 = giatri;
	else if (vitri == 7) tiet7 = giatri;
	else if (vitri == 8) tiet8 = giatri;
	else if (vitri == 9) tiet9 = giatri;
	else if (vitri == 10) tiet10 = giatri;
	else if (vitri == 11) tiet11 = giatri;
	else tiet12 = giatri;
}
int thoikhoabieu::Getvalue(int vitri)
{

	if (vitri == 1) return tiet1;
	else if (vitri == 2) return tiet2;
	else if (vitri == 3) return tiet3;
	else if (vitri == 4) return tiet4;
	else if (vitri == 5) return tiet5;
	else if (vitri == 6) return tiet6;
	else if (vitri == 7) return tiet7;
	else if (vitri == 8) return tiet8;
	else if (vitri == 9) return tiet9;
	else if (vitri == 10) return tiet10;
	else if (vitri == 11) return tiet11;
	else return tiet12;
}

thoikhoabieu::~thoikhoabieu()
{
}
