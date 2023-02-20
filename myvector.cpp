#include "myvector.h"
#include "contact.h"
#include <iostream>
using namespace std;

// constructor
template <typename T>
MyVector<T>::MyVector(int cap)
{
	v_capacity = cap;
	v_size = 0;
	data = new T[cap];
}

// destructor
template <typename T>
MyVector<T>::~MyVector()
{
	delete[] data;
}

// push back element to the end of the vector
template <typename T>
void MyVector<T>::push_back(T element)
{

	if (v_size == v_capacity)
	{
		T *temp = new T[max(1, v_size * 2)];

		for (int i = 0; i < v_capacity; i++)
		{
			temp[i] = data[i];
		}

		delete[] data;
		v_capacity = max(1, v_capacity * 2);
		data = temp;
	}

	data[v_size] = element;
	v_size++;
}

// insert element at a specific index
template <typename T>
void MyVector<T>::insert(int index, T element)
{

	if (index > v_size - 1)
	{
		throw runtime_error("Index is out of bounds...");
	}

	else
	{
		if (v_size == v_capacity)
		{
			T *temp = new T[max(1, v_size * 2)];

			for (int i = 0; i < v_capacity; i++)
			{
				temp[i] = data[i];
			}

			delete[] data;
			v_capacity = max(1, v_capacity * 2);
			data = temp;
		}

		for (int j = v_size - 1; j >= index; j--)
		{
			data[j + 1] = data[j];
		}

		data[index] = element;
		v_size++;
	}
}

// erase element at a specific index
template <typename T>
void MyVector<T>::erase(int index)
{
	if (index > v_size - 1)
	{
		throw out_of_range("Index out of bounds...");
	}
	else
	{
		for (int j = index; j < v_size - 1; j++)
		{
			data[j] = data[j + 1];
		}
		data[v_size - 1] = NULL;
		v_size--;
	}
}

// return element at a specific index
template <typename T>
T &MyVector<T>::at(int index)
{
	if (index > v_size - 1)
	{
		throw out_of_range("Index out of bounds...");
	}
	else
	{
		return data[index];
	}
}

// return front of vector
template <typename T>
const T &MyVector<T>::front()
{
	if (v_size == 0)
	{
		throw out_of_range("Vector is empty...");
	}
	else
	{
		return data[0];
	}
}

// return back of vector
template <typename T>
const T &MyVector<T>::back()
{
	if (v_size == 0)
	{
		throw out_of_range("Vector is empty...");
	}
	else
	{
		return data[v_size - 1];
	}
}

// return size of vector
template <typename T>
int MyVector<T>::size() const
{
	return v_size;
}

// return capacity of vector
template <typename T>
int MyVector<T>::capacity() const
{
	return v_capacity;
}

// shrink vector capacity to vector size
template <typename T>
void MyVector<T>::shrink_to_fit()
{
	T *temp = new T[v_size];

	for (int k = 0; k < v_size; k++)
	{
		temp[k] = data[k];
	}
	data = temp;
	v_capacity = v_size;
}

// check if vector is empty
template <typename T>
bool MyVector<T>::empty() const
{
	return (v_size == 0);
}

template class MyVector<Contact *>;