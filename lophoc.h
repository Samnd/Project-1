#ifndef LOPHOC_H_
#define LOPHOC_H_

#include <string>
#include <vector>

using namespace std;

class Lophoc
{
private:
	int maLop;
	string maHP;
	string tenHP;
	int thu;
	int start;
	int end;
	string kip;
	int prefer;
public:
	Lophoc();
	void SetPrefer(int);
	int GetPrefer();
	void SetMaLop(int);
	void SetMaHP(string);
	void SetTenHP(string);
	void SetThu(int);
	void SetStart(int);
	void SetEnd(int);
	int Getmalop();
	string GetmaHP();
	string GetTenHP();
	int Getthu();
	int Getstart();
	int Getend();
	~Lophoc();

};
#endif
