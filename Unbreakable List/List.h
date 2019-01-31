#pragma once
#include "Node.h"
#include <assert.h>
#include <typeinfo>
#include <thread>
#include <iostream>

#ifndef LOGNAME
#define LOGNAME "log.txt"
#endif // !LOGNAME

#ifdef _DEBUG
#define __OK { ErrLevel _errlevel_temp = Ok(); if (_errlevel_temp != ErrLevel::None) { printf ("Critical error in your list named %s.", name); dump (_errlevel_temp); std::this_thread::sleep_for(std::chrono::milliseconds(200)); system ("graph.dot.gd.cairo.png"); assert (_errlevel_temp == ErrLevel::None); } }
#else 
#define __OK
#endif //_DEBUG

namespace icl
{
	template <typename T>
	class list
	{
	public:
		list (const char * name_ = "unnamed");
		list (const list <T> & other);
		list <T> & operator = (const list <T> & other);
		~list ();
		node <T> * push_back (const T & data);
		node <T> * push_front (const T & data);
		node <T> * push_after (const T & data, node <T> * el);
		node <T> * push_before (const T & data, node <T> * el);
		T pop_back ();
		T pop_front ();
		T pop (node <T> * & el);
		unsigned clear ();
		ErrLevel Ok ();
		void dump (ErrLevel err = ErrLevel::None);
		unsigned getSize ();

		template <typename T>
		friend std::ostream & operator << (std::ostream & s, list <T> & v);

	protected:
		node <T> * start, *end;
		unsigned size;
		const char * name;
	};
	
}