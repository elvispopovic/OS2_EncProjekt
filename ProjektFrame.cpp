/***************************************************************
 * Name:      ProjektMain.cpp
 * Purpose:   Code for Application Frame
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

#include <wx/wfstream.h>
#include <wx/txtstrm.h>

#include <wx/filedlg.h>
#include <wx/stdpaths.h>

#include <sstream>
#include <iomanip>

#include "ProjektFrame.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


ProjektFrame::ProjektFrame(wxFrame *frame, ProjektApp *app)
    : GUIFrame(frame)
{
    aplikacija = app;
    Bind(wxOsvjeziPodatke, &ProjektFrame::OsvjeziPodatke, this);
    Bind(wxIspisiULog, &ProjektFrame::UpisiULog, this);

#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("Hello Code::Blocks user!"), 0);
    statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif
}

ProjektFrame::~ProjektFrame()
{

}

void ProjektFrame::OnClose(wxCloseEvent &event)
{
    Unbind(wxIspisiULog, &ProjektFrame::UpisiULog, this);
    Unbind(wxOsvjeziPodatke, &ProjektFrame::OsvjeziPodatke, this);
    Destroy();
}
void ProjektFrame::UcitajPoruku( wxCommandEvent& event )
{
    wchar_t ispis[3];
    wxString upis;
    int brojac;
    wxFileDialog openFileDialog(this, _("Ucitaj poruku"), "", "",
                       "textualne datoteke (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    /* postavljanje direktorija iz kojeg se pokrece aplikacija*/
    wxFileName imeDatoteke(wxStandardPaths::Get().GetExecutablePath());
    openFileDialog.SetDirectory(imeDatoteke.GetPath());
    /* otvaranje dijaloga */
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;


    /* zakomentirano se odnosi na učitavanje tekstualne datoteke
    /*
    std::wstringstream ss;
    wxFileInputStream sadrzaj(openFileDialog.GetPath());
    if (!sadrzaj.IsOk())
    {
        wxLogError("Ne mogu otvoriti datoteku '%s'.", openFileDialog.GetPath());
        return;
    }
    wxTextInputStream tekst(sadrzaj, wxT("\x09"), wxConvUTF8 );
    txtPoruka->Clear();
    while(sadrzaj.IsOk() && !sadrzaj.Eof() )
        txtPoruka->AppendText(tekst.ReadLine()+"\n");
        */

    std::ifstream citanje_datoteke( openFileDialog.GetPath().ToAscii(), std::ios::binary );
    porukaSadrzaj.assign((std::istreambuf_iterator<char>(citanje_datoteke)), (std::istreambuf_iterator<char>()));

    std::vector<unsigned char>::iterator it;
    upis.Printf(L"Učitana je datoteka sadržaja:\n");
    for(brojac = 0, it = porukaSadrzaj.begin(); it!=porukaSadrzaj.end(); ++it, ++brojac)
        if(brojac++<1024)
            upis.append(wxString::Format("%0X",(int)(*it)));
        else
        {
            upis.append(wxString("..."));
            break;
        }
    upis.append(wxString::Format(L"\n"));
    txtPoruka->AppendText(upis);

    btnKriptirajPoruku->Enable();
    btnKriptirajPoruku->SetLabel(wxT("Enkriptiraj"));
}

void ProjektFrame::KriptirajPoruku( wxCommandEvent& event )
{
    if(!(porukaSadrzaj.empty())&&(aplikacija!=nullptr))
        if(btnKriptirajPoruku->GetLabel()==wxString(L"Enkriptiraj"))
        {
            aplikacija->EnkriptirajPoruku(porukaSadrzaj);
            aplikacija->DohvatiMedjuspremnikPoruke(porukaSadrzaj);
            btnKriptirajPoruku->SetLabel(wxT("Dekriptiraj"));
        }
        else
        {
            aplikacija->DekriptirajPoruku(porukaSadrzaj);
            aplikacija->DohvatiMedjuspremnikPoruke(porukaSadrzaj);
            btnKriptirajPoruku->SetLabel(wxT("Enkriptiraj"));
        }
}



void ProjektFrame::OnQuit(wxCommandEvent &event)
{
    Unbind(wxOsvjeziPodatke, &ProjektFrame::OsvjeziPodatke, this);
    Destroy();
}

void ProjektFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Podrav! "));
}

void ProjektFrame::GenerirajAES( wxCommandEvent& event )
{
    VelicinaKljuca velicina;
    switch(radioVelicinaKljuca->GetSelection())
    {
        case 0: velicina=VelicinaKljuca::Mali; break;
        case 1: velicina=VelicinaKljuca::Srednji; break;
        case 2: velicina=VelicinaKljuca::Veliki; break;
        default: velicina=VelicinaKljuca::Srednji;
    }
    aplikacija->GenerirajAESKljuc(tcUnosLozinke->GetValue().ToStdString(),velicina, chkSol->GetValue());
}

void ProjektFrame::OsvjeziPodatke(wxCommandEvent &event)
{
    GrafickiPodaci *podaci;
    if(tbGeneriraniAES==nullptr||tbIv==nullptr||tbSol==nullptr)
        return;
    if((podaci = (GrafickiPodaci *)(event.GetClientData()))==nullptr)
        return;
    tbGeneriraniAES->SetValue(podaci->aesKljuc);
    tbIv->SetValue(podaci->iv);
    tbSol->SetValue(podaci->sol);
}
void ProjektFrame::UpisiULog(wxCommandEvent &event)
{
    txtPoruka->Clear();
    wxString ispis(event.GetString());
    if(ispis.size()>0)
        txtPoruka->AppendText(ispis.c_str());
}
