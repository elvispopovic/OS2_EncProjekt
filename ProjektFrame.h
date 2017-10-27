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
wxDECLARE_EVENT(wxIspisiULog, wxCommandEvent);

class ProjektFrame: public GUIFrame
{
    public:
        ProjektFrame(wxFrame *frame, ProjektApp *app);
        ~ProjektFrame();
    protected:
        virtual void GenerirajAES( wxCommandEvent& event );
    private:
        ProjektApp *aplikacija;
        std::vector<unsigned char> porukaSadrzaj;
        virtual void OnClose(wxCloseEvent& event);
        virtual void UcitajPoruku( wxCommandEvent& event );
        virtual void KriptirajPoruku( wxCommandEvent& event );

        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OsvjeziPodatke(wxCommandEvent &event);
        virtual void UpisiULog(wxCommandEvent &event);
};

#endif // PROJEKTMAIN_H
