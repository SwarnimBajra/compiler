#include <iostream>
#include <string>

using namespace std;

bool checkValid(string str)
{
    int len = str.length();

    // Check for invalid characters
    for (char ch : str)
    {
        if (ch != 'a' && ch != 'b' && ch != 'e')
            return false;
    }

    // e represents epsilon (null string)
    if (len == 1 && str[0] == 'e')
        return false;

    // Minimum length condition
    if (len < 2)
        return false;

    char first = str[0];
    char last = str[len - 1];

    // First and last characters must be different
    if ((first == 'a' && last == 'b') ||
        (first == 'b' && last == 'a'))
        return true;

    return false;
}

int main()
{
    string str;

    cout << "Enter string: ";
    cin >> str;

    if (checkValid(str))
        cout << "VALID STRING" << endl;
    else
        cout << "INVALID STRING" << endl;

    return 0;
}