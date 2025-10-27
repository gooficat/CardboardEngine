export module Object;

import Mathematics;

import std;

export class Transform {
public:
	Vec3 position; // experimental intellisense flagging this despite it being fully functional. Pay no heed.
	Vec3 rotation;
	Vec3 scale;

	Transform() :
		position({ 0, 0, 0 }), rotation({ 0, 0, 0 }), scale({ 1, 1, 1 }) {

	}

	Mat4 getMatrix() {
		Mat4 m = Mat4::identity();
		//m = m * Mat4::translate(position);
		m = m * Mat4::rotationX(rotation.x);
		//m = m * Mat4::rotationY(rotation.y);
		//m = m * Mat4::rotationZ(rotation.z);
		//m = ;
		//m = Mat4::scale(scale) * m;

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
