#include "Item.h"

using namespace std;
using namespace bangtal;

ObjectPtr Item::create(const string& image, ScenePtr scene, int x, int y, bool shown)
{
	auto object = ObjectPtr(new Item(image, scene, x, y, shown));
	Object::add(object);

	return object;
}

Item::Item(const string& image, ScenePtr scene, int x, int y, bool shown) : Object(image, scene, x, y, shown)
{
}

bool Item::onMouse(int x, int y, MouseAction action)
{
	if (!Object::onMouse(x, y, action)) {
		pick();
	}

	return true;
}


