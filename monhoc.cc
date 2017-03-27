#include "monhoc.h"
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

void monhoc::SetMonHoc(){
	cout<<"Nhap ma hoc phan:";
	fflush(stdin);
	getline(cin,this->maHP);
	cout<<endl<<"Nhap ten hoc phan:";
	fflush(stdin);
	getline(cin,this->tenHP);
	this->prefer = 0;
}
void monhoc::SetPrefer(int id){
	this->prefer = id
}
string monhoc::GetmaHP(){
	return this->maHP;
}
string monhoc::GettenHP(){
	return this->tenHP;
}	
string monhoc::GetPrefer(){
	return this->prefer;
}
