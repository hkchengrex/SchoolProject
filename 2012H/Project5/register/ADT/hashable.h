#ifndef _HASHABLE_H
#define _HASHABLE_H

class Hashable{
protected:
	const int HASH_BASE;

public:
	virtual int computeHash(int buckets) = 0;
};

#endif