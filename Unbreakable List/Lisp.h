#pragma once
#include "List.hpp"
#include <string>  
#include <typeinfo>
#include <map>
#include <iostream>
#include <memory>

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

		default:
			break;
		}
	}

	~LispObj ()
	{
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


icl::list<LispObj> * parser (icl::list<LispObj> * list, const std::string & string, const std::map<std::string, int> & funcmap, int * iterator, bool onlyAtoms = false)
{
	while (*iterator < string.size())
	{
		if (string[*iterator] == ' ');
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
			(*iterator)++;
			return list;
		}
		else if (string[*iterator] != ' ')
		{
			std::string str;
			str += string[*iterator];

			while (string[*iterator + 1] != ' ')
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

void listPrint (icl::list <LispObj> list, std::map <std::string, int> funcMap)
{
	using std::cout;
	using std::endl;

	cout << "(";

	while (list.getSize () > 0)
	{
		LispObj obj = list.pop_front ();

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
			listPrint (obj.objUnion.list, funcMap);
		}

		default:
			break;
		}

		if (list.getSize() > 0) cout << " ";
	}

	cout << ")";
}


LispObj objCalc (LispObj operand, const std::map <int, LispFuncPtr> & map)
{
	if (operand.type_ != LispObj::list)
		return operand;
	
	icl::list <LispObj> temp = operand.objUnion.list;
	
	operand.objUnion.list.clear ();

	while (temp.getSize () > 0)
	{
		operand.objUnion.list.push_back (objCalc (temp.pop_front (), map));
	}
	
	LispObj tempObj = operand.objUnion.list.pop_front ();

	if (tempObj.type_ != LispObj::oper)
	{
		operand.objUnion.list.push_front (tempObj);
		return operand;
	}

	LispFuncPtr func = map.at (tempObj.objUnion.num);

	LispObj ret = func (operand);

	return ret;
}