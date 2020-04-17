#include "GameObservers.h"

Observable::Observable() : observers{ new std::vector<Observer*> }
{}

Observable::~Observable()
{
	delete observers;
}

void Observable::attach(Observer* observer)
{
	observers->push_back(observer);
}

void Observable::detach(Observer* observer)
{
	for (std::vector<Observer*>::iterator i{ observers->begin() }; i != observers->end(); ++i)
	{
		if (&(*observer) == &(**i))
		{
			observers->erase(i);
			break;
		}
	}
}

void Observable::notify()
{
	for (std::uint_fast8_t i{ 0 }; i < observers->size(); ++i)
	{
		(*observers)[i]->update();
	}
}
