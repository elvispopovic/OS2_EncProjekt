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
#include <sha.h>
#include <pssr.h>
#include <whrlpool.h>
#include <files.h>

enum VelicinaAESKljuca:unsigned char{AES_mali=16, AES_srednji=24, AES_veliki=32};
enum VelicinaRSAKljuca:unsigned short{RSA_mali=256, RSA_srednji=384, RSA_veliki=512};

struct GrafickiPodaci
{
    std::string aesKljuc, sol, iv;
    VelicinaAESKljuca velicinaAES;
    std::string privatniKljuc, javniKljuc;
    std::string sazetakAES, sazetakRSA;
    CryptoPP::SecByteBlock sbAesKljuc, sbIv, sbSol;
};

struct PorukaPodaci
{
    std::wstring oznakaAES, oznakaRSA;
    std::string sadrzajAES, sadrzajRSA;
    std::string potpisAES;
    char verificirano=0;
};

class IProjektApp
{
    public:
    /* tu ce doci metode koje koristi Glavni stroj */
    virtual void KreirajSazetakAES(const std::vector<unsigned char>& poruka)=0;
    virtual void KreirajSazetakRSA(const std::vector<unsigned char>& poruka)=0;
    virtual bool EnkriptirajPorukuAES(const std::vector<unsigned char>& poruka)=0;
    virtual bool DekriptirajPorukuAES(const std::vector<unsigned char>& poruka)=0;
    virtual bool EnkriptirajPorukuRSA(const std::vector<unsigned char>& poruka)=0;
    virtual bool DekriptirajPorukuRSA(const std::vector<unsigned char>& poruka)=0;
    virtual void DohvatiMedjuspremnikPorukeAES(std::vector<unsigned char>& poruka)=0;
    virtual void DohvatiMedjuspremnikPorukeRSA(std::vector<unsigned char>& poruka)=0;
    virtual void AzurirajGrafickePodatke(const GrafickiPodaci& podaci)=0;
    virtual void UpisiAktivneKljuceve(const std::string& aesKljuc, const std::string& iv)=0;
    virtual void ZahtijevajAzuriranjeGrafickihPodataka()=0;
    virtual void UpisiPoruku(PorukaPodaci& porukaPodaci)=0;
};

class IDijalogAES
{
    public:
};


#endif // INTERFACES_H_INCLUDED
