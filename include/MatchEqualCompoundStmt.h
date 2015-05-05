#ifndef CppSpotter_MatchEqualCompoundStmt_h
#define CppSpotter_MatchEqualCompoundStmt_h

#include "BasePrinter.h"

/*
 
 Check equal statements in `if` and `else`
 
 Example:
 if (..){a==0;}
 else {a==0;}
 
 */
class EqualCompoundStmtPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};


#endif
