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
        wxbuild << _T("-Windows\n");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac\n");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux\n");
#endif

#if wxUSE_UNICODE
        wxbuild << wxT("Unicode kompilacija sa hrvatskim znakovima\n");
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
    statusBar->SetStatusText(_("Biblioteka: Crypto++ v.5.6.4"), 0);
    statusBar->SetStatusText("GUI: "+wxbuildinfo(short_f), 1);
    statusBar->SetStatusText(wxT("Autor: Elvis Popović"),2);
#endif

    biljeznica->SetPageText(0,wxT("Simetrično kriptiranje"));
    biljeznica->SetPageText(1,wxT("Asimetrično kriptiranje"));
    biljeznica->SetPageText(2,wxT("Digitalno potpisivanje"));
    //biljeznica->GetPage(2)->Hide();
    biljeznica->SetSelection(0);
    Refresh();
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
void ProjektFrame::snimiAESKljuc( wxCommandEvent& event )
{
    const int rezultat = MessageBox(NULL, L"Datoteka AES ključa i inicijalizacijskog vektora\nbit će prepisana i stari sadržaj zamijenjen novim.\nŽelite li nastaviti?",
                                    L"Snimanje AES ključa i IV u datoteku",  MB_YESNO | MB_ICONQUESTION);
    if(rezultat==IDNO)
        return;
    aplikacija->SnimiAESKljuc();
}
void ProjektFrame::ucitajAESKljuc( wxCommandEvent& event )
{
    aplikacija->UcitajAESKljuc();
    if(biljeznica->GetSelection()!=0)
        biljeznica->SetSelection(0);
}

void ProjektFrame::UcitajPoruku( wxCommandEvent& event )
{
    int stranica;
    stranica = biljeznica->GetSelection();
    switch(stranica)
    {
        case 0: this->UcitajPorukuAES(event); break;
        case 1: this->UcitajPorukuRSA(event); break;
        case 2: this->UcitajPorukuAES(event); break;
    }
}

