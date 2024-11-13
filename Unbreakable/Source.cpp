// Unbreakable - V 1.0

#define LOGNAME "graph.dot"

#include "Lisp.h"
#include <iostream>
#include "Vector.h"

std::string fileRead (std::string fileName);

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

	if (list.objUnion.list.getSize () == 0)
		return list;

	list.objUnion.list.pop_front ();

	return list;
}

LispObj car (LispObj operand)
{
	if (operand.objUnion.list.getSize() == 0)
		return operand;

	LispObj list = operand.objUnion.list.pop_front ();
	if (list.objUnion.list.getSize() == 0)
		return list;

	return list.objUnion.list.pop_front();
}

LispObj cons (LispObj operand)
{
	LispObj obj = operand.objUnion.list.pop_front ();
	LispObj list = operand.objUnion.list.pop_front ();

	list.objUnion.list.push_front (obj);

	return list;
}

LispObj null (LispObj operand)
{
	operand = operand.objUnion.list.pop_front ();

	if ((operand.type_ == LispObj::boolean && !operand.objUnion.b) || (operand.type_ == LispObj::list && operand.objUnion.list.getSize () == 0))
		return LispObj (true, LispObj::boolean);

	return LispObj (false, LispObj::boolean);
}

LispObj oe (LispObj operand)
{
	if (operand.objUnion.list.pop_front() == operand.objUnion.list.pop_front())
		return LispObj (true, LispObj::boolean);

	return LispObj (false, LispObj::boolean);
}

LispObj oh (LispObj operand)
{
	if (operand.objUnion.list.pop_front ().objUnion.num > operand.objUnion.list.pop_front().objUnion.num)
		return LispObj (true, LispObj::boolean);

	return LispObj (false, LispObj::boolean);
}

LispObj ol (LispObj operand)
{
	if (operand.objUnion.list.pop_front ().objUnion.num < operand.objUnion.list.pop_front ().objUnion.num)
		return LispObj (true, LispObj::boolean);

	return LispObj (false, LispObj::boolean);
}

LispObj oeh (LispObj operand)
{
	if (operand.objUnion.list.pop_front ().objUnion.num >= operand.objUnion.list.pop_front ().objUnion.num)
		return LispObj (true, LispObj::boolean);

	return LispObj (false, LispObj::boolean);
}

LispObj oel (LispObj operand)
{
	if (operand.objUnion.list.pop_front ().objUnion.num <= operand.objUnion.list.pop_front ().objUnion.num)
		return LispObj (true, LispObj::boolean);

	return LispObj (false, LispObj::boolean);
}

LispObj cond (LispObj operand)
{
	return operand;
}

LispObj defun (LispObj operand)
{
	return operand;
}

int main (int argc, char ** argv)
{	

	icl::list <LispObj> obj;

	std::map <std::string, int> map;
	std::map <int, LispFuncPtr> map2;

	/*const char * temp = (const char *) this;
	int summ = 0;
	for (int i = 0; i <= sizeof (*this); i++)
		summ += temp[i];*/

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

	map.insert (std::pair <std::string, int> ("null", 8));
	map2.insert (std::pair <int, LispFuncPtr> (8, null));

	map.insert (std::pair <std::string, int> ("=", 9));
	map2.insert (std::pair <int, LispFuncPtr> (9, oe));

	map.insert (std::pair <std::string, int> ("cond", 10));
	map2.insert (std::pair <int, LispFuncPtr> (10, cond));

	map.insert (std::pair <std::string, int> ("defun", 11));
	map2.insert (std::pair <int, LispFuncPtr> (11, defun));

	map.insert (std::pair <std::string, int> (">", 12));
	map2.insert (std::pair <int, LispFuncPtr> (12, oh));

	map.insert (std::pair <std::string, int> ("<", 13));
	map2.insert (std::pair <int, LispFuncPtr> (13, ol));

	map.insert (std::pair <std::string, int> (">=", 14));
	map2.insert (std::pair <int, LispFuncPtr> (14, oeh));

	map.insert (std::pair <std::string, int> ("<=", 15));
	map2.insert (std::pair <int, LispFuncPtr> (15, oel));

	std::map <int, LispObj> lispFuncMap;

	std::string input;

	int iterator = 0;

	NEED_TO_WRITE = false;

	{
		input = std::string ("(") + fileRead("defuns.lsp") + std::string (")");
		parser (&obj, input, map, &iterator);
		iterator = 0;

		LispObj temp = obj.pop_front ();
		temp = objCalc (temp, map2, lispFuncMap, map);
		obj.clear ();
	}

	NEED_TO_WRITE = true;

	if (argc == 2)
	{
		input = fileRead (argv[1]);
		parser (&obj, input, map, &iterator);
		iterator = 0;

		LispObj temp = obj.pop_front ();
		temp = objCalc (temp, map2, lispFuncMap, map);
		obj.clear ();

		std::cout << argv[1] << ": ";
		listPrint (temp, map, std::cout);
		std::cout << "\n";
	}

	listPrint (lispFuncMap[-2], map, std::cout);

	input = "";

	std::cout << "===>"; 

	while (std::getline (std::cin, input))
	{
		std::cout << "\n";

		if (input == "exit")
			break;

		parser (&obj, input, map, &iterator);
		iterator = 0;

		LispObj temp = obj.pop_front ();
		temp = objCalc (temp, map2, lispFuncMap, map);
		obj.clear ();
		obj.push_front (temp);

		listPrint (temp, map, std::cout);

		obj.clear ();
		std::cout << "\n\n===>";
	}

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

std::string fileRead (std::string fileName)
{
	int length;
	char * buffer;

	std::ofstream os (fileName, std::ios::app);
	os.close ();

	std::ifstream is;
	is.open (fileName, std::ios::binary);

	is.seekg (0, std::ios::end);
	length = is.tellg ();
	is.seekg (0, std::ios::beg);
	buffer = new char[length];
	is.read (buffer, length);
	is.close ();

	std::string output = buffer;

	delete[] buffer;

	return output;
}