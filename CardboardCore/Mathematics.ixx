export module Mathematics;

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

	static Mat4 orthographic(float left, float right, float top, float bottom, float back, float front) {
		return Mat4 {
			2.0f / (right - left), 0, 0, -(right + left) / (right - left),
			0, 2.0f / (top - bottom), 0, -(top + bottom) / (top + bottom),
			0, 0, -2.0f / (front - back), -(front + back) / (front - back),
			0, 0, 0, 1
		};
	}

	void translate(Vec3 t) {

	}

	void rotate(float angle) {
		
	}
};