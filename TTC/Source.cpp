#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <unordered_map>

using namespace std;

#define INF 999

int minimumdistance(float distance[], bool stat[]) {
    float minimum = INT_MAX;
    int mind = -1;

    for (int i = 0; i < 5; i++) {
        if (!stat[i] && distance[i] <= minimum) {
            minimum = distance[i];
            mind = i;
        }
    }

    return mind;
}

void dijkstra(float graph[5][5], int sourseterminal, string station[5]) {
    float distance[5];
    bool stat[5];

    for (int k = 0; k < 5; k++) {
        distance[k] = INT_MAX;
        stat[k] = false;
    }

    distance[sourseterminal] = 0;

    for (int j = 0; j < 5; j++) {
        int m = minimumdistance(distance, stat);
        if (m == -1) break;
        stat[m] = true;

        for (int k = 0; k < 5; k++) {
            if (!stat[k] && graph[m][k] && distance[m] != INT_MAX && distance[m] + graph[m][k] < distance[k]) {
                distance[k] = distance[m] + graph[m][k];
            }
        }
    }

    cout << "Minimum distance from {" << station[sourseterminal] << "} to every station:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Enter " << i << " to check distance from " << station[sourseterminal] << " to {" << station[i] << "} station" << endl;
    }

    int n;
    cout << "Enter the station to check the distance: ";
    cin >> n;
    cout << "Distance from {" << station[sourseterminal] << "} to {" << station[n] << "} is {" << distance[n] << "} km" << endl;

    cout << "Path: ";
    for (int k = sourseterminal; k <= n; k++) {
        cout << station[k];
        if (k != n) {
            cout << " -> ";
        }
    }
    cout << " {" << distance[n] << "} km" << endl;
}

unordered_map<string, string> users;

void signup() {
    string userID, password;
    cout << "Enter User ID: ";
    cin >> userID;
    cout << "Enter Password: ";
    cin >> password;

    if (users.find(userID) == users.end()) {
        users[userID] = password;
        cout << "User signed up successfully!" << endl;
    }
    else {
        cout << "User ID already exists. Please choose a different User ID." << endl;
    }
}

int login() {
    string userID, password;
    cout << "Enter User ID: ";
    cin >> userID;
    cout << "Enter Password: ";
    cin >> password;

    if (users.find(userID) != users.end()) {
        if (users[userID] == password) {
            cout << "Login successful!" << endl;
            return 1;
        }
        else {
            cout << "Incorrect password." << endl;
            return 0;
        }
    }
    else {
        cout << "User ID does not exist." << endl;
        return -1;
    }
}

int main() {
    float graph[5][5] = {
        {0, 10, INF, INF, 5},
        {10, 0, 3, INF, INF},
        {INF, 3, 0, 2, INF},
        {INF, INF, 2, 0, 4},
        {5, INF, INF, 4, 0}
    };

    int sourseterminal, ch, flag;
    char s;

    cout << "Welcome to Thunder Bay Transit Services" << endl;

    do {
        cout << endl;
        cout << "1) Login" << endl;
        cout << "2) Register" << endl;
        cout << "3) Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            flag = login();
            break;
        case 2:
            signup();
            cout << "Do you want to login (Y/N)?: ";
            cin >> s;
            if (s == 'y' || s == 'Y') {
                flag = login();
            }
            else {
                cout << "Thank you" << endl;
                return 0;
            }
            break;
        case 3:
            cout << "Thank you" << endl;
            return 0;
        default:
            cout << "Incorrect choice" << endl;
            break;
        }
    } while (flag != 1);

    if (flag == 1) {
        string station[5] = { "Waterfront Terminal", "City Hall", "Lakehead University", "Confederation College", "Intercity Shopping Centre" };
        char x;

        cout << "Welcome to Thunder Bay Transit Counter" << endl;

        do {
            for (int i = 0; i < 5; i++) {
                cout << "Enter " << i << " for " << station[i] << endl;
            }
            cout << "Enter the source terminal station: ";
            cin >> sourseterminal;

            dijkstra(graph, sourseterminal, station);

            cout << "Do you want to continue (Y/N): ";
            cin >> x;
        } while (x == 'y' || x == 'Y');
    }

    return 0;
}
