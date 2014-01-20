//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UHelp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmHelp *frmHelp;
//---------------------------------------------------------------------------
__fastcall TfrmHelp::TfrmHelp(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmHelp::Button1Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------
