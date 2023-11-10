// ALGO2 IS1 224B LAB05
// ILLIA KARMAZIN
// ki53819@zut.edu.pl
#include <iostream>

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
		int index = this->Size-1, index2;
		while (true)
		{
			if (index <= 0)
				break;
			index2 = floor((index - 1) / 2);
			if (comporator(this->vec[index],this->vec[index2]))
			{
				T val = this->vec[index];
				this->vec[index] = this->vec[index2];
				this->vec[index2] = val;
				index = index2;
			}
			else
				break;
		} 
	}
}

template<class T>
T HP<T>::Delete_Max(Comporator<T> comporator)
{
	//
}

int main()
{
	HP<int>* hp = new HP<int>();
	Comporator<int> comporator;
	//
    hp->Add(100, comporator);
	hp->Add(70, comporator);
	hp->Add(50, comporator);
	hp->Add(125, comporator);
	hp->Add(45, comporator);
	hp->Add(60, comporator);
	hp->Add(10, comporator);
	for (int i = 0; i < hp->Size; ++i)
		std::cout << hp->vec[i] << " ";
	//
	delete hp;
    return 0;
}