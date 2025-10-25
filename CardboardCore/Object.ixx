export module Object;

import Mathematics;

import std;

export class Transform {
public:
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;

	Transform() :
	position(0,0,0), rotation(0,0,0), scale(1,1,1) {

	}

	Mat4 getMatrix() {
		Mat4 m = Mat4::translate(position);
		m = m * Mat4::rotateZ(rotation.z);
		m = m * Mat4::rotateY(rotation.y);
		m = m * Mat4::rotateX(rotation.x);
		m = m * Mat4::scale(scale);

		return m;
	}
};


export class Object {
public:
	Object() {

	}
	Transform transform;
protected:
	std::vector<size_t> children;
};
