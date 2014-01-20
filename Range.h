//---------------------------------------------------------------------------

#ifndef RangeH
#define RangeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmRange : public TForm
{
__published:	// IDE-managed Components
        TListBox *lbPixel;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TButton *Button1;
        TTrackBar *tbTolerance;
        TEdit *Edit1;
        TLabel *Label4;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall lbPixelClick(TObject *Sender);
        void __fastcall tbToleranceChange(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
        int rec;
public:		// User declarations
        __fastcall TfrmRange(TComponent* Owner);
        int tolerance;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRange *frmRange;
//---------------------------------------------------------------------------
#endif
