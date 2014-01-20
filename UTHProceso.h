//---------------------------------------------------------------------------

#ifndef UTHProcesoH
#define UTHProcesoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class ProcesoThresholdingColorNegro : public TThread
{
private:
        AnsiString archivoOrig;
        AnsiString archivo;
        AnsiString ArchRes;
        int Xini;
        int Xfin;
        int Yini;
        int Yfin;
        int reg;
        int iReg;
        TStringGrid *sgLista;
        TImage *imPicture;
        TProgressBar *pbPicture;
        int ypos,xpos;
        long valorPixel;
        AnsiString archivoBMP;
        int TotalArchivos;
protected:
        void __fastcall proceso(AnsiString,AnsiString,int,int,int,int,int);
        void __fastcall msgFinal();
        void __fastcall Execute();
        void __fastcall GuardarTH();
        void __fastcall obtenerAltura();
        void __fastcall obtenerAncho();
        void __fastcall obtenerPixel();
        void __fastcall pintarBlanco();
        void __fastcall cargarImagen();
        void __fastcall ubicarReg_en_sglista();
        void __fastcall mostrarInfo_en_sglista();
        void __fastcall ubicarRegInicial_en_sglista();
        void __fastcall definirMaxDeProgressBar();
        void __fastcall avanzarProgressBar();

        AnsiString archivoBitmapTH;
        int yFinal,xFinal;
public:
        __fastcall ProcesoThresholdingColorNegro(bool CreateSuspended,TStringGrid *,TProgressBar *);
        __fastcall ~ProcesoThresholdingColorNegro();

};
//---------------------------------------------------------------------------
#endif
