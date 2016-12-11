#ifndef _ACTIONS_H
#define _ACTIONS_H

#include "../data/validation.h"
#include "../data/student.h"
#include "../data/course.h"
#include "../data/course_selection.h"
#include "../data/indexes.h"
#include "../obj/singleton.h"

//The file stores all the actions to be taken in the menu

void insertStd();
void modifyStd();
void deleteStd();
void queryStd();

void insertCourse();
void modifyCourse();
void deleteCourse();
void queryCourse();

void regCourse();
void dropCourse();
void modifyMark();
void queryRegCourse();

void listAllStd();
void listAllCourse();
void listAllCourseOfStd();
void listAllStdOfCourse();

void saveToDB();
void loadFromDB();

void hitEnterToContinue();

#endif