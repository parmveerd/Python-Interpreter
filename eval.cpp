// Name: Parmveer Dayal
// June 17, 2022

#include "Scanner.h"
#include "Stack.h"  // GENERIC STACK

#include <iostream>

using namespace std;


int main () {
    Scanner S(std::cin);
    Token t;

    Stack<Token> numstack, opstack;  // 2x Stacks of type Token
    

    t = S.getnext();

    // Tokens created for the numbers and operator that will be popped for operations
    Token numPop1, numPop2, opPop;

    // Expecting a well formed expression so no need to check for errors 
    while (t.tt != eof || opstack.isEmpty() != 1) {
        // If token is integer, push to number stack and get next token
        if (t.tt == integer) {
            numstack.push(t);
            t = S.getnext();
        }

        // If token is left bracket, push to operator stack and get next token
        else if (t.tt == lptok) {
            opstack.push(t);
            t = S.getnext();
        }

        else if (t.tt == rptok) {
            // If top of operator stack is left bracket, then pop it and get next token
            if (opstack.peek().tt == lptok) {
                opstack.pop();
                t = S.getnext();
            }
            // Else pop two numbers and operator and do the operation
            else {
                numPop1 = numstack.pop();
                numPop2 = numstack.pop();
                opPop = opstack.pop();
                if (opPop.tt == pltok) {
                    numPop1.val = numPop1.val + numPop2.val;
                    numstack.push(numPop1);
                }
                if (opPop.tt == mitok) {
                    numPop2.val = numPop2.val - numPop1.val;
                    numstack.push(numPop2);
                }
                if (opPop.tt == asttok) {
                    numPop1.val = numPop1.val * numPop2.val;
                    numstack.push(numPop1);
                }
                if (opPop.tt == slashtok) {
                    numPop2.val = numPop2.val / numPop1.val;
                    numstack.push(numPop2);
                }
            }
        }

        else if (t.tt == pltok || t.tt == mitok || t.tt == eof) {
            // Do operation by popping 2 numbers and operator if top of operator stack is an operator 
            if (!opstack.isEmpty() && (opstack.peek().tt == pltok || opstack.peek().tt == mitok || opstack.peek().tt == asttok || opstack.peek().tt == slashtok)) {
                numPop1 = numstack.pop();
                numPop2 = numstack.pop();
                opPop = opstack.pop();
                if (opPop.tt == pltok) {
                    numPop1.val = numPop1.val + numPop2.val;
                    numstack.push(numPop1);
                }
                if (opPop.tt == mitok) {
                    numPop2.val = numPop2.val - numPop1.val;
                    numstack.push(numPop2);
                }
                if (opPop.tt == asttok) {
                    numPop1.val = numPop1.val * numPop2.val;
                    numstack.push(numPop1);
                }
                if (opPop.tt == slashtok) {
                    numPop2.val = numPop2.val / numPop1.val;
                    numstack.push(numPop2);
                }
            }
            // Else push operator to operator stack and get next token
            else {
                opstack.push(t);
                t = S.getnext();
            }
        }
        
        else if (t.tt == asttok || t.tt == slashtok) {
            // If top of operator stack is * or /, then pop it and do the operation
            if (!opstack.isEmpty() && (opstack.peek().tt == asttok || opstack.peek().tt == slashtok)) {
                numPop1 = numstack.pop();
                numPop2 = numstack.pop();
                opPop = opstack.pop();
                if (opPop.tt == asttok) {
                    numPop1.val = numPop1.val * numPop2.val;
                    numstack.push(numPop1);
                }
                if (opPop.tt == slashtok) {
                    numPop2.val = numPop2.val / numPop1.val;
                    numstack.push(numPop2);
                }
            }
            // Else push to operator stack and get next token
            else {
                opstack.push(t);
                t = S.getnext();
            }
        }
    }

    // Display result on standard output (will be the only value in the number stack)
    std::cout << numstack.peek().val << std::endl;

    return 0;
}
