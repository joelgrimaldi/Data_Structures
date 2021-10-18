HOMEWORK 6: RICOCHET ROBOTS RECURSION


NAME: Joel Grimaldi



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com stackoverflow.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  48



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

i & j = dimensions of the board
    r = number of robots on the board
    g = number of goals
    w = number of interior walls
    m = maximum total number of moves allowed

moveRobot:	O(number squares moved)
Visualize:	O(r^m)
solution:	O(amount of paths)
-all_solutions:	O(3(moveRobot^(Visualize))(solution))
-visualize:	O(moveRobot^Visualize)
one_solution:   O(all_solutions)

I started by making a very long working version of visualize, I attempted to shorten
the runtime of this function by checking if the board had already been in the exact same
state before but with a smaller number in the spot previously, and if that was the case
then I ended that recursion by returning ret. I also made it so that robots couldn't go
one direction and then the opposite direction if it went back to the same exact position.
Finally, if the arguments didn't have a -visualize, the maximum depth of recursion was
set to when one path made it to the goal. I couldn't find any other ways to improve it
and I'm thinking that I made Visualize in a completely unoptimized way and would attempt
a different way if I had more time.


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
Correctness & approximate wall clock running time for various command
line arguments.

	- Did not attempt to make it work with multiple goals, couldn't find any more ways
	to shorten the runtime so some of the test cases kill signal before my program finishes
	what it is doing. Otherwise the code works in submitty with maxs less than 10.

TIMES:
	- puzzle1.txt -max_moves 8 -visualize A:	0m24.627s
	- puzzle1.txt -max_moves 8 -all_solutions:	0m25.061s
	- puzzle4.txt					0m1.409s
	- puzzle2.txt -max_moves 6 -all_solutions:      0m0.815s

MISC. COMMENTS TO GRADER:  
Hello, this homework was kinda aids, thanks for grading it :)


