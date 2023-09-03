
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using std::string;
using std::istringstream;
using std::istream;
using std::vector;


const string rulesText0{"Flying"};
const string rulesText1{"When Dawning Angel enters the battlefield, you gain 4 life."};
const string rulesText2{"Enchanted creature gets -2/-0. It gets -6/-0 instead as long as its controller has seven or more cards in their graveyard."};


int main()
{
    using std::cout;
    using std::endl;

    istringstream ss{rulesText1};
    vector<string> vPhrases;

    string sentence{};
    std::getline(ss, sentence);  // grabs whole sentence

    // For each sentence:
    // - Find first ,.; and store the string up to that point.
    // - Repeat until npos?

    cout << "SENTENCE: " << sentence << endl;
    cout << "PHRASES" << endl;
    cout << "=======" << endl;
    
    for (const string& str : vPhrases)
        cout << str << endl;

    // How to check for three different delimiters?
    // Get a \n line, stringstream the . then stringstream the , sections?

    return 0;
}