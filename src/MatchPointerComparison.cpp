#include "MatchPointerComparison.h"

using namespace clang;
using namespace clang::ast_matchers;

static StatementMatcher ptrMatcher = ifStmt( hasCondition( binaryOperator(
                                          hasOperatorName("<"),
                                          hasLHS(ignoringParenImpCasts(declRefExpr(
                                           to(varDecl(hasType(pointsTo(qualType(anything())))).bind("lhs"))))),
                                          hasRHS(ignoringParenImpCasts(integerLiteral(equals(0))))
                                          ))).bind("if");

void PtrCmpPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(ptrMatcher, this);
}

void PtrCmpPrinter::run(const MatchFinder::MatchResult &Result)
{
    const IfStmt * s = Result.Nodes.getStmtAs<IfStmt>("if");
    ASTContext * context = Result.Context;
    
    DiagnosticsEngine &dEngine = context->getDiagnostics();
    unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Strange pointer and zero comparison, maybe you mean *ptr < 0?");
    dEngine.Report(s->getCond()->getExprLoc(), diagID);
}