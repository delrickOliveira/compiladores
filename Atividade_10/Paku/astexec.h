#ifndef ASTEXEC_H
#define ASTEXEC_H

#include "astgen.h"
#include "hashtable.h"
#include <assert.h>
#include <math.h>

int unaryOperator(char* op, int value);
int operator(char* op, int left, int right);
static void dispatchStatement(hashtable *htable, AstElement* node);
double evalExpression(hashtable *htable, AstElement* node);
static void execStmt(hashtable *htable, AstElement* a);

double evalExpression(hashtable *htable, AstElement* node)
{    
    double left;
    double right;
    //printf("e-> %c \n", node->nodetype); 
    Variable* variable = (Variable*)malloc(sizeof(Variable));

    switch (node->nodetype)
    { 

    case 'Z':
        return !evalExpression(htable, node->right); 
        break; 

    case 'V': 
        return node->val;
        break;

    case 'N':        
        return hash_lookup(htable,node->name)->value;
        break;

    case 'U':     
        left =  evalExpression(htable, node->left);     
        return unaryOperator(node->op, left);
        break;

    case 'E':   
        left =  evalExpression(htable, node->left);         
        right = evalExpression(htable, node->right);
        return operator(node->op, left, right);
    break;

    default:
        printf("expression not found %c \n", node->nodetype);
    }
    return 0;
}

static void dispatchStatement(hashtable *htable, AstElement* node)
{
    Variable* variable = (Variable*)malloc(sizeof(Variable));
    double result;
    //printf("d-> %c \n", node->nodetype); 
    switch (node->nodetype)
    {
    case 'S':
        execStmt(htable, node);
        break;
    case 'P':
        printf("%s: %d\n", node->name, hash_lookup(htable, node->name)->value);
        break;
    case 'W':
        printf("%s\n", node->name);
        break;
    case 'R':     
        variable->name = node->name;
        printf("Digite o valor de %s: \n", node->name);
        scanf("%d", &variable->value );
        hash_insert(htable, node->name, variable);
        break;

    case 'I':
        result = evalExpression(htable, node->cond);
        
        if(result){            
            execStmt(htable, node->left);         
        }else{
            if(node->right){
                execStmt(htable, node->right);
            }            
        }
        break;

    case 'L':

        while (evalExpression(htable, node->cond) == 1)
        {
            execStmt(htable, node->right);
        }  

    break;    

    case 'D':
        variable->name = node->name;
        hash_insert(htable, node->name, variable);
        break;

    case 'A':               
        variable->name = node->name;
        variable->value = evalExpression(htable, node->right);
        if(hash_update(htable, node->name,variable) == 0){
            printf("Erro: variavel %s nao declarada \n", node->name);    
        }
        break;
    case 'B':
    default:
        //printf("desconhecido \n");
        break;
    }
}


static void execStmt(hashtable *htable, AstElement* a)
{    
    for(int i = 0; i < a->count; i++)
    {
        dispatchStatement(htable, a->statements[i]);
    }
}

//perdao
int operator(char* op, int left, int right){
    if (strcmp(op, "+") == 0){
        return left + right;
    }else if (strcmp(op, "-") == 0){
        return left - right;
    }else if (strcmp(op, "/") == 0){
        return left / right;
    }else if (strcmp(op, "*") == 0){
        return left * right;
    }else if (strcmp(op, ">=" )== 0){
        return left >= right;
    }else if (strcmp(op, "<=") == 0){
        return left <= right;
    }else if (strcmp(op, "!=") == 0){
        return left != right;
    }else if (strcmp(op, "<") == 0){
        return left < right;
    }else if (strcmp(op, ">") == 0){
        return left > right;
    }else if (strcmp(op, "==") == 0){
        return left == right;
    }else if (strcmp(op, "||") == 0){
        return left || right;
    }else if (strcmp(op, "&&") == 0){
        return left && right;
    }else if (strcmp(op, "%") == 0){
        return (int)left % (int)right;
    }else {
        return 0;
    }
}

int unaryOperator(char* op, int value){
     if (strcmp(op, "-") == 0){
        return - value;
    }else if ((strcmp(op, "`") == 0)){
        return sqrt(value);
    }
    else{
        return 0;
    }
}

#endif