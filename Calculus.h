#pragma once
#ifndef EMBEDDEDUTILS_CALCULUS_H
#define EMBEDDEDUTILS_CALCULUS_H

#include "Filters/Helper.h"

namespace Calculus
{
    template <typename T, int N = 1>
    class Differential
    {
    public:

        Differential(const T gain) : gain_(gain) { reset(); }

        template <typename U = T, typename std::enable_if<!EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline T get(const T& integral, const double dt)
        {
            auto newVal = integral * gain_ - buffer_;
            buffer_ += gain_ * newVal * dt;
            return newVal;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline T get(const T& integral, const double dt)
        {
            auto newVal = integral.array() * gain_.array() - buffer_.array();
            buffer_.array() = buffer_.array() + gain_.array() * newVal.array() * dt;
            return newVal;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, zero)>::type* = nullptr>
        inline void reset(const U& integral = U::zero()) { buffer_ = integral * gain_; }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, setZero)>::type* = nullptr>
        inline void reset(const U& integral = U::Zero(N)) { buffer_ = integral.array() * gain_.array(); }

        template <typename U = T, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
        inline void reset(const U& integral = 0.0) { buffer_ = integral * gain_; }

        inline void setGain(const T& gain) { gain_ = gain; }

    private:

        T gain_;
        T buffer_;
    };


    template <typename T, int N = 1>
    class Integral
    {
    public:

        Integral() { reset(); }

        template <typename U = T, typename std::enable_if<!EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline const T& get(const T& differential, const double dt)
        {
            buffer_ += differential * dt;
            return buffer_;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline const T& get(const T& differential, const double dt)
        {
            buffer_ = buffer_.array() + differential.array() * dt;
            return buffer_;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, zero)>::type* = nullptr>
        inline void reset(const U& integral = U::zero()) { buffer_ = integral; }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, setZero)>::type* = nullptr>
        inline void reset(const U& integral = U::Zero(N)) { buffer_ = integral; }

        template <typename U = T, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
        inline void reset(const U& integral = 0.0) { buffer_ = integral; }

    private:

        T buffer_;
    };
}

#endif // EMBEDDEDUTILS_CALCULUS_H
