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
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TImage *Image1;
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
private:	// User declarations
        int valorX;
        int valorY;
        TfrmRange* frm;
public:		// User declarations
        __fastcall TfrmImageView(TComponent* Owner);
        __fastcall TfrmImageView(TComponent* Owner,TfrmRange*);
        bool CargarImagen(AnsiString,int);
        Graficar(TImage*);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmImageView *frmImageView;
//---------------------------------------------------------------------------
#endif
