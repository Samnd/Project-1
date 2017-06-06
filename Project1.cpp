#include "stdafx.h"
#include "lophoc.h"
#include "monhoc.h"
#include "thoikhoabieu.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <regex>
#include <fstream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

//KHAI BÁO CÁC CẤU TRÚC LƯU
typedef struct node_lh
{
	Lophoc loptc;
	node_lh *next;
}Node_LopHoc;

typedef struct node_mh
{
	monhoc subject;
	node_mh *next;
}Node_MonHoc;

typedef struct CGBS
{
	string MaMonHoc;
	Node_LopHoc *ListClass;
	struct CGBS *next;
	int countOfClass;
}GroupBySubject;
typedef struct RC
{
	string MaMonHoc;
	int MaLop;
}Record;
//KẾT THÚC KHAI BÁO CẤU TRÚC

//ĐỌC DS MÔN HỌC
void createListSubject(Node_MonHoc *&ds_MonHoc)
{
	ds_MonHoc = NULL;
}
//Kiểm tra bản ghi đã đến học phần tiếp theo hay chưa
bool checkNext(string str)
{
	regex pattern("[a-zA-Z]+[a-zA-Z]+[0-9]+[0-9]+[0-9]+[0-9]");
	return regex_match(str, pattern);
}

void readASubject(ifstream& input, monhoc &monHoc)
{
	int numb = 0;
	int vitri;
	string str;
	vitri = input.tellg();
	getline(input, str);
	monHoc.SetMaHP(str);
	vitri = input.tellg();
	getline(input, str);
	do
	{
		if (str != "") break;
		vitri = input.tellg();
		getline(input, str);
	} while (true);
	if (checkNext(str))
	{
		str = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	monHoc.SetTenHP(str);
	vitri = input.tellg();
	input >> numb;
	if (numb < 0)
	{
		input.seekg(vitri, ios::beg);
		return;
	}
	monHoc.SetTCHP(numb);
	getline(input, str);
}
//Thêm một môn học vào danh sách môn học
void InsertSubject(Node_MonHoc *&ds_MonHoc, Node_MonHoc *nodeSubject)
{
	if (ds_MonHoc == NULL)
	{
		ds_MonHoc = nodeSubject;
	}
	else
	{
		nodeSubject->next = ds_MonHoc;
		ds_MonHoc = nodeSubject;
	}
}

int readAllSubject(ifstream &input, Node_MonHoc *&ds_MonHoc)
{
	int countTCHP = 0;
	input.seekg(0, ios::end); //dịch con trỏ đọc tới cuối file
	if (!input.tellg()) //nếu file rỗng, trả về -1
	{
		return -1;
	}
	else
	{
		input.seekg(0, ios::beg);
		while (input.eof() == false)
		{
			monhoc monHoc;
			cin.sync();
			readASubject(input, monHoc);
			int tchp = 0;
			tchp = monHoc.GetTCHP();
			countTCHP += tchp;
			if (countTCHP > 24)
			{
				cout << "Ban da chon so luong mon hoc toi da cho hoc ki nay!" << endl;
				return 0;
			}
			else
			{
				Node_MonHoc *nodeSubject = new Node_MonHoc;
				nodeSubject->subject = monHoc;
				nodeSubject->next = NULL;
				InsertSubject(ds_MonHoc, nodeSubject);
			}
		}
		return 0;
	}
}
//KẾT THÚC ĐỌC DANH SÁCH MÔN HỌC

//ĐỌC DS LỚP HỌC
void createListClass(GroupBySubject *&ds_LopHoc)
{
	ds_LopHoc = NULL;
}

bool readAClass(ifstream &input, Lophoc &lopHoc)
{
	int vitri;
	string str;
	int numb;
	getline(input, str);
	vitri = input.tellg();
	input >> numb;
	if (numb < 10000 || numb > 99999)
		return false;
	lopHoc.SetMaLop(numb);
	getline(input, str);
	vitri = input.tellg();
	getline(input, str);
	do
	{
		if (str != "") break;
		vitri = input.tellg();
		getline(input, str);
	} while (true);
	if (str == "TC")
	{
		str = "";
		input.seekg(vitri, ios::beg);
		return false;
	}
	lopHoc.SetMaHP(str);
	vitri = input.tellg();
	getline(input, str);
	do
	{
		if (str != "") break;
		vitri = input.tellg();
		getline(input, str);
	} while (true);
	if (str == "TC")
	{
		str = "";
		input.seekg(vitri, ios::beg);
		return false;
	}
	lopHoc.SetTenHP(str);
	input >> numb;
	if (numb < 2 || numb > 7)
		return false;
	lopHoc.SetThu(numb);
	input >> numb;
	if (numb < 1 || numb > 12)
		return false;
	lopHoc.SetStart(numb);
	input >> numb;
	if (numb < 1 || numb > 12)
		return false;
	lopHoc.SetEnd(numb);
	getline(input, str);
	return true;
}
//Tạo một danh sách môn học mới
void createNewGroup(GroupBySubject *&newGroup, Node_LopHoc *nodeClass)
{
	newGroup->MaMonHoc = (nodeClass->loptc).GetmaHP();
	newGroup->ListClass = nodeClass;
	newGroup->countOfClass = 1;
}
//Thêm danh sách lớp học của một môn học mới vào ds_LopHoc
void addASubject(GroupBySubject *newGroup, GroupBySubject *&ds_LopHoc)
{
	if (ds_LopHoc == NULL)
	{
		ds_LopHoc = newGroup;
		ds_LopHoc->next = ds_LopHoc;
	}
	else
	{
		GroupBySubject *p = ds_LopHoc;
		while (true)
		{
			if (p->next == ds_LopHoc) break;
			p = p->next;
		}
		p->next = newGroup;
		newGroup->next = ds_LopHoc;
	}
}
//Thêm một lớp vào ds lớp học của một môn học
void InsertClass(GroupBySubject *&ds_LopHoc, Node_LopHoc *nodeClass)
{
	bool checkExist = false;
	if (ds_LopHoc != NULL)
	{
		GroupBySubject *p = ds_LopHoc;
		while (true)
		{
			if (_stricmp((p->MaMonHoc).c_str(), ((nodeClass->loptc).GetmaHP()).c_str()) == 0)
			{
				checkExist = true;
				Node_LopHoc *pNode;
				p->countOfClass += 1;
				if (p->ListClass == NULL)
				{
					p->ListClass = nodeClass;
					break;
				}
				else
				{
					pNode = p->ListClass;
					p->ListClass = nodeClass;
					nodeClass->next = pNode;
					break;
				}
			}
			if (p->next == ds_LopHoc) break;
			p = p->next;
		}
	}
	if (ds_LopHoc == NULL || !checkExist)
	{
		GroupBySubject *newGroup = new GroupBySubject;
		createNewGroup(newGroup, nodeClass);
		addASubject(newGroup, ds_LopHoc);
	}
}

int readAllClassAndGroupBy(ifstream& input, GroupBySubject *&ds_LopHoc)
{
	input.seekg(0, ios::end);
	if (!input.tellg())  //kiểm tra file có rỗng không
	{
		return -1;
	}
	else
	{
		input.seekg(0, ios::beg);
		while (input.eof() == false)
		{
			Lophoc lopHoc;
			cin.sync();
			bool result = readAClass(input, lopHoc);
			if (result == false) continue;
			Node_LopHoc *nodeClass = new Node_LopHoc;
			nodeClass->loptc = lopHoc;
			nodeClass->next = NULL;
			InsertClass(ds_LopHoc, nodeClass);
		}
		return 0;
	}
}
//KẾT THÚC ĐỌC DANH SÁCH LỚP HỌC

//ĐẶT CÁC ĐIỀU KIỆN
//Mật độ thời khóa biểu
void setMyStyle(bool &myStyle)
{
	int chon;
	cout << "Ban muon thoi khoa bieu thua hay day: (0.Thua 1.Day) :";
	cin >> chon;
	if (chon == 0) myStyle = false;
	else myStyle = true;
	cout << "Done!!!"<<endl;
}
//Thêm ưu tiên cho một lớp học
void setOffer2(GroupBySubject *&ds_LopHoc, int id)
{
	GroupBySubject *p = ds_LopHoc;
	bool result = false;
	while (true)
	{
		if (p == NULL)
		{
			cout << "Ban chua nhap lop hoc nao!" << endl;
			break;
		}
		Node_LopHoc *pNode = p->ListClass;
		while (true)
		{
			if (pNode == NULL) break;
			if (pNode->loptc.Getmalop() == id)
			{
				pNode->loptc.SetPrefer(1);
				result = true;
				break;
			}
			if (pNode->next == NULL) break;
			pNode = pNode->next;
		}
		if (p->next == ds_LopHoc) break;
		p = p->next;
	}
	if (!result) cout << "Khong tim thay ma hoc phan hoac ma lop." << endl;
	else cout << "Done!" << endl;
}

void SetOffer(thoikhoabieu TKB[6], ifstream &input, int &CountOfOffer)
{
	input.open("Offer.txt", ios_base::in);
	if (input.fail())
	{
		cout << "Khong mo duoc file." << endl;
		system("pause");
		return;
	}
	while (!input.eof())
	{
		int thu;
		input >> thu;
		while (true)
		{
			string str;
			int vitri = input.tellg();
			getline(input, str);
			if (str == ".") break;
			else input.seekg(vitri, ios::beg);
			int num = 0;
			input >> num;
			TKB[thu - 2].Setvalue(1, num);
			CountOfOffer++;
		}
	}
	input.close();
}
void SetAvoid(thoikhoabieu TKB[6], ifstream &input, int &CountOfAvoid)
{
	input.open("Avoid.txt", ios_base::in);
	if (input.fail())
	{
		cout << "Khong mo duoc file." << endl;
		system("pause");
		return;
	}
	while (!input.eof())
	{
		int thu;
		input >> thu;
		while (true)
		{
			string str;
			int vitri = input.tellg();
			getline(input, str);
			if (str == ".") break;
			else input.seekg(vitri, ios::beg);
			int num = 0;
			input >> num;
			TKB[thu - 2].Setvalue(2, num);
			CountOfAvoid++;
		}
	}
	input.close();
}
//Thêm ưu tiên và không ưu tiên cho các tiết học trong tuần
void SetConditions(thoikhoabieu TKB[6], ifstream &input, int &CountOfAvoid, int &CountOfOffer)
{
	SetOffer(TKB, input, CountOfOffer);
	SetAvoid(TKB, input, CountOfAvoid);
}
//KẾT THÚC NHẬP CÁC ĐIỀU KIỆN

//BẮT ĐẦU XỬ LÝ MÔN HỌC
bool CheckSubject(string str, vector<string> vet)
{
	for (int i = 0; i < vet.size(); ++i)
	{
		if (_stricmp(str.c_str(), vet[i].c_str()) == 0)
			return true;
	}
	return false;
}
//tìm môn học có số lớp học bé nhất mà chưa được sắp xếp
string FindMinSubject(GroupBySubject *ds_LopHoc, vector<string> &vet)
{
	GroupBySubject *p = ds_LopHoc;
	string temp = "";
	int min = 100;
	while (true)
	{
		if (!CheckSubject(p->MaMonHoc, vet))
		{
			if (p->countOfClass < min)
			{
				min = p->countOfClass;
				temp = p->MaMonHoc;
			}
		}
		if (p->next == ds_LopHoc) break;
		p = p->next;
	}
	vet.push_back(temp);
	return temp;
}

//Hàm trả SortSubject về QueSub với thứ tự các môn học có số lớp tăng dần
void SortSubject(GroupBySubject *ds_LopHoc, queue<string> &QueSub, int CountOfSubject)
{
	std::vector<string> vet;
	while (QueSub.size() < CountOfSubject)
	{
		string result;
		result = FindMinSubject(ds_LopHoc, vet);
		QueSub.push(result);
	}
}
//KẾT THÚC XỬ LÝ MÔN HỌC

//Trả về số môn học cần học
int CountTheSubject(Node_MonHoc *&ds_MonHoc)
{
	int soMonHoc = 0;
	Node_MonHoc *p = ds_MonHoc;
	while (true)
	{
		soMonHoc++;
		if (p->next == NULL) break;
		p = p->next;
	}
	return soMonHoc;
}
//KẾT THÚC CÁC HÀM ĐẾM

//CÁC HÀM TIỆN ÍCH
//Hàm in kết quả
void PrintResult(thoikhoabieu TKB[6])
{
	cout << left << setw(7) <<"       "<< setw(8) << "Tiet 1" << setw(8) << "Tiet 2" << setw(8) << "Tiet 3" << setw(8) << "Tiet 4" << setw(8) << "Tiet 5" << setw(8) << "Tiet 6" << setw(8) << "Tiet 7" << setw(8) << "Tiet 8" << setw(8) << "Tiet 9" << setw(8) << "Tiet 10" << setw(8) << "Tiet 11" << setw(8) << "Tiet 12" << endl;
	for (int i = 0; i < 6; ++i)
	{
		cout << left << setw(2) << "Thu " << i+2 <<setw(2)<<"  "<< setw(8) << TKB[i].Getvalue(1) << setw(8) << TKB[i].Getvalue(2) << setw(8) << TKB[i].Getvalue(3) << setw(8) << TKB[i].Getvalue(4) << setw(8) << TKB[i].Getvalue(5) << setw(8) << TKB[i].Getvalue(6) << setw(8) << TKB[i].Getvalue(7) << setw(8) << TKB[i].Getvalue(8) << setw(8) << TKB[i].Getvalue(9) << setw(8) << TKB[i].Getvalue(10) << setw(8) << TKB[i].Getvalue(11) << setw(8) << TKB[i].Getvalue(12) << endl;
	}
}
//Trả về lớp học có mã lớp học là id
Lophoc FindId(GroupBySubject *ds_LopHoc, int id)
{
	GroupBySubject *p = ds_LopHoc;
	while (true)
	{
		Node_LopHoc *pNode = p->ListClass;
		while (true)
		{
			if ((pNode->loptc).Getmalop() == id)
			{
				return pNode->loptc;
			}
			if (pNode->next == NULL || pNode->next == p->ListClass) break;
			pNode = pNode->next;
		}
		if (p->next == ds_LopHoc) break;
		p = p->next;
	}
}
void EarseTimeTable(thoikhoabieu TKB[6])
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 1; j < 13; ++j)
		{
			TKB[i].Setvalue(0, j);
		}
	}
}
string Whatis(GroupBySubject *ds_Lophoc, int id)
{
	GroupBySubject *p = ds_Lophoc;
	while (true)
	{
		Node_LopHoc *pNode = p->ListClass;
		while (true)
		{
			if (pNode->loptc.Getmalop() == id)
			{
				string str = pNode->loptc.GetTenHP();
				return str;
			}
			if (pNode->next == NULL) break;
			pNode = pNode->next;
		}
		if (p->next == ds_Lophoc) break;
		p = p->next;
	}
	return "None";
}
//KẾT THÚC HÀM TIỆN ÍCH

