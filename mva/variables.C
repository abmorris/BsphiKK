#include "tmvaglob.C"
#include "TLegend.h"
#include "TText.h"
#include <map>
#include <string>

using namespace std;

// this macro plots the distributions of the different input variables
// used in TMVA (e.g. running TMVAnalysis.C).  Signal and Background are overlayed.

// input: - Input file (result from TMVA),
//        - normal/decorrelated/PCA
//        - use of TMVA plotting TStyle
void variables( TString fin = "TMVA.root", TString dirName = "InputVariables_Id", TString title = "TMVA Input Variables",
                Bool_t isRegression = kFALSE, Bool_t useTMVAStyle = kTRUE )
{
   // Define new x-axis titles
   map<string, string> newtitle;
//   newtitle["B_s0_ln_FDCHI2"]  = "#it{B_{s}}^{0} #ln#it{#chi}_{FD}^{2}";
//   newtitle["B_s0_ln_IPCHI2"]  = "#it{B_{s}}^{0} #ln#it{#chi}_{IP}^{2}";
//   newtitle["B_s0_ln_EVCHI2"]  = "#it{B_{s}}^{0} #ln#it{#chi}_{EV}^{2}";
//   newtitle["B_s0_PT_fiveGeV"] = "#it{B_{s}}^{0} #it{p_{T}} / 5 [GeV/#it{c}^{2}]";
//   newtitle["B_s0_Eta"]        = "#it{B_{s}}^{0} #it{#eta}";
//   newtitle["minK_PT_GeV"]     = "min #it{K} #it{p_{T}} [GeV/#it{c}^{2}]";
//   newtitle["minK_ln_IPCHI2"]  = "min #it{K} #ln#it{#chi}_{IP}^{2}";
   newtitle.insert(pair<string, string>("B_s0_ln_FDCHI2","#it{B_{s}}^{0} ln#it{#chi}_{FD}^{2}"));
   newtitle.insert(pair<string, string>("B_s0_ln_IPCHI2","#it{B_{s}}^{0} ln#it{#chi}_{IP}^{2}"));
   newtitle.insert(pair<string, string>("B_s0_ln_EVCHI2","#it{B_{s}}^{0} ln#it{#chi}_{EV}^{2}"));
   newtitle.insert(pair<string, string>("B_s0_PT_fiveGeV","#it{B_{s}}^{0} #it{p_{T}} / 5 [GeV/#it{c}^{2}]"));
   newtitle.insert(pair<string, string>("B_s0_Eta","#it{B_{s}}^{0} #it{#eta}"));
   newtitle.insert(pair<string, string>("minK_PT_GeV","min #it{K} #it{p_{T}} [GeV/#it{c}^{2}]"));
   newtitle.insert(pair<string, string>("minK_ln_IPCHI2","min #it{K} ln#it{#chi}_{IP}^{2}"));
   
   
   TString outfname = dirName;
   outfname.ToLower(); outfname.ReplaceAll( "input", ""  );

   // set style and remove existing canvas'
   TMVAGlob::Initialize( useTMVAStyle );

   // obtain shorter histogram title 
   TString htitle = title; 
   htitle.ReplaceAll("variables ","variable");
   htitle.ReplaceAll("and target(s)","");
   htitle.ReplaceAll("(training sample)","");

   // checks if file with name "fin" is already open, and if not opens one
   TFile* file = TMVAGlob::OpenFile( fin );

   TDirectory* dir = (TDirectory*)file->Get( dirName );
   if (dir==0) {
      cout << "No information about " << title << " available in directory " << dirName << " of file " << fin << endl;
      return;
   }
   dir->cd();

   // how many plots are in the directory?
   Int_t noPlots = TMVAGlob::GetNumberOfInputVariables( dir ) +
      TMVAGlob::GetNumberOfTargets( dir );

   // counter variables
   Int_t countCanvas = 0;

   // loop over all objects in directory
   TKey*    key  = 0;
   Bool_t   createNewFig = kFALSE;
   TIter next(dir->GetListOfKeys());
   while ((key = (TKey*)next())) {
      if (key->GetCycle() != 1) continue;

      if (!TString(key->GetName()).Contains("__Signal") && 
          !(isRegression && TString(key->GetName()).Contains("__Regression"))) continue;

      // make sure, that we only look at histograms
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if (!cl->InheritsFrom("TH1")) continue;
      TH1 *sig = (TH1*)key->ReadObj();
      TString hname(sig->GetName());

      TCanvas canv(Form( "canv%i", countCanvas ));
      // find the corredponding backgrouns histo
      TString bgname = hname;
      bgname.ReplaceAll("__Signal","__Background");
      TH1 *bgd = (TH1*)dir->Get(bgname);
      if (bgd == NULL) {
         cout << "ERROR!!! couldn't find background histo for" << hname << endl;
         exit;
      }

      // this is set but not stored during plot creation in MVA_Factory
      TMVAGlob::SetSignalAndBackgroundStyle( sig, (isRegression ? 0 : bgd) );            

//      sig->SetTitle( TString( htitle ) + ": " + sig->GetTitle() );
      sig->SetTitle("");
      TMVAGlob::SetFrameStyle( sig, 1.2 );

      // normalise both signal and background
      if (!isRegression) TMVAGlob::NormalizeHists( sig, bgd );
      else {
         // change histogram title for target
         TString nme = sig->GetName();
         if (nme.Contains( "_target" )) {
            TString tit = sig->GetTitle();
            sig->SetTitle( tit.ReplaceAll("Input variable", "Regression target" ) );
         }
      }

      // finally plot and overlay
      Float_t sc = 1.1;
      sig->SetMaximum( TMath::Max( sig->GetMaximum(), bgd->GetMaximum() )*sc );
      sig->Draw( "hist" );
      canv.SetLeftMargin( 0.17 );

      sig->GetYaxis()->SetTitleOffset( 1.70 );
      if (!isRegression) {
         bgd->Draw("histsame");
         TString ytit = TString("(1/N) ") + sig->GetYaxis()->GetTitle();
         sig->GetYaxis()->SetTitle( ytit ); // histograms are normalised
      }
      cout << newtitle[sig->GetXaxis()->GetTitle()] << endl;
      sig->GetXaxis()->SetTitle(newtitle[sig->GetXaxis()->GetTitle()].c_str());
      // Draw legend
      /*
      if (countPad == 1 && !isRegression) {
         TLegend *legend= new TLegend( canv.GetLeftMargin(),
                                       1-canv.GetTopMargin()-.15,
                                       canv.GetLeftMargin()+.4,
                                       1-canv.GetTopMargin() );
         legend->SetFillStyle(1);
         legend->AddEntry(sig,"Signal","F");
         legend->AddEntry(bgd,"Background","F");
         legend->SetBorderSize(1);
         legend->SetMargin( 0.3 );
         legend->Draw("same");
      }
      */

      // redraw axes
      sig->Draw("sameaxis");

      // text for overflows
      Int_t    nbin = sig->GetNbinsX();
      Double_t dxu  = sig->GetBinWidth(0);
      Double_t dxo  = sig->GetBinWidth(nbin+1);
      TString uoflow = "";
      if (isRegression) {
         uoflow = Form( "U/O-flow: %.1f%% / %.1f%%", 
                        sig->GetBinContent(0)*dxu*100, sig->GetBinContent(nbin+1)*dxo*100 );
      }
      else {
         uoflow = Form( "U/O-flow (S,B): (%.1f, %.1f)%% / (%.1f, %.1f)%%", 
                        sig->GetBinContent(0)*dxu*100, bgd->GetBinContent(0)*dxu*100,
                        sig->GetBinContent(nbin+1)*dxo*100, bgd->GetBinContent(nbin+1)*dxo*100 );
      }
  
//      TText* t = new TText( 0.98, 0.14, uoflow );
//      t->SetNDC();
//      t->SetTextSize( 0.040 );
//      t->SetTextAngle( 90 );
//      t->AppendPad();    

      // save canvas to file
      TString fname = Form( "plots/%s_c%i", outfname.Data(), countCanvas );
      TMVAGlob::plot_logo();
      TMVAGlob::imgconv( &canv, fname );
      countCanvas++;
   }

   return;
}
