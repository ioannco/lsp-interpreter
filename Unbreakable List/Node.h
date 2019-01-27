#pragma once
#include <fstream>
#include <cstdio>
#include <cassert>


enum ErrLevel
{
	None,

	WrongSize,
	TransitivityBreak,
	UnexpectedEnd
};

template <typename T>
class Node
{
public:
	Node () :
		data (),
		prev (nullptr),
		next (nullptr)
	{
	}

	Node (T inData, Node<T> * ptrPrev = nullptr, Node<T> * ptrNext = nullptr) :
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

	Node<T> * prev;
	Node<T> * next;


};

