#pragma once
#include <sstream>
#include<algorithm>
#include<iostream>
#include<map>
#include<fstream>
#include<string>
#include<cstring>
#include"studentinfo.h"
#include"studentcourse.h"
#ifndef STUDENT_H_
#define STUDENT_H_
using namespace std;
class Student {
public:
	map<string, Studentinfo> info_map;
	map<string, vector<Studentcourse>> course_map;
	vector<pair< Studentinfo, vector<Studentcourse>>>student;
	vector<string>schoolyear_vec;
	vector<double> score_vec;
	vector<double >averagescore_vec;
	vector<string> id_vec;
	vector<string> name_vec;
	void readinfo(ifstream& is);//读入info
	void readcourse(ifstream& is);//读入course
	void sortbyid();
	void show();
	void sortbyname();
	void sortbyscore();//
	void sortbyaveragescore();
	void sortbyschoolyear();
	void find();//查找函数，由键盘输入，按要求输出到txt文件
	void remove();//删除函数
	//以上函数均可测试，除find之外都是输出到控制台中
};

void Student::readinfo(ifstream& is) {
	string s;
	while (getline(is, s))
	{
		if (s[0] == '1') {
			string::size_type it1 = s.find_first_not_of("\t");
			string::size_type p1 = s.find_first_of("\t", it1);
			string id = s.substr(it1, p1);
			string::size_type it2 = s.find_first_not_of("\t", p1);
			string::size_type p2 = s.find_first_of("\t", it2);
			string name = s.substr(it2, p2 - p1 - 1);
			string::size_type it3 = s.find_first_not_of("\t", p2);
			string::size_type p3 = s.find_first_of("\t", it3);
			string sex = s.substr(it3, p3 - p2 - 1);
			string::size_type it4 = s.find_first_not_of("\t", p3);
			string::size_type p4 = s.find_first_of("\t", it4);
			string year = s.substr(it4, 4);
			string month = s.substr(it4 + 5, 1);
		    string day = s.substr(it4 + 7, 1);
			string::size_type it5 = s.find_first_not_of("\t", p4);
			string::size_type p5 = s.find_first_of("\t", it5);
			string school_year = s.substr(it5, p5 - p4 - 1);
			string::size_type it6 = s.find_first_not_of("\t", p5);
			string::size_type p6 = s.find_first_of("\t", it6);
			string birthday_place = s.substr(it6, p6 - p5 - 1);
			schoolyear_vec.push_back(school_year);
			id_vec.push_back(id);
			name_vec.push_back(name);
			info_map[id] =Studentinfo(name, sex, Date(year, month, day), id, school_year, birthday_place);
		}

	}
}
void Student::readcourse(ifstream& is) {
	string s;
	while (getline(is, s))
	{
		if (s[0] == '1')
		{
			string::size_type it1 = s.find_first_not_of("\t");
			int p1 = s.find_first_of("\t", it1);
			string id = s.substr(it1, p1);
			string::size_type it2 = s.find_first_not_of("\t", p1);
			int p2 = s.find_first_of("\t", it2);
			string course = s.substr(it2, p2 - p1 - 1);
			string::size_type it3 = s.find_first_not_of("\t", p2);
			int p3 = s.find_first_of("\t", it3);
			double credits= stod(s.substr(it3, p3 - p2 - 1));
			string::size_type it4 = s.find_first_not_of("\t", p3);
			int p4 = s.find_first_of("\t", it4);
			double score = stod(s.substr(it4, p4 - p3 - 1));
			auto course_vec = course_map[id];
			course_map[id].push_back(Studentcourse(id, course, credits, score));		
		}
	}
}
void Student::sortbyschoolyear() {
	student.clear();
	cout << "sortbyschollyear" << endl;
	sort(schoolyear_vec.begin(), schoolyear_vec.end());
	for (int q = 0; q < schoolyear_vec.size(); q++)
	{
		cout << schoolyear_vec[q] << endl;
	}
	for (int i = 0; i != schoolyear_vec.size(); i++)
	{
		for (map<string, Studentinfo>::iterator iter1 = info_map.begin(); iter1 != info_map.end(); iter1++)
		{
			for (map<string, vector<Studentcourse>>::iterator iter2 = course_map.begin(); iter2 != course_map.end(); iter2++)
			{
				if (iter1->first == iter2->first && iter1->second.school_year== schoolyear_vec[i])
					student.push_back(make_pair(iter1->second, iter2->second));
			}
		}

	}

}
void Student::sortbyscore() {
	cout << "输入要根据分数进行排序的科目" << endl;
	student.clear();
	string s;
	cin >> s;
	for (map<string, vector<Studentcourse>>::iterator iter1 = course_map.begin(); iter1 != course_map.end(); iter1++)
	{
		for (vector<Studentcourse>::iterator iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++)
		{
			if (iter2->course == s)
				score_vec.push_back(iter2->score);
		}
	}
	sort(score_vec.begin(), score_vec.end());
	cout << "sortbyscore(低到高)" << endl;
	for (int q = 0; q < score_vec.size(); q++)
	{
		cout << score_vec[q] << endl;
	}
	for (int i = 0; i != score_vec.size(); i++)
	{
		for (map<string, Studentinfo>::iterator iter4 = info_map.begin(); iter4 != info_map.end(); iter4++)
		{
			for (map<string, vector<Studentcourse>>::iterator iter5 = course_map.begin(); iter5 != course_map.end(); iter5++)
			{
				for(int j=0; j<iter5->second.size(); j++)
				{
					if((iter4->first==iter5->first)&&(iter5->second[j].course==s)&&(iter5->second[j].score==score_vec[i]))
						student.push_back(make_pair(iter4->second, iter5->second));
				}	
			}
		}

	}
}
void Student::sortbyaveragescore() {
	cout << "sortbyaveragescore(低到高)" << endl;
	student.clear();
	for (map<string, vector<Studentcourse>>::iterator iter1 = course_map.begin(); iter1 != course_map.end(); iter1++)
	{
		double m = 0;
		for (vector<Studentcourse>::iterator iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++) {
			m = m + iter2->score;
		}
		double a = m / (iter1->second.size());
		averagescore_vec.push_back(a);
	}
	sort(averagescore_vec.begin(), averagescore_vec.end());
	for (int q = 0; q < averagescore_vec.size(); q++)
	{
		cout << averagescore_vec[q] << endl;
	}
	for (int i = 0; i != averagescore_vec.size(); i++)
	{
		for (map<string, Studentinfo>::iterator iter1 = info_map.begin(); iter1 != info_map.end(); iter1++)
		{
			for (map<string, vector<Studentcourse>>::iterator iter2 = course_map.begin(); iter2 != course_map.end(); iter2++)
			{
				double c = 0;
				for (vector<Studentcourse>::iterator iter3 = iter2->second.begin(); iter3 != iter2->second.end(); iter3++)
				{
					c = c + iter3->score;
				}
				double a = c / (iter2->second.size());
				if(iter1->first == iter2->first &&a==averagescore_vec[i])
					student.push_back(make_pair(iter1->second, iter2->second));
			}
		}

	}
	

}
void Student::sortbyid() {
	student.clear();
	cout << "sortbyid" << endl;
	sort(id_vec.begin(), id_vec.end());
	for (int q = 0; q < id_vec.size(); q++)
	{
		cout << id_vec[q] << endl;
	}
	int i = 0;
	for (map<string, Studentinfo>::iterator iter1 = info_map.begin(); iter1 != info_map.end(); iter1++)
	{
		for (map<string, vector<Studentcourse>>::iterator iter2 = course_map.begin(); iter2 != course_map.end(); iter2++)
		{
			if (iter1->first == iter2->first&&iter2->first ==id_vec[i])
				student.push_back(make_pair(iter1->second, iter2->second));
		}
		i++;
	}
}
void Student::show() {
	int i = 1;
	for (vector<pair< Studentinfo, vector<Studentcourse>>>::iterator iter1 = student.begin(); iter1 != student.end();iter1++) {
		cout << "第" << i << "位" << endl;
		iter1->first.show();
		for (vector<Studentcourse>::iterator iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++) {
			iter2->show();
		}
		i++;
	}
	cout << endl << endl;
}
void Student::sortbyname() {
	student.clear();
	cout << "sort by name" << endl;
	sort(name_vec.begin(), name_vec.end());
	for (int q = 0; q < name_vec.size(); q++)
	{
		cout << name_vec[q] << endl;
	}
	for (int i = 0; i != name_vec.size(); i++)
	{
		for (map<string, Studentinfo>::iterator iter1 = info_map.begin(); iter1 != info_map.end(); iter1++)
		{
			for (map<string, vector<Studentcourse>>::iterator iter2 = course_map.begin(); iter2 != course_map.end(); iter2++)
			{
				if (iter1->first == iter2->first && iter1->second.name == name_vec[i])
					student.push_back(make_pair(iter1->second, iter2->second));
			}
		}
		
	}

}
void Student::find() {
	ofstream fout;
	fout.open("result.txt", ios_base::app);
	vector<pair<Studentinfo, vector<Studentcourse>>> student_vec;
	vector<pair<Studentinfo, vector<Studentcourse>>> student_vec2;
	cout << "please input the attribution find (input 'q' to quit) " << endl;
	vector<pair<string, pair<string, string>>> v;
	string r, op, value;;
	getline(cin,r);
	while (r!="q")
	{
		getline(cin, op);
		getline(cin, value);
		v.push_back(make_pair(r, make_pair(op, value)));
		fout << r << op << value << endl;
		getline(cin, r);
	}
	
	for (auto iter1 = student.begin(); iter1 != student.end(); iter1++)
	{
		bool flag = true;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].first == "id") {
				if (v[i].second.first == "==") {
					if (v[i].second.second != iter1->first.id)
						flag = false;
				}
				else if (v[i].second.first == "!=") {
					if (v[i].second.second == iter1->first.id)
						flag = false;
				}
			}
			else if (v[i].first == "name") {
				if (v[i].second.first == "==") {
					if (v[i].second.second != iter1->first.name)
						flag = false;
				}
				else if (v[i].second.first == "!=") {
					if (v[i].second.second == iter1->first.name)
						flag = false;
				}
			}

			else if (v[i].first == "school_year") {
				if (v[i].second.first == "==") {
					if (v[i].second.second != iter1->first.school_year)
						flag = false;
				}
				else if (v[i].second.first == "!=") {
					if (v[i].second.second == iter1->first.school_year)
						flag = false;
				}
				else if (v[i].second.first == "<") {
					if (v[i].second.second > iter1->first.school_year)
						flag = false;
				}
				else if (v[i].second.first == ">") {
					if (v[i].second.second < iter1->first.school_year)
						flag = false;
				}
			}
			else if (v[i].first == "birth_place") {
				if (v[i].second.first == "==") {
					if (v[i].second.second != iter1->first.birthday_place)
						flag = false;
				}
				else if (v[i].second.first == "!=") {
					if (v[i].second.second == iter1->first.birthday_place)
						flag = false;
				}
			}
			else if (v[i].first == "course") {
				bool flag2 = false;
				for (auto iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++) {
					if (v[i].second.first == "==") {
						if (iter2->course == v[i].second.second)
							flag2 = true;
					}
				}
				if (flag2 == false)
					flag = false;
			}
			else if (v[i].first == "score") {
				string a;
				for (int j = 0; j < v.size(); j++) {
					if (v[j].first == "course")
						a = v[j].second.second;
				}
				for (auto iter3 = iter1->second.begin(); iter3 != iter1->second.end(); iter3++) {
					if (iter3->course == a) {
						if (v[i].second.first == ">") {
							if (iter3->score <= stod(v[i].second.second))
								flag = false;
						}
						else if (v[i].second.first == "<") {
							if (iter3->score >= stod(v[i].second.second))
								flag = false;
						}
					}

				}
			}
			else if (v[i].first == "total_credits") {
				double sum = 0;
				for (auto iter3 = iter1->second.begin(); iter3 != iter1->second.end(); iter3++)
				{
					sum = sum + iter3->credits;
				}
				if (v[i].second.first == ">") {
					if (sum <= stod(v[i].second.second))
						flag = false;
				}
				if (v[i].second.first == "<") {
					if (sum >= stod(v[i].second.second))
						flag = false;
				}
			} 
			else if (v[i].first == "average_score") {
				double average = 0;
				double total = 0;
				for (auto iter3 = iter1->second.begin(); iter3 != iter1->second.end(); iter3++)
				{
					total = total + iter3->score;
				}
				average = total /( iter1->second.size());
				if (v[i].second.first == ">") {
					if (average <= stod(v[i].second.second))
						flag = false;
				}
				if (v[i].second.first == "<") {
					if (average >= stod(v[i].second.second))
						flag = false;
				}
			}
		}
		if (flag) {
			student_vec.push_back(make_pair(iter1->first, iter1->second));
		}
		if (!flag) {
			student_vec2.push_back(make_pair(iter1->first, iter1->second));
		}
	}
	fout << "满足条件的学生：" << endl;
	for (auto iter = student_vec.begin(); iter != student_vec.end(); iter++) {
		fout <<"name:"<< iter->first.name << endl;
		fout <<"sex:"<< iter->first.sex << endl;
		fout <<"birthday"<< iter->first.birthday.year<<"."<< iter->first.birthday.month<<"."<< iter->first.birthday.day << endl;
		fout <<"id:"<< iter->first.id << endl;
		fout <<"schoolyear"<< iter->first.school_year << endl;
		fout <<"birthplace"<< iter->first.birthday_place << endl;
		
	}
	fout << "不满足条件的学生:" << endl;
	for (auto iter = student_vec2.begin(); iter != student_vec2.end(); iter++) {
		fout << "name:" << iter->first.name << endl;
		fout << "sex:" << iter->first.sex << endl;
		fout << "birthday" << iter->first.birthday.year << "." << iter->first.birthday.month << "." << iter->first.birthday.day << endl;
		fout << "id:" << iter->first.id << endl;
		fout << "schoolyear" << iter->first.school_year << endl;
		fout << "birthplace" << iter->first.birthday_place << endl;
	}
	fout << endl << endl;
}
void Student::remove() {
	vector<pair<Studentinfo, vector<Studentcourse>>> student_vec;
	cout << "please input the attribution to delete(input 'q' to quit) " << endl;
	vector<pair<string, pair<string, string>>> v;
	string r, op, value;;
	getline(cin, r);
	while (r != "q")
	{
		getline(cin, op);
		getline(cin, value);
		v.push_back(make_pair(r, make_pair(op, value)));
		getline(cin, r);
	}
	for (auto iter1 = student.begin(); iter1 != student.end(); iter1++)
	{
		bool flag = true;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].first == "id") {
				if (v[i].second.first == "==") {
					if (v[i].second.second != iter1->first.id)
						flag = false;
				}
				else if (v[i].second.first == "!=") {
					if (v[i].second.second == iter1->first.id)
						flag = false;
				}
			}
			else if (v[i].first == "name") {
				if (v[i].second.first == "==") {
					if (v[i].second.second != iter1->first.name)
						flag = false;
				}
				else if (v[i].second.first == "!=") {
					if (v[i].second.second == iter1->first.name)
						flag = false;
				}
			}

			else if (v[i].first == "school_year") {
				if (v[i].second.first == "==") {
					if (v[i].second.second != iter1->first.school_year)
						flag = false;
				}
				else if (v[i].second.first == "!=") {
					if (v[i].second.second == iter1->first.school_year)
						flag = false;
				}
				else if (v[i].second.first == "<") {
					if (v[i].second.second > iter1->first.school_year)
						flag = false;
				}
				else if (v[i].second.first == ">") {
					if (v[i].second.second < iter1->first.school_year)
						flag = false;
				}
			}
			else if (v[i].first == "birth_place") {
				if (v[i].second.first == "==") {
					if (v[i].second.second != iter1->first.birthday_place)
						flag = false;
				}
				else if (v[i].second.first == "!=") {
					if (v[i].second.second == iter1->first.birthday_place)
						flag = false;
				}
			}
			else if (v[i].first == "course") {
				bool flag2 = false;
				for (auto iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++) {
					if (v[i].second.first == "==") {
						if (iter2->course == v[i].second.second)
							flag2 = true;
					}
				}
				if (flag2 == false)
					flag = false;
			}
			else if (v[i].first == "score") {
				string a;
				for (int j = 0; j < v.size(); j++) {
					if (v[j].first == "course")
						a = v[j].first;
				}
				for (auto iter3 = iter1->second.begin(); iter3 != iter1->second.end(); iter3++) {
					if (iter3->course == a) {
						if (v[i].second.first == ">") {
							if (iter3->score <= stod(v[i].second.second))
								flag = false;
						}
						else if (v[i].second.first == "<") {
							if (iter3->score >= stod(v[i].second.second))
								flag = false;
						}
					}

				}
			}
			else if (v[i].first == "total_credits") {
				double sum = 0;
				for (auto iter3 = iter1->second.begin(); iter3 != iter1->second.end(); iter3++)
				{
					sum = sum + iter3->credits;
				}
				if (v[i].second.first == ">") {
					if (sum <= stod(v[i].second.second))
						flag = false;
				}
				if (v[i].second.first == "<") {
					if (sum >= stod(v[i].second.second))
						flag = false;
				}
			}
			else if (v[i].first == "average_score") {
				double average = 0;
				double total = 0;
				for (auto iter3 = iter1->second.begin(); iter3 != iter1->second.end(); iter3++)
				{
					total = total + iter3->score;
				}
				average = total / (iter1->second.size());
				if (v[i].second.first == ">") {
					if (average <= stod(v[i].second.second))
						flag = false;
				}
				if (v[i].second.first == "<") {
					if (average >= stod(v[i].second.second))
						flag = false;
				}
			}
		}
		if (!flag) 
			student_vec.push_back(make_pair(iter1->first, iter1->second));
	}
	cout << "删除后:" << endl;
	for (auto iter = student_vec.begin(); iter != student_vec.end(); iter++) {
		iter->first.show();
}
	
}

#endif