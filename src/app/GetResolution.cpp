// Standard headers
#include <string>
#include <iostream>
#include <vector>
// BOOST headers
#include "boost/program_options.hpp"
// ROOT headers
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
// RooFit headers
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
// Custom headers
#include "plotmaker.h"
#include "progbar.h"
using std::cout;
using std::endl;
using std::string;
using std::vector;
void GetResolution(string filename, vector<string> particlename, string branchname, string xtitle, string unit, string plotname, double xlow, double xup, int nbins)
{
/*Input***********************************************************************/
  TFile* file = new TFile(filename.c_str());
  TTree* tree;
  if((TTree*)file->Get("DecayTreeTuple/DecayTree") != (TTree*)0x0)
  {
    tree  = (TTree*)file->Get("DecayTreeTuple/DecayTree");
  }
  else if((TTree*)file->Get("DecayTree") != (TTree*)0x0)
  {
    tree  = (TTree*)file->Get("DecayTree");
  }
  else if((TTree*)file->Get("MCDecayTree") != (TTree*)0x0)
  {
    tree  = (TTree*)file->Get("MCDecayTree");
  }
  else
  {
    cout << "Couldn't find tree." << endl;
    return;
  }
  cout << "Tree found." << endl;
/*Construct resolution********************************************************/
  // KK_TRUEP branches are identical to B_s0_TRUEP (bug?)
  // phi_1020_TRUEP is fine, so are individual kaons
  int n = particlename.size();
  TLorentzVector TRUEP[n+1];
  double TRUEP_E[n];
  double TRUEP_X[n];
  double TRUEP_Y[n];
  double TRUEP_Z[n];
  for(int i = 0; i < n; i++)
  {
     tree->SetBranchAddress((particlename[i]+"_TRUEP_E").c_str(),&TRUEP_E[i]);
     tree->SetBranchAddress((particlename[i]+"_TRUEP_X").c_str(),&TRUEP_X[i]);
     tree->SetBranchAddress((particlename[i]+"_TRUEP_Y").c_str(),&TRUEP_Y[i]);
     tree->SetBranchAddress((particlename[i]+"_TRUEP_Z").c_str(),&TRUEP_Z[i]);
  }
  double SIMMASS; tree->SetBranchAddress(branchname.c_str(),&SIMMASS);
  // Output tree and branches
  TTree* newtree = new TTree();
  double res ; newtree->Branch("res" ,&res ,"res/D" );
  double mass; newtree->Branch("mass",&mass,"mass/D");
  cout << "Constructing resolution for " << n << "-body invariant mass" << endl;
  progbar bar(tree->GetEntries());
  for(int i = 0; i < tree->GetEntries(); i++)
  {
    tree->GetEntry(i);
    TRUEP[n].SetPxPyPzE(0,0,0,0);
    for(int j = 0; j < n; j++)
    {
      TRUEP[j].SetPxPyPzE(TRUEP_X[j],TRUEP_Y[j],TRUEP_Z[j],TRUEP_E[j]);
      TRUEP[n] = TRUEP[n]+TRUEP[j];
    }
    mass = TRUEP[n].M();
    res = mass - SIMMASS;
    if(i%(tree->GetEntries()/100)==0)
    {
      bar.print(i);
    }
    if(res < xlow || res > xup) continue;
    newtree->Fill();
  }
  bar.terminate();
/*Plot************************************************************************/
  using namespace RooFit;
  RooRealVar* x = new RooRealVar("res",xtitle.c_str(),xlow,xup);
  RooDataSet* data;
  cout << "Importing tree" << endl;
  data = new RooDataSet("data","",RooArgSet(*x),Import(*newtree));
  RooRealVar mean("mean","",0,-10,10);
  RooRealVar sigma("sigma","mass resolution",20,0,100);
  RooGaussian* model = new RooGaussian("model","",*x,mean,sigma);
  model->fitTo(*data);
  RooPlot* frame = x->frame();
  cout << "Plotting" << endl;
  data->plotOn(frame,Binning(nbins));
  model->plotOn(frame);
  frame->SetMaximum(frame->GetMaximum()*1.3);
  plotmaker plotter(frame);
  plotter.SetTitle(("#Delta"+xtitle), unit);
  plotter.Draw()->SaveAs((plotname+".pdf").c_str());
  TCanvas can;
  newtree->Draw("res:mass");
  can.SaveAs("2Dscatter.pdf");
}
/*Main function***************************************************************/
int main(int argc, char* argv[])
{
  using namespace boost::program_options;
  options_description desc("Allowed options",120);
  string file, branch, cuts, xtitle, unit, plot, weight;
  vector<string> partic;
  double xlow, xup;
  int nbins;
  desc.add_options()
    ("help,H"    ,                                                                                    "produce help message"                  )
    ("file,F"    , value<string        >(&file  )->default_value("ntuples/BsphiKK_MC_mvacut.root"  ), "data ntuple"                           )
    ("particle,P", value<vector<string>>(&partic)->multitoken()                                     , "list particles to sum"                 )
    ("branch,B"  , value<string        >(&branch)->default_value("KK_M"                            ), "mass branch to compare to"             )
    ("title,T"   , value<string        >(&xtitle)->default_value("#it{m}(#it{K^{#plus}K^{#minus}})"), "x-axis title (takes ROOT LaTeX format)")
    ("unit,U"    , value<string        >(&unit  )->default_value("MeV/#it{c}^{2}"                  ), "x-axis unit (takes ROOT LaTeX format)" )
    ("plot,O"    , value<string        >(&plot  )->default_value("massresolution"                  ), "output plot filename"                  )
    ("upper,u"   , value<double        >(&xup   )->default_value(50                                ), "x-axis upper limit"                    )
    ("lower,l"   , value<double        >(&xlow  )->default_value(-50                               ), "x-axis lower limit"                    )
    ("bins,b"    , value<int           >(&nbins )->default_value(50                                ), "number of bins"                        )
  ;
  variables_map vmap;
  store(parse_command_line(argc, argv, desc), vmap);
  notify(vmap);
  if (vmap.count("help"))
  {
    cout << desc << endl;
    return 1;
  }
//  partic = vmap["particle"].as<vector<string>>();
  if(partic.size() == 0)
  {
    partic.push_back("Kplus0");
    partic.push_back("Kminus0");
  }
  cout << "Entering main function" << endl;
  GetResolution(file,partic,branch,xtitle,unit,plot,xlow,xup,nbins);
  return 0;
}
