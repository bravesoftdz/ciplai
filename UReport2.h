//---------------------------------------------------------------------------

#ifndef UReport2H
#define UReport2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmReport : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmReport(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmReport *frmReport;
//---------------------------------------------------------------------------
#endif
