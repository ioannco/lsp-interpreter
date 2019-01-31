#pragma once
#include "List.hpp"
#include <string>  
#include <typeinfo>
#include <map>
#include <iostream>

class LispObj
{
public:
	union LispObjUnion
	{
		int num;
		std::string str;
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

	LispObj (std::string str, Type type) :
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

	}

	

	Type type_;
	LispObjUnion objUnion;
};

icl::list<LispObj> * parser (icl::list<LispObj> * list, std::string * string, const std::map<std::string, int> & funcmap)
{
	while (true)
	{
		char c = (*string)[0];

		if (c == '(')
		{
			*string = string->substr (1);
			icl::list<LispObj> * newlist = new icl::list<LispObj>;

			parser (newlist, string, funcmap);

			list->push_back (LispObj (newlist, LispObj::Type::list));
		}
		else if (c >= '0' && c <= '9')
		{
			std::string num;
			num += c;

			*string = string->substr (1);
			c = (*string)[0];

			while (c >= '0' && c <= '9')
			{
				num += c;

				*string = string->substr (1);
				c = (*string)[0];
			}

			list->push_back (LispObj (std::stoi (num), LispObj::num));
		}
		else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		{
			std::string str;
			str += c;

			*string = string->substr (1);
			c = (*string)[0];

			while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
			{
				str += c;


				*string = string->substr (1);
				c = (*string)[0];
			}

		
			if (funcmap.find (str) != funcmap.end ())
				list->push_back (LispObj (funcmap.at(str), LispObj::oper));
			else
				list->push_back (LispObj (str, LispObj::string));
		}
		else if (c == ')')
		{
			*string = string->substr (1);
			return list;
		}
		

		if (string->size () == 0)
			break;

		*string = string->substr (1);
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
				if (i.second = obj.objUnion.num)
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

		cout << " ";
	}

	cout << ")";
}