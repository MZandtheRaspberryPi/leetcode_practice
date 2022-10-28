// design a parking lot using object orientated principles

/*
will do parking lot with multiple levels, each level has multiple rows of spots
can park motorcycles, cars, buses
motorcycle, any spot, car single compact or single large spot, bus 5 large spots consecutive and same row.
bus cant park in smaller spots
*/

#include <string>
#include<vector>

class Level {

};

// parking spot by variable for size of spot.
// could do classes for large, compact. but they dont
// need diff behavior
class ParkingSpot
{
	public:
	  ParkingSpot(Level lvl, int r, int n, VehicleSize s);
		bool isAvailable();
		
		// check if spot big enough and available
		bool canFitVehicle(Vehicle vehicle);
		
		bool park(Vehicle v);
		
		int getRow();
		int getSpotNumber();
		
		void removeVehicle();
	  
	
	private:
	  Vehicle vehicle; 
		VehicleSize spotSize;
		int row;
		int spotNumber;
		Level level;
	
	
};

enum VehicleSize
{
	Motorcycle,
	Compact,
	Large
};

class Vehicle
{
	protected:
	  std::vector<ParkingSpot> parkingSpots;
		std::string licensePlate;
		int spotsNeeded;
		VehicleSize size;
		
	public:
	  int getSpotsNeeded() { return spotsNeeded; }
		VehicleSize getVehicleSize { return size; }
		// park vehicle in this spot, among others potentially
		void parkInSpot(ParkingSpot s)
		{
		  parkingSpots.push_back(S);
		}
		
		// remove car from spot, and notify spot that it is gone
		void clearSpots();
		
		// check if spot big enough for vehicle and available. size only. not enough spots
	  virtual bool canFitInSpot(ParkingSpot spot) = 0;
};

class Bus : public Vehicle
{
	public:
	  Bus()
		{
			spotsNeeded = 5;
			size = VehicleSize.Large;
		}
		
		// check if spot is a large, doesnt check num of spots
		bool canFitInSpot(ParkingSpot spot);
};

class Car : public Vehicle
{
	public:
	  Car()
		{
			spotsNeeded = 1;
			size = VehicleSize.Compact;
		}
		// check if spot is a compact, doesnt check num of spots
		bool canFitInSpot(ParkingSpot spot);
};

// parking lot is wrapper for array of levels. hence we can seperate logic to find spots and parking cars
// from broader actions. else, we would need to hold parking spots in double array to map level
// number to list of spots. hence, cleaner.

class Level
{
	public:
	  Level(int flr, int numberSpots);
		int availableSpots() { return availableSpots; }
		// find place to park vehicle, return false if failed
		bool parkVehicle(Vehicle vehicle);
		// when car removed from teh spot, increment available spots
		void spotFreed() { availableSpots++; }
		
	
	private:
	  int floor;
		std::vector<ParkingSpot> spots;
		int availableSpots = 0; // number of free spots
		const static int SPOTS_PER_ROW = 10;
		// park vehicle starting at spot number, and continue until vehicle.spotsneeded
		bool parkStartingAtSpot(int num, vehicle v);
		// find spot to park vehicle, return index of spot or -1 on fail
		int findAvailableSpots(Vehicle vehicle);
};

class ParkingLot
{
	public:
	  ParkingLot();
		// park vehicle in a spot (or multiple spots)
		// return false if failed
		bool parkVehicle(Vehicle vehicle);
		
	private:
	  std::vector<Level> levels;
		const int NUM_LEVELS = 5;
	  
	
	
};

