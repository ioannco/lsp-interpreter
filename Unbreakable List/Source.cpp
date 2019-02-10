//Unbreakable List - V 1.0

#define LOGNAME "graph.dot"

#include "Windows.h"
#include "Lisp.h"
#include <iostream>

LispObj op (LispObj operand)
{
	int summ = operand.objUnion.list.pop_front ().objUnion.num;

	while (operand.objUnion.list.getSize () > 0)
	{
		summ += operand.objUnion.list.pop_front ().objUnion.num;
	}

	return LispObj (summ, LispObj::num);
}

LispObj om (LispObj operand)
{
	int start = operand.objUnion.list.pop_front ().objUnion.num;

	while (operand.objUnion.list.getSize () > 0)
	{
		start -= operand.objUnion.list.pop_front ().objUnion.num;
	}

	return LispObj (start, LispObj::num);
}

LispObj multiply (LispObj operand)
{
	int start = operand.objUnion.list.pop_front ().objUnion.num;

	while (operand.objUnion.list.getSize () > 0)
	{
		start *= operand.objUnion.list.pop_front ().objUnion.num;
	}

	return LispObj (start, LispObj::num);
}

LispObj divide (LispObj operand)
{
	int start = operand.objUnion.list.pop_front ().objUnion.num;

	while (operand.objUnion.list.getSize () > 0)
	{
		start /= operand.objUnion.list.pop_front ().objUnion.num;
	}

	return LispObj (start, LispObj::num);
}

LispObj cdr (LispObj operand)
{
	LispObj list = operand.objUnion.list.pop_front ();
	list.objUnion.list.pop_front ();

	return list;
}

LispObj car (LispObj operand)
{
	return operand.objUnion.list.pop_front ().objUnion.list.pop_front();
}

LispObj cons (LispObj operand)
{
	LispObj obj = operand.objUnion.list.pop_front ();
	LispObj list = operand.objUnion.list.pop_front ();

	list.objUnion.list.push_front (obj);

	return list;
}

int main ()
{
	icl::list <LispObj> obj;

	std::map <std::string, int> map;
	std::map <int, LispFuncPtr> map2;

	map.insert (std::pair <std::string, int> ("+", 1));
	map2.insert (std::pair <int, LispFuncPtr> (1, op));

	map.insert (std::pair <std::string, int> ("-", 2));
	map2.insert (std::pair <int, LispFuncPtr> (2, om));

	map.insert (std::pair <std::string, int> ("*", 3));
	map2.insert (std::pair <int, LispFuncPtr> (3, multiply));

	map.insert (std::pair <std::string, int> ("/", 4));
	map2.insert (std::pair <int, LispFuncPtr> (4, divide));

	map.insert (std::pair <std::string, int> ("car", 5));
	map2.insert (std::pair <int, LispFuncPtr> (5, car));

	map.insert (std::pair <std::string, int> ("cdr", 6));
	map2.insert (std::pair <int, LispFuncPtr> (6, cdr));

	map.insert (std::pair <std::string, int> ("cons", 7));
	map2.insert (std::pair <int, LispFuncPtr> (7, cons));

	std::string input;

	int iterator = 0;

	std::cout << ">";

	while (std::getline (std::cin, input))
	{
		if (input == "exit")
			break;

		parser (&obj, input, map, &iterator);
		iterator = 0;

		LispObj temp = obj.pop_front ();
		temp = objCalc (temp, map2);
		obj.clear ();
		obj.push_front (temp);

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