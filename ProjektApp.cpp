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
wxDEFINE_EVENT(wxIspisiULog, wxCommandEvent);

bool ProjektApp::OnInit()
{
    ProjektFrame* frame = new ProjektFrame(0L, this);
    grafickiPodaci = new GrafickiPodaci;
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
    return 0;
}

void ProjektApp::GenerirajAESKljuc(const std::string& lozinka, VelicinaKljuca velicina, bool koristiSol)
{
    glavniStroj->GenerirajAESKljuc(lozinka,velicina,1024, koristiSol);
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

void ProjektApp::AzurirajGrafickePodatke(const GrafickiPodaci& podaci)
{
    std::lock_guard<std::mutex> lock( m_grafickiPodaci );
    wxCommandEvent *commandEvent = new wxCommandEvent(wxOsvjeziPodatke);
    commandEvent->SetEventObject( (wxObject *)this );
    grafickiPodaci->aesKljuc.assign(podaci.aesKljuc);
    grafickiPodaci->iv.assign(podaci.iv);
    grafickiPodaci->sol.assign(podaci.sol);
    commandEvent->SetEventObject( (wxObject *)this );
    commandEvent->SetClientData((void *)grafickiPodaci);
    wxQueueEvent( wxGlavnaFormaDest, commandEvent );
}

void ProjektApp::UpisiPoruku(std::wstring& sadrzaj)
{
    wxCommandEvent *dogadjajUpis = new wxCommandEvent(wxIspisiULog);
    std::lock_guard<std::mutex> lock( m_upisULog);
    if(ispisivanjeDozvoljeno==false)
        return;
    dogadjajUpis->SetEventObject( (wxObject *)this );
    dogadjajUpis->SetString( sadrzaj.c_str() );
    wxQueueEvent( wxGlavnaFormaDest, dogadjajUpis );
}
