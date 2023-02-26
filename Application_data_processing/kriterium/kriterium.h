#pragma once

template <typename O, typename T>
class Kriterium
{
public:
	virtual ~Kriterium() = default;
	virtual T ohodnot(O obj) = 0;

};