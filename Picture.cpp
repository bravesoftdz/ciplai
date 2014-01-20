#ifndef PictureH
#define PictureH
#include "Picture.h"
#include <fstream>
#include "vector.h"
#include "sstream.h"
using namespace modeling;
//------------------------------------------------------------------------------
//  Picture class
//------------------------------------------------------------------------------
Picture::Picture(int nreg,int nchar)
{
 RecNum=0;
 CharNum=0;
 RecNum=nreg;
 CharNum=nchar;
 FileName=NULL;
 Height=NULL;
 Width=NULL;
 tolerance=0;
 totalRGB=0;
 TotalPixel=NULL;
 LAI=NULL;
 TimeDuration=NULL;
 SaveOutput=false;

 FileName=new char*[RecNum];
 for(int i=0;i<RecNum;i++)
   FileName[i]=new char[CharNum+1];
 Height=new int[RecNum];
 Width=new int[RecNum];
 TotalPixel=new int[RecNum];
 LAI=new double[RecNum];
 TimeDuration=new char*[RecNum];
 for(int i=0;i<RecNum;i++)
   TimeDuration[i]=new char[CharNum+1];
 CleanVariables();
}
//------------------------------------------------------------------------------
Picture::~Picture()
{
 CleanVariables();
 if (FileName != NULL)
 {
   for(int i=0;i<RecNum;i++)
     delete[] FileName[i];
   delete[] FileName;
   FileName=NULL;
 }
 if (Height != NULL)
 {
  delete[]Height;
  Height=NULL;
 }
 if (Width != NULL)
 {
  delete[]Width;
  Width=NULL;
 }
 if (TotalPixel != NULL)
 {
  delete[]TotalPixel;
  TotalPixel=NULL;
 }
 if (LAI != NULL)
 {
  delete[]LAI;
  LAI=NULL;
 }
 if (TimeDuration != NULL)
 {
   for(int i=0;i<RecNum;i++)
     delete[] TimeDuration[i];
   delete[] TimeDuration;
   TimeDuration=NULL;
 }
 CharNum=0;
 RecNum=0;
}
//------------------------------------------------------------------------------
void Picture::CleanVariables()
{
  // limpia variables igualandolas a cero
  for(int i=0;i<RecNum;i++)
  {
    CleanRecord(i);
  }
}
//------------------------------------------------------------------------------
int Picture::GetTotalRecords()
{
  return RecNum;
}
//------------------------------------------------------------------------------
void Picture::SubtractOneRecord()
{
  RecNum--;
}
//------------------------------------------------------------------------------
void Picture::CleanRecord(int rec)
{
    Height[rec]=0;
    Width[rec]=0;
    tolerance=0;
    totalRGB=0;
    TotalPixel[rec]=0;
    LAI[rec]=0.0;
    strcpy(FileName[rec],"");
    strcpy(TimeDuration[rec],"");
}
//------------------------------------------------------------------------------
void Picture::DeleteRecord(int rec)
{
  int i,j;
/*
  if(rec==0)
  {
    CleanRecord(rec);
    SubtractOneRecord();
    return;
  }
*/  
  // se verifica si es el último registro
  if(rec==RecNum-1)
  { // es ultimo
    CleanRecord(rec);
    SubtractOneRecord();
    return;
  }
  if(rec<RecNum-1)
  { // no es ultimo
    for(i=rec;i<RecNum-1;i++)
    {
      Height[i]=Height[i+1];
      Width[i]=Width[i+1];
      TotalPixel[i]=TotalPixel[i+1];
      LAI[i]=LAI[i+1];
      strcpy(FileName[i],FileName[i+1]);
      strcpy(TimeDuration[i],TimeDuration[i+1]);
    }
    CleanRecord(RecNum-1);
    SubtractOneRecord();
  }
}
//---------------------------------------------------------------------------
void Picture::addRGB(int red,int green, int blue,int reg)
{
  rgb[reg][0]=red;
  rgb[reg][1]=green;
  rgb[reg][2]=blue;
}
//---------------------------------------------------------------------------
#endif

