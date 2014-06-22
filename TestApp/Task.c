
#include <stdlib.h>

#include "Task.h"

// State machine states
typedef enum State {
    State_Same = 0,
    State_Code,
    State_CommentLeadin,
    State_CommentLeadout,
    State_CComment,
    State_CppComment,
    State_String,
    State_Escaped,
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

// State translation table
Branch transTable[8][5] = 
{
    /*                              0:code symbols             1:'/'                        2:'*'                        3:'\n'                 4:'"'              
    /* State_Same           */  { { State_Same, 0 },       { State_Same, 0 },          { State_Same, 0 },           { State_Same, 0 },     { State_Same, 0 }        },    /* State_Same           */
    /* State_Code           */  { { State_Same, 1 },       { State_CommentLeadin, 0 }, { State_Same, 1 },           { State_Same, 1 },     { State_String, 1 }      },    /* State_Code           */ 
    /* State_CommentLeadin  */  { { State_Code, 1 },       { State_CppComment, 0 },    { State_CComment, 0 },       { State_Code, 1 },     { State_String, 1 }      },    /* State_CommentLeadin  */ 
    /* State_CommentLeadout */  { { State_CComment, 0 },   { State_Code, 0 },          { State_Same, 0 },           { State_CComment, 0 }, { State_CComment, 0 }    },    /* State_CommentLeadout */
    /* State_CComment       */  { { State_Same, 0 },       { State_Same, 0 },          { State_CommentLeadout, 0 }, { State_Same, 0 },     { State_Same, 0 }        },    /* State_CComment       */ 
    /* State_CppComment     */  { { State_Same, 0 },       { State_Same, 0 },          { State_Same, 0 },           { State_Code, 1 },     { State_Same, 1 }        },    /* State_CppComment     */
    /* State_String         */  { { State_Same, 1 },       { State_Same, 1 },          { State_Same, 1 },           { State_Code, 1 },     { State_Code, 1 }        },    /* State_CppComment     */
    /* State_Escaped        */  { { State_String, 1 },     { State_String, 1 },        { State_String, 1 },         { State_Code, 1 },     { State_Code, 1 }        },    /* State_CppComment     */
};

void step2(char *str, long long *iR, long long *iW, State *s)
{
    // Get control index for symbol 
    int ctrlIdx = CtrlSymbol(str[*iR]);

    // Output slash if no comment confirmed
    if (*s == State_CommentLeadin)
    {
        if (ctrlIdx != 1 && ctrlIdx != 2)
        {
            str[*iW] = '/';
            (*iW)++;
        }
    }

    // Get decision branch
    Branch b = transTable[*s][ctrlIdx];

    // Shift state
    if (b.nextState != State_Same)
    {
        *s = b.nextState;
    }

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
