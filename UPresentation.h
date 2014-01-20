//---------------------------------------------------------------------------

#ifndef UPresentationH
#define UPresentationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TfrmPresentation : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TButton *cmdContinue;
        TLabel *Label4;
        TPanel *Panel1;
        TImage *Image2;
        TPanel *Panel2;
        TImage *Image1;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmPresentation(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPresentation *frmPresentation;
//---------------------------------------------------------------------------
#endif
