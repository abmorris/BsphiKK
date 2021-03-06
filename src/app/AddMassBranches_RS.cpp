#include <string.h>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
using namespace std;
void addBranches(string filename = "f1420")
{
  cout << "Adding branches to " << filename << endl;
/*Input************************************************************************/
  // Open the input file and create the output file
  TFile* infile  = TFile::Open((filename+".root"   ).c_str()),
       * outfile = TFile::Open((filename+"_Bs0_branches.root").c_str(),"RECREATE");
  // Get the input tree and create an empty output tree
  TTree* intree  = (TTree*)infile->Get("tree"),
       * outtree = intree->CloneTree(0);
  // Read the number of events in the input file
  Int_t n = intree->GetEntries();
  double mphiKK;
  intree->SetBranchAddress("m_b",&mphiKK);
  outtree->Branch("B_s0_M",&mphiKK);
  outtree->Branch("B_s0_LOKI_Mass",&mphiKK);
  double mKK;
  intree->SetBranchAddress("mkk",&mKK);
  outtree->Branch("KK_M",&mKK);
  outtree->Branch("BCON_KK_M",&mKK);
/*Event loop*******************************************************************/
  for(Int_t i = 0; i < n; i++)
  {
    intree->GetEntry(i);
/*Fill tree and show progress**************************************************/
    outtree->Fill();
  }
/*Write the output*************************************************************/
  outtree->Write();
  infile->Close();
  outfile->Close();
  return;
}
int main(int argc, char* argv[])
{
  if(argc==1)
  {
    cout << "Please provide a filename." << endl;
    return 1;
  }
  else if(argc>2)
  {
    cout << "Too many arguments." << endl;
    return 1;
  }
  addBranches(((string)argv[1]).substr(0,((string)argv[1]).find(".root")));
  return 0;
}
