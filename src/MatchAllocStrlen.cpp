#include "MatchAllocStrlen.h"

using namespace clang;
using namespace clang::ast_matchers;


static StatementMatcher MallocMatcher = callExpr(callee(functionDecl(hasName("malloc"))),
                                                 hasArgument(0,
                                                             callExpr(callee(functionDecl(hasName("strlen")))).bind("strlen")
                                                             )
                                                 );
static StatementMatcher NewMacther = newExpr().bind("new");;

void AllocStrlenPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(MallocMatcher, this);
}

void AllocStrlenPrinter::run(const MatchFinder::MatchResult &Result)
{
    ASTContext * context = Result.Context;
    const CXXNewExpr * newExpr = Result.Nodes.getStmtAs<CXXNewExpr>("new");
    if (newExpr)
    {
        std::string allocType = newExpr->getAllocatedType().getAsString();
        
        if (allocType.find("char")!=std::string::npos && newExpr->getArraySize())
        {
            // check new char[strlen(..)+1]
            if ( const CallExpr * arg = dyn_cast<CallExpr>(newExpr->getArraySize()) )
            {
                // we have function call as argument
                const CastExpr * implicCast = dyn_cast<CastExpr>(arg->getCallee());
                
                if ( const DeclRefExpr * declRef = dyn_cast<DeclRefExpr>(implicCast->getSubExpr()) )
                {
                    std::string funcName = declRef->getNameInfo().getAsString();
                    // check function name
                    if (funcName.compare("strlen") == 0)
                    {
                        DiagnosticsEngine &dEngine = context->getDiagnostics();
                        unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Maybe you should add +1 after strlen?");
                        dEngine.Report(arg->getLocEnd(), diagID);
                    }
                }
                
            }
        }
    }
    else
    {
        const CallExpr * strlenCall = Result.Nodes.getStmtAs<CallExpr>("strlen");
    
        DiagnosticsEngine &dEngine = context->getDiagnostics();
        unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Maybe you should add +1 after strlen?");
        dEngine.Report(strlenCall->getLocEnd(), diagID);
    }
}