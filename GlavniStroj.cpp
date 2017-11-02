#include "GlavniStroj.h"

using namespace std;
using namespace CryptoPP;

GlavniStroj::GlavniStroj(IProjektApp *projektApp)
{
    this->projektApp=projektApp;
    ispis = new char[16000];
    ispisw = new wchar_t[1024];
}

GlavniStroj::~GlavniStroj()
{
    delete[] ispisw;
    delete[] ispis;
}


bool GlavniStroj::GenerirajAESKljuc(const string& lozinka, VelicinaAESKljuca& velicina, int brojIteracija, bool koristiSol, GrafickiPodaci& povratniPodaci)
{
    AutoSeededX917RNG<CryptoPP::AES> aesRng;
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    povratniPodaci.sbSol.New(velicina);
    povratniPodaci.sbIv.New(AES::BLOCKSIZE);
    povratniPodaci.sbAesKljuc.New(velicina);
    aesRng.GenerateBlock(povratniPodaci.sbSol,velicina);
    aesRng.GenerateBlock(povratniPodaci.sbIv,AES::BLOCKSIZE);
    if(lozinka.size()>0)
    {
        if(koristiSol)
            pbkdf.DeriveKey(povratniPodaci.sbAesKljuc,velicina,0x00,(byte*)(lozinka.data()),lozinka.size(),povratniPodaci.sbSol, povratniPodaci.sbSol.size(),brojIteracija);
        else
            pbkdf.DeriveKey(povratniPodaci.sbAesKljuc,velicina,0x00,(byte*)(lozinka.data()),lozinka.size(),nullptr, 0,brojIteracija);
    }
    else
        aesRng.GenerateBlock(povratniPodaci.sbAesKljuc,velicina);

    povratniPodaci.aesKljuc.assign(IspisiBinarnePodatke(povratniPodaci.sbAesKljuc.data(),povratniPodaci.sbAesKljuc.size()));
    povratniPodaci.iv.assign(IspisiBinarnePodatke(povratniPodaci.sbIv.data(),povratniPodaci.sbIv.size()));
    if(koristiSol)
        povratniPodaci.sol.assign(IspisiBinarnePodatke(povratniPodaci.sbSol.data(),povratniPodaci.sbSol.size()));
    else
        povratniPodaci.sol.assign(string(" ---"));

    return true;
}

bool GlavniStroj::GenerirajRSAKljuceve(VelicinaRSAKljuca& velicina, GrafickiPodaci& povratniPodaci)
{
    AutoSeededRandomPool rsaRng;
    privatniKljuc.GenerateRandomWithKeySize(rsaRng, velicina<<3);
    RSA::PublicKey javniKljuc(privatniKljuc);

    privatniKljuc.Save(HexEncoder(new StringSink(povratniPodaci.privatniKljuc),true,2," ").Ref());
    javniKljuc.Save(HexEncoder(new StringSink(povratniPodaci.javniKljuc),true, 2, " ").Ref());
}

bool GlavniStroj::UpisiAktivneKljuceve(CryptoPP::SecByteBlock& aesKljuc, CryptoPP::SecByteBlock& iv)
{
    this->aesKljuc=aesKljuc;
    this->iv=iv;
}

void GlavniStroj::ZahtijevajAzuriranjeGrafickihPodataka()
{
    podaci.aesKljuc.assign(IspisiBinarnePodatke(aesKljuc.data(),aesKljuc.size()));
    podaci.iv.assign(IspisiBinarnePodatke(iv.data(),iv.size()));
    projektApp->AzurirajGrafickePodatke(podaci);
}

void GlavniStroj::KreirajSazetakAES(const vector<unsigned char>& poruka)
{
    SHA224 sha;
    podaci.sazetakAES.clear();
    StringSink sazetakSink(podaci.sazetakAES);
    ArraySource(poruka.data(), poruka.size(), true, new HashFilter(sha, new HexEncoder(new Redirector(sazetakSink),true,2," ")));
    projektApp->AzurirajGrafickePodatke(podaci);
}
void GlavniStroj::KreirajSazetakRSA(const vector<unsigned char>& poruka)
{
    SHA224 sha;
    podaci.sazetakRSA.clear();
    StringSink sazetakSink(podaci.sazetakRSA);
    ArraySource(poruka.data(), poruka.size(), true, new HashFilter(sha, new HexEncoder(new Redirector(sazetakSink),true,2," ")));
    projektApp->AzurirajGrafickePodatke(podaci);
}

