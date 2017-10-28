#ifndef GLAVNISTROJ_H
#define GLAVNISTROJ_H

#include "GUIFrame.h"
#include "Interfaces.h"

class GlavniStroj : public wxFrame
{
    public:
        GlavniStroj(IProjektApp *projektApp);
        virtual ~GlavniStroj();
        virtual bool GenerirajAESKljuc(const std::string& lozinka, VelicinaKljuca& velicina, int brojIteracija, bool koristiSol, GrafickiPodaci& povratniPodaci);
        virtual bool UpisiAktivneKljuceve(CryptoPP::SecByteBlock& aesKljuc, CryptoPP::SecByteBlock& iv);
        virtual void ZahtijevajAzuriranjeGrafickihPodataka();
        virtual void KreirajSazetak(const std::vector<unsigned char>& poruka);
        virtual void EnkriptirajPoruku(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& enkriptirano);
        virtual void DekriptirajPoruku(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& dekriptirano);

    protected:
        IProjektApp *projektApp;
        CryptoPP::SecByteBlock aesKljuc, iv;

    private:
        char *ispis;
        wchar_t *ispisw;
        GrafickiPodaci podaci;
        std::string IspisiBinarnePodatke(byte *podaci, int velicina);

};

#endif // GLAVNISTROJ_H
