export module Mathematics;
import std;
import <stdint.h>;
import <typeinfo>;
import <cmath>;

export
template <uint8_t n>
class Vec {
public:
	Vec() : data{ 0 } {}
	Vec(float v) : data (v) {}
	Vec(const std::array<float, n>& v) {
		for (int8_t i = 0; i != v.size(); i += 1) {
			data[i] = v[i];
		}
	}
	float& operator[] (uint8_t i) {
		return data[i];
	}
	float* get() {
		return &data[0];
	}
//protected:
	float data[n];
};

export class Vec2 : public Vec<2> {
public:
	using Vec::Vec;
	float& x = data[0];
	float& y = data[1];
};

export class Vec3 : public Vec<3> {
public:
	using Vec::Vec;
	float& x = data[0];
	float& y = data[1];
	float& z = data[2];
};

export class Vec4 : public Vec<4> {
public:
	using Vec::Vec;
	float& x = data[0];
	float& y = data[1];
	float& z = data[2];
	float& w = data[3];
};

export
template <uint8_t n>
class Mat {
public:
	Mat(float v) : data{ Vec<n>(v)} {}
	Mat() { Mat(0); }
	Mat(const std::array<Vec<n>, n>& v) {
		for (int8_t i = 0; i != v.size(); i += 1) {
			data[i] = v[i];
		}
	}
	Vec<n>& operator[] (uint8_t i) {
		return data[i];
	}
	float *get() {
		return data[0].get();
	}
//protected:
	Vec<n> data[n];
};

export class Mat4 : public Mat<4> {
public:
	using Mat::Mat;
	static Mat4 identity() {
		return Mat4(std::array<Vec<4>, 4>{
			Vec<4>({ 1, 0, 0, 0 }),
			Vec<4>({ 0, 1, 0, 0 }),
			Vec<4>({ 0, 0, 1, 0 }),
			Vec<4>({ 0, 0, 0, 1 })
		});
	}
	static Mat4 simpleOrtho(float x, float y, float z) {
		return Mat4(std::array<Vec<4>, 4>{
			Vec<4>({1 / x, 0, 0, 0}),
			Vec<4>({0, 1 / y, 0, 0 }),
			Vec<4>({0, 0, 1 / z, 0 }),
			Vec<4>({0, 0, 0, 1     })
		});
	}
	static Mat4 rotationX(float a) {
		return Mat4(std::array<Vec<4>, 4>{
			Vec<4>({ 1, 0, 0, 0 }),
			Vec<4>({ 0, cosf(a), -sinf(a), 0}),
			Vec<4>({ 0, sinf(a), cosf(a), 0}),
			Vec<4>({ 0, 0, 0, 1 })
		});
	}
	static Mat4 rotationY(float a) {
		return Mat4(std::array<Vec<4>, 4>{
			Vec<4>({ cosf(a), 0, sinf(a), 0}),
			Vec<4>({ 0, 1, 0, 0 }),
			Vec<4>({ -sinf(a), 0, cosf(a), 0}),
			Vec<4>({ 0, 0, 0, 1 })
		});
	}
	static Mat4 rotationZ(float a) {
		return Mat4(std::array<Vec<4>, 4>{
			Vec<4>({ cosf(a), -sinf(a), 0, 0}),
			Vec<4>({ sinf(a), cosf(a), 0, 0}),
			Vec<4>({ 0, 0, 1, 0 }),
			Vec<4>({ 0, 0, 0, 1 })
		});
	}
	static Mat4 translate(Vec3 t) {
		return Mat4(std::array<Vec<4>, 4>{
			Vec<4>({ 1, 0, 0, 0 }),
			Vec<4>({ 0, 1, 0, 0 }),
			Vec<4>({ 0, 0, 1, 0 }),
			Vec<4>({ t.x, t.y, t.z, 1 })
		});
	}
	Mat4 operator * (Mat4 b) {
		Mat4 result(0);
		//static int hasPrintedOut = 0;
		//hasPrintedOut++;

		for (int i = 0; i != 4; ++i) {
			for (int j = 0; j != 4; ++j) {
				for (int k = 0; k != 4; ++k) {
					result[i][j] += this->data[i][k] * b[k][j];
					//if (hasPrintedOut == 100)
					//	std::cout << this->data[i][k] << " " << b[k][j] << std::endl;
				}
			}

			//std::cout << std::endl;
		}
		//std::cout << "\n" << std::endl;

		return result;
	}
};