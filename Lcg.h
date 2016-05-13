#pragma once
typedef unsigned long ulong;

class Lcg
{
	private:
		ulong _a, _b, _c, _t;

	public:
		Lcg(ulong a, ulong b, ulong c, ulong t);
		~Lcg();

		ulong Generate();
		ulong *Generate(int count);
};

