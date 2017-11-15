enroll(1701, [c01, c10]).
enroll(1602, [c21]).
enroll(1711, [c01, c32, 10]).
enroll(1501, []).
teach(p01, [c01, c21]).
teach(p02, [c23]).
teach(p03, [c10]).
teach(p04, []).

enroll_part(X, Y) :- enroll(X, [ _ | Y | _]).

prof_ids(X, Y) :- enroll(X, Z).
