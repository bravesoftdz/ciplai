//---------------------------------------------------------------------------

#ifndef UReportH
#define UReportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include "UImageOutput.h"
//---------------------------------------------------------------------------
class TfrmReport : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *sgLista;
        TProgressBar *pbPicture;
        TLabel *lblWorking;
        TSpeedButton *sbReport;
        TSpeedButton *sbExit;
        TSaveDialog *sdSaveReport;
        TLabel *lblError;
        void __fastcall sgListaDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall sgListaSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall sbExitClick(TObject *Sender);
        void __fastcall sbReportClick(TObject *Sender);
        void __fastcall sbDeleteClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
        //Picture* picture;
        int TotalRec;
        int FixedRow;
        TfrmImageOutput* frmImageOutput;
        AnsiString ErrorPicture;
        AnsiString FileNotPicture;
        AnsiString InitialPicture;
        AnsiString OutputFolder;
        void BorrarFila(int);
        void MostrarImagen(int);
        void MostrarOutput(int);
public:		// User declarations
        bool processed;
        TfrmImageView* frmImage;
        TfrmImageView *frmImage3;
        void SetPictureInformation(Picture*);
        void SetPicture(TfrmImageView*);
        void SetOutput(TfrmImageOutput*);
        void SetErrorPicture(AnsiString);
        void SetInitialPicture(AnsiString);
        void SetFileNotPicture(AnsiString);

        void ShowRecords();
        void Limpiar_sgLista();
        void CalculateAreaOfPictureTH();
        void CalculateAreaOfPictureClassic(double,int,AnsiString,int,int,double,double,int);
        void msgFinal();
        void proceso(AnsiString,AnsiString,AnsiString,int,int,int,int,int,double,TImage*,int,int,int,double,double,int);
        void proceso2(AnsiString,AnsiString,AnsiString,int,int,int,int,int);
        void GuardarReporte();
        __fastcall TfrmReport(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmReport *frmReport;
//---------------------------------------------------------------------------
#endif
