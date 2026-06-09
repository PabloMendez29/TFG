#include "GETorus.h"


//
// FUNCIÓN: GETorus::GETorus(GLint p, GLint m, GLfloat r0, GLfloat r1)
//
// PROPÓSITO: Crea la figura
//
GETorus::GETorus(GLint p, GLint m, GLfloat r0, GLfloat r1)
{
	int numFaces = 2 * m * p;           // Number of faces
	int numVertices = (m + 1) * (p + 1);  // Number of vertices
	vertices.resize(numVertices);
	indices.resize(numFaces * 3);

	int verticesIndex = 0;
	int indicesIndex = 0;

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= p; j++)
		{
			float pCos = (float)cos(glm::radians(360.0f * j / p));
			float pSin = (float)sin(glm::radians(360.0f * j / p));
			float mCos = (float)cos(glm::radians(360.0f * i / m));
			float mSin = (float)sin(glm::radians(360.0f * i / m));

			vertices[verticesIndex] = { { (r1 + r0 * pCos) * mCos, (r1 + r0 * pCos) * mSin, r0 * pSin}, {pCos * mCos, pCos * mSin, pSin} };
			verticesIndex++;
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < p; j++)
		{
			indices[indicesIndex] = (p + 1) * i + j;
			indices[indicesIndex + 1] = (p + 1) * (i + 1) + j;
			indices[indicesIndex + 2] = (p + 1) * (i + 1) + j + 1;
			indicesIndex += 3;

			indices[indicesIndex] = (p + 1) * i + j;
			indices[indicesIndex + 1] = (p + 1) * (i + 1) + j + 1;
			indices[indicesIndex + 2] = (p + 1) * i + j + 1;
			indicesIndex += 3;
		}
	}
}
