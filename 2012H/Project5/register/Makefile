CPP = g++

VPATH = menu obj data ADT

Register: main.o validation.o singleton.o
	$(CPP) -o Register main.o menu.o actions.o validation.o singleton.o

main.o: main.cpp menu.o actions.o
	$(CPP) -c main.cpp

menu.o: menu.cpp actions.o menu.h
	$(CPP) -c $<

actions.o: actions.cpp actions.h validation.o singleton.o
	$(CPP) -c $<

validation.o: validation.cpp validation.h course.h student.h course_selection.h indexes.h hash_table.h hashable.h sort_list.h
	$(CPP) -c $<

singleton.o: singleton.cpp singleton.h course.h student.h course_selection.h indexes.h hash_table.h hashable.h sort_list.h
	$(CPP) -c $<

clean: 
	rm -f *.o Register 

version:
	$(CPP) -v