//Unbreakable List - V 1.0

#include "List.h"
#include <iostream>

using namespace std;

int main ()
{
	List <int> list;

	list.push_back (3);
	Node <int> * el = list.push_back (4);
	list.push_back (6);
	list.push_after (5, el);

	cout << list.pop_back () << endl;
	cout << list.pop_back () << endl;
	cout << list.pop_back () << endl;
	cout << list.pop_back () << endl;

	system ("pause");

	return 0;
}