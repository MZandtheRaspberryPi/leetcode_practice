/*

An animal shelter holds only dogs and cats, and operates on a strictly FIFO basis.
people must either adopt oldest based on arrival time of all animals at the shelter,
or they can select whether prefer a dog or a cat and they will receive oldest animal of that type.
they cannot select which specfic animal they would like.

create data structures to maintain system and implement operations such as enqueue
dequeueAny, dequeueDog and dequeueCat. You may use built-in Linked List datastructure.

Use one linked list for cats, one for dogs. keep track of head and tail.
animal type has name, as well as order and functions to get/set order.
cat and dog inherit from animal.

Node has animal, and next.

animal shelter class has functions, map of linkedl ist info.
enqueue assigns an order to animal, increments order of our class. puts into cat or dog list depending on animal type.
deque cat returns last cat. dequeue dog returns last dog.
dequeue any compares last dog vs last cat age and returns older.


*/

#include <map>
#include <stdio.h>
#include <string>

enum AnimalType
{
	CAT,
	DOG
};

class Animal
{
	public:
	  Animal(std::string name, AnimalType type);
	  int getOrder();
		void setOrder(int order);
		AnimalType getType();
		std::string getName();
	private:
	  AnimalType type_;
	  int order_;
		std::string name_;
};

Animal::Animal(std::string name, AnimalType type) : name_(name), type_(type)
{
}

std::string Animal::getName()
{
	return name_;
}

void Animal::setOrder(int order)
{
	order_ = order;
}

int Animal::getOrder()
{
	return order_;
}

AnimalType Animal::getType()
{
	return type_;
}

struct AnimalNode
{
	Animal* animal;
	AnimalNode* next;
};

struct AnimalNodeListInfo
{
	AnimalNode* head;
	AnimalNode* tail;
};


class AnimalShelter
{
	public:
	  AnimalShelter();
		~AnimalShelter();
	  void enqueue(Animal& animal);
		Animal dequeueAny();
		Animal dequeueDog();
		Animal dequeueCat();
	
	private:
	  Animal popFromLL(AnimalNode*& head, AnimalNode*& tail);
	  std::map<AnimalType, AnimalNodeListInfo> linked_list_info_by_animal_type_;
		int order_;
};

AnimalShelter::AnimalShelter()
{
	AnimalNodeListInfo ll_info{};
	ll_info.head = nullptr;
	ll_info.tail = nullptr;
	linked_list_info_by_animal_type_[AnimalType::CAT] = ll_info;
	linked_list_info_by_animal_type_[AnimalType::DOG] = ll_info;
	
	order_ = 0;
}

AnimalShelter::~AnimalShelter()
{
	AnimalNodeListInfo& cat_ll_info = linked_list_info_by_animal_type_[AnimalType::CAT];
	AnimalNodeListInfo& dog_ll_info = linked_list_info_by_animal_type_[AnimalType::DOG];
	
	AnimalNode* runner = cat_ll_info.head;
	AnimalNode* prev = runner;
	while (runner != nullptr)
	{
		prev = runner;
		runner = runner->next;
		delete prev;
	}
	
	runner = dog_ll_info.head;
	prev = runner;
	while (runner != nullptr)
	{
		prev = runner;
		runner = runner->next;
		delete prev;
	}
	
	
}


Animal AnimalShelter::popFromLL(AnimalNode*& head, AnimalNode*& tail)
{
	AnimalNode* animal_node = head;
	Animal animal = *animal_node->animal;
	
	if (head == tail)
	{
		head = tail = nullptr;
	}
	else
	{
		head = head->next;
	}
	
	delete animal_node;
	return animal;
}

void AnimalShelter::enqueue(Animal& animal)
{
	animal.setOrder(order_);
	order_++;
	
	AnimalNode* animal_node = new AnimalNode{};
	animal_node->animal = &animal;
	animal_node->next = nullptr;
	
	AnimalNodeListInfo& animal_list_info = linked_list_info_by_animal_type_[animal.getType()];
	
	if (animal_list_info.head == nullptr && animal_list_info.tail == nullptr)
	{
		animal_list_info.head = animal_node;
		animal_list_info.tail = animal_node;
	}
	else
	{
		// else put to back of list.
		animal_list_info.tail->next = animal_node;
		animal_list_info.tail = animal_node;
	}
}

Animal AnimalShelter::dequeueAny()
{ 
	AnimalNodeListInfo& cat_ll_info = linked_list_info_by_animal_type_[AnimalType::CAT];
	AnimalNodeListInfo& dog_ll_info = linked_list_info_by_animal_type_[AnimalType::DOG];
	
	if (cat_ll_info.head != nullptr && dog_ll_info.head != nullptr)
	{
		if (cat_ll_info.head->animal->getOrder() < dog_ll_info.head->animal->getOrder())
		{
			return popFromLL(cat_ll_info.head, cat_ll_info.tail);
		}
		else
		{
			return popFromLL(dog_ll_info.head, dog_ll_info.tail);
		}
	}
	else if (cat_ll_info.head != nullptr)
	{
		return popFromLL(cat_ll_info.head, cat_ll_info.tail);
	}
	else if (dog_ll_info.head != nullptr)
	{
		return popFromLL(dog_ll_info.head, dog_ll_info.tail);
	}
	else
	{
		return Animal("blanky", AnimalType::CAT);
	}
}

Animal AnimalShelter::dequeueDog()
{
	
	AnimalNodeListInfo& dog_ll_info = linked_list_info_by_animal_type_[AnimalType::DOG];
	if (dog_ll_info.head == nullptr)
	{
		return Animal("blanky", AnimalType::DOG);
	}
	else
	{
		return popFromLL(dog_ll_info.head, dog_ll_info.tail);
	}
}

Animal AnimalShelter::dequeueCat()
{
	
	AnimalNodeListInfo& cat_ll_info = linked_list_info_by_animal_type_[AnimalType::CAT];
	if (cat_ll_info.head == nullptr)
	{
		return Animal("blanky", AnimalType::CAT);
	}
	else
	{
		return popFromLL(cat_ll_info.head, cat_ll_info.tail);
	}
}



int main() {

  AnimalShelter shelter = AnimalShelter();
	Animal skitty = Animal("skitty", AnimalType::CAT);
	Animal moofi = Animal("moofi", AnimalType::CAT);
	Animal slip = Animal("slip", AnimalType::CAT);
	Animal doofus = Animal("doofus", AnimalType::CAT);
	Animal fido = Animal("fido", AnimalType::DOG);
	Animal foofoo = Animal("foofoo", AnimalType::DOG);
	Animal ruff = Animal("ruff", AnimalType::DOG);
	Animal smoodo = Animal("smoodo", AnimalType::DOG);
	shelter.enqueue(skitty);
	shelter.enqueue(moofi);
	shelter.enqueue(ruff);
	Animal adopted_animal = shelter.dequeueAny();
	printf("got %s\n", adopted_animal.getName().c_str());
	adopted_animal = shelter.dequeueAny();
	printf("got %s\n", adopted_animal.getName().c_str());
	adopted_animal = shelter.dequeueAny();
	printf("got %s\n", adopted_animal.getName().c_str());
	shelter.enqueue(smoodo);
	shelter.enqueue(foofoo);
	shelter.enqueue(slip);
	adopted_animal = shelter.dequeueCat();
	printf("got %s\n", adopted_animal.getName().c_str());
	adopted_animal = shelter.dequeueAny();
	printf("got %s\n", adopted_animal.getName().c_str());
	adopted_animal = shelter.dequeueAny();
	printf("got %s\n", adopted_animal.getName().c_str());
	
	
  
}