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

enum VelicinaKljuca:unsigned char{Mali=16, Srednji=24, Veliki=32};

struct GrafickiPodaci
{
    std::string aesKljuc, sol, iv;
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
    virtual void EnkriptirajPoruku(const std::vector<unsigned char>& poruka)=0;
    virtual void DekriptirajPoruku(const std::vector<unsigned char>& poruka)=0;
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
