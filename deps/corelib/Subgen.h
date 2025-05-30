#pragma once

#define SUBGENMAX 1000000000

typedef struct Subgen
{
    int state[55];
    int si;
    int sj;
    int seed;
}
Subgen;

inline int SubgenNext(Subgen* subgen)
{
	if (!subgen->si--) subgen->si = 54;
	if (!subgen->sj--) subgen->sj = 54;
    int x = subgen->state[subgen->si] - subgen->state[subgen->sj];
	if (x < 0) x += SUBGENMAX;
	return subgen->state[subgen->si] = x;
}
inline Subgen SubgenCreate(int seed)
{
    Subgen subgen;

    subgen.si = 0;
    subgen.sj = 24;
    subgen.seed = seed;

    int p2 = 1;
	subgen.state[0] = seed % SUBGENMAX;

    for (int i = 1, j = 21; i < 55; i++, j += 21)
    {
		if (j >= 55) j -= 55;
		subgen.state[j] = p2;
        p2 = seed - p2;
		if (p2 < 0) p2 += SUBGENMAX;
		seed = subgen.state[j];
	}

	for (int i = 0; i < 165; i++)
        SubgenNext(&subgen);

    return subgen;
}
inline float SubgenFractionUnsigned(Subgen* subgen)
{
    return SubgenNext(subgen) / (float)SUBGENMAX;
}
inline float SubgenFractionSigned(Subgen* subgen)
{
    return SubgenFractionUnsigned(subgen) * 2 - 1;
}
inline float SubgenRange(Subgen* subgen, float min, float max)
{
    return min + ((max - min) * SubgenFractionUnsigned(subgen));
}

Subgen _Subgen1Instance;
__attribute__((constructor))
inline void _Subgen1Init() { _Subgen1Instance = SubgenCreate(0); }
inline int Subgen1Next() { return SubgenNext(&_Subgen1Instance); }
inline float Subgen1FractionUnsigned() { return SubgenFractionUnsigned(&_Subgen1Instance); }
inline float Subgen1FractionSigned() { return SubgenFractionSigned(&_Subgen1Instance); }
inline float Subgen1Range(float min, float max) { return SubgenRange(&_Subgen1Instance, min, max); }
