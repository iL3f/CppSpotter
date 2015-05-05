#include "MatchMemset.h"

using namespace clang;
using namespace clang::ast_matchers;


static StatementMatcher MemsetMatcher = callExpr(callee(functionDecl(hasName("memset")))).bind("memset");

void MemsetPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(MemsetMatcher, this);
}

void MemsetPrinter::run(const MatchFinder::MatchResult &Result)
{
    const CallExpr * memsetCall = Result.Nodes.getStmtAs<CallExpr>("memset");
    ASTContext * context = Result.Context;
    //Utility::PrintInfo("Found memset call");
    
    const Expr * thirdArg = memsetCall->getArg(2);
    
    // trying to get third arg as int
    const IntegerLiteral * intVal;
    if (isa<IntegerLiteral>(thirdArg))
    {
        intVal = cast<IntegerLiteral>(thirdArg);
    }
    else if (isa<ImplicitCastExpr>(thirdArg))
    {
        const ImplicitCastExpr * castEx = cast<ImplicitCastExpr>(thirdArg);
        if (isa<UnaryOperator>(castEx->getSubExpr()))
        {
            // error, third arg can't be negative
            intVal = nullptr;
            clang::DiagnosticsEngine &dEngine = (context)->getDiagnostics();
            unsigned diagID = dEngine.getCustomDiagID(clang::DiagnosticsEngine::Warning, "Argument can't be negative");
            dEngine.Report(thirdArg->getExprLoc(), diagID);
        }
        else
        {
            intVal = cast<IntegerLiteral>(castEx->getSubExpr());
        }
    }
    else
    {
        intVal = nullptr;
    }
    
    if (intVal)
    {
        uint64_t val = intVal->getValue().getZExtValue();
        // check val not 0
        if (val == 0)
        {
            DiagnosticsEngine &dEngine = context->getDiagnostics();
            unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Argument shouldn't be 0");
            dEngine.Report(thirdArg->getExprLoc(), diagID);
        }
        else
        {
            // check val % sizeof(arg1) == 0
            const Expr * firstArg = memsetCall->getArg(0);
            
            if (const ImplicitCastExpr * castEx = dyn_cast<ImplicitCastExpr>(firstArg))
            {
                if (const ImplicitCastExpr * impCast = dyn_cast<ImplicitCastExpr>(castEx->getSubExpr()))
                {
                    //impCast->dump();

#define NUM_TYPES 3
                    const char * names[NUM_TYPES] =  {"char", "short", "int"};
                    size_t sizes[NUM_TYPES] = {sizeof(char), sizeof(short), sizeof(int)};
                    
                    int i;
                    for (i=0; i<NUM_TYPES; i++)
                    {
                        std::string castType = impCast->getType().getAsString();
                        if (castType.find(names[i]) != std::string::npos)
                        {
                            // found type
                            //llvm::outs() << "Found Type: "<<names[i] << "\n";
                            break;
                        }
                    }
                    if (i==NUM_TYPES)
                    {
                        DiagnosticsEngine &dEngine = context->getDiagnostics();
                        unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "You shouldn't use constant here");
                        dEngine.Report(thirdArg->getExprLoc(), diagID);
                    }
                    else if ((val % sizes[i]) != 0)
                    {
                        DiagnosticsEngine &dEngine = context->getDiagnostics();
                        unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Incorrect size for such type");
                        dEngine.Report(thirdArg->getExprLoc(), diagID);
                    }
#undef NUM_TYPES
                }
            }
            
        }
    }
    

    
}