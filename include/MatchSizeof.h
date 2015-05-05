#ifndef CppSpotter_MatchSizeof_h
#define CppSpotter_MatchSizeof_h

#include "BasePrinter.h"

/*
 
 Check sizeof(expression) or sizeof(const)
 
 Example:
 sizeof(A++) or sizeof(buf-1) or sizeof(1)
 */

class SizeofPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};


#endif
