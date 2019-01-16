//Unbreakable List - V 1.0

#include "List.h"
#include <iostream>

using namespace std;

int main ()
{
	List <int> list;

	for (int i = 0; i < 1000; i++)
		list.push_back (rand () % 2000);
	
	list.dump ();

	system ("pause");

	return 0;
}