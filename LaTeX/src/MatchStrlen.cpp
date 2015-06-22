#include "MatchStrlen.h"

using namespace clang;
using namespace clang::ast_matchers;


static StatementMatcher strlenMatcher =
        callExpr(callee(functionDecl(
                        hasName("strlen"))),
                hasArgument(0,
                            binaryOperator(
                            hasOperatorName("+"),
                                hasRHS(
                                integerLiteral(
                                equals(1)).bind("+1")
                                )
                            )
                )).bind("strlen");

void StrlenOnePrinter::addToFinder(MatchFinder *finder)
{
    finder->addMatcher(strlenMatcher, this);
}

void StrlenOnePrinter::run(const MatchFinder::MatchResult &Result)
{
    const IntegerLiteral * pluseOne =
        Result.Nodes.getStmtAs<IntegerLiteral>("+1");
    ASTContext * context = Result.Context;
    
    DiagnosticsEngine &dEngine = context->getDiagnostics();
    unsigned diagID = dEngine.getCustomDiagID(
                    DiagnosticsEngine::Warning,
                "Maybe you mean strlen(..)+1 ?"
                                              );
    dEngine.Report(pluseOne->getLocEnd(), diagID);
    
    
}