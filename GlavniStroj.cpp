#include "GlavniStroj.h"

using namespace std;
using namespace CryptoPP;

GlavniStroj::GlavniStroj(IProjektApp *projektApp)
{
    this->projektApp=projektApp;
    ispis = new wchar_t[16000];
    //GenerirajAESKljuc(string("Ovo je lozinka"),VelicinaKljuca::SREDNJI, 1024);
}

GlavniStroj::~GlavniStroj()
{
    delete[] ispis;
}

bool GlavniStroj::GenerirajAESKljuc(const string& lozinka, VelicinaKljuca& velicina, int brojIteracija, bool koristiSol=true)
{
    AutoSeededX917RNG<CryptoPP::AES> aesRng;
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    sol.New(velicina);
    iv.New(AES::BLOCKSIZE);
    aesKljuc.New(velicina);
    aesRng.GenerateBlock(sol,velicina);
    aesRng.GenerateBlock(iv,AES::BLOCKSIZE);
    if(lozinka.size()>0)
    {
        if(koristiSol)
            pbkdf.DeriveKey(aesKljuc,velicina,0x00,(byte*)(lozinka.data()),lozinka.size(),sol, sol.size(),brojIteracija);
        else
            pbkdf.DeriveKey(aesKljuc,velicina,0x00,(byte*)(lozinka.data()),lozinka.size(),nullptr, 0,brojIteracija);
    }
    else
        aesRng.GenerateBlock(aesKljuc,velicina);

    podaci.aesKljuc.assign(IspisiBinarnePodatke(aesKljuc.data(),aesKljuc.size()));
    podaci.iv.assign(IspisiBinarnePodatke(iv.data(),iv.size()));
    if(koristiSol)
        podaci.sol.assign(IspisiBinarnePodatke(sol.data(),sol.size()));
    else
        podaci.sol.assign(string(" ---"));

    projektApp->AzurirajGrafickePodatke(podaci);

}

void GlavniStroj::KreirajSazetak(const vector<unsigned char>& poruka)
{
    SHA512 sha;
    StringSink sazetakSink(podaci.sazetak);
    ArraySource(poruka.data(), poruka.size(), true, new HashFilter(sha, new HexEncoder(new Redirector(sazetakSink))));
    projektApp->AzurirajGrafickePodatke(podaci);

}

void GlavniStroj::EnkriptirajPoruku(const vector<unsigned char>& poruka, vector<unsigned char>& enkriptirano)
{
    wstring upis;
    CBC_Mode<CryptoPP::AES>::Encryption enkriptor;
    if(aesKljuc.size()==0)
        return;
    enkriptor.SetKeyWithIV(aesKljuc.BytePtr(), aesKljuc.size(), iv.BytePtr(), iv.size());
    enkriptirano.resize(poruka.size()+AES::BLOCKSIZE); //prostor za padding
    ArraySink kriptSink(&enkriptirano[0], enkriptirano.size());
    try
    {
        ArraySource(poruka.data(), poruka.size(), true, new StreamTransformationFilter(enkriptor, new Redirector(kriptSink)));
        enkriptirano.resize(kriptSink.TotalPutLength());
        if(poruka.size()>512)
            swprintf(ispis, L"Kriptirani sadržaj:\n%s...\n",IspisiBinarnePodatke(enkriptirano.data(),512).data());
        else
            swprintf(ispis, L"Kriptirani sadržaj:\n%s\n",IspisiBinarnePodatke(enkriptirano.data(),512).data());
        upis.assign(ispis);
    }
    catch(exception& e)
    {
        swprintf(ispis,L"Dogodila se iznimka: poruka se ne može enkriptirati.\n");
    }
    projektApp->UpisiPoruku(upis);
}

void GlavniStroj::DekriptirajPoruku(const vector<unsigned char>& poruka, vector<unsigned char>& dekriptirano)
{
    wstring upis;
    CBC_Mode<AES>::Decryption dekriptor;
    if(aesKljuc.size()==0)
        return;
    dekriptor.SetKeyWithIV(aesKljuc.BytePtr(), aesKljuc.size(), iv.BytePtr(), iv.size());
    dekriptirano.resize(poruka.size());
    ArraySink dekriptSink(&dekriptirano[0], dekriptirano.size());

    try
    {
        ArraySource(poruka.data(), poruka.size(), true, new StreamTransformationFilter(dekriptor, new Redirector(dekriptSink)));
        dekriptirano.resize(dekriptSink.TotalPutLength());
        if(poruka.size()>512)
            swprintf(ispis, L"Dekriptirani sadržaj:\n%s...\n",IspisiBinarnePodatke(dekriptirano.data(),512).data());
        else
            swprintf(ispis, L"Dekriptirani sadržaj:\n%s\n",IspisiBinarnePodatke(dekriptirano.data(),512).data());
        upis.assign(ispis);
    }
    catch(exception& e)
    {
        swprintf(ispis,L"Dogodila se iznimka: poruka ne sadrži potreban format za dekriptiranje.\n");
    }
    projektApp->UpisiPoruku(upis);
}

string GlavniStroj::IspisiBinarnePodatke(byte *podaci, int velicina)
{
    string upis;
    /* HexEncoder preuzima objekt i na kraju ga uništava. Zato mora biti StringSink da se saèuva upis*/
    HexEncoder enkoder(new StringSink(upis));
    enkoder.Put(podaci,velicina);
    enkoder.MessageEnd();
    return upis;
}



