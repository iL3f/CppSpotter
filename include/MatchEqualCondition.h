#ifndef __CppSpotter__MatchEqualCondition__
#define __CppSpotter__MatchEqualCondition__

#include "BasePrinter.h"

/*
 
 Check equal `if` and `else if` conditions
 
 Example:
 if(a==0) {}
 else if(a==0){}
 
 */
class EqualConditionPrinter : public BasePrinter
{
public:
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder);
    
    virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);
};

#endif /* defined(__CppSpotter__MatchEqualCondition__) */
