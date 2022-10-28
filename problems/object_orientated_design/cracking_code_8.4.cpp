// design a parking lot using object orientated principles

/*
handle ambiguity
what parking lot for cars, bikes, both?
who for a city downtown, for a farmer in land, for a restaurant, for a company with ads?
how? paid, free?
when is there expiration for the parking or is it taken as long as want

assume we are making a parking lot down town in a city that is free and doesnt expire per spot

core objects
vehicle
car
bicycle
motorbike
parking space
parking lot

relationships
parking lot has many spaces
a parking space has a vehicle, or doesnt

actions
a parking lot can request a parking space
a parking space can admit or emit a vehicle.

a parking lot will have a vector of parking spaces
it will also have a count of free spaces. when a space is requested it will check if one is available
and if so, get the next free space and admit the vehicle.
it will keep track of the last couple spots that were freed so that we can quickly admit cars in constant time
it will also have a map of vehicle to parking index so we can keep track of which vehicle is where

// need a mapping from vehicle to parkign space, as we remove a vehicle, not a space

make flexible for many vehicles. coordinate apis among objects.
*/

#include <deque>
#include <map>
#include <vector>

class Vehicle
{
	public:
	  Vehicle(int vehicle_id);
		int getId()
		{
			return vehicle_id;
		}
	
	private:
	  int vehicle_id;
};

class Car : public Vehicle
{
	
};

class Motorcycle : public Vehicle
{
	
};

class Bicycle : public Vehicle
{
	
};

class ParkingSpace
{
	public:
		ParkingSpace(int id)
		{
			id = id;
			is_occupied = false;
		}
		bool checkIfOccupied()
		{
			return is_occupied;
		}
		void setIsOccupied()
		{
			is_occupied = true;
		}
		void unsetIsOccupied()
		{
			is_occupied = false;
		}
	
	private:
	  int id;
		bool is_occupied;
};

class ParkingLot
{
	public:
	  ParkingLot(int number_of_spaces)
		{
			for (int i = 0; i < number_of_spaces; i++)
			{
				ParkingSpace space(i);
				spaces.push_back(space);
			}
			spaces_free = number_of_spaces;
		}
		
		// checks if we have a free spot, if not returns -1.
		// if we do adds vehicle to spot
		int addVehicle(Vehicle vehicle)
		{
			if (spaces_free < 1 || vehicle_to_space_mapping.find(vehicle.getId()) != vehicle_to_space_mapping.end())
			{
				return -1;
			}
			
			int free_spot = -1;
			if (last_leavers_indices.size() > 0)
			{
				free_spot = last_leavers_indices.front();
				last_leavers_indices.pop_front();
			}
			else
			{
				for (int i = 0; i < spaces.size(); i++)
				{
					if (!spaces[i].checkIfOccupied())
					{
						free_spot = i;
						break;
					}
				}			
			}
			if (free_spot == -1)
			{
				return -1;
			}
			spaces[free_spot].setIsOccupied();
			vehicle_to_space_mapping[vehicle.getId()] = free_spot;
			spaces_free--;
		}
		
		int removeVehicle(Vehicle vehicle)
		{
			if (vehicle_to_space_mapping.find(vehicle.getId()) == vehicle_to_space_mapping.end())
			{
				return -1;
			}
			
			int space_index = vehicle_to_space_mapping[vehicle.getId()];
			spaces[space_index].unsetIsOccupied();
			vehicle_to_space_mapping.erase(vehicle.getId());
			spaces_free++;
			
			if (last_leavers_indices.size() >= last_leavers_to_track)
			{
				last_leavers_indices.pop_back();
			}
			last_leavers_indices.push_front(space_index);
		}
		
		
	
	private:
	  std::vector<ParkingSpace> spaces;
		std::deque<int> last_leavers_indices;
		std::map<int, int> vehicle_to_space_mapping;
		int spaces_free;
		int last_leavers_to_track = 10;
	
	
};

int main()
{
	
}