bool GlavniStroj::EnkriptirajPorukuAES(const vector<unsigned char>& poruka, vector<unsigned char>& enkriptirano)
{
    PorukaPodaci upis;
    CBC_Mode<CryptoPP::AES>::Encryption enkriptor;
    if(aesKljuc.size()==0)
        return false;

    int brojac=0;
    for(vector<unsigned char>::const_iterator it=poruka.begin(); brojac<80; ++it, brojac++)
            cout << (int)(*it) << " ";
    cout << endl;

    enkriptor.SetKeyWithIV(aesKljuc.BytePtr(), aesKljuc.size(), iv.BytePtr(), iv.size());
    enkriptirano.clear();
    enkriptirano.resize(poruka.size()+AES::BLOCKSIZE); //prostor za padding
    ArraySink kriptSink(&enkriptirano[0], enkriptirano.size());
    try
    {
        ArraySource(poruka.data(), poruka.size(), true, new StreamTransformationFilter(enkriptor, new Redirector(kriptSink)));
        enkriptirano.resize(kriptSink.TotalPutLength());
        if(enkriptirano.size()>512)
            sprintf(ispis, "%s...\n",IspisiBinarnePodatke(enkriptirano.data(),512).data());
        else
            sprintf(ispis, "%s\n",IspisiBinarnePodatke(enkriptirano.data(),512).data());
        swprintf(ispisw,L"Poruka - enkriptirani sadržaj");
        upis.sadrzajAES.assign(ispis);
        upis.oznakaAES.assign(ispisw);
        projektApp->UpisiPoruku(upis);
        return true;
    }
    catch(exception& e)
    {
        sprintf(ispis,"---\n");
        projektApp->UpisiPoruku(upis);
        return false;
    }
}

bool GlavniStroj::DekriptirajPorukuAES(const vector<unsigned char>& poruka, vector<unsigned char>& dekriptirano)
{
    PorukaPodaci upis;
    CBC_Mode<AES>::Decryption dekriptor;
    if(aesKljuc.size()==0)
        return false;

    dekriptor.SetKeyWithIV(aesKljuc.BytePtr(), aesKljuc.size(), iv.BytePtr(), iv.size());
    dekriptirano.clear();
    dekriptirano.resize(poruka.size());
    ArraySink dekriptSink(&dekriptirano[0], dekriptirano.size());

    try
    {
        ArraySource(poruka.data(), poruka.size(), true, new StreamTransformationFilter(dekriptor, new Redirector(dekriptSink)));
        dekriptirano.resize(dekriptSink.TotalPutLength());
        if(dekriptirano.size()>512)
            sprintf(ispis, "%s...\n",IspisiBinarnePodatke(dekriptirano.data(),512).data());
        else
            sprintf(ispis, "%s\n",IspisiBinarnePodatke(dekriptirano.data(),dekriptirano.size()).data());
        upis.sadrzajAES.assign(ispis);
        swprintf(ispisw,L"Poruka - dekriptirani sadržaj");
        upis.sadrzajAES.assign(ispis);
        upis.oznakaAES.assign(ispisw);
        projektApp->UpisiPoruku(upis);
        return true;
    }
    catch(exception& e)
    {
        sprintf(ispis,"---\n");
        projektApp->UpisiPoruku(upis);
        return false;
    }
}

bool GlavniStroj::EnkriptirajPorukuRSA(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& enkriptirano)
{
    PorukaPodaci upis;
    Integer kriptiranoBroj;
    RSA::PublicKey javniKljuc(privatniKljuc);
    if(poruka.size()>(javniKljuc.GetModulus().BitCount()>>3))
        return false;

    //PotpisiPoruku(poruka);



    Integer porukaBroj((const byte *)poruka.data(), poruka.size());
    kriptiranoBroj=javniKljuc.ApplyFunction(porukaBroj);
    size_t velicina = kriptiranoBroj.MinEncodedSize();

    enkriptirano.resize(velicina);
    kriptiranoBroj.Encode(enkriptirano.data(),enkriptirano.size());

    sprintf(ispis, "%s\n",IspisiBinarnePodatke(enkriptirano.data(),velicina).data());
    swprintf(ispisw,L"Poruka - enkriptirani sadržaj");
    upis.sadrzajRSA.assign(ispis);
    upis.oznakaRSA.assign(ispisw);
    projektApp->UpisiPoruku(upis);
    return true;
}
bool GlavniStroj::DekriptirajPorukuRSA(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& dekriptirano)
{
    PorukaPodaci upis;
    Integer dekriptiranoBroj;
    Integer porukaBroj((const byte *)poruka.data(), poruka.size());
    dekriptiranoBroj=privatniKljuc.CalculateInverse(prng,porukaBroj);
    size_t velicina=dekriptiranoBroj.MinEncodedSize();
    dekriptirano.resize(velicina);
    dekriptiranoBroj.Encode(dekriptirano.data(),dekriptirano.size());

    sprintf(ispis, "%s\n",IspisiBinarnePodatke(dekriptirano.data(),velicina).data());
    swprintf(ispisw,L"Poruka - dekriptirani sadržaj");
    upis.sadrzajRSA.assign(ispis);
    upis.oznakaRSA.assign(ispisw);
    projektApp->UpisiPoruku(upis);
    return true;
}

