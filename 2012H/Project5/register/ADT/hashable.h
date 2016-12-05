#ifndef _HASHABLE_H
#define _HASHABLE_H

//An abstract class with a virtual hash function
class Hashable{
public:
	virtual int computeHash(int buckets) const = 0;
};

#endif