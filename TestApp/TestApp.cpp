// TestApp.cpp : Defines the entry point for the console application.
//

#include <tchar.h>
#include <vector>

#include <stdio.h>

#include "Task.h"

// The comments below are in fact syntatically correct
/\
*\
Ugly
comment
*\
/

/\
/ Ugly comment cpp stype

/\
\
\
/ One more ugly comment in cpp

/\
* Yet another ugly c comment

/\
* This is a regular C comment *\
and it's longer that expected (IntelliSenge went crazy here, me too) *\
even longer - but finite *\
\
/


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

