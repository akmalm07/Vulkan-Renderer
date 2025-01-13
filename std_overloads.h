#pragma once


#include "config.h"


template <class T>
std::vector<T>& operator+=(std::vector<T>& left, const std::vector<T>& right)//This will move it
{
	left.insert(left.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end())); 

	return left;
}
