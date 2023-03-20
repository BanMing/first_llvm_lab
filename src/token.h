#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <map>

// The lexer(scanner) returns tokens [0-255] if it is an unknown character
// otherwise one of these for known things.
enum Token
{
    tok_eof = -1,

    // commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5
};

// Filled in if tok_indetifier
static std::string IdentifierStr;

// Filed in if tok_number
static double NumVal;

// gettok - Return the next token from standard input.
static int gettok()
{
    static int LastChar = ' ';

    // Skip any whitespace.
    while (isspace(LastChar))
    {
        LastChar = getchar();
    }

    // identifier: [a-zA-Z][a-zA-Z0-9]*
    if (isalpha(LastChar))
    {
        IdentifierStr = LastChar;
        while (isalnum(LastChar = getchar()))
        {
            IdentifierStr += LastChar;
        }

        if (IdentifierStr == "def")
        {
            return tok_def;
        }

        if (IdentifierStr == "extern")
        {
            return tok_extern;
        }

        return tok_identifier;
    }

    // Number: [0-9.]+
    if (isdigit(LastChar) || LastChar == '.')
    {
        std::string NumStr;
        do
        {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0);
        return tok_number;
    }

    // Comment until end of line.
    if (LastChar == '#')
    {
        do
        {
            LastChar = getchar();
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
        {
            return gettok();
        }
    }

    // Check for end of file.  Don't eat the EOF.
    if (LastChar == EOF)
        return tok_eof;

    // Otherwise, just return the character as its ascii value.
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}

// CurTok/getNextToken - Provide a simple taken buffer.
// CurTok is the current token the parser is looking at.
// getNextToken reads another token from the lexer and updates CurTok with its results.
static int CurTok;
static int getNextToken()
{
    return CurTok = gettok();
}

#endif //_TOKEN_H_