//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UReport2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmReport *frmReport;
#include "UTHProceso.cpp"
//---------------------------------------------------------------------------
__fastcall TfrmReport::TfrmReport(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
