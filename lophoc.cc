#include "lophoc.h"
#include <iostream>
#include <stdio.h>

using namespace std;

lophoc::lophoc()
{
	this->maLop = 0;
	this->maHP = NULL;
	this->thu = 0;
	this->start = 0;
	this->end = 0;
}
void lophoc::SetLopHoc()
{
	cout<<"Nhap ma lop:";
	cin>>this->maLop;
	cout<<endl<<"Nhap ma hoc phan:";
	fflush(stdin);
	getline(cin,this->maHP);
	cout<<endl<<"Nhap thu:";
	cin>>this->thu;
	cout<<endl<<"Nhap thoi gian bat dau";
	cin>>this->start;
	cout<<endl<<"Nhap thoi gian ket thuc:";
	cin>>this->end;
}
int	lophoc::Getmalop(){
	return this->maLop;
}
string lophoc::GetmaHP(){
	return this->maHP;
}
int	lophoc::Getthu(){
	return this->thu;
}
int	lophoc::Getstart(){
	return this->start;
}
int	lophoc::Getend(){
	return this->end;
}