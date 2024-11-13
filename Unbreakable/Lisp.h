#pragma once
#include "List.hpp"
#include <string>  
#include <typeinfo>
#include <map>
#include <iostream>
#include <memory>

bool NEED_TO_WRITE = true;

class LispObj
{
public:
	struct LispObjUnion
	{
		int num;
		std::string str;
		icl::list <LispObj> list;
		bool b;

		LispObjUnion () :
			num (0),
			str(),
			list(),
			b (false)
		{

		}

		~LispObjUnion ()
		{
		}
	};

	enum Type
	{
		none,
		string,
		num,
		oper,
		list,
		boolean
	};

	LispObj ()
	{

	}

	LispObj (int num, Type type) :
		objUnion(),
		type_(type)
	{
		objUnion.num = num;
	}

	LispObj (bool b, Type type) :
		objUnion (),
		type_ (type)
	{
		objUnion.b = b;
	}

	LispObj (std::string str, Type type) :
		objUnion (),
		type_ (type)
	{
		objUnion.str = str;
	}

	LispObj (icl::list <LispObj> list, Type type) :
		objUnion (),
		type_ (type)
	{
		objUnion.list = icl::list<LispObj> ();
		objUnion.list = list;
	}

	LispObj (const LispObj & obj) :
		objUnion (),
		type_ (obj.type_)
	{
		switch (type_)
		{
		case LispObj::none: objUnion.num = 0;
			break;

		case LispObj::string: objUnion.str = obj.objUnion.str;
			break;

		case LispObj::num: objUnion.num = obj.objUnion.num;
			break;

		case LispObj::oper: objUnion.num = obj.objUnion.num;
			break;

		case LispObj::list: objUnion.list = obj.objUnion.list;
			break;
			
		case LispObj::boolean: objUnion.b = obj.objUnion.b;
			break;

		default:
			break;
		}
	}

	~LispObj ()
	{
	}

	bool operator == (const LispObj & a)
	{
		if (this->objUnion.num == a.objUnion.num &&
			this->objUnion.b == a.objUnion.b &&
			this->objUnion.str == a.objUnion.str)
			return true;
		
		return false;
	}

	Type type_;
	LispObjUnion objUnion;
};


class LispFuncPtr
{
public:
	typedef LispObj lispFunc_t (LispObj);
	LispFuncPtr (lispFunc_t * in) :
		ptr (in)
	{

	}

	lispFunc_t * ptr;
	
	LispObj operator () (LispObj & param)
	{
		return ptr (param);
	}

};

std::map <std::string, int> _FuncMap;
//LispObj objCalc (LispObj operand, const std::map <int, LispFuncPtr> & map);

icl::list<LispObj> * parser (icl::list<LispObj> * list, const std::string & string, const std::map<std::string, int> & funcmap, int * iterator, bool onlyAtoms = false)
{
	while (*iterator < string.size())
	{
		if (string[*iterator] == ' ' || string[*iterator] == '\n' || string[*iterator] == '\r' || string[*iterator] == '\t');
		else if (string[*iterator] == '(')
		{
			(*iterator)++;
			icl::list<LispObj> newlist;

			parser (&newlist, string, funcmap, iterator);

			list->push_back (LispObj (newlist, LispObj::Type::list));
		}
		else if (string[*iterator] == '\'')
		{
			(*iterator) += 2;

			icl::list<LispObj> newlist;

			parser (&newlist, string, funcmap, iterator, true);

			list->push_back (LispObj (newlist, LispObj::Type::list));
		}
		else if (string[*iterator] >= '0' && string[*iterator] <= '9')
		{
			std::string num;
			num += string[*iterator];

			while (string[*iterator + 1] >= '0' && string[*iterator + 1] <= '9')
			{
				(*iterator)++;
				num += string[*iterator];
			}

			list->push_back (LispObj (std::stoi (num), LispObj::num));
		}
		else if (string[*iterator] == ')')
		{
			return list;
		}
		else if (string[*iterator] != ' ')
		{
			std::string str;
			str += string[*iterator];

			while (string[*iterator + 1] != ' ' && string[*iterator + 1] != ')')
			{
				(*iterator)++;
				str += string[*iterator];
			}

			if (str == "T")
				list->push_back (LispObj (true, LispObj::boolean));
			else if (str == "NIL")
				list->push_back (LispObj (false, LispObj::boolean));
			else if (!onlyAtoms && funcmap.find (str) != funcmap.end ())
				list->push_back (LispObj (funcmap.at (str), LispObj::oper));
			else
				list->push_back (LispObj (str, LispObj::string));
		}

		(*iterator)++;
	}
	return list;
}

std::ostream & operator << (std::ostream & s, LispObj & v)
{
	return s;
}

void listPrint (LispObj obj, std::map <std::string, int> funcMap, std::ostream & cout)
{
	using std::endl;
		
	switch (obj.type_)
	{
	case LispObj::Type::num:
	{
		cout << obj.objUnion.num; 
	}
	break;

	case LispObj::Type::string:
	{
		cout << obj.objUnion.str;
	}
	break;

	case LispObj::Type::oper:
	{
		for (auto i : funcMap)
		{
			if (i.second == obj.objUnion.num)
				cout << i.first;
		}
	}
	break;

	case LispObj::Type::list:
	{
		cout << "(";

		while (obj.objUnion.list.getSize() > 0)
		{
			listPrint (obj.objUnion.list.pop_front (), funcMap, cout);

			if (obj.objUnion.list.getSize() > 0) cout << " ";
		}

		cout << ")";
	}
	break;

	case LispObj::Type::boolean:
	{
		if (obj.objUnion.b == true)
			cout << "T";
		else
			cout << "NIL";
	}
	break;

	default:
		break;
	}
}

