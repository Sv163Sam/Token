#include <iostream>
#include <vector>
#include <unordered_map>
#include <variant>
#include <cctype>

struct OpeningBracket {
    std::string value;
};

struct ClosingBracket {
    std::string value;
};

struct Number {
    int value;
};

struct UnknownToken {
    std::string value;
};

struct MinToken {
    int value;
};

struct AbsToken {
    int value;
};

struct Plus {
    int left_operand;
    int right_operand;
};

struct Minus {
    int left_operand;
    int right_operand;
};

struct Multiply {
    int left_operand;
    int right_operand;
};

struct Modulo {
    int left_operand;
    int right_operand;
};

struct Divide {
    int left_operand;
    int right_operand;
};

struct MaxToken {
    int value;
};

struct SquareToken {
    int value;
};

using Token = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, AbsToken, Plus, Minus, Multiply, Modulo, Divide, MaxToken, SquareToken>;

const std::unordered_map<std::string, Token> TokenType = {
        {"min", MinToken{0}},
        {"abs", AbsToken{0}},
        {"max", MaxToken{0}},
        {"square", SquareToken{0}},
        {"+", Plus{0, 0}},
        {"-", Minus{0, 0}},
        {"*", Multiply{0, 0}},
        {"/", Divide{0, 0}},
        {"%", Modulo{0, 0}},
        {"(", OpeningBracket{}},
        {")", ClosingBracket{}}
};

int ToDigit(unsigned char symbol) {
    return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos) {
    int value = 0;
    auto symbol = static_cast<unsigned char>(input[pos]);

    while (std::isdigit(symbol)) {
        value = value * 10 + ToDigit(symbol);
        if (pos == input.size() - 1) {
            ++pos;
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }
    return Number{value};
}

Token ParseName(const std::string& input, size_t& pos) {
    std::string name;
    auto symbol = static_cast<unsigned char>(input[pos]);

    while (std::isalpha(symbol) || std::ispunct(symbol)) {
        name += symbol;
        if (pos == input.size() - 1) {
            ++pos;
            break;
        }

        symbol = static_cast<unsigned char>(input[++pos]);
    }

    if (auto it = TokenType.find(name); it != TokenType.end())
        return it->second;

    return UnknownToken{name};
}

std::vector<Token> Tokenize(const std::string& input) {
    std::vector<Token> tokens;
    const size_t size = input.size();
    size_t pos = 0;

    while (pos < size) {
        const auto symbol = static_cast<unsigned char>(input[pos]);
        if (std::isspace(symbol)) {
            ++pos;
        } else if (std::isdigit(symbol)) {
            tokens.emplace_back(ParseNumber(input, pos));
        } else if (std::isalpha(symbol) || std::ispunct(symbol)) {
            tokens.emplace_back(ParseName(input, pos));
        } else {
            tokens.emplace_back(UnknownToken{std::string(1, symbol)});
            ++pos;
        }
    }
    return tokens;
}

int main() {
    std::string input = "(1 + 2) * 3 / 4 + 5 * (6 - 7) + 1";
    std::vector<Token> tokens = Tokenize(input);
    return 0;
}