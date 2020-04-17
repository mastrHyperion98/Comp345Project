#pragma once

#include <vector>

class Observer
{
public:
	~Observer() = default;
	virtual void update() = 0;
protected:
	Observer() = default;
};

class Observable
{
public:
	Observable();
	~Observable();

	virtual void attach(Observer*);
	virtual void detach(Observer*);
	virtual void notify();

private:
	std::vector<Observer*>* observers;
};
