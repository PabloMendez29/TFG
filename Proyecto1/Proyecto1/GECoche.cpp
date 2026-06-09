 #include "GECoche.h"
#include "GECoche_pieces.h"
#include "GEObject.h"
#include "GEPiece.h"
#include "GETexture.h"
#include "GEMaterial.h"

//
// FUNCIÓN: GECoche::GECoche(GEGraphicsContext* gc, uint32_t indice)
//
// PROPÓSITO: Construye las piezas del coche y les asigna su material y textura
//
GECoche::GECoche(GEGraphicsContext* gc, uint32_t indice)
{

	this->indice = indice;

	mtl = new GEMaterial[7];
	mtl[0].Ka = glm::vec3(0.0f, 0.0f, 0.0f); //Negro
	mtl[0].Kd = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[0].Ks = glm::vec3(0.1f, 0.1f, 0.1f);
	mtl[0].Shininess = 8.0f;

	mtl[1].Ka = glm::vec3(0.05f, 0.05f, 0.05f); //Gris oscuro
	mtl[1].Kd = glm::vec3(0.2f, 0.2f, 0.2f);
	mtl[1].Ks = glm::vec3(0.3f, 0.3f, 0.3f);
	mtl[1].Shininess = 16.0f;

	mtl[2].Ka = glm::vec3(0.2f, 0.2f, 0.2f); //Gris claro
	mtl[2].Kd = glm::vec3(0.5f, 0.5f, 0.5f);
	mtl[2].Ks = glm::vec3(0.4f, 0.4f, 0.4f);
	mtl[2].Shininess = 24.0f;

	mtl[3].Ka = glm::vec3(0.4f, 0.4f, 0.4f); //Gris muy claro
	mtl[3].Kd = glm::vec3(0.8f, 0.8f, 0.8f);
	mtl[3].Ks = glm::vec3(0.6f, 0.6f, 0.6f);
	mtl[3].Shininess = 32.0f;

	mtl[4].Ka = glm::vec3(0.6f, 0.6f, 0.6f); //Blanco
	mtl[4].Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	mtl[4].Ks = glm::vec3(1.0f, 1.0f, 1.0f);
	mtl[4].Shininess = 64.0f;

	mtl[5].Ka = glm::vec3(0.1f, 0.0f, 0.0f); //Rojo carmesi
	mtl[5].Kd = glm::vec3(0.6f, 0.05f, 0.1f);
	mtl[5].Ks = glm::vec3(0.5f, 0.2f, 0.2f);
	mtl[5].Shininess = 32.0f;

	mtl[6].Ka = glm::vec3(0.0f, 0.1f, 0.15f); //Azul celeste
	mtl[6].Kd = glm::vec3(0.4f, 0.7f, 1.0f);
	mtl[6].Ks = glm::vec3(0.6f, 0.8f, 1.0f);
	mtl[6].Shininess = 48.0f;


	textures = new GETexture*[7];

	textures[0] = new GETexture(gc, "textures/Blanco.jpg");
	textures[1] = new GETexture(gc, "textures/Llanta.jpg");
	textures[2] = new GETexture(gc, "textures/Matricula.jpg");
	textures[3] = new GETexture(gc, "textures/Logo.jpg");
	textures[4] = new GETexture(gc, "textures/FaroTrasero.jpg");
	textures[5] = new GETexture(gc, "textures/FaroLateral.jpg");
	textures[6] = new GETexture(gc, "textures/Agujeros.jpg");


	pieces[0] = new GECoche_0(indice); //Interior
	pieces[0]->setTexture(textures[1]);
	pieces[0]->setMaterial(mtl[1]);

	pieces[1] = new GECoche_1(indice); //Carroceria Interior
	pieces[1]->setTexture(textures[0]);
	pieces[1]->setMaterial(mtl[0]);

	pieces[2] = new GECoche_2(indice); //Cosos negros delante
	pieces[2]->setTexture(textures[0]);
	pieces[2]->setMaterial(mtl[0]);

	pieces[3] = new GECoche_3((uint32_t) 4); //Rueda Atras Der
	pieces[3]->setTexture(textures[0]);
	pieces[3]->setMaterial(mtl[2]);

	pieces[4] = new GECoche_4((uint32_t) 3); //Rueda Adelante Der
	pieces[4]->setTexture(textures[0]);
	pieces[4]->setMaterial(mtl[2]);

	pieces[5] = new GECoche_5(indice); //Faros traseros
	pieces[5]->setTexture(textures[4]);
	pieces[5]->setMaterial(mtl[1]);

	pieces[6] = new GECoche_6(indice); //Ventanas
	pieces[6]->setTexture(textures[0]);
	pieces[6]->setMaterial(mtl[6]);

	pieces[7] = new GECoche_7(indice); //Coso arriba
	pieces[7]->setTexture(textures[0]);
	pieces[7]->setMaterial(mtl[2]);

	pieces[8] = new GECoche_8(indice); //Marcos Ventanas
	pieces[8]->setTexture(textures[0]);
	pieces[8]->setMaterial(mtl[1]);

	pieces[9] = new GECoche_9(indice); //Lineas superiores
	pieces[9]->setTexture(textures[0]);
	pieces[9]->setMaterial(mtl[3]);

	pieces[10] = new GECoche_10(indice); //Carroceria principal
	pieces[10]->setTexture(textures[0]);
	pieces[10]->setMaterial(mtl[5]);

	pieces[11] = new GECoche_11(indice); //Espejos
	pieces[11]->setTexture(textures[0]);
	pieces[11]->setMaterial(mtl[6]);

	pieces[12] = new GECoche_12(indice); //Faros laterales
	pieces[12]->setTexture(textures[5]);
	pieces[12]->setMaterial(mtl[4]);

	pieces[13] = new GECoche_13(indice); //Manillares y resto
	pieces[13]->setTexture(textures[0]);
	pieces[13]->setMaterial(mtl[4]);

	pieces[14] = new GECoche_14(indice); //Retrovisores
	pieces[14]->setTexture(textures[0]);
	pieces[14]->setMaterial(mtl[1]);

	pieces[15] = new GECoche_15(indice); //Carroceria inferior
	pieces[15]->setTexture(textures[1]);
	pieces[15]->setMaterial(mtl[1]);

	pieces[16] = new GECoche_16(indice); //Cosos negros
	pieces[16]->setTexture(textures[0]);
	pieces[16]->setMaterial(mtl[0]);

	pieces[17] = new GECoche_17(indice); //Matricula delantera
	pieces[17]->setTexture(textures[2]);
	pieces[17]->setMaterial(mtl[4]);

	pieces[18] = new GECoche_18(indice); //Matricula trasera
	pieces[18]->setTexture(textures[2]);
	pieces[18]->setMaterial(mtl[4]);

	pieces[19] = new GECoche_19(indice); //Logo trasero
	pieces[19]->setTexture(textures[3]);
	pieces[19]->setMaterial(mtl[4]);

	pieces[20] = new GECoche_20(indice); //Tubos de escape
	pieces[20]->setTexture(textures[0]);
	pieces[20]->setMaterial(mtl[1]);

	pieces[21] = new GECoche_21(indice); //Letrero
	pieces[21]->setTexture(textures[2]);
	pieces[21]->setMaterial(mtl[3]);

	pieces[22] = new GECoche_22(indice); //Limpia parabrisas
	pieces[22]->setTexture(textures[0]);
	pieces[22]->setMaterial(mtl[0]);

	pieces[23] = new GECoche_23(indice); //Cosos delanteros ???
	pieces[23]->setTexture(textures[0]);
	pieces[23]->setMaterial(mtl[2]);

	pieces[24] = new GECoche_24(indice); // Faros delanteros
	pieces[24]->setTexture(textures[0]);
	pieces[24]->setMaterial(mtl[3]);

	pieces[25] = new GECoche_25(indice); // Logo delantero
	pieces[25]->setTexture(textures[3]);
	pieces[25]->setMaterial(mtl[4]);

	pieces[26] = new GECoche_26(indice); // Parachoques
	pieces[26]->setTexture(textures[0]);
	pieces[26]->setMaterial(mtl[1]);

	pieces[27] = new GECoche_27((uint32_t) 3); // LLanta Adelante Der
	pieces[27]->setTexture(textures[1]);
	pieces[27]->setMaterial(mtl[1]);

	pieces[28] = new GECoche_28((uint32_t) 2); // Rueda Atras Izq
	pieces[28]->setTexture(textures[0]);
	pieces[28]->setMaterial(mtl[2]);

	pieces[29] = new GECoche_29((uint32_t) 2); // LLanta Atras Izq
	pieces[29]->setTexture(textures[1]);
	pieces[29]->setMaterial(mtl[1]);

	pieces[30] = new GECoche_30((uint32_t) 4); // LLanta Atras Der
	pieces[30]->setTexture(textures[1]);
	pieces[30]->setMaterial(mtl[1]);

	pieces[31] = new GECoche_31((uint32_t) 1); // Rueda Adelante Izq
	pieces[31]->setTexture(textures[0]);
	pieces[31]->setMaterial(mtl[2]);

	pieces[32] = new GECoche_32((uint32_t) 1); // LLanta Adelante Izq
	pieces[32]->setTexture(textures[1]);
	pieces[32]->setMaterial(mtl[1]);

}

GECoche::~GECoche()
{

	for (int i = 0; i < 33; i++) 
		delete pieces[i];

	for (int i = 0; i < 7; i++) {
		//textures[i]->destroy(gc);
		delete textures[i];
	}

	delete[] textures;

	delete[] mtl;
}

int GECoche::GetNumPieces()
{
	return 33;
}

GEPiece* GECoche::GetPiece(int index)
{
	return pieces[index];
}

