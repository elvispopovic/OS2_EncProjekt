#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED

enum VelicinaKljuca:unsigned char{Mali=16, Srednji=24, Veliki=32};

struct GrafickiPodaci
{
    int test = 16;
    std::string aesKljuc;
    std::string sol;
    std::string iv;
    std::string sazetak;
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
    virtual void UpisiPoruku(std::wstring& sadrzaj)=0;
};


#endif // INTERFACES_H_INCLUDED
