#include <iostream>
#include "math/vector.h"

int main() {
    bool GEngine = true;

    while (GEngine)
    {

        const VE::Math::TVector<float> v1(0.0f, 0.0f, 0.0f);
        VE::Math::TVector<float> v2 = v1.GetNormalized();
        v2.Normalize();
        GEngine = false;

    }

    return 0;
}
