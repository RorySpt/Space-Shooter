#include "_toolkits.h"
namespace TL {
    PCHPTE pHpte = HPET::hInstance();
}

TL::XboxControllor* pXBoxC = TL::XboxControllor::gethInst();

void TL::FraCtrl(int fps)
{
    static HPET tHpte;
    double FrameTime = 1.0 / double(fps);
    while (tHpte.getIntervals_db() <= FrameTime);
    tHpte.Mark();
}

int TL::Get_Fps()
{
    static HPET tHpte;
    int ret = int(1.0 / tHpte.getIntervals_db() + 0.5);
    tHpte.Mark();
    return ret;
}
int TL::Get_Fps_t(double time)
{
    static HPET tHpte;
    static int n(0);
    double temp;
    static int ret(0);
    ++n;
    if ((temp = tHpte.getIntervals_db()) >= time)
    {
        ret = int(n / temp + 0.5);
        tHpte.Mark();
        n = 0;
    }

    return ret;
}
int TL::Get_Fps(clock_t now)
{
    static clock_t time(-1);
    int ret = int(1000 / (now - time) + 0.5);
    time = now;
    return ret;
}
