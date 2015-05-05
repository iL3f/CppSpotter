#ifndef CppSpotter_MatchSizeofMult_h
#define CppSpotter_MatchSizeofMult_h

#include "BasePrinter.h"

/*
 
 Check sizeof()*sizeof()
 
 Example:
 sizeof(str)*sizeof(TCHAR)
 */

class SizeofMultPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};

#endif
