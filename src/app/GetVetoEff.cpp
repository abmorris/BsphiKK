// C++ headers
#include <string>
#include <iostream>
#include <iomanip>
// BOOST headers
#include "boost/program_options.hpp"
// Custom headers
#include "CutEff.h"
#include "ResultDB.h"
#include "GetTree.h"
using namespace std;
void GetVetoEff(string filename, bool save, string DBfilename)
{
  cout << "Please make sure these cuts match the ones in cut.sh" << endl;
  string trigger = "(B_s0_L0HadronDecision_TOS||B_s0_L0Global_TIS)&&B_s0_Hlt1TrackAllL0Decision_TOS&&(B_s0_Hlt2Topo3BodyBBDTDecision_TOS||B_s0_Hlt2Topo4BodyBBDTDecision_TOS)&&BCON_KK_M<1800";
  Cut_t cuts[] =
  {
    Cut_t("BdPhiKstar","(abs(phiKpluspiminusM-5279.58)>50||(abs(phiKpluspiminusM-5279.58)<50&&Kminus0_ProbNNk*(1-Kminus0_ProbNNpi)>0.4))&&(abs(phiKminuspiplusM-5279.58)>50||(abs(phiKminuspiplusM-5279.58)<50&&Kplus0_ProbNNk*(1-Kplus0_ProbNNpi)>0.4))")
  , Cut_t("LbPhiKp","(abs(phiKpluspbarM-5619.5)>50||(abs(phiKpluspbarM-5619.5)<50&&Kminus0_ProbNNk*(1-Kminus0_ProbNNp)>0.5))&&(abs(phiKminuspM-5619.5)>50||(abs(phiKminuspM-5619.5)<50&&Kplus0_ProbNNk*(1-Kplus0_ProbNNp)>0.5))")
  , Cut_t("LcPhip","abs(phipM-2286.46)>24||(abs(phipM-2286.46)<24&&Kplus0_ProbNNk>Kplus0_ProbNNp&&Kminus0_ProbNNk>Kminus0_ProbNNp)&&abs(phipbarM-2286.46)>24||(abs(phipbarM-2286.46)<24&&Kplus0_ProbNNk>Kplus0_ProbNNp&&Kminus0_ProbNNk>Kminus0_ProbNNp) ")
  , Cut_t("DPhiK","abs(phiKplusM-1968.3)>24&&abs(phiKminusM-1968.3)>24")
  , Cut_t("DPhipi","abs(phipiplusM-1869.61)>24&&abs(phipiminusM-1869.61)>24")
  , Cut_t("DsPhipi","abs(phipiplusM-1968.3)>24&&abs(phipiminusM-1968.3)>24")
  };
  string totalcut = "B_s0_M>0";// Something true for all events so the others can be appended with &&
  const unsigned int n = sizeof(cuts)/sizeof(Cut_t);
  TTree* intree = GetTree(filename);
  new TCanvas;
  // Calulate efficiency for each cut
  for(unsigned int i = 0; i < n; i++)
  {
    totalcut+="&&(" + cuts[i].cut + ")";
    CutResult_t CR = CutEff(intree,trigger,cuts[i].cut);
    cuts[i].eff = CR.GetEff();
    cuts[i].efferr = CR.GetEffErr();
  }
  CutResult_t CR = CutEff(intree,trigger,totalcut);
  double totaleff = CR.GetEff();
  double totalefferr = CR.GetEffErr();
  // Print table
  cout << "Cut & Efficiency \\\\" << endl;
  for(unsigned int i = 0; i < n; i++)
  {
    cout << cuts[i].name << " & " << cuts[i].eff*100 << "\\% \\\\" << endl;
  }
  cout << "total" << " & " << totaleff*100 <<  "\\% \\\\" << endl;
  // Save to database
  if(save)
  {
    ResultDB rdb(DBfilename);
    size_t mode_start = filename.find('/')==string::npos ? 0 : filename.find_last_of('/') + 1;
    size_t mode_end   = filename.find(".root");
    string mode = filename.substr(mode_start,mode_end-mode_start);// filename between final '/' and '.root'
    for(unsigned int i = 0; i < n; i++)
    {
      rdb.Update("VetoEff"+mode+cuts[i].name,"percent",cuts[i].eff,cuts[i].efferr);
    }
    rdb.Update("VetoEff"+mode+"total","percent",totaleff,totalefferr);
    rdb.Save();
  }
}
int main(int argc, char* argv[])
{
  string filename, dbf;
  using namespace boost::program_options;
  options_description desc("Allowed options",120);
  desc.add_options()
    ("help,H",                                                         "produce help message")
    ("save"  ,                                                         "save the results"    )
    ("output-file", value<string>(&dbf)->default_value("VetoEff.csv"), "output file"         )
    ("input-file" , value<string>(&filename                         ), "input file"          )
  ;
  variables_map vmap;
  positional_options_description pd;
  pd.add("input-file", 1);
  store(command_line_parser(argc, argv).options(desc).positional(pd).run(), vmap);
  notify(vmap);
  if (vmap.count("help"))
  {
    std::cout << desc << endl;
    return 1;
  }
  if(filename.empty())
  {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }
  GetVetoEff(filename,vmap.count("save"),dbf);
  return 0;
}
