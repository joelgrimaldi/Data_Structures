HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME:  Joel Grimaldi


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com stackoverflow.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  7



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of moves that have the same starting frame

reading the database/populating your initial data structure: O(m f log(f) log(m))
       -m and f for row and column to go through database file,
	log(f) for ordering the set of fighters each time one is
	added, log(m) for adding each value to a map and sorting
	it each time.

-q (specific move): O(f)
       -only goes through a for loop checking if the fighter
	name is the target fighter, hence only f

-q (all): O(f)
       -same thing, only one for loop

-f: O(2f log(f))
       -two for loops going through a vector of fighters
	log(f) for adding to a set

-s: O(2f log(f))
       -same thing as -f

-d: O(f)
       -only has one for loop going through
	a vector of fighters


MISC. COMMENTS TO GRADER:  
hello grader, I am an aspiring good student and good grades really help me reach my goal. I know Cs
get degrees and all, but I'm just hoping for a B- or something, thanks for grading

