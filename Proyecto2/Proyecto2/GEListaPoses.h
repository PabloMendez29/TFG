#include <vector>
#include <glm/fwd.hpp>
#include "GEKeyFrame.h"



//
// CLASE: GEListaPoses
//
// DESCRIPCIÓN: Clase que almacena los keyframes de una animación
//
class GEListaPoses {

public:
	GEListaPoses();
	std::vector<Keyframe> getKeyframes();
private:

	std::vector<Keyframe> keyframes;
};