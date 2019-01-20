#pragma once
#include <fstream>
#include <cstdio>
#include <cassert>

#ifndef LOGNAME
#define LOGNAME "log.txt"
#endif // !LOGNAME

#define LIST_CRITICAL_ERROR(a) dump(); printf ("ERROR: Critical error in your list %s. Check logs!\n", name); system ("start log.txt"); return a;

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
		if (listSize < 3 && prev != nullptr && next != nullptr)
			return ErrLevel::TransitivityBreak;
		else if (listSize > 1 && prev == nullptr && next == nullptr)
			return ErrLevel::TransitivityBreak;
		
		return ErrLevel::None;
	}

	T data;

	Node<T> * prev;
	Node<T> * next;

};

