// Copyright 2025 NNTU-CS
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

#include "tstack.h"

static int precedence(char oper) {
  return (oper == '+' || oper == '-') ? 1 : (oper == '*' || oper == '/') ? 2 : 0;
}
static inline bool isOp(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
  std::string out;
  TStack<char, 128> ops;

  for (size_t i = 0; i < inf.size(); ++i) {
    char ch = inf[i];

    if (std::isspace(static_cast<unsigned char>(ch))) continue;

    if (std::isdigit(static_cast<unsigned char>(ch))) {
      while (i < inf.size() && std::isdigit(static_cast<unsigned char>(inf[i])))
        out += inf[i++];
      out += ' ';
      --i;
    } else if (ch == '(') {
      ops.push(ch);
    } else if (ch == ')') {
      while (!ops.empty() && ops.top() != '(') {
        out += ops.top();
        out += ' ';
        ops.pop();
      }
      if (!ops.empty()) ops.pop();
    } else if (isOp(ch)) {
      while (!ops.empty() && isOp(ops.top()) &&
             precedence(ops.top()) >= precedence(ch)) {
        out += ops.top();
        out += ' ';
        ops.pop();
      }
      ops.push(ch);
    }
  }
  while (!ops.empty()) {
    out += ops.top();
    out += ' ';
    ops.pop();
  }
  if (!out.empty() && out.back() == ' ') out.pop_back();
  return out;
}

int eval(const std::string& post) {
  std::stringstream ss(post);
  std::string token;
  TStack<int, 128> stack;

  while (ss >> token) {
    if (token.size() == 1 && isOp(token[0])) {
      if (stack.count() < 2)
        throw std::runtime_error("incorrect postfix expression");
      int rhs = stack.top();
      stack.pop();
      int lhs = stack.top();
      stack.pop();
      switch (token[0]) {
        case '+':
          stack.push(lhs + rhs);
          break;
        case '-':
          stack.push(lhs - rhs);
          break;
        case '*':
          stack.push(lhs * rhs);
          break;
        case '/':
          stack.push(lhs / rhs);
          break;
      }
    } else {
      stack.push(std::stoi(token));
    }
  }
  if (stack.count() != 1) throw std::runtime_error("incorrect postfix expression");
  return stack.top();
}

