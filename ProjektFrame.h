/***************************************************************
 * Name:      ProjektMain.h
 * Purpose:   Defines Application Frame
 * Author:    Elvis Popović (elvpopovi@foi.hr)
 * Created:   2017-10-17
 * Copyright: Elvis Popović ()
 * License:
 **************************************************************/

#ifndef PROJEKTMAIN_H
#define PROJEKTMAIN_H

#include "ProjektApp.h"
#include "GUIFrame.h"

wxDECLARE_EVENT(wxOsvjeziPodatke, wxCommandEvent);
wxDECLARE_EVENT(wxIspisiPoruku, wxCommandEvent);

class ProjektFrame : public GUIFrame
{
    public:
        ProjektFrame(wxFrame *frame, ProjektApp *app);
        ~ProjektFrame();
    protected:
        virtual void AESDijalog( wxCommandEvent& event );
    private:
        ProjektApp *aplikacija;
        std::vector<unsigned char> porukaSadrzajAES, porukaSadrzajRSA;
        std::vector<unsigned char> porukaPotpisivanje, potpis;
        virtual void OnClose(wxCloseEvent& event);
        virtual void snimiAESKljuc( wxCommandEvent& event );
        virtual void ucitajAESKljuc( wxCommandEvent& event );
        virtual void UcitajPorukuAES( wxCommandEvent& event );
        virtual void SnimiPorukuAES( wxCommandEvent& event );
        virtual void SnimiSifratAES( wxCommandEvent& event );
        virtual void UcitajSifratAES( wxCommandEvent& event );

        virtual void UcitajPorukuRSA( wxCommandEvent& event );
        virtual void SnimiPorukuRSA( wxCommandEvent& event );
        virtual void SnimiSifratRSA( wxCommandEvent& event );
        virtual void UcitajSifratRSA( wxCommandEvent& event );
        virtual void UcitajPoruku( wxCommandEvent& event );
        virtual void KriptirajPorukuAES( wxCommandEvent& event );
        virtual void KriptirajPorukuRSA( wxCommandEvent& event );
        virtual void GenerirajRSA( wxCommandEvent& event );
        virtual void snimiRSAKljuceve( wxCommandEvent& event );
        virtual void ucitajRSAKljuceve( wxCommandEvent& event );
        virtual void PotpisiPoruku( wxCommandEvent& event );
        virtual void Verificiraj( wxCommandEvent& event );


        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OsvjeziPodatke(wxCommandEvent &event);
        virtual void IspisiPoruku(wxCommandEvent &event);
};

class DijalogAES : public GeneratorAES, IDijalogAES
{
public:
        DijalogAES(wxFrame *frame, ProjektFrame *pf, ProjektApp *app);
private:
        ProjektApp *aplikacija;
        ProjektFrame *projektFrame;
        GrafickiPodaci podaci;
        virtual void GenerirajAES( wxCommandEvent& event );
		virtual void odustani( wxCommandEvent& event );
		virtual void potvrdi( wxCommandEvent& event );
		virtual void zatvori( wxCloseEvent& event );
};

#endif // PROJEKTMAIN_H
