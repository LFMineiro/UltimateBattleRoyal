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
        vector<SuperPower> getPowers() {
            return powers;
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
 
            friend class Hero;
            friend class Villain;
};

class Hero : public Person {
    public:
        Hero(string n): Person(n) {}
        int getTotalPower() override{
            return (Person::getTotalPower() * 1.1);
            // Heroes have 10% more power because they stand for good
        }

        Hero operator+(Hero &h) {
            Hero newHero(name + " e " + h.name);
            for (auto& power : h.powers) {
                newHero.addPower(power);
            }
            return newHero;
        }

};

class Villain : public Person {
    private:
        int jailTime = 0;
    public:
        Villain(string n): Person(n) {}

        int getTotalPower() override {
            return (Person::getTotalPower() * (1 + (0.04 * jailTime)));
            // Villains have 4% more power for each year in jail
        }
        int getJailTime() {
            return jailTime;
        }
        void setJailTime(int time) {
            jailTime = time;
        }
        
        Villain operator+(Villain &v) {
            Villain newVillain(name + " e " + v.name);
            for (auto& power : v.powers) {
                newVillain.addPower(power);
            }
            return newVillain;
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

    Confrontation confrontation;

    Hero homemAranha("Homem-Aranha");
    homemAranha.addPower(SuperPower("Soltar teia", 2));
    homemAranha.addPower(SuperPower("Sentido apurado", 2));

    Hero superHomem("Super-Homem");
    superHomem.addPower(SuperPower("Voar", 2));
    superHomem.addPower(SuperPower("Forca", 4));
    superHomem.addPower(SuperPower("Sopro Congelante", 3));

    Hero mulherMaravilha("Mulher Maravilha");
    mulherMaravilha.addPower(SuperPower("Voar", 2));
    mulherMaravilha.addPower(SuperPower("Forca", 4));
    mulherMaravilha.addPower(SuperPower("Laco", 2));

    Hero hulk("Hulk");
    hulk.addPower(SuperPower("Forca", 4));
    hulk.addPower(SuperPower("Regeneracao", 3));
    hulk.addPower(SuperPower("Artilheiro do Galo", 1));

    Hero tempestade("Tempestade");
    tempestade.addPower(SuperPower("Controlar o clima", 5));

    Hero wolverine("Wolverine");
    wolverine.addPower(SuperPower("Regeneracao", 3));
    wolverine.addPower(SuperPower("Sentido apurado", 2));
    wolverine.addPower(SuperPower("Adamantium", 2));

    Villain duende("Duende Verde");
    duende.addPower(SuperPower("Tecnologia", 3));
    duende.addPower(SuperPower("Durabilidade", 1));

    Villain cheetah("Cheetah");
    cheetah.addPower(SuperPower("Sentido apurado", 2));
    cheetah.addPower(SuperPower("Durabilidade", 1));
    cheetah.addPower(SuperPower("Velocidade", 3));

    Villain magneto("Magneto");
    magneto.addPower(SuperPower("Magnetismo", 5));

    Villain bizarro("Bizarro");
    bizarro.addPower(SuperPower("Voar", 2));
    bizarro.addPower(SuperPower("Forca", 4));
    bizarro.addPower(SuperPower("Sopro Congelante", 3));

    confrontation.fight(duende, homemAranha);
    confrontation.fight(cheetah, wolverine);
    confrontation.fight(wolverine, duende);
    confrontation.fight(cheetah, hulk);
    confrontation.fight(cheetah, superHomem);
    confrontation.fight(cheetah, mulherMaravilha);
    confrontation.fight(magneto, mulherMaravilha);
    confrontation.fight(magneto, hulk);
    confrontation.fight(magneto, superHomem);
    confrontation.fight(tempestade, magneto);
    confrontation.fight(bizarro, hulk);
    confrontation.fight(homemAranha, duende);

// Faça a dupla Duende Verde e Cheetah
// Faça a dupla Magneto e Bizarro
// Faça a dupla Super-Homem e Hulk

    Villain chettaVerde = duende + cheetah;
    Villain magnetoBizarro = magneto + bizarro;
    Hero superHulk = superHomem + hulk;

    confrontation.fight(chettaVerde, mulherMaravilha);
    confrontation.fight(magnetoBizarro, wolverine);
    confrontation.fight(magnetoBizarro, wolverine);

    
    

    return 0;
}