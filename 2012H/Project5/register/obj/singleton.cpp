#include "singleton.h"

StudentTable& getStdTable(){
	static StudentTable table;
	return table;
}

CourseTable& getCourseTable(){
	static CourseTable table;
	return table;
}

SortList<CourseSelection>& getCourseSelectionList(){
	static SortList<CourseSelection> mList;
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
