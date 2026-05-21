//
// Created by aethe on 5/20/2026.
//

#ifndef VOYAGERENGINE_VECTOR_H
#define VOYAGERENGINE_VECTOR_H
#include <type_traits>
#include <cmath>

namespace VE::Math // Prevents shadowing by allowing same variable names if they are not in the same namespace
{
    template<typename T>
    constexpr T SMALL_NUMBER = 100; // Used to scale epsilon for floating point comparisons

    template<typename T> // Vector must be either a float (4bytes), double (8bytes), or long double (8,12, or 16 bytes (depending on the system)
    struct TVector
    {
        static_assert(std::is_floating_point_v<T>, "T must be a floating point type"); // Checks if T is a floating point at compile time, if not, throw a severe error

        union // Allows datatypes to share the same chunk of memory of the largest datatype. However, each assignment overrides the previous
        {
            struct // A struct of size T*3
            {
                T X; // Vector's X component
                T Y; // Vector's Y component
                T Z; // Vector's Z component
            };

            T XYZ[3]; // An array of type T, of size T*3 allows us to access XYZ as if they were concurrently stored
        };

    public:
        TVector() = default; // No initialization. We avoid default 0 initialization to save on resources as vectors will be constructed/deconstructed many times a second
        TVector(T X_, T Y_, T Z_) : X(X_), Y(Y_), Z(Z_) {} // Construct using initial values for each component

        T& operator[](std::size_t index);
        T operator[](std::size_t index) const;
        T& Component(std::size_t index);
        T Component(std::size_t index) const;
        T Magnitude() const;
        TVector<T> GetNormalized() const;
        void Normalize();

        TVector<T>& operator+=(const TVector<T>& v); // We're passing in as pass-by-reference b/c as T becomes large we only pass in 8-bytes of data (vector<float> = 12bytes > vector<float>& = 8 bytes)
        TVector<T>& operator-=(const TVector<T>& v);
        TVector<T>& operator*=(T s);
        TVector<T>& operator/=(T s);

        // These are constants because we want to ensure we don't mutate the original values
        TVector<T> operator+(const TVector<T>& v) const;
        TVector<T> operator-(const TVector<T>& v) const;
        TVector<T> operator*(T s) const;
        TVector<T> operator/(T s) const;



    };

    template<typename T>
    T& TVector<T>::operator[](std::size_t index)
    {
        return Component(index);
    }

    template<typename T>
    T TVector<T>::operator[](std::size_t index) const
    {
        return Component(index);
    }

    template<typename T>
    T& TVector<T>::Component(std::size_t index)
    {
        return XYZ[index];
    }

    template<typename T>
    T TVector<T>::Component(std::size_t index) const
    {
        return XYZ[index];
    }

    template<typename T>
    TVector<T>& TVector<T>::operator+=(const TVector<T>& v)
    {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        return *this;
    }

    template<typename T>
    TVector<T>& TVector<T>::operator-=(const TVector<T>& v)
    {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;
        return *this;
    }


    template<typename T>
    TVector<T> TVector<T>::operator+(const TVector<T>& v) const
    {
        return TVector<T>((X + v.X), (Y + v.Y), (Z + v.Z));
    }

    template<typename T>
    TVector<T> TVector<T>::operator-(const TVector<T>& v) const
    {
        return TVector<T>((X - v.X), (Y - v.Y), (Z - v.Z));
    }

    template<typename T>
    TVector<T> TVector<T>::operator*(T s) const
    {
        return TVector<T>((X * s), (Y * s), (Z * s));
    }

    template<typename T>
    TVector<T> operator*(T s, const TVector<T>& v)
    {
        return v.operator*(s);
    }

    template<typename T>
    TVector<T> &TVector<T>::operator*=(T s)
    {
        X *= s;
        Y *= s;
        Z *= s;
        return *this;
    }

    template<typename T>
    TVector<T> TVector<T>::operator/(T s) const
    {
        s = static_cast<T>(1) / s; // Multiplication is significantly less resource intensive than division (~5-10x faster). That is why we invert s.
        return TVector<T>((X * s), (Y * s), (Z * s));
    }

    template<typename T>
    TVector<T> &TVector<T>::operator/=(T s)
    {
        s = static_cast<T>(1) / s;
        X *= s;
        Y *= s;
        Z *= s;
        return *this;
    }

    template<typename T>
    T TVector<T>::Magnitude() const
    {
        return static_cast<T>(std::sqrt((X * X) + (Y * Y) + (Z * Z)));
    }

    template<typename T>
    TVector<T> TVector<T>::GetNormalized() const
    {
        T VM = this->Magnitude();
        // We can't check for exact equality with floating point data types, that's why we use epsilon() to check for "close enough"
        if (VM <= std::numeric_limits<T>::epsilon() * SMALL_NUMBER<T>) throw std::runtime_error("Normalizing a zero vector");
        return ((*this) / VM);
    }

    template<typename T>
    void TVector<T>::Normalize()
    {
        T VM = this->Magnitude();
        if (VM <= std::numeric_limits<T>::epsilon() * SMALL_NUMBER<T>) throw std::runtime_error("Normalizing a zero vector");
        (*this) /= VM;
    }
}

#endif //VOYAGERENGINE_VECTOR_H
