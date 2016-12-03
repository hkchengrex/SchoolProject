#ifndef _HASHABLE_H
#define _HASHABLE_H

class Hashable{
protected:
	//The hash base is a property of the key, so it is put here
	const int HASH_BASE;

public:
	virtual int computeHash(int buckets) = 0;
};

#endif