#ifndef MONHOC_H_
#define MONHOC_H_

#include <string>

class Monhoc
{
private:
	string maHP;
	string tenHP;
	int prefer;
public:
	Monhoc();
	SetMonHoc();
	SetPrefer();
	GetmaHP();
	GettenHP();
	GetPrefer();
	~Monhoc();
	
};
#endif