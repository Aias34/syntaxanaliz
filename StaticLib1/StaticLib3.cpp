#include "pch.h"
#include "Syntax.h"
#include "Lexer_lib.h"
#include "fsm_lib.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool Syntax::Tree(vector <int>& tree, string name) {
    for (int i = 1; i < tree.size(); i++) {
        if (tree.size() == 1) {
            break;
        }
        if (i == tree.size() - 1) {
            if (tree[i] == 0) {
                d += "L ";
            }
            else if (tree[i] == 1) {
                d += "|-";
            }
        }
        else {
            if (tree[i] == 0) {
                d += " ";
            }
            else if (tree[i] == 1) {
                d += "|";
            }
        }
    }
    d += sub;
    d += name;
    cout << d << endl;
    d = "";
    sub = "";
    return 0;
}
Syntax::Syntax(istream& stream) : lexer{ stream }
{
    cur = lexer.getNextLexem();
    bool res = StmtList(tree);

    if (res && cur == LEX_EOF) {
        cout << "True" << endl;
    }
    else {
        cout << "False" << endl;
    }
}

Syntax::~Syntax()
{
    // dtor
}

bool Syntax::E(vector <int>& tree) {
    Tree(tree, "E");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (!E7(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::E7(vector <int>& tree) {
    Tree(tree, "E7");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    tree.push_back(1);
    if (!E6(tree)) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (!E7L(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::E7L(vector <int>& tree) {
    Tree(tree, "E7L");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }

    if (cur.first == "opor") {
        cur = lexer.getNextLexem();
        sub += " opor ";
        tree.push_back(1);
        if (!E6(tree)) {
            tree.pop_back();
            return false;
        }
        tree.push_back(0);
        if (!E7L(tree)) {
            tree.pop_back();
            return false;
        }

    }
    tree.pop_back();
    return true;
}

bool Syntax::E6(vector <int>& tree) {
    Tree(tree, "E6");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    tree.push_back(1);
    if (!E5(tree)) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (!E6L(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::E6L(vector <int>& tree) {
    Tree(tree, "E6L");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "opand") {
        cur = lexer.getNextLexem();
        sub += " opand ";
        tree.push_back(1);
        if (!E5(tree)) {
            tree.pop_back();
            return false;
        }
        tree.push_back(0);
        if (!E6L(tree)) {
            tree.pop_back();
            return false;
        }

    }

    tree.pop_back();
    return true;
}

bool Syntax::E5(vector <int>& tree) {
    Tree(tree, "E5");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    tree.push_back(1);
    if (!E4(tree)) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (!E5L(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::E5L(vector <int>& tree) {
    Tree(tree, "E5L");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }

    if (cur.first == "opeq") {
        cur = lexer.getNextLexem();
        sub += " opeq ";
        tree.push_back(0);
        if (!E4(tree)) {
            tree.pop_back();
            return false;
        }
    }
    else if (cur.first == "opne") {
        cur = lexer.getNextLexem();
        sub += " opne ";
        tree.push_back(0);
        if (!E4(tree)) {
            tree.pop_back();
            return false;
        }
    }
    else if (cur.first == "opgt") {
        cur = lexer.getNextLexem();
        sub += " opgt ";
        tree.push_back(0);
        if (!E4(tree)) {
            tree.pop_back();
            return false;
        }
    }
    else if (cur.first == "oplt") {
        cur = lexer.getNextLexem();
        sub += " oplt ";
        tree.push_back(0);
        if (!E4(tree)) {
            tree.pop_back();
            return false;
        }
    }
    else if (cur.first == "ople") {
        cur = lexer.getNextLexem();
        sub += " ople ";
        tree.push_back(0);
        if (!E4(tree)) {
            tree.pop_back();
            return false;
        }
    }
    tree.pop_back();
    return true;
}

bool Syntax::E4(vector <int>& tree) {
    Tree(tree, "E4");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    tree.push_back(1);
    if (!E3(tree)) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (!E4L(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::E4L(vector <int>& tree) {
    Tree(tree, "E4L");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "opplus") {
        cur = lexer.getNextLexem();
        sub += " opplus ";
        tree.push_back(1);
        if (!E3(tree)) {
            tree.pop_back();
            return false;
        }
        tree.push_back(0);
        if (!E4L(tree)) {
            tree.pop_back();
            return false;
        }
    }
    else if (cur.first == "opminus") {
        cur = lexer.getNextLexem();
        sub += " opminus ";
        tree.push_back(1);
        if (!E3(tree)) {
            tree.pop_back();
            return false;
        }
        tree.push_back(0);
        if (!E4L(tree)) {
            tree.pop_back();
            return false;
        }
    }
    tree.pop_back();
    return true;
}

bool Syntax::E3(vector <int>& tree) {
    Tree(tree, "E3");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    tree.push_back(1);
    if (!E2(tree)) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (!E3L(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::E3L(vector <int>& tree) {
    Tree(tree, "E3L");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "opmul") {
        cur = lexer.getNextLexem();
        sub += " opmul ";
        tree.push_back(1);
        if (!E2(tree)) {
            tree.pop_back();
            return false;
        }
        tree.push_back(0);
        if (!E3L(tree)) {
            tree.pop_back();
            return false;
        }
    }
    tree.pop_back();
    return true;
}

bool Syntax::E2(vector <int>& tree) {
    Tree(tree, "E2");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (cur.first == "opnot") {
        cur = lexer.getNextLexem();
        sub += " opnot ";
        if (!E1(tree)) {
            tree.pop_back();
            return false;
        }
    }
    else if (!E1(tree)) {
        tree.pop_back();
        return false;
    }

    tree.pop_back();
    return true;
}

bool Syntax::E1(vector <int>& tree) {
    Tree(tree, "E1");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "opinc") {
        cur = lexer.getNextLexem();
        sub += " opinc ";
        if (cur.first == "id") {
            sub += " ";
            sub += cur.second;
            sub += " ";
            cur = lexer.getNextLexem();
            tree.pop_back();
            return true;
        }
        else {
            tree.pop_back();
            return false;
        }
    }
    else if (cur.first == "lpar") {
        cur = lexer.getNextLexem();
        sub += " lpar ";
        tree.push_back(0);
        if (!E(tree)) {
            tree.pop_back();
            return false;
        }
        if (cur.first == "rpar") {
            cur = lexer.getNextLexem();
            sub += "rpar ";
            tree.pop_back();
            return true;
        }
        else {
            tree.pop_back();
            return false;
        }
    }
    else if (cur.first == "num") {
        sub += " ";
        sub += cur.second;
        sub += " ";
        cur = lexer.getNextLexem();


        tree.pop_back();
        return true;
    }
    else if (cur.first == "id") {
        sub += " ";
        sub += cur.second;
        sub += " ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!E1L(tree)) {
            tree.pop_back();
            return false;
        }
    }
    tree.pop_back();
    return true;
}

bool Syntax::E1L(vector <int>& tree) {
    Tree(tree, "E1L");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "opinc") {
        sub += " opinc ";
        cur = lexer.getNextLexem();
        tree.pop_back();
        return true;
    }
    else if (cur.first == "lpar") {
        sub += " lpar ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!ArgList(tree)) {
            tree.pop_back();
            return false;
        }
        if (cur.first == "rpar") {
            sub += " rpar ";
            cur = lexer.getNextLexem();
        }
        tree.pop_back();
        return true;
    }
    else {
        tree.pop_back();
        return true;
    }
}

bool Syntax::ArgList(vector <int>& tree) {
    Tree(tree, "ArgList");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    tree.push_back(1);
    if (!E(tree)) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (!ArgListL(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::ArgListL(vector <int>& tree) {
    Tree(tree, "ArgListL");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "comma") {
        sub += " comma ";
        cur = lexer.getNextLexem();
        tree.push_back(1);
        if (!E(tree)) {
            tree.pop_back();
            return false;
        }
        tree.push_back(0);
        if (!ArgListL(tree)) {
            tree.pop_back();
            return false;
        }
    }
    tree.pop_back();
    return true;
}

bool Syntax::Type(vector <int>& tree) {
    string a;
    a = "Type ";
	if (cur.first == "kwint" || cur.first == "kwchar") { 
		a += cur.first;
	}
    Tree(tree, a);

    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "kwint") {
        cur = lexer.getNextLexem();
        tree.pop_back();
        return true;
    }
    else if (cur.first == "kwchar") {
        cur = lexer.getNextLexem();
        tree.pop_back();
        return true;
    }
    tree.pop_back();
    return false;
}

bool Syntax::DeclareStmt(vector <int>& tree) {
    Tree(tree, "DeclareStmt");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    tree.push_back(1);
    if (!Type(tree)) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "id") {
        sub += " ";
        sub += cur.second;
        sub += " ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!DeclareStmtList(tree)) {
            tree.pop_back();
            return false;
        }
    }
    tree.pop_back();
    return true;
}

bool Syntax::DeclareStmtList(vector <int>& tree) {
    Tree(tree, "DeclareStmtL");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "lpar") {
        cur = lexer.getNextLexem();
        tree.push_back(1);
        if (!ParamList(tree)) {
            tree.pop_back();
            return false;
        }
        if (cur.first == "rpar") {
            sub += " rpar ";
            cur = lexer.getNextLexem();
            if (cur.first == "lbrace") {
                sub += " lbrace ";
                cur = lexer.getNextLexem();
                tree.push_back(0);
                if (!StmtList(tree)) {
                    tree.pop_back();
                    return false;
                }
                if (cur.first == "rbrace") {
                    sub += " rbrace ";
                    cur = lexer.getNextLexem();
                    tree.pop_back();
                    return true;
                }
            }
        }
    }
    if (cur.first == "opassign") {
        sub += " opassign ";
        cur = lexer.getNextLexem();
        if (cur.first == "num") {
            sub += " ";
            sub += cur.second;
            sub += " ";
            cur = lexer.getNextLexem(); 
            tree.push_back(0);
            if (!DeclVarList(tree)) {
                tree.pop_back();
                return false;
            }
            if (cur.first == "semicolon") {
                sub += " semicolon ";
                cur = lexer.getNextLexem();
                tree.pop_back();
                return true;
            }
            else {
                tree.pop_back();
                return false;
            }
        }
        else {
            tree.pop_back();
            return false;
        }
    }
    tree.push_back(0);
    if (DeclVarList(tree)) {
        if (cur.first == "semicolon") {
            sub += " semicolon ";
            cur = lexer.getNextLexem();
            tree.pop_back();
            return true;
        }
        else {
            tree.pop_back();
            return false;
        }
    }
    tree.pop_back();
    return false;
}

bool Syntax::DeclVarList(vector <int>& tree) {
    Tree(tree, "DeclVarList");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "comma") {
        sub += " comma ";
        cur = lexer.getNextLexem();
        if (cur.first == "id") {
            sub += " ";
            sub += cur.second;
            sub += " ";
            cur = lexer.getNextLexem();
            tree.push_back(1);
            if (!InitVar(tree)) {
                tree.pop_back();
                return false;
            }
            tree.push_back(0);
            if (!DeclVarList(tree)) {
                tree.pop_back();
                return false;
            }
        }
    }
    tree.pop_back();
    return true;
}

bool Syntax::InitVar(vector <int>& tree) {
    Tree(tree, "InitVar");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "opassign") {
        sub += " opassign ";
        cur = lexer.getNextLexem();
        if (cur.first == "num") {
            sub += " ";
            sub += cur.second;
            sub += " ";
            cur = lexer.getNextLexem();
            tree.pop_back();
            return true;
        }
        else if (cur.first == "char") {
            sub += " ";
            sub += cur.second;
            sub += " ";
            cur = lexer.getNextLexem();
            tree.pop_back();
            return true;
        }
    }
    tree.pop_back();
    return true;
}

bool Syntax::ParamList(vector <int>& tree) {
    Tree(tree, "ParamList");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    tree.push_back(1);
    if (!Type(tree)) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "id") {
        sub += " ";
        sub += cur.second;
        sub += " ";
        cur = lexer.getNextLexem(); 
        tree.push_back(0);
        if (!ParamListList(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    tree.pop_back();
    return true;
}


bool Syntax::ParamListList(vector <int>& tree) {
    Tree(tree, "ParamListList");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "comma") {
        cur = lexer.getNextLexem();
        sub += " comma ";
        tree.push_back(1);
        if (!Type(tree)) {
            tree.pop_back();
            return false;
        }
        if (cur.first == "id") {
            sub += " ";
            sub += cur.second;
            sub += " ";
            cur = lexer.getNextLexem();
            tree.push_back(0);
            if (!ParamListList(tree)) {
                tree.pop_back();
                return false;
            }
            tree.pop_back();
            return true;
        }
    }
    tree.pop_back();
    return true;
}

bool Syntax::StmtList(vector <int>& tree) {
    Tree(tree, "StmtList");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "rbrace") {
        tree.pop_back();
        return true;
    }
    tree.push_back(1);
    if (!Stmt(tree)) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (!StmtList(tree)) {
        tree.pop_back();
        return true;
    }
    tree.pop_back();
    return true;
}

bool Syntax::Stmt(vector <int>& tree) {
    Tree(tree, "Stmt");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "kwchar" || cur.first == "kwint") {
        tree.push_back(0);
        if (!DeclareStmt(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    else if (cur.first == "id") {
        tree.push_back(0);
        if (!AssignOrCallOp(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    else if (cur.first == "kwfor") {
        tree.push_back(0);
        if (!ForOp(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    else if (cur.first == "kwif") {
        tree.push_back(0);
        if (!IfOp(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    else if (cur.first == "kwwhile") {
        tree.push_back(0);
        if (!WhileOp(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    else if (cur.first == "kwswitch") {
        tree.push_back(0);
        if (!SwitchOp(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    else if (cur.first == "kwin") {
        tree.push_back(0);
        if (!IOp(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    else if (cur.first == "kwout") {
        tree.push_back(0);
        if (!OOp(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    else if (cur.first == "semicolon") {
        sub += " semicolon ";
        cur = lexer.getNextLexem();
        tree.pop_back();
        return true;
    }
    else if (cur.first == "lbrace") {
        sub += " lbrace ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!StmtList(tree)) {
            tree.pop_back();
            return false;
        }
        if (cur.first == "rbrace") {
            sub += " rbrace ";
            cur = lexer.getNextLexem();
            tree.pop_back();
            return true;
        }
    }
    else if (cur.first == "kwreturn") {
        sub += " kwreturn ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!E(tree)) {
            tree.pop_back();
            return false;
        }
        if (cur.first == "semicolon") {
            sub += " semicolon ";
            cur = lexer.getNextLexem();
        }
        tree.pop_back();
        return true;
    }
    tree.pop_back();
    return false;
}

bool Syntax::AssignOrCallOp(vector <int>& tree) {
    Tree(tree, "AssignOrCallOp");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (AssignOrCall(tree)) {
        if (cur.first == "semicolon") {
            sub += " semicolon ";
            cur = lexer.getNextLexem();
            tree.pop_back();
            return true;
        }
    }
    tree.pop_back();
    return false;
}

bool Syntax::AssignOrCall(vector <int>& tree) {
    Tree(tree, "AssignOrCall");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "id") {
        sub += " ";
        sub += cur.second;
        sub += " ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!AssignOrCallList(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    tree.pop_back();
    return false;
}

bool Syntax::AssignOrCallList(vector <int>& tree) {
    Tree(tree, "AssignOrCallList");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "opassign") {
        sub += " opassign ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!E(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    else if (cur.first == "lpar") {
        sub += " lpar ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!ArgList(tree)) {
            tree.pop_back();
            return false;
        }
        if (cur.first == "rpar") {
            sub += " rpar ";
            cur = lexer.getNextLexem();
            tree.pop_back();
            return true;
        }
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return false;
}
bool Syntax::WhileOp(vector <int>& tree) {
    Tree(tree, "WhileOp");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "kwwhile") {
        sub += " kwwhile ";
        cur = lexer.getNextLexem();
        if (cur.first == "lpar") {
            sub += " lpar ";
            cur = lexer.getNextLexem();
            tree.push_back(1);
            if (!E(tree)) {
                tree.pop_back();
                return false;
            }
            if (cur.first == "rpar") {
                sub += " rpar ";
                cur = lexer.getNextLexem();
                tree.push_back(0);
                if (!Stmt(tree)) {
                    tree.pop_back();
                    return false;
                }
                tree.pop_back();
                return true;
            }
        }
    }
    tree.pop_back();
    return false;
}

bool Syntax::ForOp(vector <int>& tree) {
    Tree(tree, "ForOp");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "kwfor") {
        sub += " kwfor ";
        cur = lexer.getNextLexem();
        if (cur.first == "lpar") {
            sub += " lpar ";
            cur = lexer.getNextLexem();
            tree.push_back(1);
            if (!ForInit(tree)) {
                tree.pop_back();
                return false;
            }
            if (cur.first == "semicolon") {
                sub += " semicolon ";
                cur = lexer.getNextLexem();
                tree.push_back(1);
                if (!ForExp(tree)) {
                    tree.pop_back();
                    return false;
                }
                if (cur.first == "semicolon") {
                    sub += " semicolon ";
                    cur = lexer.getNextLexem();
                    tree.push_back(1);
                    if (!ForLoop(tree)) {
                        tree.pop_back();
                        return false;
                    }
                    if (cur.first == "rpar") {
                        sub += " rpar ";
                        cur = lexer.getNextLexem();
                        tree.push_back(0);
                        if (!Stmt(tree)) {
                            tree.pop_back();
                            return false;
                        }
                        tree.pop_back();
                        return true;
                    }
                }
            }
        }
    }
    tree.pop_back();
    return false;
}

bool Syntax::ForInit(vector <int>& tree) {
    Tree(tree, "ForInit");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    tree.push_back(0);
    if (!AssignOrCall(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::ForExp(vector <int>& tree) {
    Tree(tree, "ForExp");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    tree.push_back(0);
    if (!E(tree)) {
        tree.pop_back();
        return true;
    }
    tree.pop_back();
    return true;
}

bool Syntax::ForLoop(vector <int>& tree) {
    Tree(tree, "FoorLoop");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "opinc") {
        sub += " opinc ";
        cur = lexer.getNextLexem();
        if (cur.first == "id") {
            sub += " ";
            sub += cur.second;
            sub += " ";
            cur = lexer.getNextLexem();
            tree.pop_back();
            return true;
        }
    }
    tree.push_back(0);
    if (!AssignOrCall(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::IfOp(vector <int>& tree) {
    Tree(tree, "IfOp");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "kwif") {
        sub += " kwif ";
        cur = lexer.getNextLexem();
        if (cur.first == "lpar") {
            sub += " lpar ";
            cur = lexer.getNextLexem();
            tree.push_back(1);
            if (!E(tree)) {
                tree.pop_back();
                return false;
            }
            if (cur.first == "rpar") {
                sub += " rpar ";
                cur = lexer.getNextLexem();
                tree.push_back(1);
                if (!Stmt(tree)) {
                    tree.pop_back();
                    return false;
                }
                tree.push_back(0);
                if (!ElsePart(tree)) {
                    tree.pop_back();
                    return false;
                }
                tree.pop_back();
                return true;
            }
        }

    }
    tree.pop_back();
    return false;
}

bool Syntax::ElsePart(vector <int>& tree) {
    Tree(tree, "ElsePart");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    if (cur.first == "kwelse") {
        sub += " kwelse ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!Stmt(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    tree.pop_back();
    return true;
}

bool Syntax::SwitchOp(vector <int>& tree) {
    Tree(tree, "SwitchOp");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "kwswitch") {
        sub += " kwswitch ";
        cur = lexer.getNextLexem();
        if (cur.first == "lpar") {
            sub += " lpar ";
            cur = lexer.getNextLexem();
            tree.push_back(1);
            if (!E(tree)) {
                tree.pop_back();
                return false;
            }
            if (cur.first == "rpar") {
                sub += " rpar ";
                cur = lexer.getNextLexem();
                if (cur.first == "lbrace") {
                    sub += " lbrace ";
                    cur = lexer.getNextLexem();
                    tree.push_back(0);
                    if (!Cases(tree)) {
                        tree.pop_back();
                        return false;
                    }
                    if (cur.first == "rbrace") {
                        sub += " rbrace ";
                        cur = lexer.getNextLexem();
                        tree.pop_back();
                        return true;
                    }
                }
            }
        }
    }
    tree.pop_back();
    return false;
}

bool Syntax::Cases(vector <int>& tree) {
    Tree(tree, "Cases");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    tree.push_back(1);
    if (!Acase(tree)) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (!CasesList(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::CasesList(vector <int>& tree) {
    Tree(tree, "CasesList");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return true;
    }
    tree.push_back(1);
    if (!Acase(tree)) {
        tree.pop_back();
        return false;
    }
    tree.push_back(0);
    if (!CasesList(tree)) {
        tree.pop_back();
        return false;
    }
    tree.pop_back();
    return true;
}

bool Syntax::Acase(vector <int>& tree) {
    Tree(tree, "Acase");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "kwcase") {
        sub += " kwcase ";
        cur = lexer.getNextLexem();
        if (cur.first == "num") {
            sub += " ";
            sub += cur.second;
            sub += " ";
            cur = lexer.getNextLexem();
            if (cur.first == "colon") {
                sub += " colon ";
                cur = lexer.getNextLexem();
                tree.push_back(0);
                if (!Stmt(tree)) {
                    tree.pop_back();
                    return false;
                }
                tree.pop_back();
                return true;
            }
        }
    }
    else if (cur.first == "kwdefault") {
        sub += " kwdefault ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!Stmt(tree)) {
            tree.pop_back();
            return false;
        }
        tree.pop_back();
        return true;
    }
    tree.pop_back();
    return false;
}

bool Syntax::IOp(vector <int>& tree) {
    Tree(tree, "IOp");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "kwin") {
        sub += " kwin ";
        cur = lexer.getNextLexem();
        if (cur.first == "id") {
            sub += " ";
            sub += cur.second;
            sub += " ";
            cur = lexer.getNextLexem();
            if (cur.first == "semicolon") {
                sub += " semicolon ";
                cur = lexer.getNextLexem();
                tree.pop_back();
                return true;
            }
        }
    }
    tree.pop_back();
    return false;
}

bool Syntax::OOp(vector <int>& tree) {
    Tree(tree, "OOp");
    if (cur == LEX_EOF) {
        tree.pop_back();
        return false;
    }
    if (cur.first == "kwout") {
        sub += " kwout ";
        cur = lexer.getNextLexem();
        tree.push_back(0);
        if (!E(tree)) {
            tree.pop_back();
            return false;
        }
        if (cur.first == "semicolon") {
            sub += " semicolon ";
            cur = lexer.getNextLexem();
            tree.pop_back();
            return true;
        }
        tree.pop_back();
        return true;
    }
    tree.pop_back();
    return false;
}

//bool Syntax::OOpL(vector <int>& tree) {
//    Tree(tree, "OOpL");
//    if (cur == LEX_EOF) {
//        tree.pop_back();
//        return true;
//    }
//    tree.push_back(0);
//    if (!E(tree)) {
//        tree.pop_back();
//        return true;
//    }
//    if (cur.first == "kwstr") {
//        sub += " kwstr ";
//        cur = lexer.getNextLexem();
//        tree.pop_back();
//        return true;
//    }