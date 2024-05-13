#ifndef SYNTAX_H
#define SYNTAX_H

#include <iostream>
#include <vector>
#include <string>
#include "Lexer_lib.h"
#include "fsm_lib.h"

using namespace std;

class Syntax
{
public:

    Syntax(std::istream&);
    virtual ~Syntax();
    bool Type(vector <int>& tree);
    bool DeclareStmt(vector <int>& tree);
    bool DeclareStmtList(vector <int>& tree);
    bool DeclVarList(vector <int>& tree);
    bool InitVar(vector <int>& tree);
    bool ParamList(vector <int>& tree);
    bool ParamListList(vector <int>& tree);
    bool StmtList(vector <int>& tree);
    bool Stmt(vector <int>& tree);
    bool AssignOrCallOp(vector <int>& tree);
    bool AssignOrCall(vector <int>& tree);
    bool AssignOrCallList(vector <int>& tree);
    bool ArgList(vector <int>& tree);
    bool ArgListL(vector <int>& tree);
    bool ForInit(vector <int>& tree);
    bool ForExp(vector <int>& tree);
    bool ForLoop(vector <int>& tree);
    bool ElsePart(vector <int>& tree);
    bool Cases(vector <int>& tree);
    bool Acase(vector <int>& tree);
    bool CasesList(vector <int>& tree);
    bool ForOp(vector <int>& tree);
    bool IfOp(vector <int>& tree);
    bool SwitchOp(vector <int>& tree);
    bool IOp(vector <int>& tree);
    bool WhileOp(vector <int>& tree);
    bool OOp(vector <int>& tree);
    bool E(vector <int>& tree);
    bool E7(vector <int>& tree);
    bool E7L(vector <int>& tree);
    bool E6(vector <int>& tree);
    bool E6L(vector <int>& tree);
    bool E5(vector <int>& tree);
    bool E5L(vector <int>& tree);
    bool E4(vector <int>& tree);
    bool E4L(vector <int>& tree);
    bool E3(vector <int>& tree);
    bool E3L(vector <int>& tree);
    bool E2(vector <int>& tree);
    bool E1(vector <int>& tree);
    bool E1L(vector <int>& tree);
    bool Tree(vector <int>& tree, string name);

protected:

private:
    Lexer lexer;
    Lexem cur;
    vector<int> tree = { -1 };
    string d = "";
    string sub = "";
    bool res;
    int len = 2;
    int i = 0;
};

#endif // LEXER_H