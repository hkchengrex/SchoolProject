(* CHENG Ho Kei, hkchengad, 12219689 *)

datatype course = C of (string * string) list;
datatype enroll = E of (int * string list) list;

fun is_tuple_in_course(x : (string * string), C([])) = false
|	is_tuple_in_course(x : (string * string), C(course)) = 
		if (length(course) = 1) 
		then 
			((#1(x)) = (#1(hd(course))))
		else
			if ((#1(x)) = (#1(hd(course))))
			then
				true
			else
				is_tuple_in_course(x, C(tl(course)));

fun insert_course([] : (string * string) list, C([])) = C([])
|	insert_course([] : (string * string) list, C(item)) = C(item)
| 	insert_course(x::tail : (string * string) list, C(item)) = 
		if is_tuple_in_course(x, C(item)) 
		then insert_course(tail, C(item)) 
		else insert_course(tail, C(item@[x]));

fun is_item_in_list([], item : string) = false
|	is_item_in_list(lst, item : string) = 
	if (hd(lst) = item)
	then true
	else is_item_in_list(tl(lst), item);

fun insert_string_distinct ([], new) = new
| 	insert_string_distinct (org , []) = org
|	insert_string_distinct (org, new) = 
		if (is_item_in_list(org, hd(new)))
		then
			insert_string_distinct(org, tl(new))
		else
			insert_string_distinct(org@[hd(new)], tl(new));

fun insert_enroll_front(x: (int * string list), E(enroll)) = E(x :: enroll);

fun insert_enroll (x: (int * string list), E([])) = E(x::[])
|	insert_enroll (x: (int * string list), E(enroll)) = 
		if ((#1(x)) = (#1(hd(enroll))))
		then
			E ((#1(hd(enroll)), insert_string_distinct(#2(hd(enroll)), #2(x))) :: tl(enroll))
		else
			insert_enroll_front(hd(enroll), insert_enroll(x, E(tl(enroll))));

fun query_students (s: string, E([])) = []
|	query_students (s: string, E(enroll)) = 
		if (is_item_in_list(#2(hd(enroll)), s))
		then #1(hd(enroll)) :: query_students(s, E(tl(enroll)))
		else query_students(s, E(tl(enroll)));

fun remove_duplicate([] : int list, b : int list) = b
|	remove_duplicate(a : int list, [] : int list) = a
|	remove_duplicate(a : int list, b : int list) = 
		if (hd(a) = hd(b))
		then 
			hd(a) :: remove_duplicate(tl(a), tl(b))
		else
			hd(a) :: hd(b) :: remove_duplicate(tl(a), tl(b));

fun get_distinct_std_list(pro: string, C([]), E(enroll)) = []
|	get_distinct_std_list(pro: string, C(course), E(enroll)) = 
	if (#2(hd(course)) = pro)
	then 
		remove_duplicate(query_students(#1(hd(course)), E(enroll)), get_distinct_std_list(pro, C(tl(course)), E(enroll)))
	else
		get_distinct_std_list(pro, C(tl(course)), E(enroll));

fun count_distinct_students(pro: string, C(course), E(enroll)) = length(get_distinct_std_list(pro, C(course), E(enroll)));

fun insert_course_front(x: (string * string), C(course)) = C(x :: course);

fun delete_course(s: string, C([])) = C([])
|	delete_course(s: string, C(course)) = 
		if (#1(hd(course)) = s)
		then delete_course(s, C(tl(course)))
		else insert_course_front(hd(course), delete_course(s, C(tl(course))));

fun delete_string(s: string, []: string list) = []
|	delete_string(s: string, lst: string list) = 
		if (s = hd(lst))
		then delete_string(s, tl(lst))
		else hd(lst) :: delete_string(s, tl(lst));

fun delete_enroll(s: string, E([])) = E([])
|	delete_enroll(s: string, E(enroll)) = 
		insert_enroll_front((#1(hd(enroll)), delete_string(s, #2(hd(enroll)))), delete_enroll(s, E(tl(enroll))));


fun delete_course_enroll(s: string, C(course), E(enroll)) = (delete_course(s, C(course)), delete_enroll(s, E(enroll)));

(*Test Cases For Q1*)(*
insert_course ([], C [("comp10", "p01")]);
insert_course ([("comp12", "p02")], C []);
insert_course ([("comp10", "p02")], C [("comp10", "p01")]);
insert_course ([("comp13", "p01"), ("comp12", "p02")], C [("comp10","p01")]);
insert_course ([("comp10", "p02"), ("comp13", "p01"), ("comp12", "p02")], C [("comp10", "p01"), ("comp13", "p01")]);
*)

(*Test Cases For Q1*)(*
insert_enroll ((1702, []), E [(1701, ["comp10", "comp11"])]);
insert_enroll ((1701, ["comp10", "comp11"]), E []);
insert_enroll ((1701, ["comp11", "comp10"]), E [(1701, ["comp10","comp12"])]);
insert_enroll ((1702, ["comp10"]), E [(1701, ["comp10", "comp11"])]);
*)

(*Test Cases For Q3*)(*
query_students ("comp10", E []);
query_students ("comp10", E [(1701, ["comp10"])]);
query_students ("comp11", E [(1701, ["comp10"])]);
query_students ("comp10", E [(1701, ["comp10", "comp11"]), (1702,["comp13", "comp10"]), (1703, [])]);
*)


(*Test Cases For Q4*)(*
count_distinct_students ("p01", C [], E []);
count_distinct_students ("p01", C [("comp10", "p01")], E []);
count_distinct_students ("p01", C [("comp10", "p01")], E [(1701,["comp10"]), (1702, ["comp13"])]);
count_distinct_students ("p01", C [("comp10", "p01"), ("comp12","p02"), ("comp13", "p01")], E [(1701, ["comp10", "comp11"]), (1702,["comp13"])]);
*)

(*Test Cases For Q5*)(*
delete_course_enroll ("comp10", C [], E[]);
delete_course_enroll ("comp10", C [("comp10", "p01")], E []);
delete_course_enroll ("comp10", C [("comp10","p01")],E[(1701,["comp10"])]);
delete_course_enroll ("comp10", C [("comp10", "p01"), ("comp12","p02")], E [(1701, ["comp10", "comp11"]), (1702, ["comp13", "comp10"]),(1703, [])]);
*)

