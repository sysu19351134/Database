#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#ifndef STUDENTCOURSE_H_
#define STUDENTCOURSE_H_
class Studentcourse {
public:
    string id;
	string course;
	double credits;
	double score;
	inline void show();
	Studentcourse() {}
	Studentcourse(string a,string b,double c,double d):id(a),course(b),credits(c),score(d){}
};
void Studentcourse::show() {
	cout << "course:" << course << endl;
	cout << "credits:" << credits << endl;
	cout << "score:" << score << endl;
}

#endif