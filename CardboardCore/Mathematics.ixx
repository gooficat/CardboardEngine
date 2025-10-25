export module Mathematics;
import std;

export class Vec2 {
public:
	float x;
	float y;
};

export class Vec3 {
public:
	float x;
	float y;
	float z;
};

export struct Mat4 {
	float	x1, y1, z1, w1,
			x2, y2, z2, w2,
			x3, y3, z3, w3,
			x4, y4, z4, w4;

	static Mat4 identity() {
		return Mat4{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
	}

	static Mat4 orthographic(float left, float right, float top, float bottom, float far, float near) {
		return Mat4 {
			2.0f/(right-left), 0, -(right+left)/(right-left),
			0, 2.0f/(top-bottom), 0, -(top+bottom)/(top-bottom),
			0, 0, -2.0f/(far-near), 0, -(far+near)/(far-near),
			0, 0, 0, 1
		};
	}
	static Mat4 simpleOrtho(float x, float y, float z) {
		return Mat4 {
			1 / x, 0, 0, 0,
			0, 1 / y, 0, 0,
			0, 0, 1 / z, 0,
			0, 0, 0, 1
		};
	}

	static Mat4 translate(Vec3 t) {
		return Mat4 {
			1, 0, 0, t.x,
			0, 1, 0, t.y,
			0, 0, 1, t.z,
			0, 0, 0, 1
		};
	}

	static Mat4 rotateX(float a) {
		float ca = std::cosf(a);
		float sa = std::sinf(a);

		return Mat4 {
			1, 0, 0, 0,
			0,ca,-sa,0,
			0,sa,ca, 0,
			0, 0, 0, 1
		};
	}
	static Mat4 rotateY(float a) {
		float ca = std::cosf(a);
		float sa = std::sinf(a);

		return Mat4{
			ca,0,sa, 0,
			0, 1, 0, 0,
			-sa,0,ca,0,
			0, 0, 0, 1
		};
	}
	static Mat4 rotateZ(float a) {
		float ca = std::cosf(a);
		float sa = std::sinf(a);

		return Mat4{
			ca,-sa,0,0,
			sa,ca,0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}
	static Mat4 scale(Vec3 s) {
		return Mat4 {
			s.x, 0, 0, 1,
			0, s.y, 0, 1,
			0, 0, s.z, 1,
			0, 0, 0, 1
		};
	}
	Mat4 operator*(Mat4 b) {
		return Mat4 {
			x1 * b.x1, y1 * b.x2, z1 * b.x3, w1 * b.x4,
			x2 * b.y1, y2 * b.y2, z2 * b.y3, w2 * b.y4,
			x3 * b.z1, y3 * b.z2, z3 * b.z3, w3 * b.z4,
			x4 * b.w1, y4 * b.w2, z4 * b.w3, w4 * b.w4
		};
	}
};