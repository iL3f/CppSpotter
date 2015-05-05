#include "MatchMalloc.h"

using namespace clang;
using namespace clang::ast_matchers;


static StatementMatcher MallocMatcher = callExpr(callee(functionDecl(hasName("malloc"))),
                                                 hasArgument(0,
                                                             callExpr(callee(functionDecl(hasName("strlen")))).bind("strlen")
                                                             )
                                                 ).bind("malloc");

void MallocPrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(MallocMatcher, this);
}

void MallocPrinter::run(const MatchFinder::MatchResult &Result)
{
    const CallExpr * strlenCall = Result.Nodes.getStmtAs<CallExpr>("strlen");
    ASTContext * context = Result.Context;
    
    DiagnosticsEngine &dEngine = context->getDiagnostics();
    unsigned diagID = dEngine.getCustomDiagID(DiagnosticsEngine::Warning, "Maybe you should add +1 after strlen?");
    dEngine.Report(strlenCall->getLocEnd(), diagID);
}