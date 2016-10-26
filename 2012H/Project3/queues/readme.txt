/**********************************************************************
 *  Randomized Queues and Deques
 **********************************************************************/

Name: Cheng Ho Kei
ID: 12219689
Login: hkchengad
Hours to complete assignment (optional): 6


/**********************************************************************
 *  Explain briefly how you implemented the randomized queue and deque.
 *  Which data structure did you choose (array, linked list, etc.)
 *  and why?
 **********************************************************************/

For randomized queue, I used array so that random access operation can be done in constant amortized time.
Sometimes I would need to resize the array during an access operation but as it is amortized, 
occasional slow resizing is fine.

For deque, I used doubly linked list so that I can manipulate the list from both the beginning and the end
pretty easily.


/**********************************************************************
 *  Briefly describe why any sequence of N randomized queue operations,
 *  starting from an empty randomized queue, takes O(N) time.
 **********************************************************************/

As the operations are in constant amortized time, most of the times it takes O(1) to compelte one operation.
Some other times it may cost extra time, but that extra time (resizing the array), when spread out to
all operations, would take O(cN) times, so that total operation time would be O(cN + N*1) = O(N).


/**********************************************************************
 *  Briefly describe why each Deque operation takes O(1) time.
 **********************************************************************/

In each deque operation, I only handled a constant amount of pointers assignment, 
which is independent of the size of the list, so it would takes O(1) time.


/**********************************************************************
 *  How much memory (in bytes) does your data type use to store N items.
 *  Use tilde notation to simplify your answer. Use the memory requirements
 *  for a "typical machine" given in Lecture. In your analysis, don't include
 *  the memory for the items themselves (as this memory is allocated by
 *  the client and depends on the item type.
 *  For a typical machine, refer to page 11 of 
 *  https://www.cs.princeton.edu/courses/archive/spr10/cos226/lectures/02-14Analysis-2x2.pdf
 **********************************************************************/

RandomizedQueue: 
I used two integers, one pointer.
Therefore, ignoring memory of the items, it is constant memory 4+4+4 = 12 bytes.

Dequeue: 
I used one integer, 1 node pointer and N+1 nodes.
In each node, there are 2 node pointers.
Therefore I used 4+4 + 4+4(sentinal node) + 4*2*N ~ 8N bytes.


/**********************************************************************
 *  Known bugs / limitations.
 **********************************************************************/
/

/**********************************************************************
 *  List whatever help (if any) that you received and from whom,
 *  including help from staff members or lab TAs.
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