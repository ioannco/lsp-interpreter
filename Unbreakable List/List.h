#pragma once
#include "Node.h"
#include <assert.h>

template <typename T>
class List
{
public:
	List () :
		start (nullptr),
		end (nullptr),
		size (0)
	{

	}

	~List ()
	{

	}

	Node <T> * push_back (T data)
	{

		if (size == 0)
		{
			size++;

			return end = start = new Node <T> (data);
		}

		if (size == 1)
		{
			size++;

			end = new Node <T> (data, start);
			start->next = end;
			return end;
		}
		
		size++;

		Node <T> * add = new Node <T> (data, end);
		end->next = add;
		return end = add;
	}

	Node <T> * push_front (T data)
	{
		if (size == 0)
		{
			size++;
			return end = start = new Node <T> (data);
		}

		if (size == 1)
		{
			size++;

			start = new Node <T> (data, nullptr, end);
			end->prev = start;

			return start;
		}

		size++;

		Node <T> * add = new Node <T> (data, nullptr, start);
		start->prev = add;
		return start = add;
	}

	T pop_back ()
	{
		assert (size > 0);
			
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

			size--;
			return buff;
		}

		T buff = end->data;
		end = end->prev;
		delete (end->next);
		end->next = nullptr;

		size--;
		return buff;
	}

	T pop_front ()
	{
		assert (size > 0);

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

			size--;
			return buff;
		}

		T buff = start->data;
		start = start->next;
		delete (start->prev);
		start->prev = nullptr;

		size--;
		return buff;
	}

protected:
	Node <T> * start, * end;
	unsigned size;
};

