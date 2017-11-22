enroll(1701, [c01, c10]).
enroll(1602, [c21]).
enroll(1711, [c01, c32, c10]).
enroll(1501, []).
teach(p01, [c01, c21]).
teach(p02, [c23]).
teach(p03, [c10]).
teach(p04, []).

member(X, [X|_]).
member(X, [_|Tail]) :- member(X, Tail).

incourse(X, Y) :- enroll(X, Z), member(Y, Z). % Student X has enrolled course Y
teach_course(X, Y) :- teach(X, Z), member(Y, Z). % Professor X teaches course Y

teach_std(X, Y) :- teach_course(X, Z), incourse(Y, Z). % Professor X teaches student Y

prof_ids(X, Y) :- teach_std(X, Y).
