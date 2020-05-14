
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using std::string;
using std::istringstream;
using std::vector;


const string rulesText{"When Dawning Angel enters the battlefield, you gain 4 life."};


int main()
{
    using std::cout;
    using std::endl;

    istringstream ss{rulesText};
    vector<string> vPhrases;

    string sentence{};
    std::getline(ss, sentence);  // grabs whole sentence

    istringstream ssSentence{sentence};
    string phrase{};
    while (!ssSentence.eof())
    {
        char c = static_cast<char>(ssSentence.peek());
        if (c != ',' && c != '.' && c != ';')
        {
            c = static_cast<char>(ssSentence.get());
            phrase += c;
        }
        else
        {
            vPhrases.push_back(phrase);
            phrase.clear();
            ssSentence.ignore(1); // skip ,.; and ws
            ssSentence >> std::ws;
        }
    }

    cout << "SENTENCE: " << sentence << endl << endl;
    cout << "PHRASES" << endl;
    cout << "=======" << endl;
    
    for (const string& str : vPhrases)
        cout << str << endl;

    // How to check for three different delimiters?
    // Get a \n line, stringstream the . then stringstream the , sections?

    return 0;
}