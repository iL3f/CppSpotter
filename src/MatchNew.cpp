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
    
    if (newExpr->getInitializer())
    {
        // check if one item allocation
        if ( allocType.find("char") != std::string::npos ||
             allocType.find("short") != std::string::npos ||
             allocType.find("int") != std::string::npos ||
             allocType.find("long") != std::string::npos
            )
        {
            DiagnosticsEngine &dEngine = context->getDiagnostics();
            unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Maybe you mean [] brackets?");
            dEngine.Report(newExpr->getInitializer()->getLocStart(), diagID);
        }
    }
    
    
    
}