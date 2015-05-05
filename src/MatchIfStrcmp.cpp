#include "MatchIfStrcmp.h"

using namespace clang;
using namespace clang::ast_matchers;


static StatementMatcher IfStrcmpMatcher = ifStmt(hasCondition(ignoringImpCasts(callExpr(callee(functionDecl(hasName("strcmp"))))))).bind("if");
static StatementMatcher IfStrncmpMatcher = ifStmt(hasCondition(ignoringImpCasts(callExpr(callee(functionDecl(hasName("strncmp"))))))).bind("if");

void IfStrCmpPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(IfStrcmpMatcher, this);
    finder->addMatcher(IfStrncmpMatcher, this);
}

void IfStrCmpPrinter::run(const MatchFinder::MatchResult &Result)
{
    const IfStmt * ifSt = Result.Nodes.getStmtAs<IfStmt>("if");
    ASTContext * context = Result.Context;
    
    DiagnosticsEngine &dEngine = context->getDiagnostics();
    unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Better to rewrite this `if` condition to explicit `!=0`");
    dEngine.Report(ifSt->getLocStart(), diagID);
    
    
}