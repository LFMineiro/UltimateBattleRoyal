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

        int getTotalPower(){
            return (Person::getTotalPower() * (1 + (0.04 * jailTime)));
            // Villains have 4% more power for each year in jail
        }
        int getJailTime() {
            return jailTime;
        }
        void setJailTime(int time) {
            jailTime = time;
        }
};

class Confrontation {
    public:
        void fight(Person& p1, Person& p2) {
            int p1Power = p1.getTotalPower();
            int p2Power = p2.getTotalPower();

            Villain* v1 = dynamic_cast<Villain*>(&p1);
            Villain* v2 = dynamic_cast<Villain*>(&p2);

            if(p1Power > p2Power) {
                if(v2) {
                    cout << p1.getName() << " wins against " << p2.getName() << endl;
                    v2->setJailTime(v2->getJailTime()  + 2);
                }
                else {
                    cout << p1.getName() << " wins against " << p2.getName() << endl;
                }
            }
            else if(p1Power < p2Power) {
                if(v1) {
                    cout << p2.getName() << " wins against " << p1.getName() << endl;
                    v1->setJailTime(v1->getJailTime() + 2);
                }
                else {
                    cout << p2.getName() << " wins against " << p1.getName() << endl;
                }
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
    cout << "Lex Luthor has " << villain.getJailTime() << " years in Jail" << endl;

    return 0;
}