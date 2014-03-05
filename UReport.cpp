//---------------------------------------------------------------------------
#include <vcl.h>
#include <SysUtils.hpp>
#include <cassert>
#pragma hdrstop
#include <Picture.cpp>
#include "UMain.h"
#include "UImageView.h"
#include "UReport.h"
#include <math.h>
#include "UMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmReport *frmReport;
Picture* picture;
#include "UTHProceso.cpp"
//---------------------------------------------------------------------------
__fastcall TfrmReport::TfrmReport(TComponent* Owner)
        : TForm(Owner)
{
  TotalRec=12;
  sgLista->RowCount=TotalRec;
  sgLista->ColWidths[0]=30;
  sgLista->ColWidths[1]=180;
  sgLista->ColWidths[2]=120;
  sgLista->ColWidths[3]=100;
  sgLista->ColWidths[4]=100;
  sgLista->ColWidths[5]=100;
  sgLista->ColWidths[6]=100;
  sgLista->ColWidths[7]=100;
  sgLista->Cells[0][1]="No";
  sgLista->Cells[1][1]="Directory";
  sgLista->Cells[2][1]="Filename";
  sgLista->Cells[3][0]="Image Width";
  sgLista->Cells[4][0]="Image Height";
  sgLista->Cells[3][1]="Number of Pixels";
  sgLista->Cells[4][1]="Number of Pixels";
  sgLista->Cells[5][0]="Canopy cover";
  sgLista->Cells[5][1]="Number of Pixels";
  sgLista->Cells[6][0]="Canopy cover";
  sgLista->Cells[6][1]="%";
  sgLista->Cells[7][0]="Area";
  sgLista->Cells[7][1]="cm2";
  FixedRow=2;
  frmImage3=new TfrmImageView(this);
  frmImage3->Visible=false;
  frmImage3->Top=100;
  frmImage3->Left=300;
  processed=false;
}
//---------------------------------------------------------------------------
void TfrmReport::SetPictureInformation(Picture* pic)
{
  picture=pic;
}
//---------------------------------------------------------------------------
void TfrmReport::SetPicture(TfrmImageView* frmimag)
{
  frmImage=frmimag;
}
//---------------------------------------------------------------------------
void TfrmReport::SetErrorPicture(AnsiString err)
{
  ErrorPicture=err;
}
//---------------------------------------------------------------------------
void TfrmReport::SetFileNotPicture(AnsiString filenot)
{
  FileNotPicture=filenot;
}
//---------------------------------------------------------------------------
void TfrmReport::SetInitialPicture(AnsiString init)
{
  InitialPicture=init;
}
//---------------------------------------------------------------------------
void TfrmReport::ShowRecords()
{
  Limpiar_sgLista();
  int total=picture->GetTotalRecords();
  if(total>TotalRec-2) sgLista->RowCount=total+2;
  for(int i=0;i<picture->GetTotalRecords();i++)
  {
    sgLista->Cells[0][i+2]=i+1;
    sgLista->Cells[1][i+2]=ExtractFileDir(AnsiString(picture->FileName[i]));
    sgLista->Cells[2][i+2]=ExtractFileName(AnsiString(picture->FileName[i]));
    sgLista->Cells[3][i+2]=AnsiString(picture->Width[i]);
    sgLista->Cells[4][i+2]=AnsiString(picture->Height[i]);
  }
//  MostrarImagen(2);
}
//---------------------------------------------------------------------------
void __fastcall TfrmReport::sgListaDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
  if(ARow==0 || ARow==1 || ACol==0 || ACol==3 || ACol==4 || ACol==5 || ACol==6 || ACol==7 || ACol==8)
  {
    if(ACol<9)
    {
      TStringGrid* StringGrid =
      static_cast<TStringGrid*>(Sender);
      assert(StringGrid != NULL);
      StringGrid->Canvas->FillRect(Rect);

      AnsiString text(
      StringGrid->Cells[ACol][ARow]);
      RECT RText = static_cast<RECT>(Rect);
      InflateRect(&RText, -3, -3);

      DrawText(StringGrid->Canvas->Handle,
      text.c_str(), text.Length(), &RText,
      DT_CENTER | DT_SINGLELINE |
      DT_VCENTER
      );
    }
  }
}
//---------------------------------------------------------------------------
void TfrmReport::Limpiar_sgLista()
{
  int filas=sgLista->RowCount;
  for(int i=2;i<filas;i++)
  {
    sgLista->Cells[0][i]="";
    sgLista->Cells[1][i]="";
    sgLista->Cells[2][i]="";
    sgLista->Cells[3][i]="";
    sgLista->Cells[4][i]="";
    sgLista->Cells[5][i]="";
    sgLista->Cells[6][i]="";
    sgLista->Cells[7][i]="";
  }
  sgLista->RowCount=TotalRec;
  sgLista->Row=2;
  sgLista->Col=0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmReport::sgListaSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
  MostrarImagen(ARow);
  MostrarOutput(ARow);
}
//---------------------------------------------------------------------------
void TfrmReport::MostrarOutput(int ARow)
{
  if(processed) // si se procesaron las fotos
  {
    if(picture->SaveOutput)
    {
      AnsiString archivo;
      archivo=picture->FileName[ARow-2];
      AnsiString archivoX=ExtractFileName(archivo);
      AnsiString archivoBitmapTH="";
      for(int z=1;z<=archivoX.Length()-4;z++)
      {
        archivoBitmapTH=archivoBitmapTH+archivoX[z];
      }
      archivoBitmapTH=archivoBitmapTH+"_Thr";
      archivoBitmapTH=OutputFolder+"\\"+archivoBitmapTH+".bmp";
      if (FileExists(archivoBitmapTH))
      {
        frmImage3->CargarImagen(archivoBitmapTH,3);
        frmImage3->Visible=true;
      }
      else
      {
        frmImage3->CargarImagen(FileNotPicture,2);
        frmImage3->Visible=true;
      }
    }
  }
}
//---------------------------------------------------------------------------
void TfrmReport::MostrarImagen(int ARow)
{
  if(ARow>1)
  {
    int total=picture->GetTotalRecords();
    if(ARow-1>total)
    {
      frmImage->CargarImagen(InitialPicture,1);
    }
    else
    {
      AnsiString archivo=AnsiString(picture->FileName[ARow-2]);
      if (!FileExists(archivo))
      {
        frmImage->CargarImagen(FileNotPicture,2);
        frmImage->Visible=true;
      }
      else
      {
        bool conforme=frmImage->CargarImagen(archivo,0);
        if(conforme)
        {
          frmMain->ModificarStatusBar(archivo);
        }
        if(!conforme)
        {
          frmImage->CargarImagen(ErrorPicture,2);
          frmMain->ModificarStatusBar("");
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
void TfrmReport::CalculateAreaOfPictureTH()
{
  ProcesoThresholdingColorNegro *pro1;
  pro1=new ProcesoThresholdingColorNegro(false,sgLista,pbPicture);
}
//---------------------------------------------------------------------------
void TfrmReport::msgFinal()
{
  Application->MessageBoxA("Process finished succesful!!!","Finish!");
  frmMain->HabilitarAplicacion();
}
//---------------------------------------------------------------------------

void __fastcall TfrmReport::sbExitClick(TObject *Sender)
{
this->Visible=false;
}
//---------------------------------------------------------------------------
void TfrmReport::CalculateAreaOfPictureClassic(double threshold,int kindOpen,AnsiString FolderOutput,int rulepx,int rulecm,double plantDist,double rowDist,int plantxPic)
{
  if(frmImage3->Visible) {frmImage3->Visible=false;frmImage3->Refresh();}


  int TotalArchivos=0;
  TotalArchivos=picture->GetTotalRecords();
  if(TotalArchivos<=0){return;} /* si no se ha seleccionado ningún archivo se
                                            se termina el proceso */
/* se crea directorio de reporte */
//  AnsiString DirReport=ExtractFileDir(AnsiString(picture->FileName[0]))+"\\result";
//  CreateDir(DirReport);
  AnsiString DirReport=FolderOutput;
  OutputFolder=FolderOutput;
/* se crea archivo resumen */
  AnsiString ArchivoResumen="";
/*
  AnsiString ArchivoResumen=DirReport+"\\resumen.txt";
  FILE *streamRes;
  streamRes = fopen (ArchivoResumen.c_str(),"w");
  if(streamRes==NULL){fclose(streamRes);}
  else
  {
    fprintf(streamRes,"%s\n",  "               Total     CC                         ");
    fprintf(streamRes,"%s\n\n","Width Height   Pixels     %      File name");
    fclose(streamRes);
  }
*/
//definirMaxDeProgressBar;
  pbPicture->Max=TotalArchivos;
/* SE INICIA EL PROCESO */
  SetCurrentDir("c:\\");
  int iReg=0;
  AnsiString archivoOrig,archivoBitmapTH,archivoBMP;
  for(iReg=0;iReg<TotalArchivos;iReg++)
  {
// se ubica el archivo en el sgLista
// ubicarReg_en_sglista
    sgLista->Row=iReg+2;
    sgLista->Refresh();
// se forma el nombre del archivo bitmap salida
    archivoOrig=picture->FileName[iReg];
    AnsiString archivoX=ExtractFileName(archivoOrig);
    archivoBitmapTH="";
    for(int z=1;z<=archivoX.Length()-4;z++)
    {
      archivoBitmapTH=archivoBitmapTH+archivoX[z];
    }
    archivoBitmapTH=archivoBitmapTH+"_Thr";
    archivoBitmapTH=DirReport+"\\"+archivoBitmapTH+".bmp";
// cargo la imagen
    try
    {
      archivoBMP=picture->FileName[iReg];
      TImage* img;
      img=NULL;
      img=new TImage(this);
      proceso(archivoOrig,archivoBitmapTH,ArchivoResumen,0,picture->Width[iReg],0,picture->Height[iReg],iReg,threshold,img,kindOpen,rulepx,rulecm,plantDist,rowDist,plantxPic);
      if(picture->SaveOutput)
      {
        img->Picture->SaveToFile(archivoBitmapTH);
      }
      delete img;
      img=NULL;
    }
    catch(...)
    {
      picture->Height[iReg]=0;
      picture->Width[iReg]=0;
      picture->TotalPixel[iReg]=0;
      picture->LAI[iReg]=0.0;
      picture->Area[iReg]=0.0;
      picture->TimeDuration[iReg]=0;
    }
// mostrarInfo_en_sglista
    sgLista->Cells[3][iReg+2]=picture->Width[iReg];
    sgLista->Cells[4][iReg+2]=picture->Height[iReg];
    if(picture->TotalPixel[iReg]==0) sgLista->Cells[5][iReg+2]="0";
    else sgLista->Cells[5][iReg+2]=FormatFloat("#,###",picture->TotalPixel[iReg]);
    if(picture->LAI[iReg]==0.0) sgLista->Cells[6][iReg+2]="0.00";
    else sgLista->Cells[6][iReg+2]=FormatFloat("#.##",picture->LAI[iReg]);
    if(picture->Area[iReg]==0.0) sgLista->Cells[7][iReg+2]="0.00";
    else sgLista->Cells[7][iReg+2]=FormatFloat("#.##",picture->Area[iReg]);
    sgLista->Refresh();
// guardar imagen thresholding
//  Image1->Picture->SaveToFile(archivoBitmapTH);
// avanzarProgressBar
    pbPicture->Position=iReg+1;
  }
/* FINALIZA EL PROCESO */
  processed=true;
//  ubicarRegInicial_en_sglista;
  sgLista->Row=2;
//  Synchronize(msgFinal);
// View output picture if saveOutput is true
  if(picture->SaveOutput)
  {
    frmImage3->Visible=true;
    MostrarOutput(2);
  }
  msgFinal();
}
//---------------------------------------------------------------------------
void TfrmReport::proceso(AnsiString archivoOrig,AnsiString archivo,AnsiString ArchRes,int Xini,int Xfin,int Yini,int Yfin,int reg,double threshold,TImage *img,int kindOpen,int rulepx,int rulecm,double plantDist,double rowDist,int plantxPic)
{
//  FILE *streamRes;
//  streamRes = fopen (ArchRes.c_str(),"a");
//  if(streamRes==NULL){fclose(streamRes);}
//  rewind(streamRes);
  int contPixel=0;
  int xpos=Xini;
  int ypos=Yini;
  int valorPixel=0;
  int Red,Green,Blue;
  int yFinal=Yfin;
  int xFinal=Xfin;
  TColor pixel;
  long lngColor;
  int red,green,blue;
  double calc;
  img->Width=xFinal;
  img->Height=yFinal;
  for (ypos=0; ypos<yFinal; ypos++)
  {
    for (xpos=0; xpos<xFinal; xpos++)
    {
      valorPixel = int(frmImage->Image1->Canvas->Pixels[xpos][ypos]);
      pixel=frmImage->Image1->Canvas->Pixels[xpos][ypos];
      lngColor=pixel;

      red=(lngColor % 256);
      green=((lngColor/256)%256);
      blue=(lngColor/65536);

      if(green==0 && red==0 && blue==0)
      {
        calc=0.0;
      }
      else
      {
//        calc=double((green-red)+(green-blue))/double(green+red+green+blue);
        calc=double(green-red)/double(green+red);
      }

      if(calc>=threshold)
      {
        contPixel++;
//      img->Canvas->Pixels[xpos][ypos]=pixel;
        img->Canvas->Pixels[xpos][ypos]=clGreen;
      }
      else
      {
//        img->Canvas->Pixels[xpos][ypos]=clWhite;
        img->Canvas->Pixels[xpos][ypos]=clRed;
      }
    }
  }
  if(kindOpen==1)
  {
    frmImage3->Image1->Picture->LoadFromFile(archivoOrig);
    frmImage3->Graficar(img);
    frmImage3->Caption="Output";
    frmImage3->Visible=true;
  }

/*
  double altura=height;
  double coef=0.0000002*pow(altura,1.9525); // square medium 5x5
  double area=double(contPixel)*coef;
*/
//  double factor=0.013308565; // factor:bastidor entero
//  double areaCobertura=factor*double(contPixel);
//  double areaTotal=factor*double(((Xfin-Xini)*(Yfin-Yini)));
//  double lai=(double(contPixel)/double(((Xfin-Xini)*(Yfin-Yini))))*100.00;
//  double lai=(areaCobertura/areaTotal)*100.00;
//  double area=0.01459854*double(contPixel); // celda 1 del bastidor
//  fprintf(streamRes,"%i   %i    %i  %s    %s\n",xFinal,yFinal,contPixel,FormatFloat("0.00",float(lai)),archivoOrig.c_str());
//  fclose(streamRes);
  double area=(double(contPixel)*double(rulecm)*double(rulecm))/(double(rulepx)*double(rulepx));
  double lai=(area/(double(plantxPic)*plantDist*rowDist))*100.00;
  picture->TotalPixel[reg]=contPixel;
  picture->LAI[reg]=lai;
  picture->Area[reg]=area;
  frmImage->Visible=true;
}

//---------------------------------------------------------------------------
void __fastcall TfrmReport::sbReportClick(TObject *Sender)
{
  GuardarReporte();
}
//---------------------------------------------------------------------------
void TfrmReport::GuardarReporte()
{
  if(sdSaveReport->Execute())
  {
    AnsiString reporte=sdSaveReport->FileName;
    FILE *streamRes;
    streamRes = fopen (reporte.c_str(),"w");
    if(streamRes==NULL){fclose(streamRes);}
    rewind(streamRes);
    int TotalArchivos=0;
    TotalArchivos=picture->GetTotalRecords();

    if(streamRes==NULL){fclose(streamRes);return;}
    else
    {
      fprintf(streamRes,"%s\n",  "Image   Image      CC      CC      Area");
      fprintf(streamRes,"%s\n\n","Width   Height   Pixels     %       cm2       Filename");
    }

    int i;
    for(i=0;i<TotalArchivos;i++)
    {
      fprintf(streamRes,"%i     %i      %i    %s   %s    %s\n",picture->Width[i],picture->Height[i],picture->TotalPixel[i],FormatFloat("0.00",float(picture->LAI[i])),FormatFloat("0.00",float(picture->Area[i])),picture->FileName[i]);
    }
    fclose(streamRes);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmReport::sbDeleteClick(TObject *Sender)
{
int numreg=picture->GetTotalRecords();
int fila=sgLista->Row;
if(numreg>0 && fila-FixedRow+1<=numreg && fila>=FixedRow)
{
  BorrarFila(fila);
  MostrarImagen(sgLista->Row);
}
}
//---------------------------------------------------------------------------
void TfrmReport::BorrarFila(int Index)
{
  int fila=Index-FixedRow+1;
  int numreg=picture->GetTotalRecords();
  int i,j;
  if(fila==numreg)
  {
    for(j=0;j<sgLista->ColCount;j++){sgLista->Cells[j][fila+FixedRow-1]="";}
    picture->DeleteRecord(fila-1);
    sgLista->Refresh();
    sgLista->Row=fila+FixedRow-1;
    MostrarImagen(sgLista->Row);
    if(sgLista->RowCount>TotalRec-FixedRow+FixedRow) sgLista->RowCount--;
    return;
  }
  if(fila<numreg)
  { // no es ultimo
    for(i=fila;i<numreg;i++)
    {
      for(j=0;j<sgLista->ColCount;j++)
      {
        sgLista->Cells[j][i+FixedRow-1]=sgLista->Cells[j][i+1+FixedRow-1];
        if(j==0)
        {
          sgLista->Cells[0][i+FixedRow-1]=sgLista->Cells[j][i+1+FixedRow-1]-1;
        }
      }
    }
    for(j=0;j<sgLista->ColCount;j++)
    {
      sgLista->Cells[j][numreg+FixedRow-1]="";
    }
    if(sgLista->RowCount>TotalRec) sgLista->RowCount--;
    picture->DeleteRecord(fila-1);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmReport::FormClose(TObject *Sender,
      TCloseAction &Action)
{
delete frmImage3;
}
//---------------------------------------------------------------------------
