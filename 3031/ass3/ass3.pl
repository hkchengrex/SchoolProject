enroll(1701, [c01, c10]).
enroll(1602, [c21]).
enroll(1711, [c01, c21, c10]).
enroll(1501, []).
teach(p01, [c01, c21]).
teach(p02, [c23]).
teach(p03, [c10]).
teach(p04, []).

stu_list(List) :- findall(X, teach(X, _), List).
pro_list(List) :- findall(X, teach(X, _), List).

member(X, [X|_]).
member(X, [_|Tail]) :- member(X, Tail).

head(X, [X|_]).
tail(X, [_|X]).

incourse(Stu, Cou) :- enroll(Stu, List), member(Cou, List), !.
teach_course(Pro, Cou) :- teach(Pro, List), member(Cou, List), !.
teach_std(Pro, Stu) :- teach_course(Pro, Cou), incourse(Stu, Cou), !. 

teach_coulist(Pro, CouList) :- member(X, CouList), teach_course(Pro, X), !.

list_prof_ids(CouList, [Head|ResTail], [Head|ProTail]) :- teach_coulist(Head, CouList), list_prof_ids(CouList, ResTail, ProTail), !.
list_prof_ids(CouList, ResList, [ProHead|ProTail]) :- \+ teach_coulist(ProHead, CouList),  list_prof_ids(CouList, ResList, ProTail), !.
list_prof_ids(_, [], []) :- !.

prof_ids(Stu, List) :- enroll(Stu, CouList), pro_list(ProList), list_prof_ids(CouList, List, ProList).
