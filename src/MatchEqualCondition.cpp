#include "MatchEqualCondition.h"

using namespace clang;
using namespace clang::ast_matchers;

static StatementMatcher EqualCondMatcher = ifStmt(hasElse(ifStmt().bind("elseIf"))).bind("if");

void EqualConditionPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(EqualCondMatcher, this);
}

void EqualConditionPrinter::run(const MatchFinder::MatchResult &Result)
{
    const IfStmt * ifSt = Result.Nodes.getNodeAs<IfStmt>("if");
    ASTContext * context = Result.Context;

    // compare first "if" with next else ifs
    const Stmt * elseStmt = ifSt->getElse();
    while (elseStmt)
    {
        const IfStmt  * elseIf = llvm::dyn_cast<IfStmt>(elseStmt);
        if (!elseIf)
        {
            // if has no more else if
            break;
        }
        
        if (Utility::areSameStmt(context, ifSt->getCond(), elseIf->getCond()))
        {
            clang::DiagnosticsEngine &dEngine = context->getDiagnostics();
            unsigned diagID = dEngine.getCustomDiagID(clang::DiagnosticsEngine::Warning, "Equal `if` and `else if` condition");
            dEngine.Report(ifSt->getIfLoc(), diagID);
        }
        // go to next else
        elseStmt = elseIf->getElse();
    }
    
}
