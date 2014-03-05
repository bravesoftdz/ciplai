//---------------------------------------------------------------------------
#include <Clipbrd.hpp>
#include <memory>
#include <vcl.h>
#include <math.h>
#pragma hdrstop
#include "Picture.cpp"
#include "UMain.h"
#include "UImageView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmImageView *frmImageView;
int x1,y1,x2,y2;
//---------------------------------------------------------------------------
__fastcall TfrmImageView::TfrmImageView(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
__fastcall TfrmImageView::TfrmImageView(TfrmMain* Owner)
        : TForm(Owner)
{
  frmMain=Owner;
  Image1->Canvas->Pen->Color= clRed;
}
//---------------------------------------------------------------------------
__fastcall TfrmImageView::TfrmImageView(TComponent* Owner,TfrmRange* _frm)
        : TForm(Owner)
{
  frm=_frm;
  Image1->Canvas->Pen->Color= clRed;
}
//---------------------------------------------------------------------------
bool TfrmImageView::CargarImagen(AnsiString ArchivoImagen,int cod)
{
  try
  {
    Image1->Picture->LoadFromFile(ArchivoImagen);
    Image1->Refresh();
    if(cod==0) this->Caption="Picture : " + ExtractFileName(ArchivoImagen);
    if(cod==1) this->Caption="Canopy cover";
    if(cod==2) this->Caption="ERROR !!!";
    if(cod==3) this->Caption="Output picture";
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


void __fastcall TfrmImageView::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{

/*
valorX=X;
valorY=Y;
double dx=double(valorX)/double(Image1->Width);
double dy=double(valorY)/double(Image1->Height);
int ix=int(ceil(dx*double(Image1->Picture->Width)));
int iy=int(ceil(dy*double(Image1->Picture->Height)));

      int valorPixel = int(Image1->Canvas->Pixels[ix-1][iy-1]);


      long lngColor=valorPixel;

      int red=(lngColor % 256);
      int green=((lngColor/256)%256);
      int blue=(lngColor/65536);

AnsiString texto=AnsiString (Image1->Width) + " " + AnsiString (X) + " " + AnsiString (ix) + " " + AnsiString (red) + " " + AnsiString (green) + " " + AnsiString (blue) + " ";
Image1->Hint=texto;
*/
}
//---------------------------------------------------------------------------
void TfrmImageView::Graficar(TImage *img)
{
// copiar la informacion al clipboard
  unsigned int DataHandle;
  HPALETTE APalette;
  unsigned short MyFormat;
//  std::auto_ptr<Graphics::TBitmap> Bitmap(new Graphics::TBitmap());
  try
  {
    img->Picture->SaveToClipboardFormat(MyFormat,DataHandle,APalette);
    Clipboard()->SetAsHandle(MyFormat,DataHandle);
  }
  catch (...)
  {
     ShowMessage("Failed to copy image to clipboard!");
  }
// Copy image from clipboard


  TClipboard *cb = Clipboard();
  if (cb->HasFormat(CF_BITMAP))
  {
    std::auto_ptr<Graphics::TBitmap> Bitmap(new Graphics::TBitmap());
    try
    {
      Bitmap->LoadFromClipboardFormat(CF_BITMAP, cb->GetAsHandle(CF_BITMAP), 0);
      Image1->Canvas->Draw(0, 0, Bitmap.get());
    }
    catch (...)
    {
      MessageBeep(0);
      ShowMessage("Error reading image from clipboard!");
    }
    cb->Clear();
  }
  else
  {
    MessageBeep(0);
    ShowMessage("Cannot find image in clipboard!");
  }

/*

  img->Picture->LoadFromClipboardFormat(MyFormat,DataHandle,APalette);
  img->Refresh();
*/

}
//---------------------------------------------------------------------------




void __fastcall TfrmImageView::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Image1->Canvas->MoveTo(X,Y);
x1=X;
y1=Y;
}
//---------------------------------------------------------------------------

void __fastcall TfrmImageView::Image1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
Image1->Canvas->LineTo(X,Y);
x2=X;
y2=Y;
double h = sqrt(pow((y1-y2),2)+pow((x2-x1),2));
frmMain->setEdit(h);
        
}
//---------------------------------------------------------------------------

