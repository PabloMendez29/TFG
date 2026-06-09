#include "GEAnimation.h"

//
// FUNCIÓN: GESpheGEAnimation::GEAnimation(GESkeleton* esqueleto, std::vector<Keyframe> keyframes)
//
// DESCRIPCIÓN: Consturctuctor de la animacion
//
GEAnimation::GEAnimation(GESkeleton* esqueleto, std::vector<Keyframe> keyframes) {
    this->esqueleto = esqueleto;
    this->keyframes = keyframes;
}

//
// FUNCIÓN: GESpheGEAnimation::GEAnimation(GESkeleton* esqueleto, std::vector<Keyframe> keyframes)
//
// DESCRIPCIÓN: Actualiza la pose del esqueleto en función del tiempo actual
//              Determina entre que keyframes se encuentra el tiempo y aplica interpolación
//              Si solo hay un keyframe directamente muestra esa pose
//
void GEAnimation::actualizaEsqueleto(float tiempo) {

    if (keyframes.size() > 1) {
        int transicion = getTransicion(tiempo);

        for (int i = 0; i <= transicion; i++) {
            tiempo -= keyframes[i].tiempo;
        }

        esqueleto->setPose(getPose(tiempo, transicion));
    }
    else {
        esqueleto->setPose(keyframes[0].pose);
    }

}

//
// FUNCIÓN: GEAnimation::getTransicion(float tiempo)
//
// DESCRIPCIÓN: Determina qué transición (par de keyframes) corresponde a un tiempo dado
//              Devuelve el índice del keyframe inicial de la transición.
//
int GEAnimation::getTransicion(float tiempo) {
    float acumulador = keyframes[0].tiempo;


    for (int i = 1; i < keyframes.size() - 1; i++) {
        acumulador += keyframes[i].tiempo;

        if (tiempo < acumulador)
            return i - 1;
    }
    return keyframes.size() - 2;
}

//
// FUNCIÓN: GEAnimation::getPose(float t, int transicion)
//
// DESCRIPCIÓN: Devuelve la pose interpolada entre dos keyframes consecutivos
//
std::vector<glm::vec3> GEAnimation::getPose(float t, int transicion) {

    float tNorm = t / keyframes[transicion + 1].tiempo;
    tNorm = glm::clamp(tNorm, 0.0f, 1.0f);
    return interpolar(keyframes[transicion].pose, keyframes[transicion + 1].pose, tNorm);
}

//
// FUNCIÓN: GEAnimation::interpolar(const std::vector<glm::vec3>& inicio, const std::vector<glm::vec3> & final, float t)
//
// DESCRIPCIÓN: Interpola dos poses 
//
std::vector<glm::vec3> GEAnimation::interpolar(const std::vector<glm::vec3>& inicio,
    const std::vector<glm::vec3> & final,
    float t) {
    std::vector<glm::vec3> result;
    for (int i = 0; i < inicio.size(); i++) {
        result.push_back(inicio[i] + t * (final[i] - inicio[i]));
    }
    return result;
}



