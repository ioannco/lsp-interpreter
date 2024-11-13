#pragma once

namespace icl
{
	template <class T>
	class vector
	{
	public:
		vector ();
		vector (unsigned size);
		unsigned resize (unsigned size);
		unsigned push_back (T element);
		T pop_back ();
		unsigned size ();
		
		T & operator [] (unsigned iterator)
		{
			if (iterator >= alloc_size_)
				assert (!"vector: out of range");

			return container_[iterator];
		}

	private:
		T * container_;
		unsigned alloc_size_;
	};

	template <typename T>
	vector<T>::vector () :
		container_ (nullptr),
		alloc_size_ (0)
	{

	}

	template <typename T>
	vector<T>::vector (unsigned size) :
		container_ (nullptr),
		alloc_size_ (0)
	{
		resize (size);
	}

	template <typename T>
	unsigned vector<T>::resize (unsigned size)
	{
		T * newArray = new T[size];

		for (int i = 0; i < alloc_size_ && i < size; i++)
			newArray[i] = container_[i];

		if (size > alloc_size_)
			for (int i = alloc_size_; i < size; i++)
				newArray[i] = 0;

		if (container_)
			delete [] (container_);

		container_ = newArray;

		return alloc_size_ = size;
	}

	template <typename T>
	unsigned vector<T>::push_back (T element)
	{
		resize (alloc_size_ + 1);

		container_[alloc_size_ - 1] = element;

		return alloc_size_ - 1;
	}


	template <typename T>
	T vector<T>::pop_back ()
	{
		if (alloc_size_ == 0)
			return T ();

		T buff = container_[alloc_size_ - 1];

		resize (alloc_size_ - 1);

		return buff;
	}

	template <typename T>
	unsigned vector<T>::size ()
	{
		return alloc_size_;
	}
	
}