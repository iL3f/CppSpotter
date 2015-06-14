#ifndef CppSpotter_MatchPointerComparison_h
#define CppSpotter_MatchPointerComparison_h

#include "BasePrinter.h"

/*
 
 Check pointer and 0 comparison
 
 Example:
 if (ptr < 0)
 */

class PtrCmpPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};

#endif
