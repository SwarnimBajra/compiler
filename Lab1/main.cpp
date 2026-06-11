#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

// Token structure
struct Token {
    string type;
    string value;
};

bool isKeyword(const string &word) {
    string keywords[] = {
        "int", "float", "if", "else", "while", "for", "return", "void"
    };

    for (string k : keywords) {
        if (word == k)
            return true;
    }
    return false;
}

bool isOperator(char ch) {
    string ops = "+-*/=<>!&|";
    return ops.find(ch) != string::npos;
}

bool isDelimiter(char ch) {
    string delims = "();{}[],";
    return delims.find(ch) != string::npos;
}

int main() {
    ifstream file("file.txt");

    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    vector<Token> tokens;
    string word;
    char ch;

    while (file.get(ch)) {

        if (isspace(ch))
            continue;

        // KEYWORD / IDENTIFIER
        if (isalpha(ch)) {
            word = "";
            word += ch;

            while (file.get(ch) && isalnum(ch)) {
                word += ch;
            }

            if (file) file.unget();

            if (isKeyword(word))
                tokens.push_back({"KEYWORD", word});
            else
                tokens.push_back({"IDENTIFIER", word});
        }

        // NUMBER
        else if (isdigit(ch)) {
            word = "";
            word += ch;

            while (file.get(ch) && isdigit(ch)) {
                word += ch;
            }

            if (file) file.unget();

            tokens.push_back({"NUMBER", word});
        }

        // OPERATOR
        else if (isOperator(ch)) {
            string op(1, ch);

            char next = file.peek();
            if ((ch == '=' && next == '=') ||
                (ch == '<' && next == '=') ||
                (ch == '>' && next == '=') ||
                (ch == '!' && next == '=') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|')) {

                file.get(ch);
                op += ch;
            }

            tokens.push_back({"OPERATOR", op});
        }

        // DELIMITER
        else if (isDelimiter(ch)) {
            string d(1, ch);
            tokens.push_back({"DELIMITER", d});
        }

        // UNKNOWN (optional safety)
        else {
            string u(1, ch);
            tokens.push_back({"UNKNOWN", u});
        }
    }

    // OUTPUT
    cout << "\nTOKENS GENERATED:\n";
    cout << "---------------------------------\n";

    for (auto &t : tokens) {
        cout << "< " << t.type << " , " << t.value << " >" << endl;
    }

    cout << "\nTotal tokens: " << tokens.size() << endl;

    return 0;
}