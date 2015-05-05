#include "MatchNew.h"

using namespace clang;
using namespace clang::ast_matchers;


static StatementMatcher NewMatcher = newExpr().bind("new");

void NewPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(NewMatcher, this);
}

void NewPrinter::run(const MatchFinder::MatchResult &Result)
{
    const CXXNewExpr * newExpr = Result.Nodes.getStmtAs<CXXNewExpr>("new");
    ASTContext * context = Result.Context;
    
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
    else if (newExpr->getInitializer())
    {
        // check if one item allocation
        if ( allocType.find("char") != std::string::npos ||
             allocType.find("short") != std::string::npos ||
             allocType.find("int") != std::string::npos)
        {
            DiagnosticsEngine &dEngine = context->getDiagnostics();
            unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Maybe you mean [] brackets?");
            dEngine.Report(newExpr->getInitializer()->getLocStart(), diagID);
        }
    }
    
    
    
}