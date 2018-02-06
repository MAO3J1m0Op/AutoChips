#include <iostream>
#include <string>
using namespace std;

char yn;
char hotkey;
string answer;
int dl = 0;      // Dealer or "button"
int lb = 1;      // Little/small blind
int lbv = 10;    // Value of small blind
int bb = 2;      // Big blind
int bbv = 20;    // Value of big blind
string name[10]; // Stores the names of all 10 players
int players;     // The number of players playing - 1
int cash[10];    // Stores how many chips each player has
int call[10] = { 
    0,0,0,0,0,0,0,0,0,0
};               // How much money each player is from calling the bet
bool active[10] = {
    false,false,false,false,false,false,false,false,false,false
};               // Keeps track of whether the players are active or have folded for that hand.
int cashout[10] = {
    false,false,false,false,false,false,false,false,false,false
};               // A player will cash out and be permanantly be out of the game.
bool gone[10];   // Keeps track of whether each player has gone
int potraise;
int pot = 0;     // The money in the pot
int up = 2;
int nsd;
int bet ()
{
    for (int n=0;n < 10;++n) {gone[n] = false;}
    int before;
    while (true) {
        before = up;
        bool stoploop[10] = {false,false,false,false,false,false,false,false,false,false};
        ++up;
        while (active[up] == false) {
            ++up;
            if (up > players) {up = 0;}
        } if (up == before) {
            cout << name[up] << " is the only active player and wins the pot of $" << pot << "!\n";
            cash[up] += pot;
            pot = 0;
            return 1;
        }
        cout << name[up] << " is up with $" << cash[up] << ".\nWhat would you like to do?\n";
        if (potraise == 0) {
            cout << "[c]heck\n[f]old\n[b]et\n> ";
            cin >> hotkey;
            if ('c' == hotkey) {
                cout << name[up] << " checks.\n";
            } else if ('f' == hotkey) {
                active[up] = false;
                call[up] = 0;
                cout << name[up] << " folds.\n";
            } else if ('b' == hotkey) {
                cout << "How much do you want to bet? It must be at least $" << bbv << ".\n> ";
                cin >> potraise;
                cout << name[up] << " bets $" << potraise << ".\n";
                for (int n=0;n <= players;++n) {
                    if (active[n] == true) {call[n] += potraise;}
                }
                cash[up] -= potraise;
                pot += potraise;
                call[up] = 0;
            }
            gone[up] = true;
        } else {
            cout << "[c]all the bet ($" << call[up] << ")\n[f]old\n> ";
            cin >> hotkey;
            if ('c' == hotkey) {
                cout << name[up] << " calls the bet by putting $" << call[up] << " into the pot.\n";
                cash[up] -= call[up];
                pot += call[up];
                call[up] = 0;
                cout << "Would you like to raise the bet?\n(y/n) > ";
                cin >> yn;
                if ('y' == yn) {
                    cout << "By how much?\n> ";
                    cin >> potraise;
                    cout << name[up] << " raises the bet by $" << potraise << ".\n";
                    for (int n=0;n <= players;++n) {
                        if (active[n] == true) {call[n] += potraise;}
                    }
                    cash[up] -= potraise;
                    pot += potraise;
                    call[up] = 0;
                }
            } else if ('f' == hotkey) {
                active[up] = false;
                call[up] = 0;
                cout << name[up] << " folds.\n";
            }
            gone[up] = true;
        }
        for (int n=0;n < 10;++n) {
            if (gone[n] == true) {
                if (call[n] == 0) {stoploop[n] = true;}
            } else if (active[n] == false) {stoploop[n] = true;}
        }
        if (stoploop[0] == true and stoploop[1] == true and stoploop[2] == true and stoploop[3] == true and stoploop[4] == true and stoploop[5] == true and stoploop[6] == true and stoploop[7] == true and stoploop[8] == true and stoploop[9] == true) {break;}
    }
    for (int n=0;n < 10;++n) {call[n] = 0;}
    potraise = 0;
    int call[10] = {0,0,0,0,0,0,0,0,0,0};
    return 0;
}

