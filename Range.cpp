//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Range.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmRange *frmRange;
//---------------------------------------------------------------------------
__fastcall TfrmRange::TfrmRange(TComponent* Owner)
        : TForm(Owner)
{
  rec=-1;
  tolerance=0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRange::Button1Click(TObject *Sender)
{
if(rec==-1){ShowMessage("Select the pixel to remove!");}
else
{
lbPixel->Items->Delete(rec);
rec=-1;
}
}
//---------------------------------------------------------------------------
void __fastcall TfrmRange::lbPixelClick(TObject *Sender)
{
rec=lbPixel->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRange::tbToleranceChange(TObject *Sender)
{
  Edit1->Text=tbTolerance->Position;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRange::Edit1Change(TObject *Sender)
{
tolerance=Edit1->Text.ToInt();
}
//---------------------------------------------------------------------------
void __fastcall TfrmRange::Button2Click(TObject *Sender)
{
lbPixel->Items->Clear();
}
//---------------------------------------------------------------------------

