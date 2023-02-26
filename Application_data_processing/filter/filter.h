#pragma once
template <typename O>
class Filter
{
public:
	virtual ~Filter() = default;
	virtual bool pass(O obj) = 0;
};