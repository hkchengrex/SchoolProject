#ifndef _ACTIONS_H
#define _ACTIONS_H

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

void backToMainMenu();

#endif