int main ()
{
    cout << "How many people are playing?\n> ";
    cin >> players;
    if (players > 10){
      cout <<"10 players is the maximum allowed";
      exit(0);
      
    }
    players -= 1;
    for (int n;n <= players;++n) {
        cout << "What is player " << n << "'s name?\n> ";
        cin >> name[n];
        active[n] = true;
        cashout[n] = true;
    }
    cout << "Do you want to give everyone the same amount of starter cash?\n(y/n) > ";
    cin >> yn;
    cout << "How much money do you want ";
    if ('y' == yn) {
        cout << "everyone to start with?\n> ";
        int cashinitialize; cin >> cashinitialize;
        for (int n=0;n <= players;++n) {cash[n] = cashinitialize;}
    } else {
        for (int n=0;n <= players;++n) {
            cout << name[n] << " to start with?\n> ";
            cin >> cash[n];
        }
    }
    while (true) {
        for (int n=0;n <= players;++n) {
            if (active[n] == true) {call[n] = bbv;}
        }
        cout << name[dl] << " is the dealer.\n" << name[lb] << " is the small blind. They will cast their blind of $" << lbv << ".\n" << name[bb] << " is the big blind. They will cast their blind of $" << bbv << ".\n";
        cash[lb] -= lbv; cash[bb] -= bbv; call[lb] -= lbv; call[bb] -= bbv;
        pot += lbv + bbv;
        potraise = bbv;
        nsd = bet();
        if (nsd == 0) {
            cout << "Please deal the flop.\n";
            nsd = bet(); // No ShowDown
            if (nsd == 0) {
                cout << "Please deal the turn and press enter to continue.\n";
                nsd = bet();
                if (nsd == 0) {
                    cout << "Please deal the river and press enter to continue.\n";
                    nsd = bet();
                    if (nsd == 0) {
                        cout << "And now the showdown! Please type who wins the pot.\n> Player ";
                        int winner; cin >> winner;
                        cout << name[winner] << " wins the pot of $" << pot << "!\n";
                        pot += cash[winner];
                        pot = 0;
                    }
                }
            }
        }
        for (int n=0;n <= players;++n) {if (cashout[n] == true) {active[n] = true;}}
        cout << "Do you want to open player settings?\n(y/n) > ";
        cin >> yn;
        if ('y' == yn) {
            cout << "Opening player settings...\n";
            while (true) {
                cout << "What would you like to change?\n[a]dd new player\n[c]ash out a player\n[e]dit the amount of money a player has\nchange the [b]lind values\n[q]uit the menu\n> ";
                cin >> hotkey;
                if ('a' == hotkey) {
                    ++players;
                    cout << "Adding player " << players << "...\nWhat is player " << players << "'s name?\n> ";
                    cin >> name[players];
                    cout << "How much money do you want " << name[players] << " to start with?\n> ";
                    cin >> cash[players];
                    cout << "Giving " << name[players] << " $" << cash[players] << "...\n";
                } else if ('c' == hotkey) {
                    cout << "What player would you like to cash out?\n> Player ";
                    int playerhotkey; cin >> playerhotkey;
                    cout << "Cashing out " << name[playerhotkey] << "...\n";
                    name[playerhotkey] = "";
                    cashout[playerhotkey] = false;
                } else if ('e' == hotkey) {
                    cout << "Enter the player value you want to edit.\n> ";
                    int playerhotkey; cin >> playerhotkey;
                    cout << name[playerhotkey] << " has $" << cash[playerhotkey] << ". Are you sure you want to change it?\n(y/n) > ";
                    cin >> yn;
                    if ('y' == yn) {
                        cout << "Enter the sum of money " << name[playerhotkey] << " will have.\n> ";
                        cin >> cash[playerhotkey];
                    }
                } else if ('b' == hotkey) {
                    cout << "How much do you want the big blind to be?\n(Default: $20) > ";
                    cin >> bbv;
                    cout << "How much do you want the small blind to be?\n(Default: $10, Recommended: $" << bbv / 2 << ") > ";
                    cin >> lbv;
                } else if ('q' == hotkey) {break;}
            }
        }
        ++dl; if (dl > players) {dl = 0;}
        ++lb; if (lb > players) {lb = 0;}
        ++bb; if (bb > players) {bb = 0;}
    } return 0;
}
