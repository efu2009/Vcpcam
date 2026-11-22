#include <mod/amlmod.h>
#include <mod/logger.h>

MYMOD(net.user.pccam, PCCamera, 1.0, User)
NEEDGAME(com.rockstargames.gtavc)

static const float CAR_FOV = 70.0f;

static void* hGTAVC = nullptr;
typedef void* (*FindPlayerVehicle_t)();
static FindPlayerVehicle_t FindPlayerVehicle = nullptr;

DECL_HOOK(float, FindCamFOV, void* self)
{
    float orig = FindCamFOV(self);
    if (FindPlayerVehicle && FindPlayerVehicle() != nullptr)
        return CAR_FOV;
    return orig;
}

ON_MOD_PRELOAD()
{
    logger->SetTag("PCCamera");
    hGTAVC = aml->GetLibHandle("libGTAVC.so");
    if (!hGTAVC) { logger->Error("libGTAVC.so not found"); return; }

    FindPlayerVehicle = (FindPlayerVehicle_t)aml->GetSym(hGTAVC, "_Z17FindPlayerVehiclev");
    if (!FindPlayerVehicle) { logger->Error("FindPlayerVehicle missing"); return; }

    HOOKSYM(FindCamFOV, hGTAVC, "_ZN7CCamera10FindCamFOVEv");
    logger->Info("PCCamera loaded");
}
