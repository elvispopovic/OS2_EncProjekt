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

void ProjektApp::GenerirajAESKljuc(IDijalogAES *dijalog, const std::string& lozinka, VelicinaKljuca velicina, bool koristiSol, GrafickiPodaci& povratniPodaci)
{
    glavniStroj->GenerirajAESKljuc(lozinka,velicina,1024, koristiSol, povratniPodaci);
}

void ProjektApp::EnkriptirajPoruku(const std::vector<unsigned char>& poruka)
{
    glavniStroj->EnkriptirajPoruku(poruka, medjuspremnikPoruke);
}

void ProjektApp::DekriptirajPoruku(const std::vector<unsigned char>& poruka)
{
    glavniStroj->DekriptirajPoruku(poruka, medjuspremnikPoruke);
}
void ProjektApp::DohvatiMedjuspremnikPoruke(std::vector<unsigned char>& poruka)
{
    poruka=medjuspremnikPoruke;
}

void ProjektApp::KreirajSazetak(const std::vector<unsigned char>& poruka)
{
    glavniStroj->KreirajSazetak(poruka);
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
    grafickiPodaci->sazetak.assign(podaci.sazetak);
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
    this->porukaPodaci->oznaka = porukaPodaci.oznaka;
    this->porukaPodaci->sadrzaj = porukaPodaci.sadrzaj;
    dogadjajUpis->SetClientData((void *)(this->porukaPodaci));
    wxQueueEvent( wxGlavnaFormaDest, dogadjajUpis );
}
