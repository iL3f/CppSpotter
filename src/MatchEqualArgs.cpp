#include "MatchEqualArgs.h"

using namespace clang;
using namespace clang::ast_matchers;


static StatementMatcher strcmpMatcher = callExpr(callee(functionDecl(hasName("strcmp")))).bind("funcCall");
static StatementMatcher strncmpMatcher = callExpr(callee(functionDecl(hasName("strncmp")))).bind("funcCall");
static StatementMatcher memmoveMatcher = callExpr(callee(functionDecl(hasName("memmove")))).bind("funcCall");
static StatementMatcher memcpyMatcher = callExpr(callee(functionDecl(hasName("memcpy")))).bind("funcCall");
static StatementMatcher strstrMatcher = callExpr(callee(functionDecl(hasName("strstr")))).bind("funcCall");


void CRTEqualArgsPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(strcmpMatcher, this);
    finder->addMatcher(strncmpMatcher, this);
    finder->addMatcher(memmoveMatcher, this);
    finder->addMatcher(memcpyMatcher, this);
    finder->addMatcher(strstrMatcher, this);
}

void CRTEqualArgsPrinter::run(const MatchFinder::MatchResult &Result)
{
    ASTContext * context = Result.Context;
    const CallExpr * funcCall = Result.Nodes.getStmtAs<CallExpr>("funcCall");
    
    const Expr * firstArg = funcCall->getArg(0);
    const Expr * secondArg = funcCall->getArg(1);
    
    if ( Utility::areSameStmt(context, firstArg, secondArg) )
    {
        DiagnosticsEngine &dEngine = context->getDiagnostics();
        unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Arguments are the same");
        dEngine.Report(funcCall->getExprLoc(), diagID);
    }
    
    
}