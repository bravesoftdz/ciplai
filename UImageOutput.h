//---------------------------------------------------------------------------

#ifndef UImageOutputH
#define UImageOutputH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmImageOutput : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TImage *Image1;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmImageOutput(TComponent* Owner);
        bool CargarImagen(AnsiString,int);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmImageOutput *frmImageOutput;
//---------------------------------------------------------------------------
#endif
