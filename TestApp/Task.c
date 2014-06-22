
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

static char reallySmallCharStack = -1;
static State reallySmallStateStack = -1;

// State translation table
Branch transTable[8][6] = 
{
 /*                              0:regular symbols           1:'/'                        2:'*'                        3:'\n'                 4:'"'                 5:'\'              
 /* 0:State_Code           */  { { State_Same, 1 },     { State_CommentLeadin, 0 }, { State_Same, 1 },           { State_Same, 1 },     { State_String, 1 },   { State_Escaped /*!*/, 0 } },    /* State_Code           */ 
 /* 1:State_CommentLeadin  */  { { State_Code, 1 },     { State_CppComment, 0 },    { State_CComment, 0 },       { State_Code, 1 },     { State_String, 1 },   { State_Escaped /*!*/, 0 } },    /* State_CommentLeadin  */ 
 /* 2:State_CommentLeadout */  { { State_CComment, 0 }, { State_Code, 0 },          { State_Same, 0 },           { State_CComment, 0 }, { State_CComment, 0 }, { State_Escaped /*!*/, 0 } },    /* State_CommentLeadout */
 /* 3:State_CComment       */  { { State_Same, 0 },     { State_Same, 0 },          { State_CommentLeadout, 0 }, { State_Same, 0 },     { State_Same, 0 },     { State_Escaped /*!*/, 0 } },    /* State_CComment       */ 
 /* 4:State_CppComment     */  { { State_Same, 0 },     { State_Same, 0 },          { State_Same, 0 },           { State_Code, 1 },     { State_Same, 1 },     { State_Escaped /*!*/, 0 } },    /* State_CppComment     */
 /* 5:State_String         */  { { State_Same, 1 },     { State_Same, 1 },          { State_Same, 1 },           { State_Code, 1 },     { State_Code, 1 },     { State_Escaped, 1 }       },    /* State_String         */
 /* 6:State_Escaped        */  { { State_Prev, 1 },     { State_Prev, 1 },          { State_Prev, 1 },           { State_Prev, 0 },     { State_Prev, 1 },     { State_Prev, 1 }          },    /* State_Escaped        */
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
            currState = reallySmallStateStack;
            reallySmallStateStack = -1;
            break; 
        case State_Same:
            break;
        default:
            currState = b.nextState;
    }

    if (0) {}
    else if (prevState == State_CommentLeadin)
    {
        if (!(currState == State_CComment || currState == State_CppComment))
        {
            // comment not confirmed, return the char
            str[*iW] = reallySmallCharStack;
            (*iW)++;
        }

        reallySmallCharStack = -1;
    }
    else if (currState == State_CommentLeadin)
    {
        reallySmallCharStack = c;
    }
    else if (currState == State_Escaped)
    {
        reallySmallStateStack = prevState; 
    }

    *s = currState;

    // output if required
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

    long long iR = 0; // reading position
    long long iW = 0; // writing position
    State s = State_Code;

    while (str[iR] != '\0')
    {
        step2(str, &iR, &iW, &s);

        iR++;
    }

    str[iW] = 0;

    return;
}


void step(char *str, long long *iR, long long *iW, State *s)
{
    int bOutput = 0;

    switch (*s)
    {
    case State_Code:
        if (0) {}
        else if (str[*iR] == '/')
        {
            *s = State_CommentLeadin;
        }
        else
        {
            bOutput = 1;
        }

        break;

    case State_CommentLeadin:
        if (0) {}
        else if (str[*iR] == '/')
        {
            *s = State_CppComment;
        }
        else if (str[*iR] == '*')
        {
            *s = State_CComment;
        }
        else {
            str[*iW] = '/';
            (*iW)++;

            *s = State_Code;
            bOutput = 1;
        }
        break;

    case State_CppComment:
        if (0) {}
        else if (str[*iR] == '\n')
        {
            *s = State_Code;
            bOutput = 1;
        }

        break;

    case State_CComment:
        if (0) {}
        else if (str[*iR] == '*')
        {
            *s = State_CommentLeadout;
        }

        break;

    case State_CommentLeadout:
        if (0) {}
        else if (str[*iR] == '/')
        {
            *s = State_Code;
        }
        else if (str[*iR] == '*')
        {
            *s = State_CommentLeadout;
        }
        else
        {
            *s = State_CComment;
        }

        break;
    }

    if (bOutput == 1)
    {
        str[*iW] = str[*iR];
        (*iW)++;
    }

    return;
}