bool GlavniStroj::PotpisiPoruku(const vector<unsigned char>& poruka, vector<unsigned char>& potpis)
{
    std:: cout << "Potpisivanje" << std::endl;
        //char *privFileName;
    //FileSource privFile(privFileName, true, new HexDecoder);
    //RSASSA_PKCS1v15_SHA_Signer priv(privFile);
    PorukaPodaci upis;

    AutoSeededRandomPool rng;
    if(privatniKljuc.GetModulus()==0)
        return false;

    upis.potpisAES.clear();

    //RSASS<PSSR, Whirlpool>::Signer potpisivanje;
    RSASS<PSSR, SHA224>::Signer potpisivanje(privatniKljuc);
    potpis.resize(privatniKljuc.GetModulus().ByteCount());

    ArraySink potpisSink(potpis.data(),potpis.size());
    ArraySource ss1(poruka.data(), poruka.size(), true, new SignerFilter(rng,potpisivanje,&potpisSink));
    potpis.resize(potpisSink.TotalPutLength());

    ArraySource(potpis.data(), potpis.size(), true, new HexEncoder(new StringSink(upis.potpisAES),true,2," "));
    projektApp->UpisiPoruku(upis);
    return true;
}

bool GlavniStroj::VerificirajPoruku(const vector<unsigned char>& poruka, const vector<unsigned char>& potpis)
{
    std:: cout << "Verificiranje" << std::endl;
    PorukaPodaci upis;
    //char *pubFileName;
    //FileSource pubFile(pubFilename, true, new HexDecoder);
	//RSASSA_PKCS1v15_SHA_Verifier pub(pubFile);
    RSA::PublicKey javniKljuc(privatniKljuc);
    RSASS<PSSR, SHA224>::Verifier verifikacija(javniKljuc);
    bool rezultat = false;

    rezultat=verifikacija.VerifyMessage(poruka.data(),poruka.size(), potpis.data(), potpis.size());
    switch(rezultat)
    {
        case true: upis.verificirano=1; break;
        case false: upis.verificirano=-1; break;
    }
    projektApp->UpisiPoruku(upis);
    return rezultat;
}

void GlavniStroj::Test()
{
    string potpisHex;
    vector<unsigned char> poruka;
    int i;
    for(i=0; i<100; i++)
        poruka.push_back(i);


    vector<unsigned char> potpis;

    AutoSeededRandomPool rng;
    RSA::PrivateKey privatniKljuc;
    privatniKljuc.GenerateRandomWithKeySize(rng, 256*8);

    RSASS<PSSR, SHA256>::Signer potpisivanje(privatniKljuc);

    RSA::PublicKey javniKljuc(privatniKljuc);
    RSASS<PSSR, SHA256>::Verifier verifikacija(javniKljuc);


    potpis.resize(256);
    ArraySink potpisSink(potpis.data(), potpis.size());
    ArraySource as(poruka.data(), poruka.size(), true, new SignerFilter(rng, potpisivanje, &potpisSink));
    potpis.resize(potpisSink.TotalPutLength());


    ArraySource(potpis.data(), potpis.size(), true, new HexEncoder(new StringSink(potpisHex)));
    cout << "Potpis (hex): " << potpisHex << endl;


    bool rezultat = false;
    rezultat=verifikacija.VerifyMessage(poruka.data(),poruka.size(), potpis.data(), potpis.size());

    //drugi nacin: dobivanje binarnog potpisa iz heksadecimalne reprezentacije
    vector<unsigned char> potpis1;
    potpis1.resize(256);
    ArraySink potpis1Sink(potpis1.data(), potpis1.size());
    StringSource ss(potpisHex,true, new HexDecoder(&potpis1Sink));
    potpis1.resize(potpis1Sink.TotalPutLength());

    rezultat = verifikacija.VerifyMessage(poruka.data(),poruka.size(), potpis1.data(), potpis1.size());

    if(rezultat)
        std::cout << "Provjereno: OK" << std::endl;
    else
        std::cout << "Provjereno: ERROR" << std::endl;

}

string GlavniStroj::IspisiBinarnePodatke(byte *podaci, int velicina)
{
    string upis;

    /* HexEncoder preuzima objekt i na kraju ga uništava. Zato mora biti StringSink da se saèuva upis*/
    HexEncoder enkoder(new StringSink(upis),true,2," ");
    enkoder.Put(podaci,velicina);
    enkoder.MessageEnd();
    return upis;
}



