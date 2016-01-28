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

	/*list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << *it << "\t";
	std::cout << std::endl;*/
	system("pause");
	return 0;
}