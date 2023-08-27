#include <fstream>
#include <iostream>
#include <string>

#include "utils.hpp"
using namespace std;
string createTokenFile()
{
    string home = getenv("HOME");
	ofstream tokenF(home + "/.canvas_token");
    if(tokenF.fail())
    {
        cerr << "[fatal] Failed to open token file" << endl;
        exit(1);
    }
    cout << "To create that file, please enter your token: " << flush;
    string inputStr;
    getline(cin, inputStr);
    tokenF << inputStr;
    tokenF.close();
    return inputStr;
}
