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
	void SetMonHoc();
	void SetPrefer();
	string GetmaHP();
	string GettenHP();
	string GetPrefer();
	~Monhoc();
	
};
#endif