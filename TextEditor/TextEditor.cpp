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
		std::cout << *p << '\t';
	}
	std::cout << std::endl;

	list<int> l;
	int data[] = { 21, 45, 1, 30, 52, 3, 58, 47, 22, 59, 0, 58 };
	for (int i = 0; i < 12; i++)
		l.push_back(data[i]);
	
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << *it << "\t";
	std::cout << std::endl;

	l.sort();

	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << *it << "\t";
	std::cout << std::endl;
	system("pause");
	return 0;
}