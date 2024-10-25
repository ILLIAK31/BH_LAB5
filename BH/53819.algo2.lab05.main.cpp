﻿// ALGO2 IS1 224B LAB05
// ILLIA KARMAZIN
// ki53819@zut.edu.pl
#include <iostream>
#include <string>
#include <time.h>

template <class T>
class Comporator
{
public:
	Comporator()=default;
	~Comporator();
	bool operator()(T x, T y)
	{
		return (x > y) ? true : false;
	}
};

template<class T>
Comporator<T>::~Comporator(){}

template <class T>
class HP
{
public:
	HP()=default;
	~HP();
	int Size{ 0 }, MS{ 1 };
	T* vec = new T[MS];
	void Add(T value,Comporator<T> comporator);
	T Delete_Max(Comporator<T> comporator);
	void Clear(Comporator<T> comporator);
	void Print();
	void HP_Up(int index, Comporator<T> comporator);
	void HP_Down(int index, Comporator<T> comporator);
};

template<class T>
HP<T>::~HP()
{
	this->vec = nullptr;
	delete[] this->vec;
}

template<class T>
void HP<T>::Add(T value, Comporator<T> comporator)
{
	if (this->Size != this->MS)
	{
		this->vec[this->Size] = value;
		++this->Size;
	}
	else
	{
		this->MS *= 2;
		T* copy_val = this->vec;
		this->vec = nullptr;
		this->vec = new T[this->MS];
		for (int index = 0; index < this->Size; ++index)
		{
			this->vec[index] = copy_val[index];
		}
		this->vec[this->Size] = value;
		++this->Size;
		copy_val = nullptr;
		delete[] copy_val;
	}
	if (this->Size != 1)
	{
		int index = this->Size-1;
		this->HP_Up(index, comporator);
	}
}

template<class T>
T HP<T>::Delete_Max(Comporator<T> comporator)
{
	if (this->Size == 0)
		return NULL;
	else if (this->Size == 1)
	{
		int MAX = this->vec[0];
		this->vec[0] = NULL;
		--this->Size;
		return MAX;
	}
	else
	{
		int MAX = this->vec[0];
		this->vec[0] = this->vec[this->Size - 1];
		this->vec[this->Size - 1] = NULL;
		this->HP_Down(0, comporator);
		--this->Size;
		return MAX;
	}
}

template<class T>
void HP<T>::Clear(Comporator<T> comporator)
{
	while (this->Size)
		this->Delete_Max(comporator);
}

template<class T>
void HP<T>::Print()
{
	std::cout << "\t| Binary Heap (Max) |\n\t| Size : " << this->Size << " |\n";
	std::string parent, left, right;
	for (int index = 0; index < this->Size; ++index)
	{
		if (index == 0)
			parent = "NULL";
		else
			parent = std::to_string(int(floor((index - 1) / 2)));
		if (((2 * index) + 1) < this->Size)
			left = std::to_string((2 * index) + 1);
		else
			left = "NULL";
		if (((2 * index) + 2) < this->Size)
			right = std::to_string((2 * index) + 2);
		else
			right = "NULL";
		std::cout << "| Index " << index << " | Parent : " << parent << " | Left : " << left << " | Right : " << right << " | Value : " << this->vec[index] << " |\n";
	}
}

template<class T>
void HP<T>::HP_Up(int index, Comporator<T> comporator)
{
	int index2;
	if (index <= 0)
		return;
	index2 = floor((index - 1) / 2);
	if (comporator(this->vec[index], this->vec[index2]))
	{
		T val = this->vec[index];
		this->vec[index] = this->vec[index2];
		this->vec[index2] = val;
		index = index2;
	}
	else
		return;
	HP_Up(index,comporator);
	return;
}

template<class T>
void HP<T>::HP_Down(int index, Comporator<T> comporator)
{
	if ((((2 * index) + 1) < this->Size) || (((2 * index) + 2) < this->Size))
	{
		if (((((2 * index) + 1) < this->Size) && (((2 * index) + 2) >= this->Size)) && (this->vec[index] < this->vec[(2 * index) + 1]))
		{
			T val = this->vec[index];
			this->vec[index] = this->vec[(2 * index) + 1];
			this->vec[(2 * index) + 1] = val;
			index = (2 * index) + 1;
			HP_Down(index, comporator);
		}
		else if (((((2 * index) + 1) >= this->Size) && (((2 * index) + 2) < this->Size)) && (this->vec[index] < this->vec[(2 * index) + 2]))
		{
			T val = this->vec[index];
			this->vec[index] = this->vec[(2 * index) + 2];
			this->vec[(2 * index) + 2] = val;
			index = (2 * index) + 2;
			HP_Down(index, comporator);
		}
		else if ((comporator(this->vec[(2 * index) + 1], this->vec[(2 * index) + 2])) && (this->vec[index] < this->vec[(2 * index) + 1]))
		{
			T val = this->vec[index];
			this->vec[index] = this->vec[(2 * index) + 1];
			this->vec[(2 * index) + 1] = val;
			index = (2 * index) + 1;
			HP_Down(index, comporator);
		}
		else if ((comporator(this->vec[(2 * index) + 2], this->vec[(2 * index) + 1])) && (this->vec[index] < this->vec[(2 * index) + 2]))
		{
			T val = this->vec[index];
			this->vec[index] = this->vec[(2 * index) + 2];
			this->vec[(2 * index) + 2] = val;
			index = (2 * index) + 2;
			HP_Down(index, comporator);
		}
		else
			return;
	}
	else
		return;
	return;
}

int main()
{
	HP<int>* hp = new HP<int>();
	Comporator<int> comporator;
    clock_t timer1, timer2, timer3, timer4;
	int value;
	double avr{ 0 };
	timer1 = clock();
	for (int index = 0; index < 10000; ++index)
	{
		value = rand() % RAND_MAX;
		timer3 = clock();
		hp->Add(value, comporator);
		timer4 = clock();
		avr += (timer4 - timer3) / (double)CLOCKS_PER_SEC;
	}
	timer2 = clock();
	avr /= 10000;
	avr *= 1000;
	hp->Print();
	std::cout << "| Full time : " << (timer2 - timer1) / (double)CLOCKS_PER_SEC << " s | Average per obj : " << avr << " ms |\n\n";
	avr = 0;
	timer1 = clock();
	for (int index = 0; index < 1000; ++index)
	{
		timer3 = clock();
		int value2 = hp->Delete_Max(comporator);
		timer4 = clock();
		std::cout << "| " << value2 << " |\n";
		avr += (timer4 - timer3) / (double)CLOCKS_PER_SEC;
	}
	timer2 = clock();
	avr /= 1000;
	avr *= 1000;
	std::cout << "| Full time : " << (timer2 - timer1) / (double)CLOCKS_PER_SEC << " s | Average per obj : " << avr << " ms |\n";
	hp->Clear(comporator);
	delete hp;
    return 0;
}