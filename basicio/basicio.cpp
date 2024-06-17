#include<fstream>
#include<string>
#include<iostream>
#include<vector>
#include<stdio.h>

using namespace std;

string command;
bool foundRoom = false;
int x;
int y;
int z;

string getFullLine(ifstream& file, int line) {
    file.clear();
    file.seekg(ios::beg);
    for (int i = 0; i < line - 1; ++i) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string out;
    getline(file, out);
    file.clear();
    file.seekg(ios::beg);
    return out;
}


vector<string> parseString(string input) {
    vector<string> output = {};
    string current;
    bool formerWasNumber=true;
    for (int i = 0;i < input.length(); ++i) {
        if (!isdigit(input[i]) && input[i] != ' ' && input[i] != '-') {
            formerWasNumber = false;
        }

            if (input[i] == ' ' && formerWasNumber) {
                output.push_back(current);
                current = "";
        }else {
                current += input[i];
            }
    }
    output.push_back(current);
    return output;
}

int linesInFile(ifstream& file) {
    file.clear();
    file.seekg(ios::beg);
    int count =0;
    string dummy;
    for (int lines = 0; getline(file, dummy); lines++) {
        count++;
    };
    file.clear();
    file.seekg(ios::beg);
    return count;
}

void handleMovement(string command) {
    if (command == "w") {
        x++;
    }
    if (command == "e") {
        x--;
    }
    if (command == "n") {
        y++;
    }
    if (command == "s") {
        y--;
    }
    if (command == "u") {
        z++;
    }
    if (command == "d") {
        z--;
    }
}


int main()
{

    ifstream inData;
    ifstream stats;
    ofstream outData;

    stats.open("stats.txt");
    inData.open("indata.txt");
    outData.open("outdata.txt");

    x = stoi(getFullLine(stats, 1));
    y = stoi(getFullLine(stats, 2));
    z = stoi(getFullLine(stats, 3));

    while (true) {
        foundRoom = false;
        getline(cin, command);
        handleMovement(command);
      
        if (command == "x") {
            stats.close();
            ofstream newStats("stats.txt");
            newStats << x << "\n" << y << "\n" << z;
            newStats.close();
            stats.open("stats.txt");
        }


        for (int i = 0; i <= linesInFile(inData); ++i) {
            string rawData = getFullLine(inData, i);
            vector<string> cleanData = parseString(rawData);
            int roomX = stoi(cleanData.at(0));
            int roomY = stoi(cleanData.at(1));
            int roomZ = stoi(cleanData.at(2));

            if (roomX == x && roomY == y && roomZ == z) {
                cout << cleanData.at(3) << endl;
                foundRoom = true;
            }

        }
        if (foundRoom == false) {
            if (command[0] == '!') {
                inData.close();
                ofstream newData("indata.txt", ios_base::app);
                newData << "\n" << x << ' ' << y << ' ' << z << ' ' << command.erase(0, 1);
                newData.close();
                inData.open("indata.txt");

            }
        }

    }


}
