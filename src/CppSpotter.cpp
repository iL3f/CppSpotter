#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/AST/AST.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <llvm/Support/raw_ostream.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

#include "AllMatchers.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace
{
    class CppSpotterASTAction : public PluginASTAction
    {
        MatchFinder finder;
        std::list<BasePrinter*> printers;
    public:
        virtual clang::ASTConsumer *CreateASTConsumer(CompilerInstance &Compiler,
                                                      llvm::StringRef InFile)
        {
         
            addPrinter(new EqualConditionPrinter);
            addPrinter(new EqualBinaryPrinter);
            addPrinter(new EqualCompoundStmtPrinter);
            addPrinter(new MemsetPrinter);
            addPrinter(new MallocPrinter);
            addPrinter(new NewPrinter);
            addPrinter(new IfStrCmpPrinter);
            addPrinter(new CRTEqualArgsPrinter);
            addPrinter(new SizeofPrinter);
            addPrinter(new StrlenOnePrinter);
            addPrinter(new SizeofMultPrinter);
            
            return finder.newASTConsumer();
        }
        
        bool ParseArgs(const CompilerInstance &CI, const
                       std::vector<std::string>& args) {
            for (auto argument : args)
            {
                llvm::errs() << "CppSpotter arg = " << argument << "\n";
            }
            return true;
        }
    private:
        void addPrinter(BasePrinter * printer)
        {
            printer->addToFinder(&finder);
            printers.push_back(printer);
        }
    };
}
 
static clang::FrontendPluginRegistry::Add<CppSpotterASTAction>
X("CppSpotter", "Cpp Error Spotter");