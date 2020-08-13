#pragma once
#include "Header.h"

class Timer final
{
private:
    class Time
    {
    private:
        Time()
        {
            reset();
        }

        ~Time() = default;

        void reset()
        {
            QueryPerformanceFrequency(&m_countTime);
            QueryPerformanceCounter(&m_curTime);
            QueryPerformanceCounter(&m_prevTime);
        }

        float update()
        {
            QueryPerformanceCounter(&m_curTime);

            // delta time = current time - previous time
            m_dDeltaTime = (static_cast<double>(m_curTime.QuadPart) - static_cast<double>(m_prevTime.QuadPart)) / static_cast<double>(m_countTime.QuadPart);

            m_fDeltaTime = static_cast<float>(m_dDeltaTime);
            m_prevTime = m_curTime;

            return m_fDeltaTime;
        }

    private:
        LARGE_INTEGER m_countTime;
        LARGE_INTEGER m_curTime;
        LARGE_INTEGER m_prevTime;
        double m_dDeltaTime;
        float m_fDeltaTime;


        friend Timer;
    };

private:
    static Time m_mainTimer;

public:
    Timer() = delete;
    ~Timer() = delete;

    static float DeltaTime()
    {
        return m_mainTimer.m_fDeltaTime;
    }

    static void Update()
    {
        m_mainTimer.update();
    }

    static void Reset()
    {
        m_mainTimer.reset();
    }
};