// TestApp.cpp : Defines the entry point for the console application.
//

#include <tchar.h>
#include <vector>

#include <stdio.h>

#include "Task.h"

/\
*\
Regular
comment
*\
/

/\
/ This is not a C++ / C99 comment!


/\
\
\
/ But this is a C++ / C99 comment!


/\
* This is not a C or C++ comment!

/\
* This is a regular C comment *\
but this is just a routine continuation *\
and that was not the end either - but this is *\
\
/


//int ch = "\*";

int _tmain(int argc, _TCHAR* argv[])
{



    printf("this is \\/* \"a string\" */\\ with escaped chars");
    printf("\n");

    printf("this is \\/* \"a string\" */\\ with escaped chars");
    printf("\n");

    printf("this is \\/* \"a tricky string */\\ with escaped chars");
    printf("\n");

    printf("this is \\/* \"a string /*\" \\ with escaped */ chars");
    printf("\n");


    int id = 2 + 2;

    std::vector<std::string> strVect = {
        "the",
        "the word",
        "the sentence with more words",
        "the spaces in the end     ",
        "     the spaces in the beginning",
        "the spaces in the      middle",
        "    the   spaces  everywhere   "
    };

    for (auto &s : strVect)
    {
        std::string strTmp = s;
        char *szTmp  = const_cast<char*>(strTmp.c_str());

        removeComments(szTmp);
    }

    
    return 0;
}

