#include <iostream>
#include <vector>
#include "string"
/* �� ���� �������� ���������� ���������. 
���� ���� ������� ����� n �� ��������� ��������� � 0 �� n-1. 
����� �������� ���������� �������� �������� � ���� �������. 
��� ������� ��������� �� ������ ������ ��������  ���������� ���������, 
� ����� ���� �������� (������ ��������� � ������� ����� 
���������� �������). ����� ����� ���� ��������� �������� 
���������� � ������ �������� � ����� ��������� ���������.*/
using namespace std;

struct table {
	char symbol;
	vector<int> z;
};

class Automat {
private:
	vector<int> S;
	vector<int> F;
	vector<vector<table>> Q; //	1 ������ ������, 2 ������ �������
public:
	Automat(vector<int> s, vector<int> f, vector<vector<table>> o) {
		S = s;
		F = f;
		Q = o;
	}
	vector<int> get_S() {
		return S;
	}
	vector<int> get_F() {
		return F;
	}
	vector<int> get_delta(int g, char w) {
		vector<int> prev;
		for (int i = 0; i < Q[g].size(); i++)
			if (Q[g][i].symbol == w) 
				return Q[g][i].z;
		return prev;
	}
};
bool intersection(vector<int> s, vector<int> f) { //�����������
	for (int i = 0; i < s.size(); i++)
		for (int j = 0; j < f.size(); j++)
			if (s[i] == f[j]) return true;
	return false;
}
vector<int> union_q(vector<int> q, char k, Automat* M) { //	�����������
	vector<int> prev;
	vector<int> res;
	for (int i = 0; i < q.size(); i++) {
		prev = M->get_delta(q[i], k);
		for (int i = 0; i < prev.size(); i++)
			res.push_back(prev[i]);
	}
	return res;
}

pair<bool, int> maxString(Automat* M, string w, int p) { //	�������� �������
	bool flag;
	int r;
	vector<int> currStates;
	if (intersection(M->get_S(), M->get_F())) 
		flag = true;
	else
		flag = false;
	r = 0;
	currStates = M->get_S();
	for (int i = p; i < w.length(); i++) {
		currStates = union_q(currStates, w[i], M);
		if (currStates.size() == 0)
			break;
		if (intersection(currStates, M->get_F())) {
			flag = true;
			r = i - p + 1;
		}
	}
	pair<bool, int> res = make_pair(flag, r);
	return res;
}

int main() {
	setlocale(LC_ALL, "Rus");
	int n, g, kol, per,st; //����� ���������
	char p;
	cout << "������� ����� ��������� ";
	cin >> n;
	vector<int> S, F; //  ��������� ��������� � ��������� �������������� ���������
	vector<char> alph;
	cout << "������� ���������� �������� � �������� ";
	cin >> g;
	cout << "������� ������� �� �������: ";
	for (int i = 0; i < g; i++) {
		cin >> p;
		alph.push_back(p);
	}
	cout << endl << "������� ������� ��������� ";
	vector<vector<table>> delta;
	for (int i = 0; i < n; i++) {
		cout <<endl<< i << "-�� ���������: \n";
		vector<table> prev;
		for (int j = 0; j < g; j++) {
			table t;
			vector<int> v1;
			cout << "��� "  << " ������� "<< alph[j]<<". ������� ����� ���������? ";
			cin >> kol;
			cout << "������� ��� �������� ";
			for (int k = 0; k < kol; k++) {
				cin >> per;
				v1.push_back(per);
			}
			t.symbol = alph[j];
			t.z = v1;
			prev.push_back(t);
		}
		delta.push_back(prev);
	}
	int fin, start;
	cout << endl << "������� ���������� ��������� ��������� ";
	cin >> start;
	cout << "������� ��� ��������� ";
	for (int j = 0; j < start; j++) {
		cin >> st;
		S.push_back(st);
	}
	cout << endl << "������� ���������� �������� ��������� ";
	cin >> fin;
	cout << "������� ��� ��������� ";
	for (int j = 0; j < fin; j++) {
		cin >> st;
		F.push_back(st);
	}
	Automat *M = new Automat(S, F, delta);
	string w;
	cout << endl << "W= ";
	cin >> w;
	pair<bool, int> result = make_pair(false, -1);
	result = maxString(M, w, 3);
	if (result.first)
		cout << result.second << endl;
	system("pause");
	return 0;
}