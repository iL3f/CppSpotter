#ifndef CppSpotter_BasePrinter_h
#define CppSpotter_BasePrinter_h

#include "Utility.h"

class BasePrinter : public clang::ast_matchers::MatchFinder::MatchCallback
{
public:
    // add printer to match finder
    virtual void addToFinder(clang::ast_matchers::MatchFinder * finder) = 0;
    
    /*void onStartOfTranslationUnit()
    {
        llvm::errs() << "Start trans unit\n";
    }

    void onEndOfTranslationUnit()
    {
        llvm::errs() << "End trans unit\n";
    }*/
};

#endif
