//---------------------------------------------------------------------------

#ifndef UHelpH
#define UHelpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TfrmHelp : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit1;
        TButton *Button1;
        TPanel *Panel1;
        TImage *Image1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmHelp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmHelp *frmHelp;
//---------------------------------------------------------------------------
#endif
