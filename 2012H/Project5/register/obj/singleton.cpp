#include "singleton.h"

StudentTable& getStdTable(){
	static StudentTable table;
	return table;
}

CourseTable& getCourseTable(){
	static CourseTable table;
	return table;
}

SortedList<CourseSelection>& getCourseSelectionList(){
	static SortedList<CourseSelection> mList;
	return mList;
}

StudentKeyTable& getStdKeyTable(){
	static StudentKeyTable table;
	return table;
}

CourseKeyTable& getCourseKeyTable(){
	static CourseKeyTable table;
	return table;
}
