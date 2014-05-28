//---------------------------------------------------------------------------
#include <FileCtrl.hpp>
#include <vcl.h>
#pragma hdrstop
#include "Picture.cpp"
#include "UMain.h"
#include "UImageView.h"
#include "UReport.h"
#include "UCargarImagenes.h"
#include "UAbout.h"
#include "UHelp.h"
#include "UPresentation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
TfrmImageView *frmImage;
TfrmReport *frmRep;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
  TfrmPresentation* frm=new TfrmPresentation(this);
  frm->ShowModal();
  if(frm!=NULL)
  {
    delete frm;
    frm=NULL;
  }
  kindOpen=0;
  opicdiag->InitialDir=ExtractFileDir(Application->ExeName);
  ErrorPicture=Application->ExeName;
  ErrorPicture=ExtractFileDir(ErrorPicture);
  ErrorPicture=ErrorPicture+"\\bitmap.bmp";
  InitialPicture=Application->ExeName;
  InitialPicture=ExtractFileDir(InitialPicture);
  InitialPicture=InitialPicture+"\\initial.bmp";
  FileNotPicture=Application->ExeName;
  FileNotPicture=ExtractFileDir(FileNotPicture);
  FileNotPicture=FileNotPicture+"\\filenot.bmp";

  picture=NULL;
  picture=new Picture(0,0);

  frmImage= NULL;
  frmImage= new TfrmImageView(this);
  frmImage->Show();
  frmImage->Top=100;
  frmImage->Left=30;

  frmRep= NULL;
  frmRep= new TfrmReport(this);
  frmRep->Show();
  frmRep->Visible=false;
  int anchoRep;
  int anchoMain;
  anchoMain=this->Width;
  anchoRep=frmRep->Width;
  frmRep->Left=anchoMain-anchoRep-40;
  frmRep->Top=90;
  frmRep->SetPicture(frmImage);
  frmRep->SetErrorPicture(ErrorPicture);
  frmRep->SetFileNotPicture(FileNotPicture);
  frmRep->SetInitialPicture(InitialPicture);
  frmRep->SetPictureInformation(picture);
  processing=false;
  edFolderOutput->Text=ExtractFileDir(Application->ExeName);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::sbExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::sbOpenFileClick(TObject *Sender)
{
if(!processing)
{
if(opicdiag->Execute())
{
  AnsiString ArchivoImagen;
  bool conforme=false;
  ArchivoImagen=opicdiag->FileName; // devuelve ruta con nombre del archivo
  conforme=frmImage->CargarImagen(ArchivoImagen,0);
  if(conforme)
  {
    kindOpen=1; // 1: Open one picture
    TotalArchivos=1;
    // Crear clase picture
    if(picture!=NULL)
    {
      delete picture;
      picture=NULL;
    }
    picture=NULL;
    int tamanio=ArchivoImagen.Length();
    picture=new Picture(1,tamanio);
    // capturar información de la imágen
    strcpy(picture->FileName[0],ArchivoImagen.c_str());
    TImage *Image2=new TImage(this);
    Image2->Picture->LoadFromFile(ArchivoImagen);
    picture->Height[0]=Image2->Picture->Height;
    picture->Width[0]=Image2->Picture->Width;
    delete(Image2);
    // actualiza el Status Bar
    ModificarStatusBar(ArchivoImagen);
    AbrirFormularioReporte(true);
    frmRep->ShowRecords();
    frmImage->SetFocus();
    frmRep->frmImage3->Visible=false;
    frmRep->processed=false;
  }
  else
  {
    AnsiString mensaje;
    mensaje="The file '"+ ExtractFileName(ArchivoImagen) + "' can not be displayed !";
    Application->MessageBoxA(mensaje.c_str(),"Warning!");
  }
}
}
}
//---------------------------------------------------------------------------
void TfrmMain::ModificarStatusBar(AnsiString InArchivoDato)
{
  StatusBar1->Panels->Items[1]->Text=" "+InArchivoDato;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::AbrirFormularioReporte(bool mostrar)
{
  frmRep->SetPictureInformation(picture);
  frmRep->Visible=mostrar;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::sbReportClick(TObject *Sender)
{
  AbrirFormularioReporte(true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::sbOpenFilesClick(TObject *Sender)
{
// muestro el formulario
if(!processing)
{
AnsiString Caption = "Select a Folder of pictures";
const WideString Root = "C:\"";
AnsiString Directory = "C:\\";

if(SelectDirectory(Caption, Root, Directory))
{
  kindOpen=2; // open many pctures
  flbFiles->Directory=Directory;
  TotalArchivos=flbFiles->Count;
  // Crear clase picture
  if(picture!=NULL)
  {
    delete picture;
    picture=NULL;
  }
  picture=NULL;

  int tamanio=0;
  AnsiString archivo="";
  for(int i=0;i<TotalArchivos;i++)
  {
    archivo=Directory+"\\"+flbFiles->Items->Strings[i];
    if(archivo.Length()>tamanio) tamanio=archivo.Length();
  }
  picture=new Picture(TotalArchivos,tamanio);
  // capturar información de la imágen
  for(int i=0;i<TotalArchivos;i++)
  {
    archivo=Directory+"\\"+flbFiles->Items->Strings[i];
    strcpy(picture->FileName[i],archivo.c_str());

    TImage *Image2=new TImage(this);
    try
    {
      Image2->Picture->LoadFromFile(archivo);
      picture->Height[i]=Image2->Picture->Height;
      picture->Width[i]=Image2->Picture->Width;
    }
    catch(...)
    {
      picture->Height[i]=0;
      picture->Width[i]=0;
    }
    delete(Image2);
  }
  // se visualiza la primera imágen
  if(picture->GetTotalRecords()==0)
  {
    frmImage->CargarImagen(InitialPicture,1);
    frmMain->ModificarStatusBar(archivo);
  }
  else
  {
    bool conforme=frmImage->CargarImagen(picture->FileName[0],0);
    if(conforme) frmMain->ModificarStatusBar(picture->FileName[0]);
    if(!conforme)
    {
      frmImage->CargarImagen(ErrorPicture,2);
      frmMain->ModificarStatusBar("");
    }
  }
  // actualiza el Status Bar
  AbrirFormularioReporte(true);
  frmRep->ShowRecords();
  frmRep->frmImage3->Visible=false;
  frmImage->SetFocus();
  frmRep->processed=false;
}
}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::sbEmptyFileListClick(TObject *Sender)
{
  if(!processing)
  {
    if(picture!=NULL)
    {
      delete picture;
      picture=NULL;
    }
    frmRep->Limpiar_sgLista();
    frmImage->CargarImagen(InitialPicture,1);
    frmMain->ModificarStatusBar("");
    frmRep->processed=false;
    frmRep->frmImage3->Visible=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::sbCalculateClick(TObject *Sender)
{
if(!processing)
{
// VALIDATION PROCESS
// validate quantity of pictures
  int TotalArchivos=picture->GetTotalRecords();
  if(TotalArchivos<=0)
  {
    ShowMessage("There is not pictures to process!");
    return;
  }
// validate value of threshold
  try
  {
    threshold=Edit1->Text.ToDouble();
    if(threshold<-1 || threshold>1)
    {
      ShowMessage("Threshold should be a number between -1 to 1!");
      Edit1->SetFocus();
      return;
    }
  }
  catch(...)
  {
    ShowMessage("Threshold should be a number between -1 to 1!");
    Edit1->SetFocus();
    return;
  }
// validate folder for output
  if(cbSave->Checked)
  {
    int num=edFolderOutput->Text.Length();
    if(num==0)
    {
      ShowMessage("Enter a folder name for saving the output!");
      return;
    }
    else
    {// validate if exists the folder
      if (!DirectoryExists(edFolderOutput->Text))
      {
        ShowMessage("The output folder doesn't exist, please enter a correct output folder !");
        edFolderOutput->SelectAll();
        edFolderOutput->SetFocus();
        return;
      }
    }
    picture->SaveOutput=true;
  }
  else
  {
    picture->SaveOutput=false;
  }
// validate size of rule en pixels
  int sizeRulePx=0;
  try
  {
    sizeRulePx=Edit2->Text.ToInt();
    if(sizeRulePx<=0)
    {
      ShowMessage("Size of rule in pixels should be a number greater than 0!");
      Edit2->SetFocus();
      return;
    }
  }
  catch(...)
  {
    ShowMessage("Size of rule in pixels should be a number greater than 0!");
    Edit2->SetFocus();
    return;
  }
// validate size of rule en centimetros
  int sizeRuleCm=0;
  try
  {
    sizeRuleCm=Edit3->Text.ToInt();
    if(sizeRuleCm<=0)
    {
      ShowMessage("Size of rule in cm should be a number greater than 0!");
      Edit3->SetFocus();
      return;
    }
  }
  catch(...)
  {
    ShowMessage("Size of rule in cm should be a number greater than 0!");
    Edit3->SetFocus();
    return;
  }
// validate plant distance
  double plantDist=0;
  try
  {
    plantDist=Edit4->Text.ToDouble();
    if(plantDist<=0)
    {
      ShowMessage("Plant distance should be a number greater than 0!");
      Edit4->SetFocus();
      return;
    }
  }
  catch(...)
  {
    ShowMessage("Plant distance should be a number greater than 0!");
    Edit4->SetFocus();
    return;
  }
// validate row distance
  double rowDist=0;
  try
  {
    rowDist=Edit5->Text.ToDouble();
    if(rowDist<=0)
    {
      ShowMessage("Row distance should be a number greater than 0!");
      Edit5->SetFocus();
      return;
    }
  }
  catch(...)
  {
    ShowMessage("Row distance should be a number greater than 0!");
    Edit5->SetFocus();
    return;
  }
// validate Number of plant per picture
  int plantxPic=0;
  try
  {
    plantxPic=Edit6->Text.ToDouble();
    if(plantxPic<=0)
    {
      ShowMessage("Number of plant per picture should be a number greater than 0!");
      Edit6->SetFocus();
      return;
    }
  }
  catch(...)
  {
    ShowMessage("Number of plant per picture should be a number greater than 0!");
    Edit6->SetFocus();
    return;
  }
// process
  frmRep->processed=false;
  frmRep->sgLista->Enabled=false;
  frmRep->lblWorking->Visible=true;
// process
  processing=true;
  AnsiString FolderOutput;
  FolderOutput=edFolderOutput->Text;
  frmRep->CalculateAreaOfPictureClassic(threshold,kindOpen,FolderOutput,sizeRulePx,sizeRuleCm,plantDist,rowDist,plantxPic);
  HabilitarAplicacion();
}
}
//---------------------------------------------------------------------------
void TfrmMain::HabilitarAplicacion()
{
  frmRep->sgLista->Enabled=true;
  frmRep->lblWorking->Visible=false;
  frmRep->pbPicture->Position=0;
  processing=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Aboutmodel1Click(TObject *Sender)
{
  TfrmAbout* frm = new TfrmAbout(this);
  frm->ShowModal();
  delete frm;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Clearall1Click(TObject *Sender)
{
  frmRep->GuardarReporte();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Help2Click(TObject *Sender)
{
  TfrmHelp* frm = new TfrmHelp(this);
  frm->ShowModal();
  delete frm;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Edit1Change(TObject *Sender)
{
processing=false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::cbSaveClick(TObject *Sender)
{
  if(cbSave->Checked)
  {
    edFolderOutput->Enabled=true;
    butFolderOutput->Enabled=true;
  }
  else
  {
    edFolderOutput->Enabled=false;
    butFolderOutput->Enabled=false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::butFolderOutputClick(TObject *Sender)
{
	AnsiString Caption = "Select a Output Folder";
	const WideString Root = "C:\"";
	AnsiString Directory = "C:\\";
	if(SelectDirectory(Caption, Root, Directory))
        {
          edFolderOutput->Text=Directory;
        }
}
//---------------------------------------------------------------------------
void TfrmMain::setEdit(int valor)
{
  Edit2->Text=valor;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Userguide1Click(TObject *Sender)
{
  AnsiString archivo=ExtractFileDir(Application->ExeName);
  archivo=archivo+"\\readme.chm";
  ShellExecute(Handle,"open",archivo.c_str(),0,0,SW_MAXIMIZE);
}
//---------------------------------------------------------------------------

