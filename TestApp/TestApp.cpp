// TestApp.cpp : Defines the entry point for the console application.
//

#include <tchar.h>
#include <vector>

#include "Task.h"


int _tmain(int argc, _TCHAR* argv[])
{
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

