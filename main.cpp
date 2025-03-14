#include "voting.h"

// Function to check if a voter is already registered
bool Voter::isRegistered(const string &voterID)
{
    ifstream file("voters.txt");
    string line, id;

    if (!file.is_open())
    {
        return false;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> id;
        if (id == voterID)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Function to register a voter
void Voter::registerVoter()
{
    cout << "Enter Voter ID: ";
    cin >> voterID;

    if (isRegistered(voterID))
    {
        cout << "Voter ID already exists. Registration failed.\n";
        return;
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    ofstream file("voters.txt", ios::app);
    if (file.is_open())
    {
        file << voterID << " " << name << " NotVoted\n";
        file.close();
        cout << "Voter registered successfully!\n";
    }
    else
    {
        cout << "Error opening file.\n";
    }
}

// Function to cast a vote
void Voter::castVote()
{
    cout << "Enter Voter ID: ";
    cin >> voterID;

    ifstream inFile("voters.txt");
    ofstream outFile("temp.txt");
    string line, id, voterName, vote;
    bool found = false;

    if (inFile.is_open() && outFile.is_open())
    {
        while (getline(inFile, line))
        {
            stringstream ss(line);
            ss >> id >> voterName >> vote;

            if (id == voterID)
            {
                found = true;
                if (vote != "NotVoted")
                {
                    cout << "You have already voted! Cannot vote again.\n";
                    outFile << line << "\n";
                }
                else
                {
                    string candidate;
                    cout << "Enter Candidate Name: ";
                    cin >> candidate;
                    outFile << id << " " << voterName << " " << candidate << "\n";
                    cout << "Vote cast successfully!\n";
                }
            }
            else
            {
                outFile << line << "\n";
            }
        }

        inFile.close();
        outFile.close();

        if (!found)
        {
            cout << "Voter ID not found. Please register first.\n";
            remove("temp.txt");
        }
        else
        {
            remove("voters.txt");
            rename("temp.txt", "voters.txt");
        }
    }
    else
    {
        cout << "Error opening files.\n";
    }
}

// Function to display voting results
void Voter::displayResults()
{
    ifstream file("voters.txt");
    if (!file.is_open())
    {
        cout << "Error opening file.\n";
        return;
    }

    unordered_map<string, int> voteCount;
    string line, id, name, vote;

    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> id >> name >> vote;
        if (vote != "NotVoted")
        {
            voteCount[vote]++;
        }
    }
    file.close();

    cout << "\nVoting Results:\n";
    for (const auto &pair : voteCount)
    {
        cout << pair.first << ": " << pair.second << " votes\n";
    }
}

// Main function
int main()
{
    int choice;
    Voter voter;

    do
    {
        cout << "\n--- Online Voting System ---\n";
        cout << "1. Register Voter\n";
        cout << "2. Cast Vote\n";
        cout << "3. View Results\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            voter.registerVoter();
            break;
        case 2:
            voter.castVote();
            break;
        case 3:
            Voter::displayResults();
            break;
        case 4:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
