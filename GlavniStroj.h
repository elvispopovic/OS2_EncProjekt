#ifndef GLAVNISTROJ_H
#define GLAVNISTROJ_H

#include "GUIFrame.h"
#include "Interfaces.h"

class GlavniStroj : public wxFrame
{
    public:
        GlavniStroj(IProjektApp *projektApp);
        virtual ~GlavniStroj();
        virtual bool GenerirajAESKljuc(const std::string& lozinka, int brojIteracija, bool koristiSol, GrafickiPodaci& povratniPodaci);
        virtual void SnimiAESKljuc(const std::string tajniDatoteka);
        virtual bool UcitajAESKljuc(const std::string tajniDatoteka);
        virtual bool GenerirajRSAKljuceve(VelicinaRSAKljuca& velicina, GrafickiPodaci& povratniPodaci);
        virtual bool SnimiRSAKljuceve(const std::string privatniDatoteka, const std::string javniDatoteka);
        virtual bool UcitajRSAKljuceve(const std::string privatniDatoteka, const std::string javniDatoteka, GrafickiPodaci& povratniPodaci);
        virtual bool UpisiAktivneKljuceve(const std::string& aesKljuc, const std::string& iv);
        virtual void ZahtijevajAzuriranjeGrafickihPodataka();
        virtual void KreirajSazetakAES(const std::vector<unsigned char>& poruka);
        virtual void KreirajSazetakRSA(const std::vector<unsigned char>& poruka);
        virtual bool PotpisiPoruku(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& potpis);
        virtual bool VerificirajPoruku(const std::vector<unsigned char>& poruka, const std::vector<unsigned char>& potpis);
        virtual bool EnkriptirajPorukuAES(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& enkriptirano);
        virtual bool DekriptirajPorukuAES(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& dekriptirano);
        virtual bool EnkriptirajPorukuRSA(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& enkriptirano);
        virtual bool DekriptirajPorukuRSA(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& dekriptirano);

    protected:
        IProjektApp *projektApp;
        CryptoPP::AutoSeededRandomPool prng;
        CryptoPP::SecByteBlock aesKljuc, iv;
        CryptoPP::RSA::PrivateKey privatniKljuc;


    private:
        char *ispis;
        wchar_t *ispisw;
        GrafickiPodaci podaci;
        std::string IspisiBinarnePodatke(byte *podaci, int velicina);

        void Test();

};

#endif // GLAVNISTROJ_H