//SINH QUẦN THỂ ĐẦU TIÊN
//Hàm CheckClass trả về lớp học có thêm được vào thời khóa biểu hay không
bool CheckClass(thoikhoabieu TKB[6], Lophoc lopHoc)
{
	int thu = lopHoc.Getthu();
	int start = lopHoc.Getstart();
	int end = lopHoc.Getend();
	for (int i = start; i < end + 1; ++i)
	{
		int status = TKB[thu - 2].Getvalue(i);
		if (status != 0 && status != 1 && status != 2)
		{
			return false;
		}
		else continue;
	}
	return true;
}
//Hàm SearchListClass trả về một danh sách liên kết đơn các lớp học của môn có mã là str
Node_LopHoc *SearchListClass(GroupBySubject *&ds_LopHoc, string str)
{
	GroupBySubject *p = ds_LopHoc;
	Node_LopHoc *pNode = NULL;
	while (true)
	{
		if (_stricmp((p->MaMonHoc).c_str(), str.c_str()) == 0)
		{
			pNode = p->ListClass;
			break;
		}
		if (p->next == ds_LopHoc)
		{
			break;
		}
		p = p->next;
	}
	return pNode;
}
//Chọn ra một lớp để xếp vào thời khóa biểu, với các lớp có ưu tiên, nếu lớp đó xếp được vào thời khóa biểu, chọn lớp này, nếu không hủy bỏ sự ưu tiên
int ChooseClass(GroupBySubject *&ds_LopHoc, thoikhoabieu TKB[6], string str)
{
	Node_LopHoc *pTemp = SearchListClass(ds_LopHoc, str);
	if (pTemp == NULL) return 0;
	int result = 0;
	Node_LopHoc *p1 = pTemp;
	while(true)
	{
		if ((p1->loptc).GetPrefer() == 1)
		{
			if (CheckClass(TKB, p1->loptc))
			{
				result = (p1->loptc).Getmalop();
				return result;
			}
			else
			{
				p1->loptc.SetPrefer(0);
				break;
			}
		}
		if (p1->next == NULL) break;
		p1 = p1->next;
	}
	Node_LopHoc *p2 = pTemp;
	while(true)
	{
		if (CheckClass(TKB, p2->loptc))
		{
			result = (p2->loptc).Getmalop();
			return result;
		}
		if (p2->next == NULL) break;
		p2 = p2->next;
	}
	return 0;
}

