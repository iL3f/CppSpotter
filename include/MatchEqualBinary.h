#ifndef CppSpotter_MatchEqualBinary_h
#define CppSpotter_MatchEqualBinary_h

#include "BasePrinter.h"

/*
 
 Check equal expressions in binary operator

 Example:
 a==0 && a==0
 
 */
class EqualBinaryPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};


#endif
