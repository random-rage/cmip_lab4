#include "Lcg.h"

Lcg::Lcg(ulong a, ulong b, ulong c, ulong t)
{
	if (c % 2 == 0)
		throw "Number C must be odd";

	if (a % 4 != 1)
		throw "Number A must be such (A mod 4 == 1)";

	_a = a;
	_b = b;
	_c = c;
	_t = t;
}

Lcg::~Lcg()
{
}

ulong Lcg::Generate()
{
	_t = (_a * _t + _c) % _b;
	return _t;
}

ulong * Lcg::Generate(int count)
{
	ulong *result = new ulong[count];

	for (int i = 0; i < count; i++)
		result[i] = Generate();

	return result;
}
