enroll(1701, [c01, c10]).
enroll(1602, [c21]).
enroll(1711, [c01, c21, c10]).
enroll(1501, []).
teach(p01, [c01, c21]).
teach(p02, [c23]).
teach(p03, [c10]).
teach(p04, []).

%% Helper functions
member(X, [X|_]).
member(X, [_|Tail]) :- member(X, Tail).

head(X, [X|_]).
tail(X, [_|X]).

incourse(Stu, Cou) :- enroll(Stu, List), member(Cou, List), !.
teach_course(Pro, Cou) :- teach(Pro, List), member(Cou, List), !.
teach_std(Pro, Stu) :- teach_course(Pro, Cou), incourse(Stu, Cou), !. 

stu_list(List) :- findall(X, enroll(X, _), List).
pro_list(List) :- findall(X, teach(X, _), List).
cou_raw_list(List) :- findall(X, teach(_, X), List).

cou_temp_list([ResHead|ResTail], [ProHead|ProTail]) :- teach(ProHead, ResHead), cou_temp_list(ResTail, ProTail).
cou_temp_list([], _).

cou_list(List) :- pro_list(ProList), cou_temp_list(TempList, ProList), flatten(TempList, List), !.

%% teach_coulist(Pro, CouList) :- member(X, CouList), teach_course(Pro, X), !.

%% dis_list_prof_ids(CouList, [Head|ResTail], [Head|ProTail]) :- teach_coulist(Head, CouList), dis_list_prof_ids(CouList, ResTail, ProTail), !.
%% dis_list_prof_ids(CouList, ResList, [ProHead|ProTail]) :- \+ teach_coulist(ProHead, CouList),  dis_list_prof_ids(CouList, ResList, ProTail), !.
%% dis_list_prof_ids(_, [], []) :- !.

%% % I did not read the question well and I made a distinct version... It works, so I'll just keep it here
%% distinct_prof_ids(Stu, List) :- enroll(Stu, CouList), pro_list(ProList), dis_list_prof_ids(CouList, List, ProList).

% Question 1
list_prof_ids([CouHead|CouTail], [ResHead|ResTail]) :- teach_course(ResHead, CouHead), list_prof_ids(CouTail, ResTail), !.
list_prof_ids([], []) :- !.

prof_ids(Stu, List) :- enroll(Stu, CouList), list_prof_ids(CouList, List).

% Question 2
cou_list_com([Head|ATail], [Head|BTail], [Head|CouTail]) :- cou_list_com(ATail, BTail, CouTail), !.
cou_list_com([_|ATail], BList, [CouHead|CouTail]) :- cou_list_com(ATail, BList, [CouHead|CouTail]), !.
cou_list_com(AList, [_|BTail], [CouHead|CouTail]) :- cou_list_com(AList, BTail, [CouHead|CouTail]), !.
cou_list_com(_, _, []) :- !.

%% common_enroll(StuA, StuB, List) :- StuA \= StuB, enroll(StuA, CouA), enroll(StuB, CouB), cou_list_com(CouA, CouB, List).
common_enroll(StuA, StuB, List) :- var(StuA), var(List), enroll(StuA, CouA), enroll(StuB, CouB), cou_list_com(CouA, CouB, List), StuA \== StuB.
common_enroll(StuA, StuB, List) :- var(StuB), var(List), enroll(StuA, CouA), enroll(StuB, CouB), cou_list_com(CouA, CouB, List), StuA \== StuB.
common_enroll(StuA, StuB, List) :- \+ var(StuA), \+ var(StuB), var(List), enroll(StuA, CouA), enroll(StuB, CouB), cou_list_com(CouA, CouB, List), StuA \== StuB, !.
common_enroll(StuA, StuB, List) :- \+ var(StuA), \+ var(StuB), \+ var(List), enroll(StuA, CouA), enroll(StuB, CouB),
	permutation(List, PerRes), cou_list_com(CouA, CouB, PerRes), StuA \== StuB, !.


% Question 3
in_coulist(Std, CouList) :- member(X, CouList), incourse(Std, X), !.

list_std_ids(CouList, [Head|ResTail], [Head|StdTail]) :- in_coulist(Head, CouList), list_std_ids(CouList, ResTail, StdTail), !.
list_std_ids(CouList, ResList, [_|StdTail]) :- list_std_ids(CouList, ResList, StdTail), !.
list_std_ids(_, [], _) :- !.

student_list(Pro, List) :- \+ var(List), permutation(List, PerRes), teach(Pro, CouList), stu_list(StuList), list_std_ids(CouList, PerRes, StuList), !.
student_list(Pro, List) :- var(List), teach(Pro, CouList), stu_list(StuList), list_std_ids(CouList, List, StuList).

%Question 4
subset([], []) :- !.
subset([Head|SubTail], [Head|MainTail]) :- subset(SubTail, MainTail).
subset([SubHead|Tail], [MainHead|Tail]) :- subset(SubHead, MainHead).
subset(SubList, [_|MainTail]) :- subset(SubList, MainTail).
subset(SubList, [MainHead|_]) :- subset(SubList, MainHead).

course_list(List) :- \+ var(List), permutation(List, PerRes), cou_list(MainList), subset(PerRes, MainList), !.
course_list(List) :- var(List), cou_list(List), !.


%Question 5
incourse_s(Stu, Cou) :- enroll(Stu, List), member(Cou, List), !.

acc_stu(Cou, Num, [StuHead|StuTail]) :- incourse_s(StuHead, Cou), acc_stu(Cou, Num2, StuTail), Num is Num2+1, !.
acc_stu(Cou, Num, [StuHead|StuTail]) :- \+ incourse_s(StuHead, Cou), acc_stu(Cou, Num, StuTail), !.
acc_stu(_, 0, []) :- !.

count_students(Cou, Num) :- \+ var(Cou), stu_list(StuList), acc_stu(Cou, Num, StuList), !.
count_students(Cou, Num) :- var(Cou), cou_list(CouList), member(Cou, CouList), stu_list(StuList), acc_stu(Cou, Num, StuList).
