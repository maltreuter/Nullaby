#ifndef NOTE_INCLUDE
#define NOTE_INCLUDE

#include <cmath>
#include <map>
#include <string>

#include "Pitch.h"

using namespace std;

class Note : public Pitch {

    public:
        const string name;
        int octave;

        Note(const string name, int octave, int duration);
        ~Note();
        int GetHalfStepID() const;
        virtual float GetFrequency() const;
        virtual Note* Clone() const;

    private:
};

#endif
