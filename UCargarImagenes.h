//---------------------------------------------------------------------------

#ifndef UCargarImagenesH
#define UCargarImagenesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TfrmCargarImagenes : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblDirectory;
        TDirectoryListBox *dlbDirectory;
        TDriveComboBox *dcbDrive;
        TLabel *Label1;
        TButton *butApply;
        TButton *butCancel;
        TFileListBox *flbFiles;
        TFilterComboBox *FilterComboBox1;
        void __fastcall butApplyClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int TotalArchivos;
        AnsiString GetFileName(int);
        __fastcall TfrmCargarImagenes(TComponent* Owner);
        __fastcall TfrmCargarImagenes(TComponent* Owner,AnsiString*);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCargarImagenes *frmCargarImagenes;
//---------------------------------------------------------------------------
#endif
