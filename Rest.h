#ifndef REST_INCLUDE
#define REST_INCLUDE

#include "Pitch.h"

using namespace std;

class Rest : public Pitch {
    public:
        Rest(int duration);
        ~Rest();
        virtual float GetFrequency() const;
        virtual Rest* Clone() const;

    private:
};

#endif
