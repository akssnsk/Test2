
#include <stdlib.h>

#include "Task.h"


typedef enum State {
    State_Code = 0,
    State_CommentLeadin,
    State_CommentLeadout,
    State_CComment,
    State_CppComment,
    State_String,
    State_Escaped,
    State_Prev,
    State_Same,
} State;


typedef struct Branch {
    State nextState;
    int output;
} Branch;


char CtrlSymbol(char c)
{
    char ctrlVal = 0;
    switch (c)
    {
        case '/':
            ctrlVal = 1;
            break;

        case '*':
            ctrlVal = 2;
            break;

        case '\n':
            ctrlVal = 3;
            break;

        case '\"':
            ctrlVal = 4;
            break;

        case '\\':
            ctrlVal = 5;
            break;
    }

    return ctrlVal;
}

static char reallyShortCharStack = -1;
static State reallyShortStateStack = -1;


Branch transTable[8][6] = 
{
 
   { { State_Same, 1 },     { State_CommentLeadin, 0 }, { State_Same, 1 },           { State_Same, 1 },     { State_String, 1 },   { State_Escaped, 0 } },    
   { { State_Code, 1 },     { State_CppComment, 0 },    { State_CComment, 0 },       { State_Code, 1 },     { State_String, 1 },   { State_Escaped, 0 } },    
   { { State_CComment, 0 }, { State_Code, 0 },          { State_Same, 0 },           { State_CComment, 0 }, { State_CComment, 0 }, { State_Escaped, 0 } },    
   { { State_Same, 0 },     { State_Same, 0 },          { State_CommentLeadout, 0 }, { State_Same, 0 },     { State_Same, 0 },     { State_Escaped, 0 } },    
   { { State_Same, 0 },     { State_Same, 0 },          { State_Same, 0 },           { State_Code, 1 },     { State_Same, 1 },     { State_Escaped, 0 } },    
   { { State_Same, 1 },     { State_Same, 1 },          { State_Same, 1 },           { State_Code, 1 },     { State_Code, 1 },     { State_Escaped, 1 } },    
   { { State_Prev, 1 },     { State_Prev, 1 },          { State_Prev, 1 },           { State_Prev, 0 },     { State_Prev, 1 },     { State_Prev, 1 }    },    
};

void step2(char *str, long long *iR, long long *iW, State *s)
{
    State prevState = *s;
    char c = str[*iR];

    
    int ctrlIdx = CtrlSymbol(c);

    
    Branch b = transTable[*s][ctrlIdx];

    
    State currState = prevState;
    switch (b.nextState)
    {
        case State_Prev:
            currState = reallyShortStateStack;
            reallyShortStateStack = -1;
            break; 
        case State_Same:
            break;
        default:
            currState = b.nextState;
    }

    if (0) {}
    else if (prevState == State_CommentLeadin && currState != State_Escaped)
    {
        if (!(currState == State_CComment || currState == State_CppComment))
        {
            
            str[*iW] = reallyShortCharStack;
            (*iW)++;
        }

        reallyShortCharStack = -1;
    }
    else if (currState == State_CommentLeadin)
    {
        reallyShortCharStack = c;
    }
    else if (currState == State_Escaped)
    {
        reallyShortStateStack = prevState;
    }

    
    *s = currState;

    
    if (b.output == 1)
    {
        str[*iW] = c;
        (*iW)++;
    }

    return;
}

void removeComments(char *str)
{
    
    if (str == NULL)
        return;

    
    if (str[0] == '\0')
        return;

    long long iR = 0;     
    long long iW = 0;     
    State s = State_Code; 

    while (str[iR] != '\0')
    {
        step2(str, &iR, &iW, &s);
        iR++;
    }

    
    str[iW] = 0;

    return;
}
