// an animal shelter holds only dogs cats, operates on strictly first in first out basis
// people must select oldest based on arrival timea of all animals at shelter, or select whether
// prefer cat or dog and will receive oldest animal of that type
// can't select which specific animal want 
// create data structure to maintain this system and implement operations such as enqueue, dequeueAny, dequeueDog, and dequeueCat.
// may use built in linked list structure.

// could maintain single queue, but then dequeueDog/dequeueCat would require iteration through queue to find first dog/cat
// would increase complexity, decrease efficiency
// alternatively, use seperate queues for dogs/cats, and place em w/in wrapper class animal queue.
// we store timestamp to mark when each animal enqueued. when we call dequeueAny, peek at heads of both dog/cat queue and return oldest

#include<queue>
#include<string>
#include<stdio.h>

class Animal{
	int order;

public:
	std::string name;

	Animal(std::string name): name(name) {
	}

	std::string getName() {
		return name;
	}

	void setOrder(int ord) {
		order = ord;
	}
	
	int getOrder() {
		return order;
	}
	
	bool isOlderThan(Animal* a) {
		return order < a->getOrder();
	}

	virtual std::string whatAnimal() = 0;
	
};

class Dog : public Animal {
	std::string animalType = std::string("Dog");
	std::string whatAnimal() {
		return animalType;
	}
public:
	Dog(std::string n) : Animal{ n } {

	}

};

class Cat : public Animal {
	std::string animalType = std::string("Cat");

	std::string whatAnimal() {
		return animalType;
	}
public:
	Cat(std::string n) : Animal{ n } {
	}
};


class AnimalQueue {
	std::queue<Dog*> dogs = std::queue<Dog*>{};
	std::queue<Cat*> cats = std::queue<Cat*>{};
	int order = 0; // acts as timestamp
	
public:
	void enqueue(Animal* a) {
		// order used as timestamp, so we can compare insertion order of dog to cat
		a->setOrder(order);
		order++;
		
		if (a->whatAnimal() == std::string("Dog")) dogs.push((Dog*)a);
		else if (a->whatAnimal() == std::string("Cat")) cats.push((Cat*)a);
	}
	
	Animal* dequeueAny() {
		// look at tops of dog and cat queues, and pop the stack w/ the oldest value
		if (dogs.size() == 0) {
			Cat* c = cats.back();
			cats.pop();
			return c;
		}
		else if (cats.size() == 0) {
			Dog* d = dogs.back();
			dogs.pop();
			return d;
		}
		
		Dog* dog = dogs.back();
		Cat* cat = cats.back();
		if (dog->isOlderThan(cat)) {
			dogs.pop();
			return dog;
		}
		else {
			cats.pop();
			return cat;
		}
	
	}

};


int main() {
	
	std::string animalNames[] = { std::string{"jack"}, std::string{"jeff"}, std::string{"john"},
								std::string{"judy"}, std::string{"jethero"}, std::string{"june"},
								std::string{"\0"} };
	std::string* animalNamesPtr = animalNames;
	AnimalQueue animals = AnimalQueue{};
	
	while (*animalNamesPtr != std::string{ "\0" }) {
		Dog* d = new Dog{*animalNamesPtr };
		Cat* c = new Cat{*animalNamesPtr };
		animals.enqueue(d);
		animals.enqueue(c);
		animalNamesPtr++;
	}
	Animal* a = animals.dequeueAny();
	std::string name = a->getName();
	printf("%s\n", name.data());
	// need to do mem mgmt
}