void AddClass(thoikhoabieu TKB[6], Lophoc lop_cur)
{
	int thu = lop_cur.Getthu();
	int start = lop_cur.Getstart();
	int end = lop_cur.Getend();
	int id = lop_cur.Getmalop();
	for (int i = start; i < end + 1; ++i)
	{
		TKB[thu - 2].Setvalue(id, i);
	}
}
//Hàm sinh ra thời khóa biểu đầu tiên
void GenerateFirst(GroupBySubject *&ds_LopHoc, thoikhoabieu TKB[6], queue<string> &QueSub,int CountOfSubject, vector<Record> &Present)
{
	queue<string> QueInner = QueSub;
	int i = 0;
	while(i < CountOfSubject)
	{
		string str = QueInner.front();
		QueInner.pop();
		int temp = ChooseClass(ds_LopHoc,TKB, str);
		if (temp == 0)
		{
			cout << "Khong the xep duoc thoi khoa bieu" << endl;
			return;
		}
		Record newRecord;
		newRecord.MaMonHoc = str;
		newRecord.MaLop = temp;
		Present.push_back(newRecord);
		Lophoc lop_cur = FindId(ds_LopHoc, temp);
		AddClass(TKB, lop_cur);
		i++;
	}
}
//Hàm kiểm tra độ hiệu quả của thời khóa biểu
int CheckTimeTable(thoikhoabieu TKB[6], bool myStyle, int CountOfOffer, int CountOfAvoid)
{
	int all_day = 0, free = 0, hole = 0, offer = 0, avoid = 0, free_all_day = 0;
	for (int i = 0; i < 6; ++i)
	{
		int count1 = 0, count2 = 0;
		for (int j = 1; j < 7; ++j)
		{
			if (TKB[i].Getvalue(j) == 0 || TKB[i].Getvalue(j) == 1 || TKB[i].Getvalue(j) == 2)
			{
				count1++;
			}
		}
		for (int j = 7; j < 13; ++j)
		{
			if (TKB[i].Getvalue(j) == 0 || TKB[i].Getvalue(j) == 1 || TKB[i].Getvalue(j) == 2)
			{
				count2++;
			}
		}
		if (count1 < 6 && count2 < 6)
		{
			free_all_day += 12 - count1 - count2;
			all_day++;
		}
		if (count1 == 6) free++;
		if (count2 == 6) free++;
		if (count1 < 6)
		{
			hole += count1;
		}
		if (count2 < 6)
		{
			hole += count2;
		}
	}
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 1; j < 13; ++j)
		{
			if (TKB[i].Getvalue(j) == 1)
			{
				offer++;
			}
			if (TKB[i].Getvalue(j) == 2)
			{
				avoid++;
			}
		}
	}
	int point = 0;
	if (myStyle)
	{
		point = all_day*7 + free*4 - hole*3 + (CountOfOffer - offer)*5 - (CountOfAvoid - avoid)*3 - free_all_day*2;
	}
	else
	{
		point = all_day*4 + free*7 - hole*4 + (CountOfOffer - offer)*5 - (CountOfAvoid - avoid)*3 - free_all_day*2;
	}
	return point;
}
//Tìm ra những môn học có thể thay đổi
void ChangeSubject(GroupBySubject *&ds_LopHoc, std::vector<string> &ChangeList)
{
	GroupBySubject *p = ds_LopHoc;
	while(true)
	{
		bool prefer = false;
		Node_LopHoc *pp = p->ListClass;
		while(true)
		{
			if ((pp->loptc).GetPrefer() == 1)
			{
				prefer = true;
				break;
			}
			if (pp->next == NULL) break;
			pp = pp->next;
		}
		if (p->countOfClass > 1 && prefer == false)
		{
			ChangeList.push_back(p->MaMonHoc);
		}
		if (p->next == ds_LopHoc) break;
		p = p->next;
	}
}

