#pragma once

#include <cstring>
#include <cctype>

typedef unsigned long Hash;
typedef unsigned long DWORD;

// Not sure where I got this from, but thanks for the joaat generator
inline Hash _GET_HASH_KEY(const char* _pValue)
{
	size_t len = strlen(_pValue);
	DWORD hash, i;
	for (hash = i = 0; i < len; ++i)
	{
		hash += tolower(_pValue[i]);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}