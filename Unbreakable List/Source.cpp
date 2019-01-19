//Unbreakable List - V 1.0

#include "List.h"
#include <iostream>

using namespace std;

int main ()
{
	List <int> list;

	for (int i = 0; i < 3; i++)
		list.push_back (rand () % 2000);

	Node <int> * ex = list.push_back (100);

	for (int i = 0; i < 3; i++)
		list.push_back (rand () % 2000);
	
	list.Ok ();

	ex->next = nullptr;

	list.Ok ();

	system ("pause");

	return 0;
}