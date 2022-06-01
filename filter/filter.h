#pragma once
template <typename O>
class Filter
{
public:
	virtual bool pass(O obj) = 0;
};