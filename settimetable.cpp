#include "lophoc.h"
#include "monhoc.h"
#include "thoikhoabieu.h"
#include <iostream>
#include <string>
#include <queue>

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
// void Avoid(int[] thu, int[] tiet, thoikhoabieu[] TKB)
// {
// 	for (int i = 0; i < thu.length(); ++i)
// 	{
// 		for (int j = 0; j < tiet.length(); ++j)
// 		{
// 			int day=thu[i];
// 			int period=tiet[j];
// 			TKB[day-2].Setvalue(2,period-1);
// 		}
// 	}
// }
// void Offer1(int[] thu, int[] tiet, thoikhoabieu[] TKB)
// {
// 	for (int i = 0; i < thu.length(); ++i)
// 	{
// 		for (int j = 0; j < tiet.length(); ++j)
// 		{
// 			int day=thu[i];
// 			int period=tiet[j];
// 			TKB[day-2].Setvalue(1,period-1);
// 		}
// 	}
// }
void SetOffer2(string maHP, int ID, thoikhoabieu[] TKB, monhoc[] subject)
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

void SetAvoid(thoikhoabieu[] TKB)
{
	queue<int> Thu;
	int check=2;
	int thu;
	do{
		cout<<"Moi ban nhap thu:";
		cin>>thu;
		Thu.push(thu);
		cout<<"Ban muon nhap tiep: 1_Yes 2_No";
		cin>>check;
	} while(check==1);
	while(!Thu.empty())
	{
		int thu_cur = Thu.front();
		cout<<"Thu"<<thu_cur<<endl;
		int check_cur=2, tiet_cur;
		do{
			cout<<"Moi ban nhap tiet:";
			cin>>tiet_cur;
			TKB[thu_cur-2].Setvalue(2,tiet_cur-1);
			cout<<"Ban muon nhap tiep: 1_Yes 2_No";
			cin>>check_cur;
		}while(check_cur == 1);
		Thu.pop();
	};
}

void SetOffer(thoikhoabieu[] TKB)
{
	queue<int> Thu;
	int check=2;
	int thu;
	do{
		cout<<"Moi ban nhap thu:";
		cin>>thu;
		Thu.push(thu);
		cout<<"Ban muon nhap tiep: 1_Yes 2_No";
		cin>>check;
	} while(check==1);
	while(!Thu.empty())
	{
		int thu_cur = Thu.front();
		cout<<"Thu"<<thu_cur<<endl;
		int check_cur=2, tiet_cur;
		do{
			cout<<"Moi ban nhap tiet:";
			cin>>tiet_cur;
			TKB[thu_cur-2].Setvalue(1,tiet_cur-1);
			cout<<"Ban muon nhap tiep: 1_Yes 2_No";
			cin>>check_cur;
		}while(check_cur == 1);
		Thu.pop();
	}
}

//Set Queue
/*Hiện có 3 mảng là: classes[] chứa các lớp, subject[] chứa các môn học, TKB[] là thời khóa biểu.
Khai báo thêm DSLop[i][j] chứa id của các lớp thuộc Môn học[j]. counting[j] là số lớp của môn học j    int** &A
Mảng counting có countOfSubject phần tử, Queue chính: QueMain*/
void Add(int** &DSLop[10][20], int j,int id, int[] counting)
{
	DSLop[j][counting[j]] = id;
}
void InputQueue(queue Que, int k)
{
	Que.push(k);
}
bool isEmpty(int[] counting)
{
	for (int i = 0; i < countOfSubject; ++i)
	{
		if (counting[i] != 0) return false;
	}
	return true;
}
int Min(int[] counting)
{
	int min = counting[0], value = 0;
	for (int i = 1; i < countOfSubject; ++i)
	{
		if (counting[i] < min)
		{
			min = counting[i];
			value = i;
		}
	}
	return value;
}
void SetQueue(int* counting[], lophoc[] classes, monhoc[] subject)
{
	for (int i = 0; i < countOfClass; ++i)
	{
		for (int j= 0; i < countOfSubject; ++i)
		{
			if (classes[i].GetmaHP() == subject[j].GetmaHP())
			{
				int id = classes[i].Getmalop();
				Add(DSLop,j,id,counting);
				*counting[j]++;
			}
		}
	}
	for (int i = 0; i < countOfSubject; ++i)
	{
		bool test;
		if (subject[i].GetPrefer() != 0)
			test = true;
		else test = false;
		if (test)
		{
			InputQueue(QueMain,i);
			*counting[i] = 0;
		}
	}
	while(!isEmpty(counting))
	{
		int k = Min(counting);
		InputQueue(QueMain,k);
		*counting[k] = 0;
	}
}

/* Có một QueMain vs thứ tự là ds các môn có số lớp tăng dần, và một mảng 2 chiều Dslop[j][] chứa id của các lớp thuộc môn học [j] 
Khởi tạo một biến myStyle vs 2 giá trị, true là thưa và false là dày*/






































































