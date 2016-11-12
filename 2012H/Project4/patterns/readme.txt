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
     40       0.01        0.00
     80       0.20        0.00
    100       0.42        0.00
    150       1.67        0.07
    200       5.26        0.12
    400       85.86       0.22
   1000       >180        1.34
   2000       >180        5.94
   4000       >180        25.57
  10000       >180        177.209


/**********************************************************************
 *  Estimate how long it would take to solve an instance of size
 *  N = 1,000,000 for each of the two algorithms using your computer.
 **********************************************************************/
Brute:    3.35 × 10^15 seconds
Sorting:  9.98 × 10^10 seconds



/**********************************************************************
 *  Theoretical   Give the worst-case running time of your programs
 *  Analysis      as a function of N. Justify your answer briefly.
 **********************************************************************/
Brute: O(N^4) as the main operation of Brute is four for loop, each with a length proportional to n.

Sorting: O(N^2logN) as for each point, it will become the origin. This gives N. Then for each point, there is a sorting operation. As unknown sorting is provided, and it is not specified in the library, I assumed best worst case one, which is O(NlogN);



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

