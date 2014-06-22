
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
    State_Escapedchar,
} State;

typedef struct Branch {
    State nextState;
    int output;
} Branch;

char CtrlSymbol(char c)
{
    char ctrlVal = 3;
    switch (c)
    {
        case '/':
            ctrlVal = 0;
            break;

        case '*':
            ctrlVal = 1;
            break;

        case '\n':
            ctrlVal = 2;
            break;
    }

    return ctrlVal;
}

Branch transTable[5][4] = 
{
    /*                                 '/'                          '*'                         '\n'                 all others    */
    /* State_Code           */  { { State_CommentLeadin, 0 }, { State_Code, 1 },           { State_Code, 1 },     { State_Code, 1 }       },    /* State_Code           */ 
    /* State_CommentLeadin  */  { { State_CppComment, 0 },    { State_CComment, 0 },       { State_Code, 1 },     { State_Code, 1 }       },    /* State_CommentLeadin  */ 
    /* State_CommentLeadout */  { { State_Code, 0 },          { State_CommentLeadout, 0 }, { State_CComment, 0 }, { State_CComment, 0 }   },     /* State_CommentLeadout */
    /* State_CComment       */  { { State_CComment, 0 },      { State_CommentLeadout, 0 }, { State_CComment, 0 }, { State_CComment, 0 }   },    /* State_CComment       */ 
    /* State_CppComment     */  { { State_CppComment, 0 },    { State_CppComment, 0 },     { State_Code, 1 },     { State_CppComment, 0 } },    /* State_CppComment     */
};

void step2(char *str, long long *iR, long long *iW, State *s)
{
    int ctrl = CtrlSymbol(str[*iR]);
    Branch b = transTable[*s][ctrl];

    if (*s == State_CommentLeadin)
    {
        if (ctrl != 0 && ctrl != 1)
        {
            str[*iW] = '/';
            (*iW)++;
        }
    }

    // shift state
    *s = b.nextState;

    // output if required
    if (b.output == 1)
    {
        str[*iW] = str[*iR];
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