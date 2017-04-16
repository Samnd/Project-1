#include "lophoc.h"
#include "monhoc.h"
#include "thoikhoabieu.h"
#include <iostream>
#include <string>
#include <queue>
#define MAXLOPHOC 50
#define MAXMONHOC 10

using namespace std;

lophoc classes[MAXLOPHOC];
monhoc subject[MAXMONHOC];
thoikhoabieu TKB[6];
int DSLop[10][20];
bool myStyle;
queue QueMain;
int countOfSubject=0;


void InputClasses()
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
void InputSubject()
{
	int conti;
	while(1)
	{
		subject[countOfSubject].SetMonHoc();
		countOfSubject++;
		cout<<"Ban muon: 1-Nhap tiep! 0-Thoat";
		cin>>conti;
		if (conti == 1) continue;
		if (conti == 0) break;
	}
}
//Set my style
void SetmyStyle()
{
	int chon;
	cout<<"Ban muon mat do thoi khoa bieu nhu the nao: 0.Thua 1.Day";
	cin>>chon;
	if (chon == 0) myStyle = false;
		else myStyle = true;

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
void SetOffer2(string maHP, int ID)
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
						TKB[day-2].Setvalue(ID,z);
				}
			}
		}
}
//Set Condition

void SetAvoid()
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
			TKB[thu_cur-2].Setvalue(2,tiet_cur);
			cout<<"Ban muon nhap tiep: 1_Yes 2_No";
			cin>>check_cur;
		}while(check_cur == 1);
		Thu.pop();
	};
}

void SetOffer()
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
			TKB[thu_cur-2].Setvalue(1,tiet_cur);
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
void Add(int j,int id, int[] counting)
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
void SetQueue(int* counting[])
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
lophoc FindId(int idsearch)
{
	for (int i = 0; i < countOfClass; ++i)
	{
		if (classes[i].Getmalop() == idsearch)
			return classes[i];
	}
}
int getlength(int j)
{
	int count;
	for (int i = 0; i < 20; ++i)
	{
		if (Dslop[j][i] != 0)
			count++;
	}
	return count;
}
int FindFree(int thu)
{
	int count;
	for (int i = 0; i < 12; ++i)
		if (TKB[thu-2].Getvalue(i) == 0)
			count++;
	return count;
}
int Rank(int j, int r)
{
	lophoc classtorank;
	int idsearch = Dslop[j][r];
	classtorank = FindId(idsearch);
	int thu, start, end;
	int pointOfStyle = 0, point = 0;
	thu = classtorank.Getthu();
	start = classtorank.Getstart();
	end = classtorank.Getend();
	if (subject[j].GetPrefer() != 0) point +=100;
	int freeToday = FindFree(thu);
	if (myStyle)
	{
		pointOfStyle = 12-freeToday;
		point += 2*pointOfStyle;
	}else{
		pointOfStyle = freeToday;
		point += 2*pointOfStyle;
	}
	for (int tiet=start; tiet <end+1; tiet++)
	{
		int status = TKB[thu-2].Getvalue(tiet);
		switch (status)
		{
			case 1: {point += 5; break;}
			case 2: {point -= 10; break;}
			default: break;
		}
	}
	return point;
}
void Swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}
void SortAgain(int j, int prio[])
{
	for (int g=0; g<20; g++)
		for (int h=1; h<21; h++)
		{
			if (prio[g]<prio[h])
				{
					Swap(Dslop[j][g],Dslop[j][h]);
					Swap(prio[g],prio[h]);
				}
		}
}
bool CheckClass(lophoc classcheck)
{
	int thu, start, end;
	thu = classcheck.Getthu();
	start = classcheck.Getstart();
	end = classcheck.Getend();
	for (int tiet=start; tiet<end+1; tiet++)
		if (TKB[thu-2].Getvalue[tiet] != 0)
			return false;
	return true;
}
void Choose(lophoc classtempo)
{
	int thu, start, end, malop;
	malop = classtempo.Getmalop();
	thu = classtempo.Getthu();
	start = classtempo.Getstart();
	end = classtempo.Getend();
	for (int tiet=start; tiet<end+1; tiet++)
		TKB[thu-2].Setvalue(malop,tiet);
}
// In ket qua
void PrintResult()
{
	cout<<"Thoi khoa bieu:"<<endl;
	for (int i = 0; i < 7; ++i)
		{
			cout<<"Thu "<<i+2<<"\t";
			for (int j = 0; j < 12; ++j)
			{
				int giatri = TKB[i].Getvalue(j);
				cout<<giatri<<"\t";
			}
			cout<<endl;
		}
}
void TimeTable(int i)
{
	j = QueMain.front();
	QueMain.pop();
	len = getLength(j); // ham getlength() lay gia tri do dai dslop j..
	int prio[len];
	for (int r =0; r<len; r++)
		prio[r] = Rank(j, r); //ham rank dua ra mang prio[len] voi gtri la rank..
	SortAgain(j,prio); //ham nay giup sap xep lai cac ma lop voi so giam dan cua tinh uu tien..
	for (int k = 0; k < len; ++k)
	{
		int temp = Dslop[j][k];
		lophoc classtempo;
		classtempo = FindId(temp); //ham FindId tra ve lop hoc co ma lop la temp..
		if (CheckClass(classtempo)) //kiem tra xem lop hoc co sap duoc vao tkb ko..
			Choose(classtempo); //chon va dien thong tin cua lop hoc vao tkb..
		else continue;
		if (i == countOfSubject)
		{
			PrintResult(); //in ket qua
		}
		else TimeTable(i+1);
	}
}

