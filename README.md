Test task
=========

Write a function to remove C and C++ comments from an input string while 
leaving all other data intact. 
For performance reasons, your function should not allocate memory, 
must handle even very long strings, and must be written in standard C.
When the function returns, str should have the same data as when it was
called, but with comments removed. If library calls are used, they must be 
present in the standard C library (both Microsoft and Unix).
C-style comments can span multiple lines.

Example C comment:

/*
 * Comments start with /* and end with the opposite
 * (// is for C++ comments)
 */

Example C++ comment:

// Another comment, can only be one line

Function prototype:

void removeComments(char *str)

{

}


Solution and usage
--------
The solution is implemented in Visual Studio 2013. The required function 
removeComments is located in files Task.h and Task.c of project TestApp. 
Unit tests are located in unittest1, resource files for unit tests are located 
in TestFiles directory.

To run all the unit test, open TestApp.sln in Visual Studio 2013, find 
the Test Explorer Window and press Run All link.


Implementation notice
--------
The solution implemented in plain C, which is required by the task, as a state 
machine with additional processing of the step for special cases. There was no
clarifications about whether a real C standard should be used and which version 
of the standard should be taken into account. Thus, comments are just erased,
leaving all the spaces and line carriages outside the comment intact. Some of 
the comments, which contradict the C standard, like nested C comments,
 /* /* */ */ are not supported and may create garbage in output.

To evaluate the performance, a 10Mb file has been used as a load test. 
The processing time for 10Mb takes about 9 sec on a laptop with 
Intel Core i5 3320M, Ivy Bridge processor.

Total implementation time took about 10 hours.