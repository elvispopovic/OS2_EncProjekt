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


bool GlavniStroj::GenerirajAESKljuc(const string& lozinka, int brojIteracija, bool koristiSol, GrafickiPodaci& povratniPodaci)
{
    SecByteBlock sbAesKljuc, sbIv, sbSol;
    AutoSeededX917RNG<CryptoPP::AES> aesRng;
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    sbSol.New(povratniPodaci.velicinaAES);
    sbIv.New(AES::BLOCKSIZE);
    sbAesKljuc.New(povratniPodaci.velicinaAES);
    aesRng.GenerateBlock(sbSol,povratniPodaci.velicinaAES);
    aesRng.GenerateBlock(sbIv,AES::BLOCKSIZE);
    if(lozinka.size()>0)
    {
        if(koristiSol)
            pbkdf.DeriveKey(sbAesKljuc,povratniPodaci.velicinaAES,0x00,(byte*)(lozinka.data()),lozinka.size(),sbSol, sbSol.size(),brojIteracija);
        else
            pbkdf.DeriveKey(sbAesKljuc,povratniPodaci.velicinaAES,0x00,(byte*)(lozinka.data()),lozinka.size(),nullptr, 0,brojIteracija);
    }
    else
        aesRng.GenerateBlock(sbAesKljuc,povratniPodaci.velicinaAES);

    povratniPodaci.aesKljuc.assign(IspisiBinarnePodatke(sbAesKljuc.data(),sbAesKljuc.size()));
    povratniPodaci.iv.assign(IspisiBinarnePodatke(sbIv.data(),sbIv.size()));
    if(koristiSol)
        povratniPodaci.sol.assign(IspisiBinarnePodatke(sbSol.data(),sbSol.size()));
    else
        povratniPodaci.sol.assign(string(" ---"));

    return true;
}

void GlavniStroj::SnimiAESKljuc(const std::string tajniDatoteka)
{
    ByteQueue red;
    string nazivTajni=tajniDatoteka+".txt";
    string tajniKljucHex;
    FileSink tajniDatSink(nazivTajni.c_str());
    if(aesKljuc.size()==0)
        return;
    HexEncoder he (new StringSink(tajniKljucHex));
    he.Put(aesKljuc.size());
    he.Put(aesKljuc.BytePtr(),aesKljuc.size());
    he.Put(iv.BytePtr(),iv.size());
    red.Put(reinterpret_cast<const byte*>(tajniKljucHex.data()),tajniKljucHex.size());
    red.CopyTo(tajniDatSink);
}
bool GlavniStroj::UcitajAESKljuc(const std::string tajniDatoteka)
{
    string nazivTajni=tajniDatoteka+".txt";
    ByteQueue red;
    byte velicina;

    string test;
    try
    {
        FileSource fsTajni(nazivTajni.c_str(), false, new HexDecoder(new Redirector(red)));
        fsTajni.PumpAll();
        red.Get(velicina);
        aesKljuc.resize(velicina);
        red.Get(aesKljuc.data(),velicina);
        iv.resize(velicina);
        ArraySink asIv(iv.data(),velicina);
        red.CopyTo(asIv);
        iv.resize(asIv.TotalPutLength());
    }
    catch( ... )
    {
        return false;
    }

    ZahtijevajAzuriranjeGrafickihPodataka();
    return true;
}

bool GlavniStroj::GenerirajRSAKljuceve(VelicinaRSAKljuca& velicina, GrafickiPodaci& povratniPodaci)
{
    AutoSeededRandomPool rsaRng;
    privatniKljuc.GenerateRandomWithKeySize(rsaRng, velicina<<3);
    RSA::PublicKey javniKljuc(privatniKljuc);

    privatniKljuc.Save(HexEncoder(new StringSink(povratniPodaci.privatniKljuc),true,2," ").Ref());
    javniKljuc.Save(HexEncoder(new StringSink(povratniPodaci.javniKljuc),true, 2, " ").Ref());
    return true;
}

