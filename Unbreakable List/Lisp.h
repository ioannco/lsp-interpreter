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
	union LispObjUnion
	{
		int num;
		std::string * str;
		icl::list <LispObj> * list;

		LispObjUnion ()
		{

		}

		~LispObjUnion ()
		{
			num = 0;
		}
	};

	enum Type
	{
		none,
		string,
		num,
		oper,
		list
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

	LispObj (std::string * str, Type type) :
		objUnion (),
		type_ (type)
	{
		objUnion.str = str;
	}

	LispObj (icl::list <LispObj> * list, Type type) :
		objUnion (),
		type_ (type)
	{
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
		/*if (type_ == list)
			delete (objUnion.list);
		else if (type_ == string)
			delete (objUnion.str);*/
	}

	

	Type type_;
	LispObjUnion objUnion;
};


class LispFuncPtr
{
public:
	typedef icl::list <LispObj> lispFunc_t (icl::list <LispObj>);
	LispFuncPtr (lispFunc_t * in) :
		ptr (in)
	{

	}

	lispFunc_t * ptr;
	
	icl::list <LispObj> operator () (const icl::list <LispObj> & param)
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
			icl::list<LispObj> * newlist = new icl::list<LispObj>;

			parser (newlist, string, funcmap, iterator);

			list->push_back (LispObj (newlist, LispObj::Type::list));
		}
		else if (string[*iterator] == '\'')
		{
			(*iterator) += 2;

			icl::list<LispObj> * newlist = new icl::list<LispObj>;

			parser (newlist, string, funcmap, iterator, true);

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
				(*iterator++);
				str += string[*iterator];
			}

			if (!onlyAtoms && funcmap.find (str) != funcmap.end ())
				list->push_back (LispObj (funcmap.at (str), LispObj::oper));
			else
				list->push_back (LispObj (new std::string (str), LispObj::string));
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
			cout << *obj.objUnion.str;
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
			listPrint (*obj.objUnion.list, funcMap);
		}

		default:
			break;
		}

		if (list.getSize() > 0) cout << " ";
	}

	cout << ")";
}
