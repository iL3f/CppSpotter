#ifndef CppSpotter_MatchMalloc_h
#define CppSpotter_MatchMalloc_h

#include "BasePrinter.h"

/*
 
 Check malloc
 
 Example:
 malloc(strlen(str)) => should be malloc(strlen(str)+1)
 
 */
class MallocPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};

#endif
