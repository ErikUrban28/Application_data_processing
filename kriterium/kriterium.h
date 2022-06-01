#pragma once

template <typename O, typename T>
class Kriterium
{
public:
	virtual T ohodnot(O obj) = 0;

};