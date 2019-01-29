//Unbreakable List - V 1.0

#define LOGNAME "graph.dot"

#include "Lisp.h"
#include <iostream>

int main ()
{
	List <LispObj> graph;

	std::string str = "(13 2 34 (4 52 6))";

	parser (&graph, &str, std::map <int, const char *>());

	return 0;
}