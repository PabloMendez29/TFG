#include <vector>
#include <glm/fwd.hpp>
#include "GESkeleton.h"
#include "GEKeyFrame.h"

//
// CLASE: GECommandContext
//
// DESCRIPCIÓN: Clase que controla la animación de un esqueleto
//
class GEAnimation {
private:

	std::vector<Keyframe> keyframes;
	GESkeleton* esqueleto;

	std::vector<glm::vec3> interpolar(const std::vector<glm::vec3>& start, const std::vector<glm::vec3>& end, float factor);

	int getTransicion(float tiempo);
	std::vector<glm::vec3> getPose(float Tiempo, int transicion);

public:
	GEAnimation(GESkeleton* esqueleto, std::vector<Keyframe> keyframes);

	void actualizaEsqueleto(float Tiempo);
};