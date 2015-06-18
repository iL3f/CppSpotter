#include "MatchSizeof.h"

using namespace clang;
using namespace clang::ast_matchers;


static StatementMatcher sizeofMatcher = unaryExprOrTypeTraitExpr(ofKind(UETT_SizeOf)).bind("sizeof");

void SizeofPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(sizeofMatcher, this);
}

void SizeofPrinter::run(const MatchFinder::MatchResult &Result)
{
    const UnaryExprOrTypeTraitExpr * szOf = Result.Nodes.getStmtAs<UnaryExprOrTypeTraitExpr>("sizeof");
    ASTContext * context = Result.Context;
    
    if (!szOf->isArgumentType())
    {
        const Expr * argEx = szOf->getArgumentExpr();
        if ( !isa<DeclRefExpr>(argEx) && isa<ParenExpr>(argEx))
        {
            const ParenExpr * pEx = dyn_cast<ParenExpr>(argEx);
            if (const UnaryOperator * unOp = dyn_cast<UnaryOperator>(pEx->getSubExpr()))
            {
                if (unOp->getOpcode() == UO_AddrOf || unOp->getOpcode() == UO_Deref)
                {
                    //sizeof(*ptr) or sizeof(&var)
                    return;
                }
            }
            else if (isa<MemberExpr>(pEx->getSubExpr()))
                return;
            else if (isa<ParenExpr>(pEx->getSubExpr()))
                pEx = dyn_cast<ParenExpr>(pEx->getSubExpr());
            
            if (!isa<DeclRefExpr>(pEx->getSubExpr()) && !isa<ArraySubscriptExpr>(pEx->getSubExpr()))
            {
                DiagnosticsEngine &dEngine = context->getDiagnostics();
                unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Maybe here mistake in sizeof?");
                dEngine.Report(szOf->getLocStart(), diagID);
                
            }
        }
    }
    
}