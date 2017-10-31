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
        virtual void GenerirajAESKljuc(IDijalogAES *dijalog, const std::string& lozinka, VelicinaAESKljuca velicina, bool koristiSol, GrafickiPodaci& povratniPodaci);
        virtual void GenerirajRSAKljuceve(VelicinaRSAKljuca& velicina, GrafickiPodaci& povratniPodaci);
        virtual void KreirajSazetak(const std::vector<unsigned char>& poruka);
        virtual bool EnkriptirajPoruku(const std::vector<unsigned char>& poruka);
        virtual bool DekriptirajPoruku(const std::vector<unsigned char>& poruka);
        virtual void DohvatiMedjuspremnikPoruke(std::vector<unsigned char>& poruka);
        virtual void AzurirajGrafickePodatke(const GrafickiPodaci& podaci);
        virtual void UpisiAktivneKljuceve(CryptoPP::SecByteBlock& aesKljuc, CryptoPP::SecByteBlock& iv);
        virtual void ZahtijevajAzuriranjeGrafickihPodataka();
        virtual void UpisiPoruku(PorukaPodaci& porukaPodaci);
    protected:
        wxEvtHandler *wxGlavnaFormaDest;
    private:
        bool ispisivanjeDozvoljeno;
        std::mutex m_grafickiPodaci, m_porukaPodaci;
        std::vector<unsigned char> medjuspremnikPoruke;
        GrafickiPodaci *grafickiPodaci;
        PorukaPodaci *porukaPodaci;
        GlavniStroj *glavniStroj;
};

#endif // PROJEKTAPP_H
