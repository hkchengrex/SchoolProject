#ifndef _HASHABLE_H
#define _HASHABLE_H

class Hashable{
public:
	virtual int computeHash(int buckets) const = 0;
};

#endif