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

void ProjektApp::GenerirajAESKljuc(IDijalogAES *dijalog, const std::string& lozinka, VelicinaAESKljuca velicina, bool koristiSol, GrafickiPodaci& povratniPodaci)
{
    glavniStroj->GenerirajAESKljuc(lozinka,velicina,1024, koristiSol, povratniPodaci);
}
void ProjektApp::GenerirajRSAKljuceve(VelicinaRSAKljuca& velicina, GrafickiPodaci& povratniPodaci)
{
    glavniStroj->GenerirajRSAKljuceve(velicina, povratniPodaci);
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

void ProjektApp::DohvatiMedjuspremnikPorukeAES(std::vector<unsigned char>& poruka)
{
    poruka=medjuspremnikPorukeAES;
}
void ProjektApp::DohvatiMedjuspremnikPorukeRSA(std::vector<unsigned char>& poruka)
{
    poruka=medjuspremnikPorukeRSA;
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

void ProjektApp::UpisiAktivneKljuceve(CryptoPP::SecByteBlock& aesKljuc, CryptoPP::SecByteBlock& iv)
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
    dogadjajUpis->SetClientData((void *)(this->porukaPodaci));
    wxQueueEvent( wxGlavnaFormaDest, dogadjajUpis );
}
