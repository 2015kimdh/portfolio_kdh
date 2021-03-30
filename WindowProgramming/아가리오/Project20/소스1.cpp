#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>


// �ʿ���� ��Ŭ���

using namespace std;

void makeData();

string fname{ "����1.txt" };

int main()
{
	makeData();

	// 1 ��

	fstream in ("����1.txt");
	vector<string> v{ istream_iterator <string>(in), istream_iterator <string>()};

	sort(v.begin(), v.end());

	auto p = v.begin();
	while (p != v.end()){
		p = adjacent_find(p, v.end()-1, [](const string& a, const string& b) {
			return a == b; });

		auto i = equal_range(p, v.end(), *p);

		if (i.second - i.first == 0)
		{
			++p;
		}
		else
		{
			for (auto j = i.first+1; j != i.second; ++j) {
				j->clear();
			}
			p = i.second;
		}
	}
	
	vector <string> vc;
	vc.reserve(175000);
	for (string f : v)
		if (f != "")
			vc.push_back(f);

	sort(vc.begin(), vc.end());


	cout << vc.size() << " �� ����"<< endl;

	cout << endl;

	// 2 ��
	string k = { "key" };
	auto n = find(vc.begin(), vc.end(), k);
	if (n == vc.end())
		cout << " ���� �ܾ��Դϴ� " << endl;
	else
		cout << distance(vc.begin(), n) << "��° ��ġ�� ����" << endl;

	cout << endl;

	// 3 ��

	auto i = vc.begin();
	char g { 'a' };
	while (1) {
		if (g != 'z') {
			string com;
			string com2;
			com += g;
			auto y = equal_range(i, vc.end(), com);

			com2 = g + 1;
			auto k = equal_range(i, vc.end(), com2);
			cout << com << " �� �����ϴ� �ܾ��" << distance(y.first, k.first) << " �� �̴�." << endl;
			i = y.second;
		}
		else
		{
			string com;
			string com2;
			com += g;
			auto y = equal_range(i, vc.end(), com);

			com2 = g + 1;
			auto k = equal_range(i, vc.end(), com2);
			cout << com << " �� �����ϴ� �ܾ��" << distance(y.first, k.first) << " �� �̴�." << endl;
			break;
		}
		g += 1;
		
	}

	// 4��
	fstream in1("�ܾ��.txt");
	string x;
	vector<string> vx;
	while (in1 >> x) {
		if (binary_search(vc.begin(), vc.end(), x))
		{
			vx.push_back(x);
		}
	}

	ofstream out{ "�ܾ�鿡 �ִ� �ܾ�.txt" };
	for (string y : vx)
		out << y << endl;
	cout << "�� " << vx.size() << " ���� �ܾ�" << endl;
	cout << "��� ������" << endl;
}

void makeData()
{
	default_random_engine dre;
	uniform_int_distribution< >alpha{ 'a', 'z' };
	uniform_int_distribution< >len{ 1, 30 };

	ofstream out { fname };

	for (int i = 0; i < 200000; ++i) {
		string s;
		for (int j = 0; j < len(dre); ++j)
			s += alpha(dre);
		out << s << " ";
		if ((i % 10) == 0)
			out << endl;
	}
	cout << "20�� �ܾ " << fname << "�� ����Ͽ���" << endl;
}