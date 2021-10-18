HOMEWORK 8: ROPES


NAME:  Joel Grimaldi


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com stackoverflow.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 30

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor: 
O((log n) (log m)): copies each nodes values into a new Node()
O(nm): takes longer

Construct from Node*:
O(log n): goes through entire rope in search of leaves for size_ variable
O(n): takes longer to construct

Index:
O(p): longest path because it's given the index
O(p): only thing that can change is p

Report:
O(np): uses index in a for loop
O(np): only thing that can change is p

iterator operator++:
O(log n): goes through rope
O(log n): will only change time by amount n

Split:
O(pnlog(n)^2): searches through rope and updates size
O(pn^3): searches take longer

Concat:
O(log(n)^2): goes through all leaves to copy and then again to get size
O(log(n)^2): same



TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

I tested split with different indexes like 12 0 21 22 -1


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

