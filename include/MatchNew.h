#ifndef CppSpotter_MatchNew_h
#define CppSpotter_MatchNew_h

#include "BasePrinter.h"

/*
 
 Check malloc
 
 Example:
 new char[strlen(str)] => should be: new char[strlen(str)+1]
 new int/char/short(n) => strange one item allocation
 
 */
class NewPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};

#endif
