//---------------------------------------------------------------------------

#ifndef UMainH
#define UMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <FileCtrl.hpp>

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TBevel *Bevel1;
        TPanel *Panel1;
        TBevel *Bevel2;
        TImage *Image1;
        TOpenPictureDialog *opicdiag;
        TStatusBar *StatusBar1;
        TMainMenu *MainMenu1;
        TMenuItem *Scenario1;
        TMenuItem *New1;
        TMenuItem *N1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *Simulation1;
        TMenuItem *Simulate1;
        TMenuItem *Report1;
        TMenuItem *Textreport1;
        TMenuItem *N2;
        TMenuItem *Clearall1;
        TMenuItem *Help1;
        TMenuItem *Aboutmodel1;
        TMenuItem *Exit1;
        TMenuItem *N3;
        TMenuItem *Help2;
        TPanel *Panel2;
        TSpeedButton *sbEmptyFileList;
        TSpeedButton *sbOpenFile;
        TSpeedButton *sbOpenFiles;
        TSpeedButton *sbCalculate;
        TSpeedButton *sbReport;
        TSpeedButton *sbExit;
        TSplitter *Splitter1;
        TPanel *Panel3;
        TLabel *Label1;
        TEdit *Edit1;
        TLabel *Label2;
        TSplitter *Splitter2;
        TPanel *Panel4;
        TSplitter *Splitter3;
        TOpenDialog *OpenDialog1;
        TPanel *Panel5;
        TCheckBox *cbSave;
        TPanel *Panel6;
        TPanel *Panel7;
        TPanel *Panel8;
        TButton *butFolderOutput;
        TEdit *edFolderOutput;
        TFileListBox *flbFiles;
        void __fastcall sbExitClick(TObject *Sender);
        void __fastcall sbOpenFileClick(TObject *Sender);
        void __fastcall sbReportClick(TObject *Sender);
        void __fastcall sbOpenFilesClick(TObject *Sender);
        void __fastcall sbEmptyFileListClick(TObject *Sender);
        void __fastcall sbCalculateClick(TObject *Sender);
        void __fastcall Aboutmodel1Click(TObject *Sender);
        void __fastcall Clearall1Click(TObject *Sender);
        void __fastcall Help2Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall cbSaveClick(TObject *Sender);
        void __fastcall butFolderOutputClick(TObject *Sender);
private:	// User declarations
//        AnsiString *ListaArchivos;
        double threshold;
        int TotalArchivos;
        int kindOpen; // Kind of load information 1: Open one picture  2: Open a folder with many pictures  0: no open yet
        Picture* picture;
        AnsiString ErrorPicture;
        AnsiString InitialPicture;
        AnsiString FileNotPicture;
        void __fastcall AbrirFormularioReporte(bool);
//        bool __fastcall SelectDirectory(const AnsiString Caption,
//				const WideString Root,
//				AnsiString &Directory);
public:		// User declarations
        void HabilitarAplicacion();
        void ModificarStatusBar(AnsiString);
        bool processing;
        __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