void ProjektFrame::UcitajPorukuAES( wxCommandEvent& event )
{
    wchar_t ispis[3];
    wxString upis;
    int brojac;
    wxFileDialog openFileDialog(this, wxT("Učitaj datoteku"), "", "",
                       "sve datoteke (*.*)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
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

    porukaSadrzajAES.clear();
    std::ifstream citanje_datoteke( openFileDialog.GetPath().ToAscii(), std::ios::binary );
    porukaSadrzajAES.assign((std::istreambuf_iterator<char>(citanje_datoteke)), (std::istreambuf_iterator<char>()));
    citanje_datoteke.close();
    porukaPotpisivanje.clear();
    porukaPotpisivanje.insert(porukaPotpisivanje.end(),porukaSadrzajAES.begin(),porukaSadrzajAES.end());

    std::vector<unsigned char>::iterator it;
    for(brojac = 0, it = porukaSadrzajAES.begin(); it!=porukaSadrzajAES.end(); ++it, ++brojac)
        if(brojac++<1024)
            upis.append(wxString::Format("%02X ",(int)(*it)));
        else
        {
            upis.append(wxString("..."));
            break;
        }
    upis.append(wxString::Format(L"\n"));
    txtAESPoruka->Clear();
    txtAESPoruka->AppendText(upis);
    txtAESPorukaPotpis->Clear();
    txtAESPorukaPotpis->AppendText(upis);

    okvirPorukeAES->GetStaticBox()->SetLabel(L"Poruka - učitana datoteka");
    aplikacija->KreirajSazetakAES(porukaSadrzajAES);

    btnKriptirajPorukuAES->Enable();
    btnSnimiPorukuAES->Enable();
    btnKriptirajPorukuAES->SetLabel(wxT("Enkriptiraj"));
}
void ProjektFrame::SnimiPorukuAES( wxCommandEvent& event )
{
    wxFileDialog saveFileDialog(this, wxT("Snimi poruku"), "", "",
                       wxT("sve datoteke (*.*)|*.*"), wxFD_SAVE);
    wxFileName imeDatoteke(wxStandardPaths::Get().GetExecutablePath());
    saveFileDialog.SetDirectory(imeDatoteke.GetPath());
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    std::ofstream snimanje_u_datoteku( saveFileDialog.GetPath().ToAscii(), std::ios::binary );
    std::copy(porukaSadrzajAES.begin(), porukaSadrzajAES.end(), std::ostreambuf_iterator<char>(snimanje_u_datoteku));
	snimanje_u_datoteku.close();
}

void ProjektFrame::SnimiSifratAES( wxCommandEvent& event )
{
    wxFileDialog saveFileDialog(this, wxT("Snimi šifrat"), "", "",
                       wxT("datoteke šifrata (*.aes)|*.aes"), wxFD_SAVE);
    wxFileName imeDatoteke(wxStandardPaths::Get().GetExecutablePath());
    saveFileDialog.SetDirectory(imeDatoteke.GetPath());
    /* otvaranje dijaloga */
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    std::ofstream snimanje_u_datoteku( saveFileDialog.GetPath().ToAscii(), std::ios::binary );
    //snimanje_u_datoteku.write(reinterpret_cast<char *>(&porukaSadrzajAES[0]), porukaSadrzajAES.size());
    std::copy(porukaSadrzajAES.begin(), porukaSadrzajAES.end(), std::ostreambuf_iterator<char>(snimanje_u_datoteku));
	snimanje_u_datoteku.close();
}
void ProjektFrame::UcitajSifratAES( wxCommandEvent& event )
{
    wchar_t ispis[3];
    wxString upis;
    int brojac;
    wxFileDialog openFileDialog(this, wxT("Učitaj enkriptiranu datoteku"), "", "",
                       "datoteke aes šifrata (*.aes)|*.aes", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    wxFileName imeDatoteke(wxStandardPaths::Get().GetExecutablePath());
    openFileDialog.SetDirectory(imeDatoteke.GetPath());
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;
    std::ifstream citanje_datoteke( openFileDialog.GetPath().ToAscii(), std::ios::binary );
    porukaSadrzajAES.assign((std::istreambuf_iterator<char>(citanje_datoteke)), (std::istreambuf_iterator<char>()));
    citanje_datoteke.close();
    porukaPotpisivanje.clear();
    aplikacija->UpisiMedjuspremnikPorukeAES(porukaSadrzajAES);
    std::vector<unsigned char>::iterator it;
    for(brojac = 0, it = porukaSadrzajAES.begin(); it!=porukaSadrzajAES.end(); ++it, ++brojac)
        if(brojac++<1024)
            upis.append(wxString::Format("%02X ",(int)(*it)));
        else
        {
            upis.append(wxString("..."));
            break;
        }
    upis.append(wxString::Format(L"\n"));
    txtAESPoruka->Clear();
    txtAESPoruka->AppendText(upis);
    tbSazetakAES->Clear();
    txtAESPorukaPotpis->Clear();

    okvirPorukeAES->GetStaticBox()->SetLabel(L"Poruka - učitan AES šifrat");
    btnKriptirajPorukuAES->Enable();
    btnKriptirajPorukuAES->SetLabel(wxT("Dekriptiraj"));
    btnSnimiPorukuAES->Disable();
    btnSnimiSifratAES->Enable();

}

void ProjektFrame::UcitajPorukuRSA( wxCommandEvent& event )
{
    wxString upis;
    int brojac;
    wxFileDialog openFileDialog(this, wxT("Učitaj datoteku"), "", "",
                       "sve datoteke (*.*)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    wxFileName imeDatoteke(wxStandardPaths::Get().GetExecutablePath());
    openFileDialog.SetDirectory(imeDatoteke.GetPath());
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    std::ifstream citanje_datoteke( openFileDialog.GetPath().ToAscii(), std::ios::binary );
    porukaSadrzajRSA.assign((std::istreambuf_iterator<char>(citanje_datoteke)), (std::istreambuf_iterator<char>()));
    std::vector<unsigned char>::iterator it;
    for(brojac = 0, it = porukaSadrzajRSA.begin(); it!=porukaSadrzajRSA.end(); ++it, ++brojac)
        if(brojac++<1024)
            upis.append(wxString::Format("%02X ",(int)(*it)));
        else
        {
            upis.append(wxString("..."));
            break;
        }
    upis.append(wxString::Format(L"\n"));
    txtRSAPoruka->Clear();
    txtRSAPoruka->AppendText(upis);
    okvirPorukeRSA->GetStaticBox()->SetLabel(L"Poruka - učitana datoteka");
    aplikacija->KreirajSazetakRSA(porukaSadrzajRSA);

    btnKriptirajPorukuRSA->Enable();
    btnKriptirajPorukuRSA->SetLabel(wxT("Enkriptiraj"));
    btnSnimiPorukuRSA->Enable();
    btnSnimiSifratRSA->Disable();
}
void ProjektFrame::SnimiPorukuRSA( wxCommandEvent& event )
{
    wxFileDialog saveFileDialog(this, wxT("Snimi poruku"), "", "",
                       wxT("sve datoteke (*.*)|*.*"), wxFD_SAVE);
    wxFileName imeDatoteke(wxStandardPaths::Get().GetExecutablePath());
    saveFileDialog.SetDirectory(imeDatoteke.GetPath());
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    std::ofstream snimanje_u_datoteku( saveFileDialog.GetPath().ToAscii(), std::ios::binary );
    std::copy(porukaSadrzajRSA.begin(), porukaSadrzajRSA.end(), std::ostreambuf_iterator<char>(snimanje_u_datoteku));
	snimanje_u_datoteku.close();
}

void ProjektFrame::SnimiSifratRSA( wxCommandEvent& event )
{
    wxFileDialog saveFileDialog(this, wxT("Snimi RSA šifrat"), "", "",
                       wxT("datoteke RSA šifrata (*.rsa)|*.rsa"), wxFD_SAVE);
    wxFileName imeDatoteke(wxStandardPaths::Get().GetExecutablePath());
    saveFileDialog.SetDirectory(imeDatoteke.GetPath());
    /* otvaranje dijaloga */
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    std::ofstream snimanje_u_datoteku( saveFileDialog.GetPath().ToAscii(), std::ios::binary );
    //snimanje_u_datoteku.write(reinterpret_cast<char *>(&porukaSadrzajAES[0]), porukaSadrzajAES.size());
    std::copy(porukaSadrzajRSA.begin(), porukaSadrzajRSA.end(), std::ostreambuf_iterator<char>(snimanje_u_datoteku));
	snimanje_u_datoteku.close();
}
void ProjektFrame::UcitajSifratRSA( wxCommandEvent& event )
{
    wchar_t ispis[3];
    wxString upis;
    int brojac;
    wxFileDialog openFileDialog(this, wxT("Učitaj enkriptiranu datoteku"), "", "",
                       "datoteke rsa šifrata (*.rsa)|*.rsa", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    wxFileName imeDatoteke(wxStandardPaths::Get().GetExecutablePath());
    openFileDialog.SetDirectory(imeDatoteke.GetPath());
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;
    std::ifstream citanje_datoteke( openFileDialog.GetPath().ToAscii(), std::ios::binary );
    porukaSadrzajRSA.assign((std::istreambuf_iterator<char>(citanje_datoteke)), (std::istreambuf_iterator<char>()));
    citanje_datoteke.close();

    aplikacija->UpisiMedjuspremnikPorukeRSA(porukaSadrzajRSA);
    std::vector<unsigned char>::iterator it;
    for(brojac = 0, it = porukaSadrzajRSA.begin(); it!=porukaSadrzajRSA.end(); ++it, ++brojac)
        if(brojac++<1024)
            upis.append(wxString::Format("%02X ",(int)(*it)));
        else
        {
            upis.append(wxString("..."));
            break;
        }
    upis.append(wxString::Format(L"\n"));
    txtRSAPoruka->Clear();
    txtRSAPoruka->AppendText(upis);
    tbSazetakRSA->Clear();

    okvirPorukeRSA->GetStaticBox()->SetLabel(L"Poruka - učitan RSA šifrat");
    btnKriptirajPorukuRSA->Enable();
    btnKriptirajPorukuRSA->SetLabel(wxT("Dekriptiraj"));
    btnSnimiPorukuRSA->Disable();
    btnSnimiSifratRSA->Enable();
}

void ProjektFrame::KriptirajPorukuAES( wxCommandEvent& event )
{
    if(!(porukaSadrzajAES.empty())&&(aplikacija!=nullptr))
        if(btnKriptirajPorukuAES->GetLabel()==wxString(L"Enkriptiraj"))
        {
            if(!aplikacija->EnkriptirajPorukuAES(porukaSadrzajAES))
                return;
            aplikacija->DohvatiMedjuspremnikPorukeAES(porukaSadrzajAES);
            btnKriptirajPorukuAES->SetLabel(wxT("Dekriptiraj"));
            btnSnimiSifratAES->Enable();
            btnSnimiPorukuAES->Disable();
        }
        else
        {
            if(!aplikacija->DekriptirajPorukuAES(porukaSadrzajAES))
            {
                wxMessageBox(wxT("Šifrat nije moguće dekriptirati.\nMogući razlog je pogrešni ključ ili sam šifrat."),wxT("Pogreška - dekripcija"));
                return;
            }

            aplikacija->DohvatiMedjuspremnikPorukeAES(porukaSadrzajAES);
            aplikacija->KreirajSazetakAES(porukaSadrzajAES);
            btnKriptirajPorukuAES->SetLabel(wxT("Enkriptiraj"));
            btnSnimiSifratAES->Disable();
            btnSnimiPorukuAES->Enable();
        }
}
void ProjektFrame::KriptirajPorukuRSA( wxCommandEvent& event )
{
    if(!(porukaSadrzajRSA.empty())&&(aplikacija!=nullptr))
        if(btnKriptirajPorukuRSA->GetLabel()==wxString(L"Enkriptiraj"))
        {
            if(!aplikacija->EnkriptirajPorukuRSA(porukaSadrzajRSA))
            {
                wxMessageBox(wxT("Sadržaj nije moguće asimetrično kriptirati.\nMogući razlog je da je predugačak."),wxT("Pogreška - RSA"));
                return;
            }

            aplikacija->DohvatiMedjuspremnikPorukeRSA(porukaSadrzajRSA);
            btnKriptirajPorukuRSA->SetLabel(wxT("Dekriptiraj"));
            btnSnimiSifratRSA->Enable();
            btnSnimiPorukuRSA->Disable();
        }
        else
        {
            if(!aplikacija->DekriptirajPorukuRSA(porukaSadrzajRSA))
                return;
            aplikacija->DohvatiMedjuspremnikPorukeRSA(porukaSadrzajRSA);
            aplikacija->KreirajSazetakRSA(porukaSadrzajRSA);
            btnKriptirajPorukuRSA->SetLabel(wxT("Enkriptiraj"));
            btnSnimiSifratRSA->Disable();
            btnSnimiPorukuRSA->Enable();
        }
}

void ProjektFrame::OnQuit(wxCommandEvent &event)
{
    Unbind(wxOsvjeziPodatke, &ProjektFrame::OsvjeziPodatke, this);
    Destroy();
}

void ProjektFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxString("Informacije o kompilaciji:\n") +
    wxT("C++ kompiler: GCC-5.1.0-TDM64 MinGW\n")
    wxT("Kriptografska biblioteka: Crypto++ v. 5.6.4\n")+
    wxT("Grafički sustav: ")+ wxbuildinfo(long_f)+ "\n" +
    wxT("Projektna aplikacija iz kolegija \"Operacijski sustavi 2\"\nAutor: Elvis Popović, 2017.");
    wxMessageBox(msg, _("Informacije"));
}

void ProjektFrame::AESDijalog( wxCommandEvent& event )
{
    DijalogAES *dijalog = new DijalogAES(0L,this,this->aplikacija);
    //dijalog->upisiAdreseAdaptera(adreseAdaptera);
    dijalog->Show();
    if(biljeznica->GetSelection()!=0)
        biljeznica->SetSelection(0);
}

void ProjektFrame::GenerirajRSA( wxCommandEvent& event )
{
    VelicinaRSAKljuca velicinaRSA;
    GrafickiPodaci podaci;
    if(biljeznica->GetSelection()!=1)
        biljeznica->SetSelection(1);
    switch(radioVelicinaRSAKljuca->GetSelection())
    {
        case 0: velicinaRSA=VelicinaRSAKljuca::RSA_mali; break;
        case 1: velicinaRSA=VelicinaRSAKljuca::RSA_srednji; break;
        case 2: velicinaRSA=VelicinaRSAKljuca::RSA_veliki; break;
        default: velicinaRSA=VelicinaRSAKljuca::RSA_srednji;
    }
    aplikacija->GenerirajRSAKljuceve(velicinaRSA, podaci);
    tbRSAPrivatniKljuc->SetValue(podaci.privatniKljuc);
    tbRSAJavniKljuc->SetValue(podaci.javniKljuc);
    btnSnimiRSAKljuc->Enable();
}
void ProjektFrame::snimiRSAKljuceve( wxCommandEvent& event )
{
    const int rezultat = MessageBox(NULL, L"Datoteke ključeva bit će prepisane i stari ključevi\nzamijenjeni novima. Želite li nastaviti?",
                                    L"Snimanje para ključeva u datoteku",  MB_YESNO | MB_ICONQUESTION);
    if(rezultat==IDNO)
        return;
    aplikacija->SnimiRSAKljuceve();
}
void ProjektFrame::ucitajRSAKljuceve( wxCommandEvent& event )
{
    GrafickiPodaci podaci;
    if(!aplikacija->UcitajRSAKljuceve(podaci))
    {
        wxMessageBox(wxT("Datoteke sa parom ključeva nisu pronađene ili su zapisi u njima neispravni."),"Upozorenje!");
        return;
    }
    if(biljeznica->GetSelection()!=1)
        biljeznica->SetSelection(1);

    tbRSAPrivatniKljuc->SetValue(podaci.privatniKljuc);
    tbRSAJavniKljuc->SetValue(podaci.javniKljuc);
}

void ProjektFrame::PotpisiPoruku( wxCommandEvent& event )
{
    if(!(porukaPotpisivanje.empty())&&(aplikacija!=nullptr))
        if(!(aplikacija->PotpisiPoruku(porukaPotpisivanje, potpis)))
            wxMessageBox(wxT("Nije generiran par ključeva.\nPoruka se ne može potpisati. Kreirajte ključeve u odjeljku asimetrične kriptografije."),"Upozorenje!");
}
void ProjektFrame::Verificiraj( wxCommandEvent& event )
{
    if(!(porukaPotpisivanje.empty())&&(aplikacija!=nullptr))
        aplikacija->VerificirajPoruku(porukaPotpisivanje, potpis);
}

void ProjektFrame::OsvjeziPodatke(wxCommandEvent &event)
{
    GrafickiPodaci *podaci;
    if((podaci = (GrafickiPodaci *)(event.GetClientData()))==nullptr)
        return;
    btnSnimiAESKljuc->Enable();
    tbAESKljuc->SetValue(podaci->aesKljuc);
    tbIv->SetValue(podaci->iv);
    tbSazetakAES->SetValue(podaci->sazetakAES);
    tbSazetakRSA->SetValue(podaci->sazetakRSA);
}
void ProjektFrame::IspisiPoruku(wxCommandEvent &event)
{
    PorukaPodaci *podaci;
    if((podaci = (PorukaPodaci *)(event.GetClientData()))==nullptr)
        return;
    if(podaci->sadrzajAES.size()>0)
    {
        txtAESPoruka->Clear();
        txtAESPoruka->AppendText(podaci->sadrzajAES.c_str());
    }
    if(podaci->oznakaAES.size()>0)
        okvirPorukeAES->GetStaticBox()->SetLabel(podaci->oznakaAES.c_str());

    if(podaci->sadrzajRSA.size()>0)
    {
        txtRSAPoruka->Clear();
        txtRSAPoruka->AppendText(podaci->sadrzajRSA.c_str());
    }

    if(podaci->oznakaRSA.size()>0)
        okvirPorukeRSA->GetStaticBox()->SetLabel(podaci->oznakaRSA.c_str());

    if(podaci->potpisAES.size()>0)
    {
        txtAESPorukaPotpis1->Clear();
        txtAESPorukaPotpis1->AppendText(podaci->potpisAES.c_str());
    }


    switch(podaci->verificirano)
    {
        case 1: lblVerificirano->SetLabel("Potpis je u redu."); break;
        case -1: lblVerificirano->SetLabel("Potpis nije ispravan."); break;
        default: lblVerificirano->SetLabel("");
    }
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

    switch(radioVelicinaAESKljuca->GetSelection())
    {
        case 0: podaci.velicinaAES=VelicinaAESKljuca::AES_mali; break;
        case 1: podaci.velicinaAES=VelicinaAESKljuca::AES_srednji; break;
        case 2: podaci.velicinaAES=VelicinaAESKljuca::AES_veliki; break;
        default: podaci.velicinaAES=VelicinaAESKljuca::AES_srednji;
    }
    aplikacija->GenerirajAESKljuc(this, tcUnosLozinke->GetValue().ToStdString(), chkSol->GetValue(), podaci);
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
    if(tbGeneriraniAES->GetValue().size()>0&&tbIv->GetValue().size()>0)
    {
        aplikacija->UpisiAktivneKljuceve(podaci.aesKljuc, podaci.iv);
        aplikacija->ZahtijevajAzuriranjeGrafickihPodataka();
    }
    Destroy();
}

void DijalogAES::zatvori( wxCloseEvent& event )
{
    aplikacija->ZahtijevajAzuriranjeGrafickihPodataka();
    Destroy();
}
