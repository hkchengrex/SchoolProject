/**********************************************************************
 *  Pattern Recognition readme.txt template
 **********************************************************************/

Name: Cheng Ho Kei
Login: hkchengad
Hours to complete assignment (optional):


/**********************************************************************
 *  Step 1.  Explain briefly how you implemented brute force.
 *           What method(s) did you add to the Point data type?
 **********************************************************************/

In Brute Force, 4 points are checked at one time. In order to select 4 points at a time and check time, I added an isCollinear method, that method would check whether the current point is collinear with the other 3 points or not.


/**********************************************************************
 *  Step 2.  Explain briefly how you implemented the sorting solution.
 *           Did you sort by angle, slope, or something else?
 *           What method(s) did you add to the Point data type?
 *           What steps did you do to print a minimal representation?
 **********************************************************************/

Each point in the list would be selected once. Then I sort all other points by their angle from the selected origin point. Then I run through the sorted list to see if there are enough consecutive terms with the same angle. If there exist such sequence, I can say that I find a line with these points and the origin. The selected points are also marked so that duplicated check is avoided.


/**********************************************************************
 *  Empirical    Fill in the table below with actual running times in
 *  Analysis     seconds when reasonable (say 180 seconds or less).
 *               You can round to the nearest tenth of a second.
 **********************************************************************/

      N       brute       sorting
---------------------------------
     10       0.00        0.00
     20       0.00        0.00
     40       0.00        0.00
     80       0.03        0.00
    100       0.03        0.00
    150       0.16        0.00
    200       0.51        0.00
    400       7.02        0.02
   1000       >180        0.13
   2000       >180        0.24
   4000       >180        1.11
  10000       >180        8.84


/**********************************************************************
 *  Estimate how long it would take to solve an instance of size
 *  N = 1,000,000 for each of the two algorithms using your computer.
 **********************************************************************/
Brute:    1.09 × 10^11 seconds
Sorting:  1.73 × 10^7 seconds



/**********************************************************************
 *  Theoretical   Give the worst-case running time of your programs
 *  Analysis      as a function of N. Justify your answer briefly.
 **********************************************************************/
Brute: O(N^4) as the main operation of Brute is four for loop, each with a length proportional to n.

Sorting: O(N^3) as for each point, it will become the origin. This gives N. Then for each point, there is a sorting operation. As unknown sorting is provided, and it is not specified in the library, I assumed quick sort, which is O(N^2) worst case. So total would be O(N) times O(N^2) sort, overall O(n^3). 



/**********************************************************************
 *  Known bugs / limitations. For example, if your program prints
 *  out different representations of the same line segment when there
 *  are 5 or more points on a line segment, indicate that here.
 **********************************************************************/
/


/**********************************************************************
 *  List whatever help (if any) that you received. Be specific with
 *  the names of lab TAs, classmates, or course staff members.
 **********************************************************************/
/


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
/



/**********************************************************************
 *  List any other comments here. Feel free to provide any feedback   
 *  on how much you learned from doing the assignment, and whether    
 *  you enjoyed doing it.                                             
 **********************************************************************/
/

