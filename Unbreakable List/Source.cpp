//Unbreakable List - V 1.0

#define LOGNAME "graph.dot"

#include "Windows.h"
#include "Lisp.h"
#include <iostream>

int main ()
{
	icl::list <LispObj> obj;

	std::map <std::string, int> map;
	std::map <int, LispFuncPtr> map2;

	std::string input;

	int iterator = 0;

	std::cout << ">";

	while (std::getline (std::cin, input))
	{
		parser (&obj, input, map, &iterator);
		listPrint (obj, map);

		obj.clear ();
		std::cout << "\n>";
	}

	system ("pause");

	return 0;
}

// (defun dist (lambda x1 y1 x2 y2) 
// (
// 	 sqrt (+ (* (- x1 x2) (- x1 x2)) (* (- y1 y2) (- y1 y2)))
// ))
//
// (dist 5 5 10 10)
//
// (defun dist (lambda x1 y1 x2 y2)
// (
//	 sqrt (+ (* (- lambda[0].val lambda[2].val) (- x1 x2)) (* (- y1 y2) (- y1 y2)))
// ))