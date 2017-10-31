#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

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

enum VelicinaAESKljuca:unsigned char{AES_mali=16, AES_srednji=24, AES_veliki=32};
enum VelicinaRSAKljuca:unsigned short{RSA_mali=128, RSA_srednji=256, RSA_veliki=384};

struct GrafickiPodaci
{
    std::string aesKljuc, sol, iv;
    std::string privatniKljuc, javniKljuc;
    std::string sazetak;
    CryptoPP::SecByteBlock sbAesKljuc, sbIv, sbSol;
};

struct PorukaPodaci
{
    std::wstring oznaka;
    std::string sadrzaj;
};

class IProjektApp
{
    public:
    /* tu ce doci metode koje koristi Glavni stroj */
    virtual void KreirajSazetak(const std::vector<unsigned char>& poruka)=0;
    virtual bool EnkriptirajPoruku(const std::vector<unsigned char>& poruka)=0;
    virtual bool DekriptirajPoruku(const std::vector<unsigned char>& poruka)=0;
    virtual void DohvatiMedjuspremnikPoruke(std::vector<unsigned char>& poruka)=0;
    virtual void AzurirajGrafickePodatke(const GrafickiPodaci& podaci)=0;
    virtual void UpisiAktivneKljuceve(CryptoPP::SecByteBlock& aesKljuc, CryptoPP::SecByteBlock& iv)=0;
    virtual void ZahtijevajAzuriranjeGrafickihPodataka()=0;
    virtual void UpisiPoruku(PorukaPodaci& porukaPodaci)=0;
};

class IDijalogAES
{
    public:
};


#endif // INTERFACES_H_INCLUDED
