//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "UImageOutput.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmImageOutput *frmImageOutput;
//---------------------------------------------------------------------------
__fastcall TfrmImageOutput::TfrmImageOutput(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool TfrmImageOutput::CargarImagen(AnsiString ArchivoImagen,int cod)
{
  try
  {
    Image1->Picture->LoadFromFile(ArchivoImagen);
    Image1->Refresh();
    if(cod==0) this->Caption="Picture : " + ExtractFileName(ArchivoImagen);
    if(cod==1) this->Caption="CIP-Vegetation cover";
    if(cod==2) this->Caption="ERROR !!!";
    if(cod==3) this->Caption="Output";
    this->Visible=true;
    this->Refresh();
    return true;
  }
  catch(...)
  {
    return false;
  }
}
//---------------------------------------------------------------------------







