
#include <stdlib.h>

#include "Task.h"

// State machine states
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

// Decision branch
typedef struct Branch {
    State nextState;
    int output;
} Branch;

// Control symbols, changing state 
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

// State translation table
Branch transTable[8][6] = 
{
 /*                              0:regular symbols           1:'/'                        2:'*'                        3:'\n'                 4:'"'                 5:'\'                                         */
 /* 0:State_Code           */  { { State_Same, 1 },     { State_CommentLeadin, 0 }, { State_Same, 1 },           { State_Same, 1 },     { State_String, 1 },   { State_Escaped, 0 } },    /* State_Code           */
 /* 1:State_CommentLeadin  */  { { State_Code, 1 },     { State_CppComment, 0 },    { State_CComment, 0 },       { State_Code, 1 },     { State_String, 1 },   { State_Escaped, 0 } },    /* State_CommentLeadin  */
 /* 2:State_CommentLeadout */  { { State_CComment, 0 }, { State_Code, 0 },          { State_Same, 0 },           { State_CComment, 0 }, { State_CComment, 0 }, { State_Escaped, 0 } },    /* State_CommentLeadout */
 /* 3:State_CComment       */  { { State_Same, 0 },     { State_Same, 0 },          { State_CommentLeadout, 0 }, { State_Same, 0 },     { State_Same, 0 },     { State_Escaped, 0 } },    /* State_CComment       */
 /* 4:State_CppComment     */  { { State_Same, 0 },     { State_Same, 0 },          { State_Same, 0 },           { State_Code, 1 },     { State_Same, 1 },     { State_Escaped, 0 } },    /* State_CppComment     */
 /* 5:State_String         */  { { State_Same, 1 },     { State_Same, 1 },          { State_Same, 1 },           { State_Code, 1 },     { State_Code, 1 },     { State_Escaped, 1 } },    /* State_String         */
 /* 6:State_Escaped        */  { { State_Prev, 1 },     { State_Prev, 1 },          { State_Prev, 1 },           { State_Prev, 0 },     { State_Prev, 1 },     { State_Prev, 1 }    },    /* State_Escaped        */
};

void step2(char *str, long long *iR, long long *iW, State *s)
{
    State prevState = *s;
    char c = str[*iR];

    // Get control index for symbol 
    int ctrlIdx = CtrlSymbol(c);

    // Get decision branch
    Branch b = transTable[*s][ctrlIdx];

    // Shift state if not the same
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
            // comment not confirmed, return the char
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

    // save the current state
    *s = currState;

    // output if requested
    if (b.output == 1)
    {
        str[*iW] = c;
        (*iW)++;
    }

    return;
}

void removeComments(char *str)
{
    // check for empty pointer
    if (str == NULL)
        return;

    // check for empty string
    if (str[0] == '\0')
        return;

    long long iR = 0;     // reading position
    long long iW = 0;     // writing position
    State s = State_Code; // initial state

    while (str[iR] != '\0')
    {
        step2(str, &iR, &iW, &s);
        iR++;
    }

    // cut the string
    str[iW] = 0;

    return;
}
