#pragma once
#include<iostream>
#include"student.h"
#include<fstream>
using namespace std;
int main() {
	ifstream c;
	c.open("StudentCourse.txt");
	ifstream i;
	i.open("StudentInfo.txt");
	Student s;
	s.readinfo(i);
	s.readcourse(c);
	s.sortbyid();
	s.find();
		return 0;
}