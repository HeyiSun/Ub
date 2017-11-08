#include "A5.hpp"

void recurStack(ItemStack* exprStack ,ITNode* root);
/**
 * eval
 *
 * @param stack: stack holding an expression to evaluate.
 *               Upon completion of evaluating a valid stack,
 *               stack should only contain one element, the result
 *               of evaluating the stack.
 *
 * @throw runtime_error: if stack is holding an invalid expression, throw
 *                       a runtime error.
 */
void eval(ItemStack& exprStack) {
    ItemStack tmp;
    int zeroSign=0;

    while(!exprStack.empty())
    {
        Item a = exprStack.top();
        exprStack.pop();
        if(a.getType()==VAL)
        {
            tmp.push(a);
        }
        else{
            if(tmp.empty())
                throw std::runtime_error("Malformed expression.");//throw error
            int num1= tmp.top().getVal();
            tmp.pop();

            if(tmp.empty())
                throw std::runtime_error("Malformed expression.");//throw error
            int num2= tmp.top().getVal();
            tmp.pop();

            switch(a.getType()) {
                case VAL:
                    break;
                case MUL:
                    tmp.push(num2 * num1);
                    break;
                case ADD:
                    tmp.push(num2 + num1);
                    break;
                case DIV:
                    if(num1==0){
                        zeroSign=1;
                        num1=1;
                    }

                        tmp.push(num2 / num1);

                    break;
                case SUB:
                    tmp.push(num2 - num1);
                    break;
            }
        }
    }


    if(tmp.size()!=1)
    {
        throw std::runtime_error("Malformed expression.");//error
    }
    else if(zeroSign==1)
    {
        throw std::runtime_error("DIV by 0 error.");
    }
    else{
        exprStack.push(tmp.top().getVal());
    }
    // Your code goes here.
}

/**
 * generateStack
 *
 * @param root: root of tree holding expression.
 *
 * @return ItemStack: containing the expression represented
 *                    by the tree in RPN (reverse Polish notation)
 *                    with first value on top
 *                    (if reading RPN from left to right)
 */
ItemStack generateStack(ITNode* root) {
   // Your code goes here.
    ItemStack exprStack;
    ItemStack* exprStack1=&exprStack;
    recurStack(exprStack1,root);
   return exprStack;
}

void recurStack(ItemStack* exprStack ,ITNode* root){
    if(root->_left==nullptr&&root->_right==nullptr)
        exprStack->push(root->_item);
    else {
        exprStack->push(root->_item);
        recurStack(exprStack,root->_right);
        recurStack(exprStack,root->_left);

        //exprStack.push(root->_item);
    }
}

int priority(Item tmp){
    switch (tmp.getType()){
        case MUL:
        case DIV:
            return 2;
        case ADD:
        case SUB:
            return 1;
        default: return 0;
    }
}

ITNode* treeIp(Item a, std::stack<ITNode*>* addrStack){
    ITNode* tmp=new ITNode(a);
    if(a.getType()==VAL)
    {
        addrStack->push(tmp);
    }
    if(a.getType()==ADD||a.getType()==SUB||a.getType()==MUL||a.getType()==DIV)
    {
        ITNode* a=addrStack->top();
        addrStack->pop();
        ITNode* b=addrStack->top();
        addrStack->pop();
        tmp->_left=b;
        tmp->_right=a;
        addrStack->push(tmp);
        return tmp;
    }
    return tmp;
}

int stoi(char ch){
    switch(ch){
        case'0':return 0;
        case'1':return 1;
        case'2':return 2;
        case'3':return 3;
        case'4':return 4;
        case'5':return 5;
        case'6':return 6;
        case'7':return 7;
        case'8':return 8;
        case'9':return 9;
        default: return 0;
    }
}

ITNode* generateExprTree (std::string expr){
    int i=0;int j;
    int negSign=0;
    int pareNum=0;
    int tmpNum;
    Item a(1);
    Item b('+');
    ITNode* root=nullptr;
    ItemStack *exprStack=new ItemStack();
    std::stack<ITNode*>* addrStack=new std::stack<ITNode*>();

    while(expr[i]!='\0')
    {
        switch(expr[i]){
            case '(':
                pareNum++;
                a=Item(2097);
                exprStack->push(a);
                break;

            case ')':
                pareNum--;
                if(pareNum<0)
                    throw std::runtime_error("Malformed expression.");
                while(!exprStack->empty()&&exprStack->top().getVal()!=2097) {
                    Item tmp=exprStack->top();
                    root=treeIp(tmp,addrStack);
                    exprStack->pop();
                }
                if(exprStack->top().getVal()==2097)
                    exprStack->pop();
                break;

            case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '0':
                tmpNum=0;
                while(expr[i]!=' '&&expr[i]!='\0'&&expr[i]!=')'&&expr[i]!='+'&&expr[i]!='-'&&expr[i]!='*'&&expr[i]!='/')
                {
                    tmpNum=tmpNum*10+stoi(expr[i]);
                    i++;
                }
                i--;

                if(negSign==1)
                {
                    negSign=0;
                    tmpNum=-tmpNum;
                }
                a=Item(tmpNum);
                root=treeIp(a,addrStack);

                break;

            case '+':
            case '-':
                if(expr[i]=='-'&&(expr[i+1]=='0'||expr[i+1]=='1'||expr[i+1]=='2'||expr[i+1]=='3'||expr[i+1]=='4'||expr[i+1]=='5'||expr[i+1]=='6'||expr[i+1]=='7'||expr[i+1]=='8'||expr[i+1]=='9'))
                {
                    negSign=1;
                    break;
                }
            case '*':
            case '/':
                b=Item(expr[i]);
                if(exprStack->empty()||priority(b)>priority(exprStack->top())){
                    exprStack->push(b);
                }
                else{
                    while(!exprStack->empty()&&priority(b)<=priority(exprStack->top())) {
                        Item tmp=exprStack->top();
                        root=treeIp(tmp,addrStack);
                        exprStack->pop();
                    }
                    exprStack->push(b);
                }
                break;
            default: break;
        }
        i++;
    }
    while(!exprStack->empty()) {
        Item tmp = exprStack->top();
        root=treeIp(tmp,addrStack);
        exprStack->pop();
    }
    delete addrStack;
    return root;



}