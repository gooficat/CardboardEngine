export module Mesh;

import std;
import OpenGL;
import Texture;
import Shader;
import Mathematics;

import <cstddef>;

namespace Cardboard
{
	export class Vertex
	{
	public:
		Vec3 position;
		Vec2 tex_coord;
		Vec3 normal;
	};

	//export class TextureVertex : public Vertex
	//{
	//public:

	//};

	export class Mesh
	{
	public:
		Mesh( const std::vector<Vertex>& vertices,
			  const std::vector<GL::Uint>& indices )
			:
			indexCount( indices.size() )
		{
			generate( vertices, indices );
		}

		virtual ~Mesh()
		{
			GL::deleteVertexArrays( 1, &VAO );

			GL::deleteBuffers( 1, &VBO );
			GL::deleteBuffers( 1, &EBO );

			//GL::deleteTextures(1, )
		}

		virtual void draw( Shader& shader )
		{
			GL::bindVertexArray( VAO );
			GL::drawElements( 0x0004, indexCount, 0x1405, 0 );
		}
	protected:
		GL::Uint VAO, VBO, EBO;
		virtual void generate( const std::vector<Vertex>& vertices, const std::vector<GL::Uint>& indices )
		{
			GL::genVertexArrays( 1, &VAO );
			GL::genBuffers( 1, &VBO );
			GL::genBuffers( 1, &EBO );

			GL::bindVertexArray( VAO );
			GL::bindBuffer( 0x8892, VBO );
			GL::bindBuffer( 0x8893, EBO );
			GL::bufferData( 0x8892, vertices.size() * sizeof( Vertex ), vertices.data(), 0x88E4 );
			GL::bufferData( 0x8893, indices.size() * sizeof( GL::Uint ), indices.data(), 0x88E4 );

			GL::enableVertexAttribArray( 0 );
			GL::vertexAttribPointer( 0, 3, 0x1406, 0, sizeof( Vertex ), ( void* ) 0 );

			GL::enableVertexAttribArray( 1 );
			GL::vertexAttribPointer( 1, 2, 0x1406, 0, sizeof( Vertex ), ( void* ) offsetof( Vertex, Vertex::tex_coord ) );

			GL::enableVertexAttribArray( 2 );
			GL::vertexAttribPointer( 2, 3, 0x1406, 0, sizeof( Vertex ), ( void* ) offsetof( Vertex, Vertex::normal ) );

		}
		GL::Sizei indexCount;
	private:
	};

}