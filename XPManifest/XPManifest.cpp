//---------------------------------------------------------------------------

#include <basepch.h>

#pragma hdrstop

#include "XPManifest.h"
#pragma package(smart_init,weak)
#pragma resource "WindowsXP.res"

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TXPManifest *)
{
    new TXPManifest(NULL);
}
//---------------------------------------------------------------------------
__fastcall TXPManifest::TXPManifest(TComponent* Owner)
    : TComponent(Owner)
{
}
//---------------------------------------------------------------------------
namespace Xpmanifest
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TXPManifest)};
         RegisterComponents("Win32", classes, 0);
    }
}
//---------------------------------------------------------------------------
 