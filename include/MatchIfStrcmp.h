#ifndef CppSpotter_MatchIfStrcmp_h
#define CppSpotter_MatchIfStrcmp_h

#include "BasePrinter.h"

/*
 
 Check if (strcmp(...)), better rewrite to if (strcmp(..) != 0 )
 Also works with strncmp
 */

class IfStrCmpPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};

#endif
