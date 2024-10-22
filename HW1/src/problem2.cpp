#include <iostream>
#include <string>

using namespace std;

void powerset(int n, string current, int index) 
{
    // Output and return when n is equal to n
    if (index == n) 
    {
        std::cout << "{" << current << "}" << std::endl;
        return;
    }
    // Using type cast to turn integer into char

    // Branch into a set containing current element
    powerset(n, current + char('a' + index), index + 1);
    // Branch into a set not containing current element
    powerset(n, current, index + 1);
}

int main() 
{
    int n;
    cin >> n;

    powerset(n, "", 0);

    system("Pause");
}
