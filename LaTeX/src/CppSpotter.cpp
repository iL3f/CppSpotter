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
        MatchFinder* finder = new MatchFinder;
        std::list<BasePrinter*> printers;
        std::list<std::string> flags;
    public:
        CppSpotterASTAction()
        {
            flags.push_back("-eqCond");
            flags.push_back("-eqBin");
            flags.push_back("-eqStmt");
            flags.push_back("-memset");
            flags.push_back("-allocStr");
            flags.push_back("-new");
            flags.push_back("-strcmp");
            flags.push_back("-eqArgs");
            flags.push_back("-sizeof");
            flags.push_back("-sizeofMul");
            flags.push_back("-strlen");
            flags.push_back("-ptrCmp");
        }
        
        virtual clang::ASTConsumer *
        CreateASTConsumer(
            CompilerInstance &Compiler,
            llvm::StringRef InFile)
        {
            for (auto argument : flags)
            {
                if (argument == "-eqCond")
                {
                    addPrinter(new EqualConditionPrinter);
                }
                else if (argument == "-eqBin")
                {
                    addPrinter(new EqualBinaryPrinter);
                }
                else if (argument == "-eqStmt")
                {
                    addPrinter(new EqualCompoundStmtPrinter);
                }
                else if (argument == "-memset")
                {
                    addPrinter(new MemsetPrinter);
                }
                else if (argument == "-allocStr")
                {
                    addPrinter(new AllocStrlenPrinter);
                }
                else if (argument == "-new")
                {
                    addPrinter(new NewPrinter);
                }
                else if (argument == "-strcmp")
                {
                    addPrinter(new IfStrCmpPrinter);
                }
                else if (argument == "-eqArgs")
                {
                    addPrinter(new CRTEqualArgsPrinter);
                }
                else if (argument == "-sizeof")
                {
                    addPrinter(new SizeofPrinter);
                }
                else if (argument == "-sizeofMul")
                {
                    addPrinter(new SizeofMultPrinter);
                }
                else if (argument == "-strlen")
                {
                    addPrinter(new StrlenOnePrinter);
                }
                else if (argument == "-ptrCmp")
                {
                    addPrinter(new PtrCmpPrinter);
                }
            }
            
            return finder->newASTConsumer();
        }
        
        bool ParseArgs(const CompilerInstance &CI, const
                       std::vector<std::string>& args)
        {
            //llvm::errs() << "WELCOME! Starting analysis...\n";
            for (auto argument : args)
            {
                auto it = std::find(flags.begin(), flags.end(), argument);
                if (it != flags.end())
                {
                    flags.erase(it);
                }
                else
                {
                    DiagnosticsEngine &D = CI.getDiagnostics();
                    unsigned DiagID = D.getCustomDiagID(DiagnosticsEngine::Error, "invalid argument '%0'");
                    D.Report(DiagID) << argument;
                    return false;
                }
            }
            return true;
        }
    private:
        
        void addPrinter(BasePrinter * printer)
        {
            printer->addToFinder(finder);
            printers.push_back(printer);
        }
    };
}
 
static clang::FrontendPluginRegistry::Add<CppSpotterASTAction>
X("CppSpotter", "Cpp Error Spotter");