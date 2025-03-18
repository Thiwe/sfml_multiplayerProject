#pragma once
#include <queue>
#include <vector>
#include <functional>
#include "Entity.h" // Includes baseProjectile definition

template <typename objectClassName>
class ObjectPool
{
public:
	// Constructor with factory function to create objects
	//reminder to self: essentially a wrapper 
	// that gives you a consistent way to handle 
	// different types of functions. 
	// std::function< typename (parameters accepted into fucntion) >
	//store a probably lambda function that will call new "projectileclass"
	ObjectPool(std::function<objectClassName* ()> factory, size_t initialSize = 10) :
		factory(factory) {
		initialize(initialSize);
	}

	~ObjectPool() {
		// Clean up all objects in the pool
		while (!available.empty()) {
			delete available.front();
			available.pop();
		}

		// Clean up any objects still in use
		for (auto obj : inUse) {
			delete obj;
		}
	}

	//create ibnitieal ibjects
	void initialize(size_t count) {
		for (size_t i = 0; i < count; i++) {
			objectClassName* obj = factory();
			obj->deactivate();
			available.push(obj);
		}
	}

	// Get an object from the pool OR create a new one
	objectClassName* getObjectFromPool() 
	{
		objectClassName* object = nullptr;

		if (available.empty()) {
			//lambda function stored in factory called and 
			// creates a new bulletprojectileclass
			object = factory(); 
		}
		else {
			object = available.front();
			available.pop();
		}

		object->activate();
		inUse.push_back(object);
		return object;
	}

	// Return an object to the pool
	void returnObjectToPool(objectClassName* object) {
		// Find the object in our in-use list
		auto it = std::find(inUse.begin(), inUse.end(), object);
		if (it != inUse.end()) {
			// Remove from in-use list
			inUse.erase(it);

			// Reset and return to available pool
			object->deactivate();
			available.push(object);
		}
	}

	// Utility methods
	size_t availableCount() const { return available.size(); }
	size_t inUseCount() const { return inUse.size(); }

private:
	std::queue<objectClassName*> available;          // Queue of available objects
	std::vector<objectClassName*> inUse;             // List of objects currently in use
	std::function<objectClassName* ()> factory;       // Function to create new objects
};

