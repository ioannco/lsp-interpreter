#pragma once
#include "List.h"

namespace icl
{
	template <typename T>
	list<T>::list (const char * name_) :
		start (nullptr),
		end (nullptr),
		size (0),
		name (name_)
	{

	}

	template<typename T>
	list<T>::list (const list <T> & other) :
		start (nullptr),
		end (nullptr),
		size (0),
		name ("unnamed")
	{
		for (node<T> * i = other.start; i != nullptr; i = i->next)
			push_back (i->data);
	}

	template<typename T>
	list <T> & list <T>::operator=(const list<T> & other)
	{
		for (node<T> * i = other.start; i != nullptr; i = i->next)
			push_back (i->data);

		return *this;
	}

	template <typename T>
	list<T>::~list ()
	{
		clear ();
		start = (node<T> *) (rand () & 49000);
		end = (node<T> *) (rand () & 49000);
		size = rand ();
		name = (const char *)(rand () & 49000);
	}

	template <typename T>
	node <T> * list<T>::push_back (const T & data)
	{
		if (!this)
			return nullptr;

		__OK;

		if (size == 0)
		{
			size++;

			return end = start = new node <T> (data);
		}

		if (size == 1)
		{
			size++;

			end = new node <T> (data, start);
			start->next = end;
			return end;
		}

		size++;

		node <T> * add = new node <T> (data, end);
		end->next = add;
		end = add;

		__OK;

		return add;
	}

	template <typename T>
	node <T> * list<T>::push_front (const T & data)
	{
		if (!this)
			return nullptr;

		__OK;

		if (size == 0)
		{
			size++;
			return end = start = new node <T> (data);
		}

		if (size == 1)
		{
			size++;

			start = new node <T> (data, nullptr, end);
			end->prev = start;

			return start;
		}

		size++;

		node <T> * list<T>::add = new node <T> (data, nullptr, start);
		start->prev = add;
		start = add;

		__OK;

		return add;
	}

	template <typename T>
	node <T> * list<T>::push_after (const T & data, node <T> * el)
	{
		if (!this)
			return nullptr;

		__OK;

		if (el == end)
			return push_back (data);

		node <T> * add = new node <T> (data, el, el->next);
		el->next->prev = add;
		el->next = add;

		size++;
		__OK;

		return add;
	}

	template <typename T>
	node <T> * list<T>::push_before (const T & data, node <T> * el)
	{
		if (!this)
			return nullptr;
		__OK;
		if (el == start)
			return push_front (data);

		node <T> * add = new node <T> (data, el->prev, el);
		el->prev->next = add;
		el->prev = add;

		size++;
		__OK;
		return add;
	}

	template <typename T>
	T list<T>::pop_back ()
	{
		if (!this)
			return T ();

		assert (size > 0);
		__OK;
		if (size == 1)
		{
			T buff = start->data;
			delete(start);
			start = end = nullptr;

			size--;
			return buff;
		}

		if (size == 2)
		{
			T buff = end->data;
			delete (end);
			end = start;
			start->next = nullptr;

			size--;
			return buff;
		}

		T buff = end->data;
		end = end->prev;
		delete (end->next);
		end->next = nullptr;

		size--;
		__OK;
		return buff;
	}

	template <typename T>
	T list<T>::pop_front ()
	{
		if (!this)
			return T ();

		assert (size > 0);
		__OK;
		if (size == 1)
		{
			T buff = start->data;
			delete(start);
			start = end = nullptr;

			size--;
			return buff;
		}

		if (size == 2)
		{
			T buff = start->data;
			delete (start);
			start = end;
			start->prev = nullptr;

			size--;
			return buff;
		}

		T buff = start->data;
		start = start->next;
		delete (start->prev);
		start->prev = nullptr;

		size--;
		__OK;
		return buff;
	}

	template <typename T>
	T list<T>::pop (node <T> * & el)
	{
		__OK;
		if (!this || !el)
			return T ();

		if (el == start)
			return pop_front ();

		if (el == end)
			return pop_back ();

		T buff = el->data;
		el->prev->next = el->next;
		el->next->prev = el->prev;

		delete (el);
		el = nullptr;

		return buff;
		__OK;
	}

	template <typename T>
	unsigned list<T>::clear ()
	{
		if (!this)
			return 0;
		__OK;

		if (size == 0)
			return 0;

		unsigned currSize = size;

		do
			pop_back ();
		while (size != 0);

		return currSize;
	}

	template <typename T>
	ErrLevel list<T>::Ok ()
	{
		unsigned counter = 0;

		for (node<T> * i = start; i != nullptr; i = i->next)
		{
			if (counter > size)
				return ErrLevel::WrongSize;

			ErrLevel level = i->Ok (size);
			if (level != ErrLevel::None)
				return level;

			counter++;
		}

		if (counter != size)
			return ErrLevel::WrongSize;

		counter = 0;

		for (node<T> * i = end; i != nullptr; i = i->prev)
		{
			if (counter > size)
				return ErrLevel::WrongSize;

			ErrLevel level = i->Ok (size);
			if (level != ErrLevel::None)
				return level;

			counter++;
		}

		if (counter != size)
			return ErrLevel::WrongSize;

		return ErrLevel::None;
	}

	template <typename T>
	void list<T>::dump (ErrLevel err)
	{
		std::ofstream log;
		log.open (LOGNAME, std::ofstream::out);

		log << "digraph D {\n";

		log << "\tlabel = \"List dump. Critical error: ";

		switch (err)
		{
		case None: log << "None, lol, wtf?";
			break;
		case WrongSize: log << "Wrong size. Seems like you have a recoursion or lost some elements.";
			break;
		case TransitivityBreak: log << "Transitivity break. Some strange pointers in one of the elements. Be more careful buddy!!";
			break;
		case UnexpectedEnd: log << "Unexpected end of the list. ";
			break;
		default: log << "??????????????????";
			break;
		}

		log << "\";\n\tlabelloc = \"t\";\n";

		log << "\tSTART [shape=plaintext label=\"START\"];\n";
		log << "\tEND [shape=plaintext label=\"END\"];\n";
		log << "\tSTART -> nd_" << start << " [style=dashed color=red];\n";
		log << "\tEND -> nd_" << end << "  [style=dashed color=red];\n\n";

		log << "\tnd_00000000 [shape = plaintext label=<<table border=\"0\" cellborder=\"0\" cellspacing=\"0\"><tr><td bgcolor=\"yellow\"><font color=\"blue\">nullptr</font></td></tr></table>>];\n\n";

		int counter = 0;

		for (node <T> * i = start; i != nullptr && counter <= size; i = i->next, counter++)
		{
			log << "\tnd_" << i << " [shape = plaintext label=<";
			log << "<table border=\"0\" cellborder=\"0\" cellspacing=\"0\">";
			log << "<tr><td bgcolor=\"blue\"><font color=\"yellow\">" << i << "</font></td></tr><tr><td bgcolor=\"red\"><font color=\"white\">" << i->data << "</font></td></tr></table>>];\n";
			log << "\tnd_" << i << "->nd_" << i->prev << ";\n";
			log << "\tnd_" << i << "->nd_" << i->next << ";\n\n";
		}

		log << "}";

		log.close ();

		system ("dmpcrt.bat");
	}

	template <typename T>
	unsigned list<T>::getSize ()
	{
		return size;
	}

	
	template<typename T>
	std::ostream & operator<<(std::ostream & s, list <T> & v)
	{
		for (node <T> * i = v.start; i != nullptr; i = i->next)
			s << "[" << *i << "] ";

		return s;
	}
}


