#ifndef CppSpotter_MatchAllocStrlen_h
#define CppSpotter_MatchAllocStrlen_h

#include "BasePrinter.h"

/*
 
 Check malloc and new strlen memory allocation
 
 Example:
 malloc(strlen(str)) => should be malloc(strlen(str)+1)
 new char[strlen(str)] => should be new char[strlen(str)+1]
 
 */
class AllocStrlenPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};

#endif
