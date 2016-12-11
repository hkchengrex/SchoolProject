Project 5 - Cheng Ho Kei (12219689)

For this project, I have used hash table with separate chaining for Student Table and Course Table, within each index, there is a Sorted Doubly-linked list. The CourseSelection list is implemented with a Sorted Doubly-linked list too, and is sorted according to student id and course code.

To implement the sorting, I have overloaded the comparison operator for all Course class, Student class and CourseSelection class. Then, a insertion is performed, with the help of std::iterator and overloaded operator, so that the order is remained.

For the hashing part, I have made an abstract class called Hashable, it has a pure virtual function called computeHash(). The actual methods are implemented in Course and Student Class, so that we can compute hash from them using the function with same name in the HashTable template.

All hashtable/SortList are implemented with templates to handle different types of data.

Two extra index tables are implemented so that the search for records in the CourseSelection list is improved. They are also themselves Hashtable, with two new types StudentKey and CourseKey. These data types have the same hash function as Student and Course, but they only contains id/code for hashing and a list of potiner to the courses that the student has registed / the students that have taken this course.

A validation helper file is also written to help check the validity of the data records. I have used #define to define some constants for error checking, like the length of student id and the max. length of course code.

I have also used separate compilation in the Makefile so that the compile time can be reduced.