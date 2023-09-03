#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

const string cardName{"Priest of Glory"};
const string etbTemplate{"When {cardname} enters the battlefield, you gain {n} life."};
const int lifeGainAmt = 3;


int main()
{
    stringstream ss{etbTemplate};
    string result{etbTemplate};

    // Find {cardname} and substitute cardName into it.
    size_t startPos = etbTemplate.find_first_of("{");
    size_t endPos = etbTemplate.find_first_of("}") + 1;

    result.replace(startPos, endPos - startPos, cardName);

    cout << "RESULT: " << result << endl;

    // Find {n} and substitute lifeGainAmt.
    startPos = result.find_first_of("{");
    endPos = result.find_first_of("}") + 1;

    result.replace(startPos, endPos - startPos, std::to_string(lifeGainAmt));

    cout << "RESULT: " << result << endl; 

    return 0;
}