bool GlavniStroj::SnimiRSAKljuceve(const string privatniDatoteka, const string javniDatoteka)
{
    ByteQueue red1, red2;
    AutoSeededRandomPool rsaRng;
    RSA::PublicKey javniKljuc(privatniKljuc);

    string nazivPrivatni=privatniDatoteka+"DER.key";
    string nazivJavni=javniDatoteka+"DER.key";

    FileSink privDatSinkDER(nazivPrivatni.c_str()), javDatSinkDER(nazivJavni.c_str());
    if(!privatniKljuc.Validate(rsaRng,3))
        return false;
    privatniKljuc.DEREncodePrivateKey(red1);
    javniKljuc.DEREncodePublicKey(red2);
    red1.CopyTo(privDatSinkDER);
    privDatSinkDER.MessageEnd();
    red2.CopyTo(javDatSinkDER);
    javDatSinkDER.MessageEnd();

    string privKljucStr, javKljucStr;
    nazivPrivatni=privatniDatoteka+".txt";
    nazivJavni=javniDatoteka+".txt";
    FileSink privDatSink(nazivPrivatni.c_str()), javDatSink(nazivJavni.c_str());
    privatniKljuc.Save(HexEncoder(&privDatSink).Ref());
    javniKljuc.Save(HexEncoder(&javDatSink).Ref());
    return true;
}
bool GlavniStroj::UcitajRSAKljuceve(const std::string privatniDatoteka, const std::string javniDatoteka, GrafickiPodaci& povratniPodaci)
{
    vector<unsigned char> pkPolje;
    pkPolje.resize(1024);
    string nazivPrivatni=privatniDatoteka+".txt";
    string nazivJavni=javniDatoteka+".txt";
    ByteQueue redPrivatni, redJavni;
    try
    {
        RSA::PublicKey javniKljuc;
        FileSource fsPrivatni(nazivPrivatni.c_str(), false, new HexDecoder(new Redirector(redPrivatni)));
        fsPrivatni.PumpAll();
        FileSource fsJavni(nazivJavni.c_str(), false, new HexDecoder(new Redirector(redJavni)));
        fsJavni.PumpAll();
        privatniKljuc.Load(redPrivatni);
        javniKljuc.Load(redJavni);
        privatniKljuc.Save(HexEncoder(new StringSink(povratniPodaci.privatniKljuc),true,2," ").Ref());
        javniKljuc.Save(HexEncoder(new StringSink(povratniPodaci.javniKljuc),true,2," ").Ref());
    }
    catch( ... )
    {
        return false;
    }
    return true;
}

bool GlavniStroj::UpisiAktivneKljuceve(const string& aesKljuc, const string& iv, VelicinaAESKljuca velicinaKljuca)
{

    this->aesKljuc.resize(velicinaKljuca);
    HexDecoder he1 (new ArraySink(this->aesKljuc.BytePtr(), this->aesKljuc.size()));
    he1.Put((byte*)(aesKljuc.c_str()), aesKljuc.size());

    this->iv.resize(AES::BLOCKSIZE);
    HexDecoder he2 (new ArraySink(this->iv.BytePtr(), this->iv.size()));
    he2.Put((byte*)(iv.c_str()),iv.size());
    return true;
}

void GlavniStroj::ZahtijevajAzuriranjeGrafickihPodataka()
{
    podaci.aesKljuc.assign(IspisiBinarnePodatke(aesKljuc.data(),aesKljuc.size()));
    podaci.iv.assign(IspisiBinarnePodatke(iv.data(),iv.size()));
    projektApp->AzurirajGrafickePodatke(podaci);
}

void GlavniStroj::KreirajSazetakAES(const vector<unsigned char>& poruka)
{
    SHA256 sha;
    podaci.sazetakAES.clear();
    StringSink sazetakSink(podaci.sazetakAES);
    ArraySource(poruka.data(), poruka.size(), true, new HashFilter(sha, new HexEncoder(new Redirector(sazetakSink),true,2," ")));
    projektApp->AzurirajGrafickePodatke(podaci);
}
void GlavniStroj::KreirajSazetakRSA(const vector<unsigned char>& poruka)
{
    SHA256 sha;
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
    //FileSource privFile(privFileName, true, new HexDecoder);
    //RSASSA_PKCS1v15_SHA_Signer priv(privFile);
    //RSASS<PSSR, Whirlpool>::Signer potpisivanje;
    PorukaPodaci upis;

    AutoSeededRandomPool rng;
    if(privatniKljuc.GetModulus()==0)
        return false;
    upis.potpisAES.clear();

    RSASS<PSSR, SHA256>::Signer potpisivanje(privatniKljuc);
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

    PorukaPodaci upis;
    RSA::PublicKey javniKljuc(privatniKljuc);
    RSASS<PSSR, SHA256>::Verifier verifikacija(javniKljuc);
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



