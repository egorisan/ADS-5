// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperand(char c) {
    return isdigit(c);
}

std::string infx2pstfx(const std::string& inf) {
    std::string result;
    TStack<char, 100> stack;
    bool spaceNeeded = false;

    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];

        if (c == ' ') {
            continue;
        }

        if (isOperand(c)) {
            result += c;
            spaceNeeded = true;
            if (i + 1 < inf.length() && isdigit(inf[i + 1])) {
                continue;
            }
            result += ' ';
        } else if (c == '(') {
            stack.Push(c);
        } else if (c == ')') {
            while (!stack.IsEmpty() && stack.Top() != '(') {
                result += stack.Pop();
                result += ' ';
            }
            stack.Pop();
        } else {
            if (spaceNeeded) {
                result += ' ';
                spaceNeeded = false;
            }
            while (!stack.IsEmpty() && stack.Top() != '('
                   && precedence(stack.Top()) >= precedence(c)) {
                result += stack.Pop();
                result += ' ';
            }
            stack.Push(c);
        }
    }

    while (!stack.IsEmpty()) {
        result += stack.Pop();
        if (!result.empty() && result.back() != ' ') {
            result += ' ';
        }
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::string number;

    for (size_t i = 0; i < post.length(); ++i) {
        char c = post[i];

        if (c == ' ') {
            continue;
        }

        if (isdigit(c)) {
            number = c;
            while (i + 1 < post.length() && isdigit(post[i + 1])) {
                number += post[++i];
            }
            stack.Push(std::stoi(number));
        } else {
            int b = stack.Pop();
            int a = stack.Pop();
            stack.Push(applyOp(a, b, c));
        }
    }

    return stack.Pop();
}
