//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UCargarImagenes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCargarImagenes *frmCargarImagenes;
//---------------------------------------------------------------------------
__fastcall TfrmCargarImagenes::TfrmCargarImagenes(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TfrmCargarImagenes::TfrmCargarImagenes(TComponent* Owner,AnsiString lista[])
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCargarImagenes::butApplyClick(TObject *Sender)
{
  TotalArchivos=flbFiles->Count;
}
//---------------------------------------------------------------------------
AnsiString TfrmCargarImagenes::GetFileName(int i)
{
  return dlbDirectory->Directory+"\\"+flbFiles->Items->Strings[i];
}
//---------------------------------------------------------------------------

