#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#ifndef STUDENTINFO_H_
#define STUDENTINFO_H_
using namespace std;
class Date {
public:
	string year;
	string month;
	string day;
	Date(){}
	Date(string a, string b, string c) :year(a), month(b), day(c) {}
    inline void print();
};
void Date::print() {
	cout << "birthday:";
	cout << year << "." << month << "." << day << endl;
}
class Studentinfo {
public:
	string name;
	string sex;
	Date birthday;
	string id;
	string school_year;
	string birthday_place;
	Studentinfo(){}
	Studentinfo(string a, string b , Date c, string d, string e, string f) :name(a), sex(b), birthday(c), id(d), school_year(e), birthday_place(f) {}
	~Studentinfo(){}
	inline void show();
};
void Studentinfo::show() {
	cout << "name:" << name << endl;
	cout << "sex:" << sex << endl;
	cout << "birthday:";
	birthday.print();
	cout << "id:" << id << endl;
	cout << "schoolyear:" << school_year << endl;
	cout << "birthplace:" << birthday_place << endl;
}



#endif
