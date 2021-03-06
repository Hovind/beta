#pragma once

#include <GL/glew.h>

namespace Engine {
	struct Position {
		float
			x,
			y;
	};
	struct Color {
		Color(): r(255), g(255), b(255), a(255) {}
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a): r(r), g(g), b(b), a(a) {}
		GLubyte
			r,
			g,
			b,
			a;
	};

	struct UV {
		float
			u,
			v;
	};

	struct Vertex {
		Position position;
		Color color;
		UV uv;

		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
	};
}