int IsInTrash(Lophoc lh, std::vector<int> Trash)
{
	int id = lh.Getmalop();
	for (int i = 0; i < Trash.size(); ++i)
	{
		if (Trash[i] == id)
			return i;
	}
	return -1;
}
//Chọn một lớp có thể thay vào thời khóa biểu
int ChooseOneClass(GroupBySubject *ds_LopHoc, string str, vector<int> &Trash, thoikhoabieu TKB[6])
{
	GroupBySubject *p = ds_LopHoc;
	Node_LopHoc *pNode;
	while(true)
	{
		if (strcmpi((p->MaMonHoc).c_str(), str.c_str()) == 0)
		{
			pNode = p->ListClass;
			break;
		}
		if (p->next == ds_LopHoc) break;
		p = p->next;
	}
	Node_LopHoc *pTemp1 = pNode;
	bool find = false;
	while(true)
	{
		if (IsInTrash(pTemp1->loptc, Trash) == -1 && CheckClass(TKB, pTemp1->loptc))
		{
			find = true;
			int result = pTemp1->loptc.Getmalop();
			return result;
		}
		if (pTemp1->next == NULL) break;
		pTemp1 = pTemp1->next;
	}
	if (find == false)
	{
		Node_LopHoc *pTemp2 = pNode;
		while(true)
		{
			if (IsInTrash(pTemp2->loptc, Trash) != -1)
			{
				int vitri = IsInTrash(pTemp2->loptc, Trash);
				Trash.erase(Trash.begin() + vitri);
			}
			if (pTemp2->next == NULL) break;
			pTemp2 = pTemp2->next;
		}
	}
	bool find_twice = false;
	Node_LopHoc *pTemp3 = pNode;
	while(true)
	{
		if (IsInTrash(pTemp3->loptc, Trash) == -1 && CheckClass(TKB, pTemp3->loptc))
		{
			find_twice = true;
			int result = pTemp3->loptc.Getmalop();
			return result;
		}
		if (pTemp3->next == NULL) break;
		pTemp3 = pTemp3->next;
	}
	if (find_twice == false)
		return 0;
}
//Thay thời khóa biểu bằng lớp đã được chọn
void ChangeTimeTable(int back_up, int temp, thoikhoabieu TKB[6])
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 1; j < 13; ++j)
		{
			int giatri = TKB[i].Getvalue(j);
			if (giatri == back_up)
			{
				TKB[i].Setvalue(temp, j);
			}
		}
	}
}
//Đưa thời khóa biểu về như cũ khi sự thay đổi không hiệu quả
void BackupTimeTable(thoikhoabieu TKB[6], vector<Record> &Present, int back_up, int temp)
{
	for (int i = 0; i < Present.size(); ++i)
	{
		if (Present[i].MaLop == temp)
		{
			Present[i].MaLop = back_up;
		}
	}
	ChangeTimeTable(temp, back_up, TKB);
}
//Hàm thay đổi cấu trúc thời khóa biểu để tìm cách xếp tốt nhất
void ChangeStructure(thoikhoabieu TKB[6], GroupBySubject *&ds_LopHoc, vector<Record> &Present, bool myStyle, int CountOfOffer, int CountOfAvoid ,int k)
{
	int n = 0;
	vector<int> Trash;
	std::vector<string> ChangeList;
	ChangeSubject(ds_LopHoc, ChangeList);
	for (int i = 0; i < Present.size(); ++i)
	{
		int temp = Present[i].MaLop;
		Trash.push_back(temp);
	}
	while(n<k && ChangeList.size() != 0)
	{
		int siz = ChangeList.size();
		string str = ChangeList[n%siz];
		int temp = ChooseOneClass(ds_LopHoc, str, Trash, TKB);
		if (temp == 0)
		{
			n++;
			continue;
		}
		else
		{
			int back_up = 0;
			int point_before = CheckTimeTable(TKB, myStyle, CountOfOffer, CountOfAvoid);
			for (int i = 0; i < Present.size(); ++i)
			{
				if (strcmpi((Present[i].MaMonHoc).c_str(), str.c_str()) == 0)
				{
					back_up = Present[i].MaLop;
					Present[i].MaLop = temp;
				}
			}
			ChangeTimeTable(back_up, temp, TKB);
			int point_after = CheckTimeTable(TKB, myStyle, CountOfOffer, CountOfAvoid);
			if (point_after >= point_before)
			{
				for (int i = 0; i < Trash.size(); i++)
				{
					if (Trash[i] == back_up)
					{
						Trash.erase(Trash.begin() + i);
						break;
					}
				}
				Trash.push_back(temp);
				n++;
				continue;
			}
			else
			{
				BackupTimeTable(TKB, Present, back_up, temp);
				n++;
				continue;
			}
		}
	}
	
}
int FindAClass(thoikhoabieu TKB[6], GroupBySubject *ds_LopHoc, vector<int> &Trash, string str)
{
	GroupBySubject *p = ds_LopHoc;
	while(true)
	{
		if (strcmpi(p->MaMonHoc.c_str(), str.c_str()) == 0)
		{
			Node_LopHoc *pp = p->ListClass;
			while(true)
			{
				if (IsInTrash(pp->loptc, Trash) == -1 && CheckClass(TKB, pp->loptc))
				{
					return pp->loptc.Getmalop();
					break;
				}
				if (pp->next == NULL) break;
				pp = pp->next;
			}
			break;
		}
		if (p->next == ds_LopHoc) break;
		p = p->next;
	}
	return 0;
}
//Xây dụng một thời khóa biểu mới từ những môn không có trong Trash
int FindNewTimetable(GroupBySubject *ds_LopHoc, vector<Record> &Present, std::vector<int> &Trash, thoikhoabieu TKB[6], vector<string> &ChangeList, ifstream &input, int &CountOfAvoid, int &CountOfOffer)
{
	EarseTimeTable(TKB);
	CountOfOffer = 0;
	CountOfAvoid = 0;
	SetConditions(TKB, input, CountOfAvoid, CountOfOffer);
	for (int i = 0; i < Present.size(); ++i)
	{
		int id = Present[i].MaLop;
		for (int j = 0; j < ChangeList.size(); ++j)
		{
			if (strcmpi(Present[i].MaMonHoc.c_str(), ChangeList[j].c_str()) == 0)
			{
				break;
			}
		}
		Lophoc lop_cur = FindId(ds_LopHoc, id);
		AddClass(TKB, lop_cur);
	}
	for (int i = 0; i < ChangeList.size(); ++i)
	{
		string str = ChangeList[i];
		int find = FindAClass(TKB, ds_LopHoc, Trash, str);
		if (find == 0)
		{
			ChangeList.erase(ChangeList.begin() + i);
			return 0;
		}
		else
		{
			for (int i = 0; i < Present.size(); ++i)
			{
				if (strcmpi(Present[i].MaMonHoc.c_str(), str.c_str()) == 0)
				{
					Present[i].MaLop = find;
					break;
				}
			}
			Lophoc lop_cur = FindId(ds_LopHoc, find);
			AddClass(TKB, lop_cur);
		}
	}
	return 1;
}
//Khi cách sắp xếp mới không hiệu quả, phục hồi lại thời khóa biểu cũ
void RestoreTimeTable(thoikhoabieu TKB[6], vector<Record> &Past, ifstream &input,int &CountOfOffer,int &CountOfAvoid, GroupBySubject *ds_LopHoc)
{
	EarseTimeTable(TKB);
	CountOfOffer = 0;
	CountOfAvoid = 0;
	SetConditions(TKB, input, CountOfAvoid, CountOfOffer);
	for (int i = 0; i < Past.size(); ++i)
	{
		int id = Past[i].MaLop;
		Lophoc lop_cur = FindId(ds_LopHoc, id);
		AddClass(TKB, lop_cur);
	}
}
//Thử tìm một quần thể mới
void FindStNew(thoikhoabieu TKB[6], GroupBySubject *&ds_LopHoc, vector<Record> &Present, bool myStyle, ifstream &input, int &CountOfAvoid, int &CountOfOffer)
{
	int n = 0;
	vector<int> Trash;
	vector<string> ChangeList;
	GroupBySubject *q = ds_LopHoc;
	int kount = 0;
	ChangeSubject(ds_LopHoc, ChangeList);
	while (true)
	{
		for (int i = 0; i < ChangeList.size(); i++)
		{
			if (strcmpi(q->MaMonHoc.c_str(), ChangeList[i].c_str()) == 0)
			{
				kount += q->countOfClass;
				break;
			}
		}
		if (q->next == ds_LopHoc) break;
		q = q->next;
	}
	while(n < kount && ChangeList.size() !=0)
	{
		int siz = ChangeList.size();
		string str = ChangeList[n%siz];
		int point_before = CheckTimeTable(TKB, myStyle, CountOfOffer, CountOfAvoid);
		int back_up = 0;
		for (int i = 0; i < Present.size(); ++i)
		{
			if (strcmpi(Present[i].MaMonHoc.c_str(), str.c_str()) == 0)
			{
				back_up = Present[i].MaLop;
				break;
			}
		}
		Trash.push_back(back_up);
		std::vector<Record> Past;
		Past = Present;
		int ch = FindNewTimetable(ds_LopHoc, Present, Trash, TKB, ChangeList, input, CountOfAvoid, CountOfOffer);
		if (ch == 1)
		{
			int point_after = CheckTimeTable(TKB, myStyle, CountOfOffer, CountOfAvoid);
			if (point_after >= point_before)
			{
				n++;
				continue;
			}
			else
			{
				RestoreTimeTable(TKB, Past, input, CountOfOffer, CountOfAvoid, ds_LopHoc);
				Present = Past;
				n++;
				continue;
			}
		}
		else
		{
			RestoreTimeTable(TKB, Past, input, CountOfOffer, CountOfAvoid, ds_LopHoc);
			Present = Past;
			n++;
			continue;
		}
	}
}
int main()
{
	//ĐỌC FILE LẤY DỮ LIỆU
	ifstream input;
	input.open("Dsmonhoc.txt", ios_base::in);
	if (input.fail())
	{
		cout << "Khong the mo duoc file ds mon hoc." << endl;
		system("pause");
		return -1;
	}
	Node_MonHoc *ds_MonHoc;
	createListSubject(ds_MonHoc);
	input.sync();
	int n1 = readAllSubject(input, ds_MonHoc);
	if (n1 == -1)
	{
		cout << "File ds mon hoc rong, vui long them thong tin vao file." << endl;
		system("pause");
		return -1;
	}
	input.close();
	input.open("Dslophoc.txt", ios_base::in);
	if (input.fail())
	{
		cout << "Khong the mo duoc file ds lop hoc." << endl;
		system("pause");
		return -1;
	}
	GroupBySubject *ds_LopHoc;
	createListClass(ds_LopHoc);
	cin.sync();
	int n2 = readAllClassAndGroupBy(input, ds_LopHoc);
	if (n2 == -1)
	{
		cout << "File ds lop hoc rong, vui long them thong tin vao file." << endl;
		system("pause");
		return -1;
	}
	input.close();
	//XẾP THỜI KHÓA BIỂU
	int Lua_chon;
	thoikhoabieu TKB[6];
	bool myStyle;
	int CountOfAvoid = 0, CountOfOffer = 0;
	int CountOfSubject = 0;
	CountOfSubject = CountTheSubject(ds_MonHoc);
	queue<string> QueSub;
	SortSubject(ds_LopHoc, QueSub, CountOfSubject);
	SetConditions(TKB, input, CountOfAvoid, CountOfOffer);
	do
	{
		cout << "-------------MENU------------------" << endl;
		cout << "1.Nhap mat do cho thoi khoa bieu." << endl;
		cout << "2.Them uu tien cho lop hoc." << endl;
		cout << "3.Sap xep thoi khoa bieu." << endl;
		cout << "4.Thoat." << endl;
		cout << "Ban chon: ";
		cin >> Lua_chon;
		if (cin.fail() || Lua_chon < 1 || Lua_chon > 4)
		{
			cin.clear();	//Bỏ qua nếu xuất hiện lỗi
			cin.ignore(32767, '\n');	//Xóa bộ đệm đến khi gặp \n
			system("cls");
			cout << "Ban chon sai! vui long thu lai!" << endl;
		}
		else
		{
			system("cls");
			switch (Lua_chon)
			{
			case 1:
			{
				setMyStyle(myStyle);
				break;
			}
			case 2:
			{
				system("cls");
				fflush(stdin);
				int id;
				cout << "---------------------------" << endl;
				cout << "Moi ban nhap ma lop: ";
				cin >> id;
				cout << endl;
				string str = Whatis(ds_LopHoc, id);
				if (strcmpi(str.c_str(), "None") == 0)
				{
					cout << "Khong tim thay ma lop nay."<<endl;
					break;
				}
				cout << "Them lop uu tien cho hoc phan:" << str<<endl;
				setOffer2(ds_LopHoc, id);
				break;
			}
			case 3:
			{
				std::vector<Record> Present;
				GenerateFirst(ds_LopHoc, TKB, QueSub, CountOfSubject, Present);
				FindStNew(TKB, ds_LopHoc, Present, myStyle, input, CountOfAvoid, CountOfOffer);
				int k;
				cout << "Moi ban nhap muc do duyet: ";
				cin >> k;
				ChangeStructure(TKB, ds_LopHoc, Present, myStyle, CountOfOffer, CountOfAvoid, k);
				system("cls");
				PrintResult(TKB);
				break;
			}
			case 4:
			{
				break;
			}
			}
		}
	} while (Lua_chon != 4);
	system("pause");
	return 0;
}