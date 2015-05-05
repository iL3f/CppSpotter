#include "MatchEqualCompoundStmt.h"

using namespace clang;
using namespace clang::ast_matchers;

static StatementMatcher EqualIfElseMatcher = ifStmt(hasElse(stmt().bind("else"))).bind("if");

void EqualCompoundStmtPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(EqualIfElseMatcher, this);
}

void EqualCompoundStmtPrinter::run(const MatchFinder::MatchResult &Result)
{
    const IfStmt * ifSt = Result.Nodes.getNodeAs<IfStmt>("if");
    const Stmt * elseStmt = Result.Nodes.getNodeAs<Stmt>("else");
    ASTContext * context = Result.Context;
    
    if (const IfStmt * elseIf = llvm::dyn_cast<IfStmt>(elseStmt))
    {
        // if we meet `elseIf`, we should take `else` from here
        elseStmt = elseIf->getThen();
    }
    
    if (Utility::areSameStmt(context, ifSt->getThen(), elseStmt))
    {
        clang::DiagnosticsEngine &dEngine = context->getDiagnostics();
        unsigned diagID = dEngine.getCustomDiagID(clang::DiagnosticsEngine::Warning, "Equal `if` and `else` body");
        dEngine.Report(ifSt->getIfLoc(), diagID);
    }

}