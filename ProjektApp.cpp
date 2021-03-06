/***************************************************************
 * Name:      ProjektApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Elvis Popović (elvpopovi@foi.hr)
 * Created:   2017-10-17
 * Copyright: Elvis Popović ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ProjektApp.h"
#include "ProjektFrame.h"

IMPLEMENT_APP(ProjektApp);

wxDEFINE_EVENT(wxOsvjeziPodatke, wxCommandEvent);
wxDEFINE_EVENT(wxIspisiPoruku, wxCommandEvent);

bool ProjektApp::OnInit()
{
    ProjektFrame* frame = new ProjektFrame(0L, this);
    grafickiPodaci = new GrafickiPodaci;
    porukaPodaci = new PorukaPodaci;
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();
    wxGlavnaFormaDest = (wxEvtHandler*)frame;
    glavniStroj = new GlavniStroj(this);

    ispisivanjeDozvoljeno=true;
    return true;
}

int ProjektApp::OnExit()
{
    ispisivanjeDozvoljeno=false;
    delete glavniStroj;
    delete grafickiPodaci;
    delete porukaPodaci;
    return 0;
}

void ProjektApp::GenerirajAESKljuc(IDijalogAES *dijalog, const std::string& lozinka, bool koristiSol, GrafickiPodaci& povratniPodaci)
{
    glavniStroj->GenerirajAESKljuc(lozinka,1024, koristiSol, povratniPodaci);
}
void ProjektApp::SnimiAESKljuc()
{
    glavniStroj->SnimiAESKljuc("tajni_kljuc");
}
bool ProjektApp::UcitajAESKljuc()
{
    return glavniStroj->UcitajAESKljuc("tajni_kljuc");
}

void ProjektApp::GenerirajRSAKljuceve(VelicinaRSAKljuca& velicina, GrafickiPodaci& povratniPodaci)
{
    glavniStroj->GenerirajRSAKljuceve(velicina, povratniPodaci);
}
void ProjektApp::SnimiRSAKljuceve()
{
    glavniStroj->SnimiRSAKljuceve("privatni_kljuc","javni_kljuc");
}
bool ProjektApp::UcitajRSAKljuceve(GrafickiPodaci& povratniPodaci)
{
    return glavniStroj->UcitajRSAKljuceve("privatni_kljuc","javni_kljuc", povratniPodaci);
}

bool ProjektApp::EnkriptirajPorukuAES(const std::vector<unsigned char>& poruka)
{
    return glavniStroj->EnkriptirajPorukuAES(poruka, medjuspremnikPorukeAES);
}
bool ProjektApp::DekriptirajPorukuAES(const std::vector<unsigned char>& poruka)
{
    return glavniStroj->DekriptirajPorukuAES(poruka, medjuspremnikPorukeAES);
}
bool ProjektApp::EnkriptirajPorukuRSA(const std::vector<unsigned char>& poruka)
{
    return glavniStroj->EnkriptirajPorukuRSA(poruka, medjuspremnikPorukeRSA);
}
bool ProjektApp::DekriptirajPorukuRSA(const std::vector<unsigned char>& poruka)
{
    return glavniStroj->DekriptirajPorukuRSA(poruka, medjuspremnikPorukeRSA);
}
bool ProjektApp::PotpisiPoruku(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& potpis)
{
    return glavniStroj->PotpisiPoruku(poruka, potpis);
}
bool ProjektApp::VerificirajPoruku(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& potpis)
{
    return glavniStroj->VerificirajPoruku(poruka, potpis);
}
void ProjektApp::SnimiPotpis(const std::string& nazivDatoteke, const std::vector<unsigned char>& potpis)
{
    glavniStroj->SnimiPotpis(nazivDatoteke, potpis);
}
bool ProjektApp::UcitajPotpis(const std::string& nazivDatoteke, std::vector<unsigned char>& potpis)
{
    return glavniStroj->UcitajPotpis(nazivDatoteke, potpis);
}

void ProjektApp::DohvatiMedjuspremnikPorukeAES(std::vector<unsigned char>& poruka)
{
    poruka=medjuspremnikPorukeAES;
}
void ProjektApp::DohvatiMedjuspremnikPorukeRSA(std::vector<unsigned char>& poruka)
{
    poruka=medjuspremnikPorukeRSA;
}
void ProjektApp::UpisiMedjuspremnikPorukeAES(const std::vector<unsigned char>& poruka)
{
    medjuspremnikPorukeAES=poruka;
}
void ProjektApp::UpisiMedjuspremnikPorukeRSA(const std::vector<unsigned char>& poruka)
{
    medjuspremnikPorukeRSA=poruka;
}


void ProjektApp::KreirajSazetakAES(const std::vector<unsigned char>& poruka)
{
    glavniStroj->KreirajSazetakAES(poruka);
}
void ProjektApp::KreirajSazetakRSA(const std::vector<unsigned char>& poruka)
{
    glavniStroj->KreirajSazetakRSA(poruka);
}

void ProjektApp::AzurirajGrafickePodatke(const GrafickiPodaci& podaci)
{
    if(ispisivanjeDozvoljeno==false)
        return;
    std::lock_guard<std::mutex> lock( m_grafickiPodaci );
    wxCommandEvent *commandEvent = new wxCommandEvent(wxOsvjeziPodatke);
    commandEvent->SetEventObject( (wxObject *)this );
    grafickiPodaci->aesKljuc.assign(podaci.aesKljuc);
    grafickiPodaci->iv.assign(podaci.iv);
    grafickiPodaci->sol.assign(podaci.sol);
    grafickiPodaci->sazetakAES.assign(podaci.sazetakAES);
    grafickiPodaci->sazetakRSA.assign(podaci.sazetakRSA);
    commandEvent->SetEventObject( (wxObject *)this );
    commandEvent->SetClientData((void *)grafickiPodaci);
    wxQueueEvent( wxGlavnaFormaDest, commandEvent );
}

void ProjektApp::UpisiAktivneKljuceve(const std::string& aesKljuc, const std::string& iv)
{
    glavniStroj->UpisiAktivneKljuceve(aesKljuc, iv);
}

void ProjektApp::ZahtijevajAzuriranjeGrafickihPodataka()
{
    glavniStroj->ZahtijevajAzuriranjeGrafickihPodataka();
}

void ProjektApp::UpisiPoruku(PorukaPodaci& porukaPodaci)
{
    if(ispisivanjeDozvoljeno==false)
        return;
    std::lock_guard<std::mutex> lock( m_porukaPodaci );
    wxCommandEvent *dogadjajUpis = new wxCommandEvent(wxIspisiPoruku);
    dogadjajUpis->SetEventObject( (wxObject *)this );
    this->porukaPodaci->oznakaAES = porukaPodaci.oznakaAES;
    this->porukaPodaci->sadrzajAES = porukaPodaci.sadrzajAES;
    this->porukaPodaci->oznakaRSA = porukaPodaci.oznakaRSA;
    this->porukaPodaci->sadrzajRSA = porukaPodaci.sadrzajRSA;
    this->porukaPodaci->potpisAES = porukaPodaci.potpisAES;
    this->porukaPodaci->verificirano=porukaPodaci.verificirano;
    dogadjajUpis->SetClientData((void *)(this->porukaPodaci));
    wxQueueEvent( wxGlavnaFormaDest, dogadjajUpis );
}
