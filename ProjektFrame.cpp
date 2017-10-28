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
    Bind(wxIspisiPoruku, &ProjektFrame::IspisiPoruku, this);

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
    Unbind(wxIspisiPoruku, &ProjektFrame::IspisiPoruku, this);
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
    for(brojac = 0, it = porukaSadrzaj.begin(); it!=porukaSadrzaj.end(); ++it, ++brojac)
        if(brojac++<1024)
            upis.append(wxString::Format("%0X",(int)(*it)));
        else
        {
            upis.append(wxString("..."));
            break;
        }
    upis.append(wxString::Format(L"\n"));
    txtPoruka->Clear();
    txtPoruka->AppendText(upis);
    okvirPoruke->GetStaticBox()->SetLabel(L"Poruka - učitana datoteka");
    aplikacija->KreirajSazetak(porukaSadrzaj);

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

void ProjektFrame::AESDijalog( wxCommandEvent& event )
{
    DijalogAES *dijalog = new DijalogAES(0L,this,this->aplikacija);
    //dijalog->upisiAdreseAdaptera(adreseAdaptera);
    dijalog->Show();
}

void ProjektFrame::OsvjeziPodatke(wxCommandEvent &event)
{
    GrafickiPodaci *podaci;
    if((podaci = (GrafickiPodaci *)(event.GetClientData()))==nullptr)
        return;
    tbAESKljuc->SetValue(podaci->aesKljuc);
    tbIv->SetValue(podaci->iv);
    tbSazetak->SetValue(podaci->sazetak);
}
void ProjektFrame::IspisiPoruku(wxCommandEvent &event)
{
    PorukaPodaci *podaci;
    if((podaci = (PorukaPodaci *)(event.GetClientData()))==nullptr)
        return;
    txtPoruka->Clear();
    if(podaci->sadrzaj.size()>0)
        txtPoruka->AppendText(podaci->sadrzaj.c_str());
    if(podaci->oznaka.size()>0)
        okvirPoruke->GetStaticBox()->SetLabel(podaci->oznaka.c_str());
}

/****************************************************************************************/
/*           DIJALOG AES                                                                */
/****************************************************************************************/

DijalogAES::DijalogAES(wxFrame *frame, ProjektFrame *pf, ProjektApp *app)
    : GeneratorAES(frame)
{
    aplikacija = app;
    projektFrame = pf;
}

void DijalogAES::GenerirajAES( wxCommandEvent& event )
{
    VelicinaKljuca velicina;
    switch(radioVelicinaKljuca->GetSelection())
    {
        case 0: velicina=VelicinaKljuca::Mali; break;
        case 1: velicina=VelicinaKljuca::Srednji; break;
        case 2: velicina=VelicinaKljuca::Veliki; break;
        default: velicina=VelicinaKljuca::Srednji;
    }
    aplikacija->GenerirajAESKljuc(this, tcUnosLozinke->GetValue().ToStdString(),velicina, chkSol->GetValue(), podaci);
    tbGeneriraniAES->SetValue(podaci.aesKljuc);
    tbIv->SetValue(podaci.iv);
    tbSol->SetValue(podaci.sol);
}

void DijalogAES::odustani( wxCommandEvent& event )
{
    Destroy();
}

void DijalogAES::potvrdi( wxCommandEvent& event )
{
    aplikacija->UpisiAktivneKljuceve(podaci.sbAesKljuc, podaci.sbIv);
    aplikacija->ZahtijevajAzuriranjeGrafickihPodataka();
    Destroy();
}

void DijalogAES::zatvori( wxCloseEvent& event )
{
    aplikacija->ZahtijevajAzuriranjeGrafickihPodataka();
    Destroy();
}