int main()
{
	int luachon;
	cout<<"_________________________"<<endl;
	cout<<"SAP XEP THOI KHOA BIEU"<<endl;
	cout<<"--------------------------"<<endl;
	cout<<"1.Nhap cac mon hoc."<<endl;
	cout<<"2.Nhap cac lop hoc"<<endl;
	cout<<"3.Nhap mat do thoi khoa bieu"<<endl;
	cout<<"4.Them uu tien cho lop hoc"<<endl;
	cout<<"5.Them uu tien cho tiet hoc"<<endl;
	cout<<"6.Tranh mot so tiet hoc"<<endl;
	cout<<"7.Sap xep thoi khoa bieu"<<endl;
	cout<<"8.Thoat"<<endl;
	cout<<endl;
	cout<<"Lua chon cua ban:";
	cin>>luachon;	
	do{
		switch(luachon)
		{
			case 1:{
				cout<<"Moi ban nhap mon hoc:"<<endl;
				InputSubject();
				break;
			}
			case 2:{
				cout<<"Moi ban nhap lop hoc:"<<endl;
				InputClasses();
				break;
			}
			case 3:{
				cout<<"Moi ban nhap mat do cho tkb:"<<endl;
				SetmyStyle();
				break;
			}
			case 4:{
				cout<<"Them uu tien cho lop hoc:"<<endl;
				string MaHP;
				int ID;
				cout<<"Moi ban nhap ma hoc phan:";
				fflush(stdin);
				getline(cin,MaHP);
				cout<<endl;
				cout<<"Moi ban nhap ma lop:";
				cin>>ID;
				SetOffer2(MaHP,ID);
				break;
			}
			case 5:{
				cout<<"Them uu tien cho lop hoc:"<<endl;
				SetOffer();
				break;
			}
			case 6:{
				cout<<"Tranh mot so tiet hoc:"<<endl;
				SetAvoid();
				break;
			}
			case 7:{
				cout<<"Xep thoi khoa bieu:"<<endl;
				TimeTable(1);
				break;
			}
		}
		cout<<"Lua chon cua ban:";
		cin>>luachon;
	}while(luachon != 8);
	return 0;
}






























































