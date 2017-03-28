#include "lophoc.h"
#include "monhoc.h"
#include "thoikhoabieu.h"
#include <iostream>
#include <string>

using namespace std;

void InputClasses(lophoc[] classes)
{
	int countOfClass=0;
	int conti;
	while(1)
	{
		classes[countOfClass].SetLopHoc();
		countOfClass++;
		cout<<"Ban muon: 1-Nhap tiep! 0-Thoat";
		cin>>conti;
		if (conti == 1) continue;
		if (conti == 0) break;
	}
}
void InputSubject(monhoc[] subject)
{
	int countOfSubject=0;
	int conti;
	while(1)
	{
		classes[countOfSubject].SetMonHoc();
		countOfSubject++;
		cout<<"Ban muon: 1-Nhap tiep! 0-Thoat";
		cin>>conti;
		if (conti == 1) continue;
		if (conti == 0) break;
	}
}
//Make Condition
void Avoid(int[] thu, int[] tiet, thoikhoabieu[] TKB)
{
	for (int i = 0; i < thu.length(); ++i)
	{
		for (int j = 0; j < tiet.length(); ++j)
		{
			int day=thu[i];
			int period=tiet[j];
			TKB[day-2].Setvalue(2,period-1);
		}
	}
}
void Offer1(int[] thu, int[] tiet, thoikhoabieu[] TKB)
{
	for (int i = 0; i < thu.length(); ++i)
	{
		for (int j = 0; j < tiet.length(); ++j)
		{
			int day=thu[i];
			int period=tiet[j];
			TKB[day-2].Setvalue(1,period-1);
		}
	}
}
void Offer2(string maHP, int ID, thoikhoabieu[] TKB, monhoc[] subject)
{
	for (int i = 0; i < countOfSubject; ++i)
		if (maHP == subject[i].GetmaHP())
		{
			subject[i].SetPrefer(ID);
			for (int j = 0; j < countOfClass; ++j)
			{
				if (maHP == classes[j].GetmaHP())
				{
					int day = classes[j].Getthu();
					int start = classes[j].Getstart();
					int end = classes[j].Getend();
					for (int z=start,z=<end,z++)
						TKB[day-2].Setvalue(ID,z-1);
				}
			}
		}
}
//Set Condition

void SetAvoid()
{
	int thu[6];
	int tiet[12];
	boolean inthu=TRUE; intiet=FALSE;
	while(inthu)
	{
		
	}
}







































































