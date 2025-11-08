export module SpriteRenderer;

import std;

import OpenGL;
import Texture;
import Mathematics;
import Shader;

namespace Cardboard
{

	export struct Sprite
	{
		Vec2 position;
		Vec2 size;
		Texture* texture;

		Sprite( Vec2 position, Vec2 size, Texture* texture ) :
			position( position ),
			size( size ),
			texture( texture )
		{

		}
	};

	export class SpriteRenderer
	{
	public:
		Shader shader;
		SpriteRenderer() :
			shader(
				"../CardboardCore/SpriteVertexShader.glsl", "../CardboardCore/SpriteFragmentShader.glsl"
			)
		{
			generateMesh();
		}

		~SpriteRenderer()
		{
			GL::deleteVertexArrays( 1, &VAO );
			GL::deleteBuffers( 1, &VBO );
			GL::deleteBuffers( 1, &EBO );
		}

		void drawSprite( Sprite& sprite )
		{
			shader.use();
			shader.setVec2( "translation", sprite.position );
			shader.setVec2( "scale", sprite.size );
			GL::bindVertexArray( VAO );
			sprite.texture->use( shader );
			GL::drawElements( 0x0004, 6, 0x1405, 0 );
		}
	private:
		GL::Uint VAO, VBO, EBO;

		void generateMesh()
		{
			std::vector<Vec2> vertices = {
				{0, 0}, {1, 0},
				{1, 1}, {0, 1}
			};
			std::vector<GL::Uint> indices {
				0, 1, 2,
				0, 2, 3
			};

			GL::genVertexArrays( 1, &VAO );
			GL::genBuffers( 1, &VBO );
			GL::genBuffers( 1, &EBO );

			GL::bindVertexArray( VAO );
			GL::bindBuffer( 0x8892, VBO );
			GL::bindBuffer( 0x8893, EBO );
			GL::bufferData( 0x8892, vertices.size() * sizeof( Vec2 ), vertices.data(), 0x88E4 );
			GL::bufferData( 0x8893, indices.size() * sizeof( GL::Uint ), indices.data(), 0x88E4 );

			GL::enableVertexAttribArray( 0 );
			GL::vertexAttribPointer( 0, 2, 0x1406, 0, sizeof( Vec2 ), ( void* ) 0 );
		}
	};
}