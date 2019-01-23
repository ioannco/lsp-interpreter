#pragma once
#include "Node.h"
#include <assert.h>
#include <typeinfo>

#ifndef LOGNAME
#define LOGNAME "log.txt"
#endif // !LOGNAME

#ifdef _DEBUG
#define __OK { ErrLevel _errlevel_temp = Ok(); if (_errlevel_temp != ErrLevel::None) { printf ("Critical error in your list named %s.", name); dump (_errlevel_temp); system ("log.txt"); assert (_errlevel_temp == ErrLevel::None); } }
#else 
#define __OK
#endif //_DEBUG

template <typename T>
class List
{
public:
	List (const char * name_ = "unnamed");
	~List ();
	Node <T> * push_back (const T & data);
	Node <T> * push_front (T data);
	Node <T> * push_after (T data, Node <T> * el);
	Node <T> * push_before (T data, Node <T> * el);
	T pop_back ();
	T pop_front ();
	T pop (Node <T> * & el);
	unsigned clear ();
	ErrLevel Ok ();
	void dump (ErrLevel err = ErrLevel::None);
	unsigned getSize ();

protected:
	Node <T> * start, * end;
	unsigned size;
	const char * name;
};

