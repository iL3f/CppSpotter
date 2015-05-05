#ifndef CppSpotter_MatchEqualArgs_h
#define CppSpotter_MatchEqualArgs_h

#include "BasePrinter.h"

/*
 
 Check strcmp,strncmp,memmove,memcpy,strstr functions on equal arguments
 
 Example:
 strcmp(str1, str1)
 */

class CRTEqualArgsPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};

#endif
