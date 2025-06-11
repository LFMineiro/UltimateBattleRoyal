#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

class SuperPower {
    private:
        string name;
        int power;

    public:
        SuperPower(string n, int p): name(n), power(p) {}
        float getPower() {
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
        virtual float getTotalPower() {
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
        float getTotalPower() override{
            return (Person::getTotalPower() * 1.1);
            // Heroes have 10% more power because they stand for good
        }

        Hero operator+(Hero &h) {
            Hero newHero(name + " e " + h.name);
            for (auto& power : h.powers) {
                newHero.addPower(power);
            }
            for(auto &power : powers) {
                newHero.addPower(power);
            }
            return newHero;
        }
        bool operator<(Hero &h1) {
            return getTotalPower() < h1.getTotalPower();
        }
        friend ostream& operator<<(ostream& os, Hero &h ) {
            os << h.getName() << " - " << h.getTotalPower();
            return os;
        }

};

class Villain : public Person {
    private:
        int jailTime = 0;
    public:
        Villain(string n): Person(n) {}

        float getTotalPower() override {
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
            for (auto& power : powers) {
                newVillain.addPower(power);
            }
            return newVillain;
    }
        bool operator<(Villain &v1) {
            return getTotalPower() < v1.getTotalPower();
        }
        friend ostream& operator<<(ostream& os, Villain &v ) {
            os << v.getName() << " - " << v.getTotalPower();
            return os;
        }
};

class Confrontation {
    public:
        void fight(Person& p1, Person& p2) {
            int p1Power = p1.getTotalPower();
            int p2Power = p2.getTotalPower();

            Villain* v1 = dynamic_cast<Villain*>(&p1);
            Villain* v2 = dynamic_cast<Villain*>(&p2);

    cout << "Battle: " << p1.getName() << " (" << p1Power << ") vs "
              << p2.getName() << " (" << p2Power << ")\n";

    if (p1Power > p2Power) {
        cout << "Winner: " << p1.getName() << "!\n";
        if (v2) {
            v2->setJailTime(v2->getJailTime() + 2);
            
        }
    } else if (p1Power < p2Power) {
        cout << "Winner: " << p2.getName() << "!\n";
        if (v1) {
            v1->setJailTime(v1->getJailTime() + 2);
            
        }
    } else {
        cout << "It's a tie! \n";
    }

    cout << "-----------------------------------------\n";      
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

    Villain cheetahVerde = duende + cheetah;
    Villain magnetoBizarro = magneto + bizarro;
    Hero superHulk = superHomem + hulk;

    confrontation.fight(cheetahVerde, mulherMaravilha);
    confrontation.fight(magnetoBizarro, wolverine);
    confrontation.fight(superHulk, magnetoBizarro);

    // Começar o ranking
    
    // A ideia aqui para os rankings separados vai ser fazer um vector com todos herois e outros com todos vilões, e com a sobrecarga do operador <, ordenadar por ordem de poder

    vector<Hero> heroes;
        heroes.emplace_back(homemAranha);
        heroes.emplace_back(superHomem);
        heroes.emplace_back(mulherMaravilha);
        heroes.emplace_back(hulk);
        heroes.emplace_back(tempestade);
        heroes.emplace_back(wolverine);
        heroes.emplace_back(superHulk);
        sort(heroes.begin(), heroes.end());
        reverse(heroes.begin(), heroes.end());
    
    vector<Villain> villains;
        villains.emplace_back(duende);
        villains.emplace_back(cheetah);
        villains.emplace_back(magneto);
        villains.emplace_back(bizarro);
        villains.emplace_back(cheetahVerde);
        villains.emplace_back(magnetoBizarro);
        sort(villains.begin(), villains.end());
        reverse(villains.begin(), villains.end());

        int h = 1;
        int v = 1;

        ofstream HeroFile("Ranking Herois.txt");
    
        HeroFile << " ====== Ranking dos Herois ====== " << endl;
        for(auto& hero : heroes) {
            HeroFile << "[" << h++ << "]) " << hero << endl ; 
    }
    ofstream VillainFile("Ranking Viloes.txt");
    
    VillainFile << " ====== Ranking dos Viloes ====== " << endl;
    for(auto& villain : villains) {
        VillainFile << "[" << v++ << "]) " << villain << endl ; 
}

    return 0;
}