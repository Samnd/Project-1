#include "thoikhoabieu.h"
#include <iostream>

using namespace std;

thoikhoabieu::thoikhoabieu()
{
	this->tiet1 = 0;
	this->tiet2 = 0;
	this->tiet3 = 0;
	this->tiet4 = 0;
	this->tiet5 = 0;
	this->tiet6 = 0;
	this->tiet7 = 0;
	this->tiet8 = 0;
	this->tiet9 = 0;
	this->tiet10 = 0;
	this->tiet11 = 0;
	this->tiet12 = 0;
}
void thoikhoabieu::Setvalue(int giatri, int vitri){
	if (vitri == 0)	this->tiet1 = giatri;
	else if (vitri == 1) this->tiet2 = giatri;
	else if (vitri == 2) this->tiet3 = giatri;
	else if (vitri == 3) this->tiet4 = giatri;
	else if (vitri == 4) this->tiet5 = giatri;
	else if (vitri == 5) this->tiet6 = giatri;
	else if (vitri == 6) this->tiet7 = giatri;
	else if (vitri == 7) this->tiet8 = giatri;
	else if (vitri == 8) this->tiet9 = giatri;
	else if (vitri == 9) this->tiet10 = giatri;
	else if (vitri == 10) this->tiet11 = giatri;
	else this->tiet12 = giatri;
}
int thoikhoabieu::Getvalue(int vitri){

	if (vitri == 0) return this->tiet1;
	else if (vitri == 1) return this->tiet2;
	else if (vitri == 2) return this->tiet3;
	else if (vitri == 3) return this->tiet4;
	else if (vitri == 4) return this->tiet5;
	else if (vitri == 5) return this->tiet6;
	else if (vitri == 6) return this->tiet7;
	else if (vitri == 7) return this->tiet8;
	else if (vitri == 8) return this->tiet9;
	else if (vitri == 9) return this->tiet10;
	else if (vitri == 10) return this->tiet11;
	else return this->tiet12;
}