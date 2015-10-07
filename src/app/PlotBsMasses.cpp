#include "TROOT.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TLegend.h"
#include "THStack.h"
#include "TStyle.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "../mkplots.h"
/******************************************************************************/
TH1D* plotBsmass(string filename = "LbphiKp_MC")
{
  cout << "Plotting Bs mass from " << filename << endl;
/*Input************************************************************************/
  // Open the input file
  TFile* infile  = new TFile(("../ntuples/"+filename+"_mvaVars_vetoes.root").c_str());
  // Get the input tree
  TTree* intree  = (TTree*)infile->Get("DecayTree");
  // Set branches to read
  Double_t B_s0_LOKI_Mass;
  intree->SetBranchAddress("B_s0_LOKI_Mass",&B_s0_LOKI_Mass);
/*Output***********************************************************************/
  TH1D* hist = new TH1D(filename.c_str(),"",100,5170,5580);
/*Fill*************************************************************************/
  for(Int_t i = 0; i < intree->GetEntries(); i++)
  {
    intree->GetEntry(i);
    hist->Fill(B_s0_LOKI_Mass);
  }
  return hist;
}
void plotBsmasses()
{
/*Input variables**************************************************************/
  // Generated events
  Int_t ngen_LbphiKp   =  511582+ 540787;
  Int_t ngen_BdphiKst  = 2007492+2020493;
  Int_t ngen_Bsphipipi = 4004542+9016672;
  Int_t ngen_Bsphiphi  = 1028748+1029997;
  Int_t ngen_BsphiKK   = ngen_Bsphiphi;
  // Fragmentation fraction ratios
  Double_t fLb_fufd = 0.404*(1-0.031*5); // 0.404(1-0.031*pT(GeV))
  Double_t fs_fufd  = 0.134;
  Double_t fs_fd    = 0.267;
  // Branching fractions
  Double_t B_phitoKK   =   0.489;
  Double_t B_KsttoKpi  = 2.0/3.0;
  Double_t B_Bsphiphi  = 1.82e-5; // Get B_BsphiKK from B_BsJpsiKK, B_BsJpsiphi and B_Bsphiphi
  Double_t B_BsJpsiphi = 1.05e-3;
  Double_t B_BsJpsiKK  = 7.70e-4-B_phitoKK*B_BsJpsiphi; // Assumes
  Double_t B_BsphiKK   = B_BsJpsiKK*B_Bsphiphi/B_BsJpsiphi;
  Double_t B_LbJpsipK  = 3.04e-4; // LHCb-PAPER-2015-032 draft
  Double_t B_LbphiKp   = B_LbJpsipK*B_Bsphiphi/B_BsJpsiphi;
  Double_t B_Bsphipipi = 3.76e-6; // Haofei's result
  Double_t B_BdphiKst  = 1.00e-5;
/*Get the histograms***********************************************************/
  TH1D* LbphiKp   = plotBsmass("LbphiKp_MC"  );
  TH1D* BdphiKst  = plotBsmass("BdphiKst_MC" );
  TH1D* Bsphipipi = plotBsmass("Bsphipipi_MC");
  TH1D* BsphiKK   = plotBsmass("BsphiKK_MC"  );
  TCanvas* can    = new TCanvas("can","");
/*Calculate normalisation for each mode****************************************/
  Double_t denominator = B_BsphiKK  *(1.0/ngen_BsphiKK);
  Double_t w_LbphiKp   = B_LbphiKp  *(1.0/ngen_LbphiKp)  /denominator;
  Double_t w_BdphiKst  = B_BdphiKst *(1.0/ngen_BdphiKst) *B_KsttoKpi/denominator;
  Double_t w_Bsphipipi = B_Bsphipipi*(1.0/ngen_Bsphipipi)/denominator;
  BsphiKK->Scale(1.0); // Probably don't need this line
  cout << "N_LbphiKp   = \t" << w_LbphiKp*(fLb_fufd/fs_fufd)*LbphiKp->GetEntries()  /BsphiKK->GetEntries() << "×N_BsphiKK" << endl
       << "N_BdphiKst  = \t" << w_BdphiKst/fs_fd            *BdphiKst->GetEntries() /BsphiKK->GetEntries() << "×N_BsphiKK" << endl
       << "N_Bsphipipi = \t" << w_Bsphipipi                 *Bsphipipi->GetEntries()/BsphiKK->GetEntries() << "×N_BsphiKK" << endl;
  LbphiKp->Scale(w_LbphiKp*(fLb_fufd/fs_fufd));
  BdphiKst->Scale(w_BdphiKst/fs_fd);
  Bsphipipi->Scale(w_Bsphipipi);
/*Create stack*****************************************************************/
  THStack* total  = new THStack("total","");
  // Add components
  total->Add(Bsphipipi,"E");
  total->Add(LbphiKp,  "E");
  total->Add(BdphiKst, "E");
  total->Add(BsphiKK      );
  // Create legend
  TLegend* leg = new TLegend(0.6,0.5,0.89,0.8);
  leg->SetHeader("Decay mode");
  leg->AddEntry(BsphiKK,  "B^0_s\\to\\phi K^+ K^-",    "l");
  leg->AddEntry(BdphiKst, "B^0\\to\\phi K^*(892)",     "l");
  leg->AddEntry(LbphiKp,  "\\Lambda_b\\to\\phi p K^-", "l");
  leg->AddEntry(Bsphipipi,"B^0_s\\to\\phi\\pi^+\\pi^-","l");
  leg->SetLineColor(0);
  leg->SetTextSize(0.04);
/*Set colours******************************************************************/
  LbphiKp->SetLineColor(kViolet);
  BdphiKst->SetLineColor(kGreen);
  Bsphipipi->SetLineColor(kBlue);
  BsphiKK->SetLineColor(kBlack );
/*Style plot*******************************************************************/
  can->SetLeftMargin(0.12);
  can->SetBottomMargin(0.12);
  can->SetFrameLineColor(0);
  total->Draw();
  leg->Draw();
  stringstream ytitle;
  ytitle << "\\text{Candidates / }" << setprecision(1) << fixed << BsphiKK->GetBinWidth(0) << "~\\text{MeV}/c^2";
  total->GetYaxis()->SetTitle(ytitle.str().c_str());
  total->GetXaxis()->SetTitle("m_{K^+K^-K^+K^-}~\\text{MeV}/c^2");
  total->GetYaxis()->SetTitleSize(0.05);
  total->GetXaxis()->SetTitleSize(0.05);
/*Draw plot********************************************************************/
  mkplots(can,"simulated_backgrounds");
  return;
}
int main()
{
  plotBsmasses();
  return 0;
}