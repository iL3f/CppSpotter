#include "MatchSizeofMult.h"

using namespace clang;
using namespace clang::ast_matchers;


static StatementMatcher sizeofMatcher = binaryOperator(hasLHS(unaryExprOrTypeTraitExpr(ofKind(UETT_SizeOf))),
                                                       hasRHS(unaryExprOrTypeTraitExpr(ofKind(UETT_SizeOf))),
                                                       hasOperatorName("*")).bind("bin");

void SizeofMultPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(sizeofMatcher, this);
}

void SizeofMultPrinter::run(const MatchFinder::MatchResult &Result)
{
    const BinaryOperator * binOp = Result.Nodes.getStmtAs<BinaryOperator>("bin");
    ASTContext * context = Result.Context;
    
    DiagnosticsEngine &dEngine = context->getDiagnostics();
    unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Strange sizeof * sizeof  multiplication");
    dEngine.Report(binOp->getOperatorLoc(), diagID);
}