LispObj objCalc (LispObj operand, std::map <int, LispFuncPtr> & map, std::map <int, LispObj> & lispFuncMap, std::map <std::string, int> & nameMap);

LispObj condCalc (LispObj operand, std::map <int, LispFuncPtr> & map, std::map <int, LispObj> & lispFuncMap, std::map <std::string, int> & nameMap)
{
	while (operand.objUnion.list.getSize () != 0)
	{
		LispObj temp = operand.objUnion.list.pop_front ();
		LispObj condition = objCalc (temp.objUnion.list.pop_front (), map, lispFuncMap, nameMap);
		if (condition == LispObj (true, LispObj::boolean))
			return objCalc (temp.objUnion.list.pop_front (), map, lispFuncMap, nameMap);
	}
}

LispObj lambdaReplace (LispObj obj, const std::map <std::string, LispObj> & lambdaMap)
{
	if (obj.type_ == LispObj::list)
	{
		LispObj temp (icl::list <LispObj> (), LispObj::list);

		while (obj.objUnion.list.getSize () > 0)
		{
			temp.objUnion.list.push_back (lambdaReplace (obj.objUnion.list.pop_front (), lambdaMap));
		}

		return temp;
	}
	else if (obj.type_ == LispObj::string)
	{
		if (lambdaMap.find (obj.objUnion.str) == lambdaMap.end ())
			return obj;
		else
			return lambdaMap.at (obj.objUnion.str);
	}
	else
		return obj;
}


LispObj funcCreate (LispObj funcObj, std::map <int, LispObj> & lispFuncMap, std::map <std::string, int> & nameMap)
{
	std::ofstream fout ("defuns.lsp", std::ios_base::app);

	funcObj.objUnion.list.push_front (LispObj (std::string("defun"), LispObj::string));

	if (NEED_TO_WRITE)
	{
		listPrint (funcObj, nameMap, fout);
		fout << std::endl;
	}

	fout.close ();
	funcObj.objUnion.list.pop_front ();

	int freeCell = -1;
	for (int i = -1; true; i--)
		if (lispFuncMap.find (i) == lispFuncMap.end ())
		{
			freeCell = i;
			break;
		}

	LispObj funcOp (freeCell, LispObj::oper);

	std::string name = funcObj.objUnion.list.pop_front ().objUnion.str;

	std::map <std::string, LispObj> lambdaList;
	lambdaList.insert (std::pair <std::string, LispObj> (name, funcOp));

	funcObj = lambdaReplace (funcObj, lambdaList);

	nameMap.insert (std::pair <std::string, int> (name, freeCell));
	lispFuncMap.insert (std::pair <int, LispObj> (freeCell, funcObj));

	return LispObj (name, LispObj::string);
}

LispObj lispFuncCalc (LispObj operand, int func, std::map <int, LispFuncPtr> & map, std::map <int, LispObj> & lispFuncMap, std::map <std::string, int> & nameMap)
{
	LispObj lambdaList = operand;

	LispObj temp = lispFuncMap.at (func);

	LispObj vars = temp.objUnion.list.pop_front ();

	std::map <std::string, LispObj> lambdaMap;

	while (lambdaList.objUnion.list.getSize () > 0)
		lambdaMap.insert (std::pair <std::string, LispObj> (vars.objUnion.list.pop_front ().objUnion.str, lambdaList.objUnion.list.pop_front ()));

	operand = lambdaReplace (temp.objUnion.list.pop_front (), lambdaMap);

	//listPrint (operand, nameMap, std::cout);

	return objCalc (operand, map, lispFuncMap, nameMap);
}

LispObj objCalc (LispObj operand, std::map <int, LispFuncPtr> & map, std::map <int, LispObj> & lispFuncMap, std::map <std::string, int> & nameMap)
{
	if (operand.type_ != LispObj::list)
		return operand;

	//listPrint (operand, nameMap, std::cout);
	//std::cout << '\n';

	LispObj tempObj = operand.objUnion.list.pop_front ();
	
	icl::list <LispObj> temp = operand.objUnion.list;
	if (temp.getSize () == 0)
		return operand; 

	if (tempObj.type_ == LispObj::list)
	{
		temp.push_front (tempObj);
		operand.objUnion.list.clear ();

		while (temp.getSize () > 0)
		{
			operand.objUnion.list.push_back (objCalc (temp.pop_front (), map, lispFuncMap, nameMap));
		}

		return operand;
	}
	else if (tempObj.type_ != LispObj::oper)
	{
		
		return operand;
	}
	else if (tempObj.objUnion.num == 10)
	{
		return condCalc (operand, map, lispFuncMap, nameMap);
	}
	else if (tempObj.objUnion.num == 11)
	{
		return funcCreate (operand, lispFuncMap, nameMap);
	}
	else if (tempObj.objUnion.num < 0)
	{
		return lispFuncCalc (operand, tempObj.objUnion.num, map, lispFuncMap, nameMap);
	}

	operand.objUnion.list.clear ();

	while (temp.getSize () > 0)
	{
		operand.objUnion.list.push_back (objCalc (temp.pop_front (), map, lispFuncMap, nameMap));
	}

	LispFuncPtr func = map.at (tempObj.objUnion.num);

	LispObj ret = func (operand);

	return ret;
}