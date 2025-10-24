export module Object;

import Mathematics;

import std;


export class Object {
//public:
private:
	std::vector<size_t> children;
};

export class Object2D : public Object {
public:
	Vec2 position;
	float rotation;
	float z;
	virtual void getMatrix() {

	}
};

export class Camera2D : public Object2D {
public:

};