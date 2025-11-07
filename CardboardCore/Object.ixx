export module Object;

import Mathematics;

import std;

namespace Cardboard
{

	export class Transform
	{
	public:
		Vec3 position; // experimental intellisense flagging this despite it being fully functional. Pay no heed.
		Vec3 rotation;
		//Vec3 scale;

		Mat4 getMatrix()
		{
			Mat4 rx = Mat4::rotationX( rotation.x );
			Mat4 ry = Mat4::rotationY( rotation.y );
			Mat4 rz = Mat4::rotationZ( rotation.z );

			Mat4 mt = Mat4::translation( position );

			return rz * ry * rx * mt; // no scaling until needed
		}
	};


	export class Object
	{
	public:
		Object()
		{

		}
		Transform transform;
	protected:
		std::vector<size_t> children;
	};


}