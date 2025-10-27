export module Mathematics;
import std;
import <stdint.h>;
import <typeinfo>;
import <cmath>;

export
struct Vec2 {
	float x, y;
};


export
struct Vec3 {
	float x, y, z;
};


export
struct Mat4 {
	
	static Mat4 identity() {
		return Mat4{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}
	static Mat4 rotationX(float a) {
		float ca = cosf(a);
		float sa = sinf(a);
		return Mat4{
			1, 0, 0, 0,
			0,ca,sa, 0,
			0,sa,ca, 0,
			0, 0, 0, 1
		};
	}
	static Mat4 rotationY(float a) {
		float ca = cosf(a);
		float sa = sinf(a);
		return Mat4{
			ca,0,-sa,0,
			0, 1, 0, 0,
			sa,0, ca,0,
			0, 0, 0, 1
		};
	}
	static Mat4 rotationZ(float a) {
		float ca = cosf(a);
		float sa = sinf(a);
		return Mat4{
			ca,sa,0, 0,
			-sa,ca,0,0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}
	static Mat4 translation(Vec3 t) {
		return Mat4{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			t.x, t.y, t.z, 1
		};
	}
	static Mat4 scaling(Vec3 s) {
		return Mat4{
			s.x,0,0, 0,
			0,s.y,0, 0,
			0, 0,s.z,0,
			0, 0, 0, 1
		};
	}
	Mat4 operator * (Mat4& m) {
		Mat4 result;

		for (int i = 0; i != 4; ++i) {
			for (int j = 0; j != 4; ++j) {
				result[j * 4 + i] = 0;
				for (int k = 0; k != 4; ++k) {
					result[j * 4 + i] += data[j * 4 + k] * m[k * 4 + i];
				}
			}
		}

		return result;
	}
	static Mat4 simpleOrtho(float x, float y, float z) {
		return Mat4{
			1/x,0,0, 0,
			0,1/y,0, 0,
			0,0, 1/z,0,
			0, 0, 0, 1
		};
	}
	float& operator [] (uint8_t i) {
		return data[i];
	}
	float data[4 * 4];
};