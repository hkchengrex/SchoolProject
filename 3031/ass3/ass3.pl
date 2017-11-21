enroll(1701, [c01, c10]).
enroll(1602, [c21]).
enroll(1711, [c01, c32, 10]).
enroll(1501, []).
teach(p01, [c01, c21]).
teach(p02, [c23]).
teach(p03, [c10]).
teach(p04, []).

member(X, [X|_]).
member(X, [_|Tail]) :- member(X, Tail).

prof_ids(X, L) :- enroll(X, Z), teach(L, Y), member(C, Y), member(C, Z).
