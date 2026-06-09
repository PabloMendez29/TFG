#include "GECubeMorphing.h"

//
// FUNCIÓN: GECubeAnimated::GECubeAnimated(float s)
//
// PROPÓSITO: Crea la figura
//
struct Face {
	glm::vec3 origin;
	glm::vec3 axisU;
	glm::vec3 axisV;
	glm::vec3 normal;
};

GECubeMorphing::GECubeMorphing(float s, int c)
{
	int numFaces = (c - 1) * (c - 1) * 2 * 6;
	int numVertices = c * c * 6;

	vertices.resize(numVertices);
	indices.resize(numFaces * 3);

	int verticesIndex = 0;
	int indicesIndex = 0;

	Face faces[6] = {
		// +X
		{ {+s, +s, +s}, {0, 0, -2 * s}, {0, -2 * s, 0}, {+1, 0, 0} },
		// -X
		{ {-s, +s, -s}, {0, 0, +2 * s}, {0, -2 * s, 0}, {-1, 0, 0} },
		// +Y
		{ {-s, +s, -s}, {+2 * s, 0, 0}, {0, 0, +2 * s}, {0, +1, 0} },
		// -Y
		{ {-s, -s, +s}, {+2 * s, 0, 0}, {0, 0, -2 * s}, {0, -1, 0} },
		// +Z
		{ {-s, +s, +s}, {+2 * s, 0, 0}, {0, -2 * s, 0}, {0, 0, +1} },
		// -Z
		{ {+s, +s, -s}, {-2 * s, 0, 0}, {0, -2 * s, 0}, {0, 0, -1} }
	};

	for (int f = 0; f < 6; f++) {
		for (int i = 0; i < c; i++) {
			for (int j = 0; j < c; j++) {

				float u = (float) j / (c - 1);
				float v = (float) i / (c - 1);

				glm::vec3 pos1 = faces[f].origin + faces[f].axisV * v + faces[f].axisU * u;

				glm::vec3 norm2 = glm::normalize(pos1);
				glm::vec3 pos2 = norm2 * s;

				vertices[verticesIndex++] = {pos1, faces[f].normal, pos2, norm2, {u, v}};
			}
		}
	}

	for (int f = 0; f < 6; f++) {

		int baseVertex = f * c * c;

		for (int i = 0; i < c - 1; i++) {
			for (int j = 0; j < c - 1; j++) {

				int v0 = baseVertex + i * c + j;
				int v1 = baseVertex + i * c + (j + 1);
				int v2 = baseVertex + (i + 1) * c + j;
				int v3 = baseVertex + (i + 1) * c + (j + 1);

				indices[indicesIndex++] = v0;
				indices[indicesIndex++] = v2;
				indices[indicesIndex++] = v1;

				indices[indicesIndex++] = v1;
				indices[indicesIndex++] = v2;
				indices[indicesIndex++] = v3;
			}
		}
	}


}
