namespace modeling
{
  class Picture
  {
   public:
     Picture(int,int);
     ~Picture();
     char** FileName;
     int* Height;
     int* Width;
     int* TotalPixel;
     int rgb[100][3];
     double* LAI;
     char** TimeDuration;
     void CleanVariables();
     int GetTotalRecords();
     void SubtractOneRecord();
     void CleanRecord(int);
     void DeleteRecord(int);
     int tolerance;
     int totalRGB;
     void addRGB(int,int,int,int);
     bool SaveOutput;
   private:
     int CharNum;
     int RecNum;
  };
}
