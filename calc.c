#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <math.h>
//a function to evaluate the expression
double evaluate (char []);
//a function to check and assigne the precedence to operators
int precedence(char);
//a function to calculate the numbers
double calculate(char , double , double );
//a function to check if the character is number or not
char checknumber(char);

int main(void)
{
  char expression[100];
  double result;

  printf("Enter the Expression: ");
  scanf("%[^\n]", expression);
  result = evaluate(expression);
  printf("Result = %.2lf\n", result);
  return 0;
}

double evaluate(char expr[])
{
  double nonDecNum[5]; int nIdx = 0;
  char operators[5]; int oIdx = 0;
  char decimalNum[16]; int fIdx = 0;
  char ch; int  i = 0;

  while ((ch = expr[i]) != 0) {
    if (checknumber(ch))
    {
      decimalNum[fIdx++] = ch;
      if (!checknumber(expr[i + 1]))
      {
        decimalNum[fIdx] = 0; fIdx = 0;
        sscanf(decimalNum, "%lf", &nonDecNum[nIdx++]);
      }
    }
    else
    {
      while ((oIdx > 0) && (precedence(ch) <= precedence(operators[oIdx - 1])))
      {
        nonDecNum[nIdx - 2] = calculate(operators[oIdx - 1], nonDecNum[nIdx - 2], nonDecNum[nIdx - 1]);
        oIdx--; nIdx--;
      }
      operators[oIdx++] = ch;
    }
    i++;
  }
  while (oIdx > 0) {
    nonDecNum[nIdx - 2] = calculate(operators[oIdx - 1], nonDecNum[nIdx - 2], nonDecNum[nIdx - 1]);
    oIdx--; nIdx--;
  }
  return nonDecNum[0];
}

char checknumber(char ch)
{
  if ((ch >= '0' && ch <= '9') || ch == '.') {
    return 1;
  }
  else{
    return 0;
  }
}
int precedence(char ch)
{
  int opPrecdence;
  switch (ch)
  {
    case '+':
    case '-':
    opPrecdence = 0;
    break;
    case '*':
    case '/':
    opPrecdence = 1;
    break;
    case '^':
    opPrecdence = 2;
  }
  return opPrecdence;
}

double calculate(char moperator, double num1, double num2)
{
  double result;
  switch (moperator)
  {
    case '+':
    result = num1 + num2;
    break;
    case '-':
    result = num1 - num2;
    break;
    case '*':
    result = num1 * num2;
    break;
    case '/':
    result = num1 / num2;
    break;
    case '^':
    result = pow(num1, num2);
    break;
    default:
    printf("Invalid Operator!\n");
    exit(0);
  }
  return result;
}
