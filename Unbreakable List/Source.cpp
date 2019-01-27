//Unbreakable List - V 1.0

#define LOGNAME "graph.dot"

#include "List.hpp"
#include <iostream>

#define LIST(type, name)  List type name (#name)

int main ()
{
	LIST (<int>, list); 

	for (int i = 0; i < 5; i++)
		list.push_back (rand () % 2000);

	list.dump ();

	system ("pause");

	return 0;
}