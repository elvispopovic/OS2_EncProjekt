#ifndef GLAVNISTROJ_H
#define GLAVNISTROJ_H

#include <modes.h>
#include <aes.h>
#include <sha.h>
#include <filters.h>
#include <hex.h>
#include <base64.h>
#include <osrng.h>
#include <hkdf.h>
#include <pwdbased.h>
#include <rsa.h>
#include <files.h>

#include "GUIFrame.h"
#include "Interfaces.h"

class GlavniStroj : public wxFrame
{
    public:
        GlavniStroj(IProjektApp *projektApp);
        virtual ~GlavniStroj();
        virtual bool GenerirajAESKljuc(const std::string& lozinka, VelicinaKljuca& velicina, int brojIteracija, bool koristiSol);
        virtual void KreirajSazetak(const std::vector<unsigned char>& poruka);
        virtual void EnkriptirajPoruku(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& enkriptirano);
        virtual void DekriptirajPoruku(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& dekriptirano);

    protected:
        IProjektApp *projektApp;
        CryptoPP::SecByteBlock aesKljuc, iv, sol;

    private:
        wchar_t *ispis;
        GrafickiPodaci podaci;
        std::string IspisiBinarnePodatke(byte *podaci, int velicina);

};

#endif // GLAVNISTROJ_H
