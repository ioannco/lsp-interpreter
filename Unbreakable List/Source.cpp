//Unbreakable List - V 1.0

#include "List.hpp"
#include <iostream>

#define LIST(type, name)  List type name (#name)

int main ()
{
	LIST (<int>, list); 

	for (int i = 0; i < 3; i++)
		list.push_back (rand () % 2000);

	Node <int> * ex = list.push_back (100);

	for (int i = 0; i < 3; i++)
		list.push_back (rand () % 2000);


	ex->next = nullptr;

	list.push_back (1);

	system ("pause");

	return 0;
}