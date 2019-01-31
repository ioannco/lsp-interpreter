//Unbreakable List - V 1.0

#define LOGNAME "graph.dot"

#include "Lisp.h"
#include <iostream>

int main ()
{
	icl::list <LispObj> obj;
	std::map <std::string, int> map;

	std::string str = "(1 2 3 4 (1 3 4 5))";

	parser (&obj, &str , map);

	listPrint (obj, map);

	return 0;
}