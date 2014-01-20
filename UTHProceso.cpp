//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UTHProceso.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ProcesoThresholdingColorNegro::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall ProcesoThresholdingColorNegro::ProcesoThresholdingColorNegro(bool CreateSuspended,TStringGrid *_sgLista,TProgressBar *_pbPicture)
        : TThread(CreateSuspended)
{
  FreeOnTerminate = true;
  sgLista=_sgLista;
  pbPicture=_pbPicture;
  imPicture = new TImage(Application);
}
//---------------------------------------------------------------------------
__fastcall ProcesoThresholdingColorNegro::~ProcesoThresholdingColorNegro()
{
  delete imPicture;
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::Execute()
{
  TotalArchivos=0;
  TotalArchivos=picture->GetTotalRecords();
  if(TotalArchivos<=0){return;} /* si no se ha seleccionado ningún archivo se
                                             se termina el proceso */
/* se crea directorio de reporte */

  AnsiString DirReport=ExtractFileDir(AnsiString(picture->FileName[0]))+"\\result";
  CreateDir(DirReport);
/* se crea archivo resumen */
  AnsiString ArchivoResumen=DirReport+"\\resumen.txt";
  FILE *streamRes;
  streamRes = fopen (ArchivoResumen.c_str(),"w");
  if(streamRes==NULL){fclose(streamRes);}
  else
  {
    fprintf(streamRes,"%s\n",  " Total    Total                         ");
    fprintf(streamRes,"%s\n\n"," Pixels    cm2    File name");
    fclose(streamRes);
  }
/* Progress Bar */
  Synchronize(definirMaxDeProgressBar);
/* SE INICIA EL PROCESO */
  iReg=0;
  for(iReg=0;iReg<TotalArchivos;iReg++)
  {
// se ubica el archivo en el sgLista
    Synchronize(ubicarReg_en_sglista);
// se forma el nombre del archivo bitmap salida
    archivoOrig=picture->FileName[iReg];
    AnsiString archivoX=ExtractFileName(picture->FileName[iReg]);
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
      proceso(archivoBitmapTH,ArchivoResumen,0,picture->Width[iReg],0,picture->Height[iReg],iReg);
//      Synchronize(GuardarTH);
    }
    catch(...)
    {
      picture->Height[iReg]=0;
      picture->Width[iReg]=0;
      picture->TotalPixel[iReg]=0;
      picture->LAI[iReg]=0.0;
      picture->TimeDuration[iReg]=0;
    }
    Synchronize(mostrarInfo_en_sglista);
    Synchronize(avanzarProgressBar);
  }
/* FINALIZA EL PROCESO */
  Synchronize(ubicarRegInicial_en_sglista);
  Synchronize(msgFinal);
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::proceso(AnsiString archivo,AnsiString ArchRes,int Xini,int Xfin,int Yini,int Yfin,int reg)
{
  Synchronize(cargarImagen);
  FILE *streamRes;
  streamRes = fopen (ArchRes.c_str(),"a");
  if(streamRes==NULL){fclose(streamRes);}
  rewind(streamRes);
  int contPixel=0;
  xpos=0;
  ypos=0;
  valorPixel=0;
  int Red,Green,Blue;
  yFinal=0;
  xFinal=0;
  Synchronize(obtenerAltura);
  Synchronize(obtenerAncho);
  for (ypos=0; ypos<yFinal; ypos++)
  {
    for (xpos=0; xpos<xFinal; xpos++)
    {
      Synchronize(obtenerPixel);
      if(valorPixel<=7100000) //dato
      {
        contPixel++;
      }
      else
      {
//        Synchronize(pintarBlanco);
      }

    }
  }
//  double factor=(xFinal*yFinal/1000000.0);
//  double coef=0.0007*pow(factor,-0.9301);
//  double area=contPixel*coef;
  double area=0.013308565*double(contPixel); // bastidor entero
  double lai=area/((Xfin-Xini)*(Yfin-Yini));
  fprintf(streamRes,"%i  %f      %s\n",contPixel,float(lai),(ExtractFileName(archivoOrig)).c_str());
  fclose(streamRes);
  picture->TotalPixel[reg]=contPixel;
  picture->LAI[reg]=lai;
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::msgFinal()
{
 frmReport->msgFinal();
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::GuardarTH()
{
 imPicture->Picture->SaveToFile(archivoBitmapTH);
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::obtenerAltura()
{
 yFinal=imPicture->Picture->Height;
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::obtenerAncho()
{
 xFinal=imPicture->Picture->Width;
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::obtenerPixel()
{
 valorPixel = ColorToRGB(imPicture->Canvas->Pixels[xpos][ypos]);
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::pintarBlanco()
{
 imPicture->Canvas->Pixels[xpos][ypos]=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::cargarImagen()
{
 imPicture->Picture->LoadFromFile(archivoBMP);
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::ubicarReg_en_sglista()
{
  sgLista->Row=iReg+2;
  sgLista->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::mostrarInfo_en_sglista()
{
  sgLista->Cells[3][iReg+2]=picture->Width[iReg];
  sgLista->Cells[4][iReg+2]=picture->Height[iReg];
  if(picture->TotalPixel[iReg]==0) sgLista->Cells[5][iReg+2]="0";
  else sgLista->Cells[5][iReg+2]=FormatFloat("#,###",picture->TotalPixel[iReg]);
  if(picture->LAI[iReg]==0.0) sgLista->Cells[6][iReg+2]="0.00";
  else sgLista->Cells[6][iReg+2]=FormatFloat("#.##",picture->LAI[iReg]);
  sgLista->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::ubicarRegInicial_en_sglista()
{
  sgLista->Row=2;
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::definirMaxDeProgressBar()
{
  pbPicture->Max=TotalArchivos;
}
//---------------------------------------------------------------------------
void __fastcall ProcesoThresholdingColorNegro::avanzarProgressBar()
{
  pbPicture->Position=iReg+1;
}
//---------------------------------------------------------------------------
