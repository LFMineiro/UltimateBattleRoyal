#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SuperPower {
    private:
        string name;
        int power;

    public:
        SuperPower(string n, int p): name(n), power(p) {}
        int getPower() {
            return power;
        }
};

class Person {
    private:
        string name;
        vector<SuperPower> powers;
    public:
        Person(string n): name(n) {}
        void addPower(const SuperPower& power) {
            powers.emplace_back(power);
        }
        string getName() {
            return name;
        }
        virtual int getTotalPower() {
            if(powers.empty()) {
                return 0;
            } else {
                int total = 0;
                for(auto& power : powers) {
                    total += power.getPower();
                }
                return total;
            }
        }
};

class Hero : public Person {
    public:
        Hero(string n): Person(n) {}
        int getTotalPower() override{
            return Person::getTotalPower() * 1.1;
            // Heroes have 10% more power because they stand for good
        }

};

class Villain : public Person {
    private:
        int jailTime = 0;
    public:
        Villain(string n): Person(n) {}

        int getTotalPower(){;
            return (Person::getTotalPower() * (1 + (0.04 * jailTime)));
            // Villains have 4% more power for each year in jail
        }
        void setJailTime(int time) {
            jailTime = time;
        }
};

class Confrontation {
    public:
        void fight(Hero& hero, Villain& villain) {
            int heroPower = hero.getTotalPower();
            int villainPower = villain.getTotalPower();

            cout << "The Hero " << hero.getName() << " with power " << hero.getTotalPower() << " fight against the Villain " << villain.getName() << " with power " << endl;

            if(heroPower > villainPower) {
                cout << hero.getName() << " wins with power: " << heroPower << endl;
            } else if(villainPower > heroPower) {
                cout << villain.getName() << " wins with power: " << villainPower << endl;
            } else {
                cout << "It's a tie!" << endl;
            }
        }
};


int main() {
    SuperPower flight("Flight", 100);
    SuperPower strength("Super Strength", 150);
    SuperPower invisibility("Invisibility", 80);

    Hero hero("Superman");
    hero.addPower(flight);
    hero.addPower(strength);

    Villain villain("Lex Luthor");
    villain.addPower(invisibility);
    villain.setJailTime(2);

    Confrontation confrotation;
    confrotation.fight(hero, villain);
    

}