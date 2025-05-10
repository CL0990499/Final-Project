#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Supporting Class: Diet
class Diet {
    string type;
public:
    Diet(const string& type) : type(type) {}
    string getType() const { return type; }
};

// Supporting Class: Habitat
class Habitat {
    string description;
public:
    Habitat(const string& description) : description(description) {}
    string getDescription() const { return description; }
};

// Abstract Base Class: Animal
class Animal {
protected:
    string name;
    int age;
    const string species;
    Diet diet;
    Habitat habitat;

public:
    Animal(const string& name, int age, const string& species, const Diet& diet, const Habitat& habitat)
        : name(name), age(age), species(species), diet(diet), habitat(habitat) {
    }

    virtual ~Animal() = default;

    virtual void makeSound() const = 0;
    virtual void eat() const = 0;

    // Final method to display information
    virtual void displayInfo() const final {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Species: " << species << endl;
        cout << "Diet: " << diet.getType() << endl;
        cout << "Habitat: " << habitat.getDescription() << endl;
        cout << "--------------------------" << endl;
    }
};

// Derived Class: Lion
class Lion : public Animal {
public:
    Lion(const string& name, int age, const Diet& diet, const Habitat& habitat)
        : Animal(name, age, "Lion", diet, habitat) {
    }

    void makeSound() const override {
        cout << name << " roars!" << endl;
    }

    void eat() const override {
        cout << name << " eats meat." << endl;
    }
};

// Derived Class: Elephant
class Elephant : public Animal {
public:
    Elephant(const string& name, int age, const Diet& diet, const Habitat& habitat)
        : Animal(name, age, "Elephant", diet, habitat) {
    }

    void makeSound() const override {
        cout << name << " trumpets!" << endl;
    }

    void eat() const override {
        cout << name << " eats plants and fruits." << endl;
    }
};

// Zoo Management System 
class ZooManagementSystem {
    vector<unique_ptr<Animal>> animals;

public:
    void addAnimal(unique_ptr<Animal> animal) {
        animals.push_back(move(animal));
    }

    void makeAllAnimalsSound() const {
        for (const auto& animal : animals) {
            animal->makeSound(); // polymorphism in action
        }
    }

    void displayAllAnimalInfo() const {
        for (const auto& animal : animals) {
            animal->displayInfo();
        }
    }
};

int main() {
    // Create diets and habitats
    Diet carnivore("Carnivore");
    Diet herbivore("Herbivore");
    Habitat savannah("Savannah");
    Habitat jungle("Jungle");

    // Create Zoo Management System instance
    ZooManagementSystem zoo;

    // Add animals
    zoo.addAnimal(make_unique<Lion>("Simba", 2, carnivore, savannah));
    zoo.addAnimal(make_unique<Lion>("Greg", 5, carnivore, savannah));
    zoo.addAnimal(make_unique<Elephant>("Allen", 12, herbivore, jungle));
    zoo.addAnimal(make_unique<Elephant>("Edward", 7, herbivore, jungle));

    // Make all animals sound
    cout << "Animal Sounds:\n";
    zoo.makeAllAnimalsSound();

    // Display info for all animals
    cout << "\nAnimal Information:\n";
    zoo.displayAllAnimalInfo();

    return 0;
}