#include "MatchEqualBinary.h"

using namespace clang;
using namespace clang::ast_matchers;

static StatementMatcher EqualBinaryMatcher = binaryOperator().bind("binOp");

void EqualBinaryPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(EqualBinaryMatcher, this);
}

void EqualBinaryPrinter::run(const MatchFinder::MatchResult &Result)
{
    const BinaryOperator * binOp = Result.Nodes.getStmtAs<BinaryOperator>("binOp");
    ASTContext * context = Result.Context;
    
    if (binOp->isBitwiseOp() || binOp->isLogicalOp() || binOp->isComparisonOp())
    {
        if (Utility::areSameStmt(context, binOp->getLHS(), binOp->getRHS()))
        {
            if (const ImplicitCastExpr * impCast = dyn_cast<ImplicitCastExpr>(binOp->getLHS()))
            {
                std::string tpe = impCast->getType().getAsString();
                if ((tpe == "float" ||
                     tpe == "double" ||
                     tpe == "long double") &&
                    (binOp->getOpcode() == BO_EQ ||
                     binOp->getOpcode() == BO_NE))
                    return; // skip
            }
            clang::DiagnosticsEngine &dEngine = context->getDiagnostics();
            unsigned diagID = dEngine.getCustomDiagID(clang::DiagnosticsEngine::Warning, "Equal Left and Right values in binary expression");
            dEngine.Report(binOp->getExprLoc(), diagID);
        }
    }
    
}