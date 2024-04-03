#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define a pretty-printing function for vector<string>
void prettyPrintVector(const vector<string> &vec, ostream &os)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << "\"" << vec[i] << "\"";
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
}

// Register the pretty-printing function with GDB
namespace std
{
    template <>
    struct formatter<vector<string>>
    {
        static void format(const vector<string> &vec, ostream &os)
        {
            prettyPrintVector(vec, os);
        }
    };
}

int main()
{
    vector<string> myVector = {"Hello", "World", "This", "is", "a", "test"};
    // Debug and inspect myVector in your debugger
    return 0;
}
