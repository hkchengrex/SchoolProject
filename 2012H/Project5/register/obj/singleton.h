#ifndef _SINGLETON_H
#define _SINGLETON_H

#include "../ADT/hash_table.h"
#include "../ADT/sort_list.h"

#include "../data/course.h"
#include "../data/course_selection.h"
#include "../data/student.h"
#include "../data/indexes.h"

//This file is a singleton for managing all the data records

StudentTable& getStdTable();
CourseTable& getCourseTable();

SelectionList& getCourseSelectionList();
StudentKeyTable& getStdKeyTable();
CourseKeyTable& getCourseKeyTable();

#endif