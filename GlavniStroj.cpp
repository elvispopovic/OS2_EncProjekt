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

    privatniKljuc.Save(HexEncoder(new CryptoPP::StringSink(povratniPodaci.privatniKljuc)).Ref());
    javniKljuc.Save(HexEncoder(new CryptoPP::StringSink(povratniPodaci.javniKljuc)).Ref());
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

void GlavniStroj::KreirajSazetak(const vector<unsigned char>& poruka)
{
    SHA512 sha;
    StringSink sazetakSink(podaci.sazetak);
    ArraySource(poruka.data(), poruka.size(), true, new HashFilter(sha, new HexEncoder(new Redirector(sazetakSink))));
    projektApp->AzurirajGrafickePodatke(podaci);

}

bool GlavniStroj::EnkriptirajPoruku(const vector<unsigned char>& poruka, vector<unsigned char>& enkriptirano)
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
    enkriptirano.resize(poruka.size()+AES::BLOCKSIZE); //prostor za padding
    ArraySink kriptSink(&enkriptirano[0], enkriptirano.size());
    try
    {
        ArraySource(poruka.data(), poruka.size(), true, new StreamTransformationFilter(enkriptor, new Redirector(kriptSink)));
        enkriptirano.resize(kriptSink.TotalPutLength());
        if(poruka.size()>512)
            sprintf(ispis, "%s...\n",IspisiBinarnePodatke(enkriptirano.data(),512).data());
        else
            sprintf(ispis, "%s\n",IspisiBinarnePodatke(enkriptirano.data(),512).data());
        swprintf(ispisw,L"Poruka - enkriptirani sadržaj");
        upis.sadrzaj.assign(ispis);
        upis.oznaka.assign(ispisw);
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

bool GlavniStroj::DekriptirajPoruku(const vector<unsigned char>& poruka, vector<unsigned char>& dekriptirano)
{
    PorukaPodaci upis;
    CBC_Mode<AES>::Decryption dekriptor;
    if(aesKljuc.size()==0)
        return false;



    dekriptor.SetKeyWithIV(aesKljuc.BytePtr(), aesKljuc.size(), iv.BytePtr(), iv.size());
    dekriptirano.resize(poruka.size());
    ArraySink dekriptSink(&dekriptirano[0], dekriptirano.size());

    try
    {
        ArraySource(poruka.data(), poruka.size(), true, new StreamTransformationFilter(dekriptor, new Redirector(dekriptSink)));
        dekriptirano.resize(dekriptSink.TotalPutLength());


        int brojac=0;
        for(vector<unsigned char>::const_iterator it=dekriptirano.begin(); brojac<80; ++it, brojac++)
            cout << (int)(*it) << " ";
        cout << endl;


        if(poruka.size()>512)
            sprintf(ispis, "%s...\n",IspisiBinarnePodatke(dekriptirano.data(),512).data());
        else
            sprintf(ispis, "%s\n",IspisiBinarnePodatke(dekriptirano.data(),512).data());
        upis.sadrzaj.assign(ispis);
        swprintf(ispisw,L"Poruka - dekriptirani sadržaj");
        upis.sadrzaj.assign(ispis);
        upis.oznaka.assign(ispisw);
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

string GlavniStroj::IspisiBinarnePodatke(byte *podaci, int velicina)
{
    string upis;

    /* HexEncoder preuzima objekt i na kraju ga uništava. Zato mora biti StringSink da se saèuva upis*/
    HexEncoder enkoder(new StringSink(upis));
    enkoder.Put(podaci,velicina);
    enkoder.MessageEnd();
    return upis;
}



