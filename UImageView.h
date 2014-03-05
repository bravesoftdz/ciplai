//---------------------------------------------------------------------------

#ifndef UImageViewH
#define UImageViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "Range.h"

//---------------------------------------------------------------------------
class TfrmImageView : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
        TfrmRange* frm;
        TfrmMain* frmMain;
public:		// User declarations
        __fastcall TfrmImageView(TComponent* Owner);
        __fastcall TfrmImageView(TfrmMain* Owner);
        __fastcall TfrmImageView(TComponent* Owner,TfrmRange*);
        bool CargarImagen(AnsiString,int);
        void Graficar(TImage*);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmImageView *frmImageView;
//---------------------------------------------------------------------------
#endif
