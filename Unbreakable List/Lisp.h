#pragma once
#include "List.h"
#include <string>  
#include <typeinfo>
#include <map>



class LispObj
{
public:
	union LispObjUnion
	{
		int num;
		char c;
		char string[];
		List <LispObj> * list;
	};

	enum Type
	{
		none,
		string,
		num,
		character,
		oper,
		list
	};

	template <class T>
	LispObj (T var, Type type);

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

			char c = (*string)[0];
			*string = string->substr (1);

			while (c >= '0' && c <= '9')
			{
				num += c;

				char c = (*string)[0];
				*string = string->substr (1);
			}

			list->push_back (LispObj (std::stoi (num), LispObj::num));
		}
		else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		{

		}
		else if (c == ')')
		{
			*string = string->substr (1);
			return list;
		}
		

		*string = string->substr (1);
	}

	return list;
}

template<class T>
inline LispObj::LispObj (T var, Type type) :
	type_ (type),
	objUnion ()
{
	switch (type)
	{
	case LispObj::none: objUnion.num = 0;
		break;
	case LispObj::string: objUnion.string = var;
		break;
	case LispObj::num: objUnion.num = var;
		break;
	case LispObj::character: objUnion.c = var;
		break;
	case LispObj::oper: objUnion.num = var;
		break;
	case LispObj::list: objUnion.list = var;
		break;
	default:
		break;
	}
}
