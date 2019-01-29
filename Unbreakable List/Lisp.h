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
		List <LispObj> * list;

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

	LispObj (List <LispObj> * list, Type type) :
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

List<LispObj> * parser (List<LispObj> * list, std::string * string, const std::map<int, const char *> & funcmap)
{
	while (true)
	{
		char c = (*string)[0];

		if (c == '(')
		{
			*string = string->substr (1);
			List<LispObj> * newlist = new List<LispObj>;

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

			list->push_back (LispObj (str, LispObj::num));
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