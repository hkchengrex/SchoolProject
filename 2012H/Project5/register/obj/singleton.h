#ifndef _SINGLETON_H
#define _SINGLETON_H

#include "../ADT/hash_table.h"
#include "../ADT/sort_list.h"

#include "../data/course.h"
#include "../data/course_selection.h"
#include "../data/student.h"
#include "../data/indexes.h"

StudentTable& getStdTable();
CourseTable& getCourseTable();

SortedList<CourseSelection>& getCourseSelectionList();
StudentKeyTable& getStdKeyTable();
CourseKeyTable& getCourseKeyTable();

#endif