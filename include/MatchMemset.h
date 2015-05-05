#ifndef CppSpotter_MatchMemset_h
#define CppSpotter_MatchMemset_h

#include "BasePrinter.h"

/*
 
 Check `memset` function comon errors
 
 Example:
 int a[10];
 memset(a, 0, -10) => negative size
 memset(a, sizeof(int)*5, 0) => zero size
 memset(a, 0, 10) => 10 % sizeof(int) != 0
 
 */
class MemsetPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};

#endif
