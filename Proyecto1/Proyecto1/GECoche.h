#pragma once

#include "GEObject.h"
#include "GEPiece.h"
#include "GETexture.h"
#include "GEMaterial.h"

//
// CLASE: GECoche
//
// DESCRIPCIÓN: Clase que almacena la malla del coche
//
class GECoche : public GEObject {
private:
	GETexture** textures;
	GEMaterial* mtl;
	GEPiece* pieces[33];
	int indice;

public:
	GECoche(GEGraphicsContext* gc, uint32_t indice);
	~GECoche();
	virtual int GetNumPieces();
	virtual GEPiece* GetPiece(int i);
};

