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
Solution is implemented for Visual Studio 2013 and located in files Task.h and Task.c. 
Unit tests are located in unittest1. To open and run the solution and all unit test, open TestApp.sln in Visual Studio 2013.
