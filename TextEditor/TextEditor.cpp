#include "stl_vector.h"

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
	system("pause");
	return 0;
}