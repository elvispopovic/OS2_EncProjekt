/***************************************************************
 * Name:      ProjektApp.h
 * Purpose:   Defines Application Class
 * Author:    Elvis Popović (elvpopovi@foi.hr)
 * Created:   2017-10-17
 * Copyright: Elvis Popović ()
 * License:
 **************************************************************/

#ifndef PROJEKTAPP_H
#define PROJEKTAPP_H
#include <wx/wx.h>
#include <wx/app.h>
#include <mutex>
#include "GlavniStroj.h"
#include "Interfaces.h"

class ProjektApp : public wxApp, IProjektApp
{
    public:
        virtual bool OnInit();
        virtual int  OnExit();
        virtual void GenerirajAESKljuc(const std::string& lozinka, VelicinaKljuca velicina, bool koristiSol);
        virtual void EnkriptirajPoruku(const std::vector<unsigned char>& poruka);
        virtual void DekriptirajPoruku(const std::vector<unsigned char>& poruka);
        virtual void DohvatiMedjuspremnikPoruke(std::vector<unsigned char>& poruka);
        virtual void AzurirajGrafickePodatke(const GrafickiPodaci& podaci);
        virtual void UpisiPoruku(std::wstring& sadrzaj);
    protected:
        std::mutex m_upisULog;
        wxEvtHandler *wxGlavnaFormaDest;
    private:
        bool ispisivanjeDozvoljeno;
        std::mutex m_grafickiPodaci;
        std::vector<unsigned char> medjuspremnikPoruke;
        GrafickiPodaci *grafickiPodaci;
        GlavniStroj *glavniStroj;
};

#endif // PROJEKTAPP_H
