#ifndef VOTING_H
#define VOTING_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

class Voter
{
private:
    string voterID;
    string name;

public:
    void registerVoter();
    void castVote();
    static void displayResults();
    static bool isRegistered(const string &voterID);
};

#endif
