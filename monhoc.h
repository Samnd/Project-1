#ifndef MONHOC_H_
#define MONHOC_H_

#include <string>

class monhoc
{
private:
	string maHP;
	string tenHP;
	int prefer;
public:
	monhoc();
	void SetMonHoc();
	void SetPrefer();
	string GetmaHP();
	string GettenHP();
	string GetPrefer();
	~monhoc();
	
};
#endif