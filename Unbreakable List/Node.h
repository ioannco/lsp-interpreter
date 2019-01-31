#pragma once
#include <fstream>
#include <cstdio>
#include <cassert>
#include <iostream>

namespace icl
{

	enum ErrLevel
	{
		None,

		WrongSize,
		TransitivityBreak,
		UnexpectedEnd
	};

	template <typename T>
	class node
	{
	public:
		node () :
			data (),
			prev (nullptr),
			next (nullptr)
		{
		}

		node (T inData, node<T> * ptrPrev = nullptr, node<T> * ptrNext = nullptr) :
			data (inData),
			prev (ptrPrev),
			next (ptrNext)
		{

		}

		ErrLevel Ok (unsigned listSize)
		{

			if (!this)
				return ErrLevel::None;

			if ((prev && prev->next != this) || (next && next->prev != this))
				return ErrLevel::TransitivityBreak;


			if (listSize > 2 && !prev && !next)
				return ErrLevel::WrongSize;

			if (listSize < 3 && prev && next)
				return ErrLevel::WrongSize;

			return ErrLevel::None;
		}

		T data;

		node<T> * prev;
		node<T> * next;


	};

	
	template <typename T>
	std::ostream & operator << (std::ostream & s, node <T> & obj)
	{
		s << obj.data;

		return s;
	}
}

