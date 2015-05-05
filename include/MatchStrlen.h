#ifndef CppSpotter_MatchStrlen_h
#define CppSpotter_MatchStrlen_h

#include "BasePrinter.h"

/*
 
 Check strlen(str+1)
 
 Example:
 strlen(str+1) => strlen(str)+1
 */

class StrlenOnePrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};

#endif
