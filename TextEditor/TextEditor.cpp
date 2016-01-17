#include "stl_vector.h"
#include "stl_list.h"

int main()
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	v.print();

	for (vector<int>::iterator p = v.begin(); p != v.end(); p++)
	{
		cout << *p << '\t';
	}
	cout << endl;

	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		cout << *it << "\t";
	cout << endl;
	system("pause");
	return 0;
}