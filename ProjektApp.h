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
        virtual void GenerirajAESKljuc(IDijalogAES *dijalog, const std::string& lozinka, bool koristiSol, GrafickiPodaci& povratniPodaci);
        virtual void SnimiAESKljuc();
        virtual bool UcitajAESKljuc();
        virtual void GenerirajRSAKljuceve(VelicinaRSAKljuca& velicina, GrafickiPodaci& povratniPodaci);
        virtual void SnimiRSAKljuceve();
        virtual bool UcitajRSAKljuceve(GrafickiPodaci& povratniPodaci);
        virtual void KreirajSazetakAES(const std::vector<unsigned char>& poruka);
        virtual void KreirajSazetakRSA(const std::vector<unsigned char>& poruka);
        virtual bool EnkriptirajPorukuAES(const std::vector<unsigned char>& poruka);
        virtual bool DekriptirajPorukuAES(const std::vector<unsigned char>& poruka);
        virtual bool EnkriptirajPorukuRSA(const std::vector<unsigned char>& poruka);
        virtual bool DekriptirajPorukuRSA(const std::vector<unsigned char>& poruka);
        virtual bool PotpisiPoruku(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& potpis);
        virtual bool VerificirajPoruku(const std::vector<unsigned char>& poruka, std::vector<unsigned char>& potpis);
        virtual void SnimiPotpis(const std::string& nazivDatoteke, const std::vector<unsigned char>& potpis);
        virtual bool UcitajPotpis(const std::string& nazivDatoteke, std::vector<unsigned char>& potpis);
        virtual void UpisiMedjuspremnikPorukeAES(const std::vector<unsigned char>& poruka);
        virtual void DohvatiMedjuspremnikPorukeAES(std::vector<unsigned char>& poruka);
        virtual void UpisiMedjuspremnikPorukeRSA(const std::vector<unsigned char>& poruka);
        virtual void DohvatiMedjuspremnikPorukeRSA(std::vector<unsigned char>& poruka);
        virtual void AzurirajGrafickePodatke(const GrafickiPodaci& podaci);
        virtual void UpisiAktivneKljuceve(const std::string& aesKljuc, const std::string& iv);
        virtual void ZahtijevajAzuriranjeGrafickihPodataka();
        virtual void UpisiPoruku(PorukaPodaci& porukaPodaci);
    protected:
        wxEvtHandler *wxGlavnaFormaDest;
    private:
        bool ispisivanjeDozvoljeno;
        std::mutex m_grafickiPodaci, m_porukaPodaci;
        std::vector<unsigned char> medjuspremnikPorukeAES, medjuspremnikPorukeRSA;
        GrafickiPodaci *grafickiPodaci;
        PorukaPodaci *porukaPodaci;
        GlavniStroj *glavniStroj;
};

#endif // PROJEKTAPP_H
