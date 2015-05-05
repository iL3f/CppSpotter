#ifndef CppSpotter_Utility_h
#define CppSpotter_Utility_h

#include "clang/AST/PrettyPrinter.h" 
#include "clang/Parse/Parser.h"
#include <clang/AST/AST.h>
#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <llvm/Support/raw_ostream.h>
#include <clang/AST/RecursiveASTVisitor.h>



class Utility
{
public:
    // print info message
    static void PrintInfo(const char * info)
    {
        llvm::outs() << info << "\n";
    }
    
    // compare variables
    static bool areSameVariable(const clang::ValueDecl *First, const clang::ValueDecl *Second)
    {
        return First && Second &&
        First->getCanonicalDecl() == Second->getCanonicalDecl();
    }
    
    // compare statments
    static bool areSameStmt(clang::ASTContext *Context, const clang::Stmt *First,
                            const clang::Stmt *Second)
    {
        if (!First || !Second)
            return false;
        llvm::FoldingSetNodeID FirstID, SecondID;
        First->Profile(FirstID, *Context, true);
        Second->Profile(SecondID, *Context, true);
        return FirstID == SecondID;
    }
    
};

#endif
