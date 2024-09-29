/*#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell {
private:
    string scrollName;
public:
    Spell() : scrollName("") { }
    Spell(string name) : scrollName(name) { }
    virtual ~Spell() { }
    string revealScrollName() {
        return scrollName;
    }
};

class Fireball : public Spell {
private: int power;
public:
    Fireball(int power) : power(power) { }
    void revealFirepower() {
        cout << "Fireball: " << power << endl;
    }
};

class Frostbite : public Spell {
private: int power;
public:
    Frostbite(int power) : power(power) { }
    void revealFrostpower() {
        cout << "Frostbite: " << power << endl;
    }
};

class Thunderstorm : public Spell {
private: int power;
public:
    Thunderstorm(int power) : power(power) { }
    void revealThunderpower() {
        cout << "Thunderstorm: " << power << endl;
    }
};

class Waterbolt : public Spell {
private: int power;
public:
    Waterbolt(int power) : power(power) { }
    void revealWaterpower() {
        cout << "Waterbolt: " << power << endl;
    }
};

class SpellJournal {
public:
    static string journal;
    static string read() {
        return journal;
    }
};
string SpellJournal::journal = "";



void counterspell(Spell * spell) {

    bool generic = true;

    try {
        Fireball& f = dynamic_cast <Fireball&> (*spell);
        f.revealFirepower();
        generic = false;
    }
    catch (bad_cast e) {}
    try {
        Frostbite& f = dynamic_cast <Frostbite&> (*spell);
        f.revealFrostpower();
        generic = false;
    }
    catch (bad_cast e) {}
    try {
        Waterbolt& f = dynamic_cast <Waterbolt&> (*spell);
        f.revealWaterpower();
        generic = false;
    }
    catch (bad_cast e) {}
    try {
        Thunderstorm& f = dynamic_cast <Thunderstorm&> (*spell);
        f.revealThunderpower();
        generic = false;
    }
    catch (bad_cast e) {}

    if (generic) {
        string sName = spell->revealScrollName();
        int n = sName.length();
        vector<vector<char>> seqs;
        string jour = SpellJournal::journal;
        int m = jour.length();

        int mLen = 0;

        string::iterator x = sName.begin();
        string::iterator xx = sName.begin();
        string::iterator y = jour.begin();
        string::iterator z = jour.begin();

        while (xx != sName.end()) {
            vector<char> inside;
            x = xx;
            y = jour.begin();
            z = jour.begin();
            while (x != sName.end()) {
                //cout << '\n' << *x;
                y = z;
                while (y != jour.end()) {
                    //cout << *x << '\t' << *y << '\n';
                    if (*x == *y) {
                        inside.push_back(*x);
                        y++;
                        z = y;
                        break;
                    }
                    y++;
                }
                x++;
            }
            seqs.push_back(inside);
            xx++;
        }


        for (int i = 0; i < seqs.size(); i++)
        {
            if (seqs[i].size() > mLen) mLen = seqs[i].size();
        }
        cout << mLen;
    }

}



class Wizard {
public:
    Spell* cast() {
        Spell* spell;
        string s; cin >> s;
        int power; cin >> power;
        if (s == "fire") {
            spell = new Fireball(power);
        }
        else if (s == "frost") {
            spell = new Frostbite(power);
        }
        else if (s == "water") {
            spell = new Waterbolt(power);
        }
        else if (s == "thunder") {
            spell = new Thunderstorm(power);
        }
        else {
            spell = new Spell(s);
            cin >> SpellJournal::journal;
        }
        return spell;
    }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while (T--) {
        Spell* spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}*/