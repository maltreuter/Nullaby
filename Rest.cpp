#include "Rest.h"

using namespace std;

Rest::Rest(int duration) : Pitch(duration) {

}

Rest::~Rest() {

}

float Rest::GetFrequency() const {
    return 0.0;
}

Rest* Rest::Clone() const {
    return new Rest(this->duration);
}

