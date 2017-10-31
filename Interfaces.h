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
    std::string sazetakAES, sazetakRSA;
    CryptoPP::SecByteBlock sbAesKljuc, sbIv, sbSol;
};

struct PorukaPodaci
{
    std::wstring oznakaAES, oznakaRSA;
    std::string sadrzajAES, sadrzajRSA;
};

class IProjektApp
{
    public:
    /* tu ce doci metode koje koristi Glavni stroj */
    virtual void KreirajSazetakAES(const std::vector<unsigned char>& poruka)=0;
    virtual void KreirajSazetakRSA(const std::vector<unsigned char>& poruka)=0;
    virtual bool EnkriptirajPorukuAES(const std::vector<unsigned char>& poruka)=0;
    virtual bool DekriptirajPorukuAES(const std::vector<unsigned char>& poruka)=0;
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
