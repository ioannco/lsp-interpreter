#pragma once


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

	T data;

	Node<T> * prev;
	Node<T> * next;

};

