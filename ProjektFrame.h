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
        std::vector<unsigned char> porukaSadrzaj;
        virtual void OnClose(wxCloseEvent& event);
        virtual void UcitajPoruku( wxCommandEvent& event );
        virtual void KriptirajPoruku( wxCommandEvent& event );
        virtual void GenerirajRSA( wxCommandEvent& event );
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
