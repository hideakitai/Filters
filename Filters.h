#pragma once
#ifndef EMBEDDEDUTILS_FILTERS_H
#define EMBEDDEDUTILS_FILTERS_H

#include "Helper.h"

namespace Filter
{
    template <typename T, int N = 1>
    class LPF
    {
    public:
        LPF() { reset(); }
        LPF(T gain) : gain_(gain), buffer_() { reset(); }

        template <typename U = T, typename std::enable_if<!EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline T get(const T& curr_val, double dt)
        {
            buffer_ = curr_val + (curr_val - buffer_) * gain_ * (double)dt;
            return buffer_;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline T get(const T& curr_val, double dt)
        {
            buffer_ = curr_val.array() + (curr_val.array() - buffer_.array()) * gain_.array() * (double)dt;
            return buffer_;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, zero)>::type* = nullptr>
        inline void reset() { buffer_ = U::zero(); }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, setZero)>::type* = nullptr>
        inline void reset() { buffer_.setZero(N); }

        template <typename U = T, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
        inline void reset() { buffer_ = 0.0; }

        inline void setGain(T gain) { gain_ = gain; }

    private:

        T gain_;
        T buffer_;
    };


    template <typename T, int N>
    class HPF
    {
        HPF() { reset(); }
        HPF(T gain) : gain_(gain), buffer_() { reset(); }

        template <typename U = T, typename std::enable_if<!EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline T get(const T& curr_val, double dt)
        {
            T new_val = curr_val - buffer_;
            buffer_ += new_val * gain_ * dt;
            return new_val;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline T get(const T& curr_val, double dt)
        {
            T new_val = curr_val.array() - buffer_.array();
            buffer_ += new_val.array() * gain_.array() * dt;
            return new_val;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, zero)>::type* = nullptr>
        inline void reset() { buffer_ = U::zero(); }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, setZero)>::type* = nullptr>
        inline void reset() { buffer_.setZero(N); }

        template <typename U = T, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
        inline void reset() { buffer_ = 0.0; }

        inline void setGain(double gain) { gain_ = gain; }

    private:
        T gain_;
        T buffer_;
    };


//    template <typename T>
//    class BPF
//    {
//
//    };
}

#endif // EMBEDDEDUTILS_FILTERS_H
