void drawHisto(string output, std::vector< TH1F* > thisVector, std::vector<float> Vec_M, std::vector<float> Vec_R, int rebin, string xaxisTitle, string yaxisTitle, float xmin, float xmax, bool logX){

  TCanvas c1;

  if(logX && thisVector.size()>0)
    {
      c1.SetLogx();
      thisVector[0]->GetXaxis()->SetRangeUser(1,xmax);
    }

  TLegend *legend=new TLegend(0.55,0.74,0.95,0.98);
  legend->SetTextFont(72);
  legend->SetTextSize(0.035);

  float ymax = 0;

  for(int k=0;k<thisVector.size();k++)
    {
      float Nevents = thisVector[k]->GetEntries(); 

      char name [100];
      sprintf(name, "M=%.1f R=%.1f", Vec_M[k] , Vec_R[k] ); 
      thisVector[k]->SetTitle(0);
      thisVector[k]->Rebin(rebin);
      thisVector[k]->SetLineColor(k+1);
      thisVector[k]->GetXaxis()->SetTitle(xaxisTitle.c_str());
      thisVector[k]->GetYaxis()->SetTitle(yaxisTitle.c_str());
      thisVector[k]->GetXaxis()->SetRangeUser(xmin,xmax);

      //thisVector[k]->Scale(float(1/Nevents));

      if(thisVector[k]->GetMaximum()>ymax)
	ymax=thisVector[k]->GetMaximum();

      legend->AddEntry(thisVector[k],name,"l");
      
      if(k==0)
	thisVector[k]->Draw("HIST");
      else
	thisVector[k]->Draw("HISTsame");
    }

  thisVector[0]->GetYaxis()->SetRangeUser(0,ymax*1.3);
  //thisVector[0]->GetYaxis()->SetRangeUser(0,1);
  thisVector[0]->GetXaxis()->SetTicks("+-");
  thisVector[0]->GetXaxis()->SetTitleOffset(1.5);

  legend->Draw();

  char outputname[100];
  sprintf(outputname,"%s.png",output.c_str());
  c1.SaveAs(outputname);

  c1.Close();

}


void drawEff(string output, std::vector< TH1F* > DenVector, std::vector< TH1F* > NumVector, std::vector<float> Vec_M, std::vector<float> Vec_R, int rebin, string xaxisTitle, string yaxisTitle,string selection){

  TCanvas c1;

  TH2F *h2_efficiency = new TH2F("h2_efficiency",selection.c_str(),50,0,10000,21,-0.025,1.025);

  for(int k=0;k<DenVector.size();k++)
    {
      float den = DenVector[k]->GetEntries();
      float num = NumVector[k]->GetEntries();

      float eff = 0;
      if(den>0)
	eff = num/den;

      cout << "M,R = " << Vec_M[k] << "," << Vec_R[k] << " : Efficiency="<< eff << endl;

      h2_efficiency->Fill(Vec_M[k],Vec_R[k],eff);
    }

  h2_efficiency->GetZaxis()->SetRangeUser(0,1);
  h2_efficiency->GetZaxis()->SetTitleOffset(0.7);
  h2_efficiency->GetZaxis()->SetTitle("Selection efficiency");
  h2_efficiency->GetXaxis()->SetTitle(xaxisTitle.c_str());
  h2_efficiency->GetYaxis()->SetTitle(yaxisTitle.c_str());
  h2_efficiency->SetMarkerSize(1.5);

  h2_efficiency->Draw("colztext");

  char outputname[100];
  sprintf(outputname,"%s.png",output.c_str());
  c1.SaveAs(outputname);

  c1.Close();
}



void makePlots(){

  // general options

  gROOT->Reset();
  gStyle->SetOptStat(0);

  //load histograms

  TFile *file_M500_R0p1 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-500_R-0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M500_R0p2 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-500_R-0p2_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M500_R0p3 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-500_R-0p3_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M500_R0p5 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-500_R-0p5_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M500_R0p7 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-500_R-0p7_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M500_R0p9 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-500_R-0p9_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");

  TFile *file_M1000_R0p1 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M1000_R0p2 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p2_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M1000_R0p3 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p3_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M1000_R0p5 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p5_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M1000_R0p7 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p7_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M1000_R0p9 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-1000_R-0p9_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");

  TFile *file_M4000_R0p1 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-4000_R-0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M4000_R0p2 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-4000_R-0p2_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M4000_R0p3 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-4000_R-0p3_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M4000_R0p5 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-4000_R-0p5_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M4000_R0p7 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-4000_R-0p7_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M4000_R0p9 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-4000_R-0p9_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");

  TFile *file_M8000_R0p1 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-8000_R-0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M8000_R0p2 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-8000_R-0p2_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M8000_R0p3 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-8000_R-0p3_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M8000_R0p5 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-8000_R-0p5_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M8000_R0p7 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-8000_R-0p7_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M8000_R0p9 = TFile::Open("Output_Res1ToRes2GluTo3Glu_V2/Res1ToRes2GluTo3Glu_M1-8000_R-0p9_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");

  std::vector< TFile* > Vec_Files;

  Vec_Files.push_back(file_M500_R0p1);
  Vec_Files.push_back(file_M500_R0p2);
  Vec_Files.push_back(file_M500_R0p3);
  Vec_Files.push_back(file_M500_R0p5);
  Vec_Files.push_back(file_M500_R0p7);
  Vec_Files.push_back(file_M500_R0p9);

  Vec_Files.push_back(file_M1000_R0p1);
  Vec_Files.push_back(file_M1000_R0p2);
  Vec_Files.push_back(file_M1000_R0p3);
  Vec_Files.push_back(file_M1000_R0p5);
  Vec_Files.push_back(file_M1000_R0p7);
  Vec_Files.push_back(file_M1000_R0p9);

  Vec_Files.push_back(file_M4000_R0p1);
  Vec_Files.push_back(file_M4000_R0p2);
  Vec_Files.push_back(file_M4000_R0p3);
  Vec_Files.push_back(file_M4000_R0p5);
  Vec_Files.push_back(file_M4000_R0p7);
  Vec_Files.push_back(file_M4000_R0p9);

  Vec_Files.push_back(file_M8000_R0p1);
  Vec_Files.push_back(file_M8000_R0p2);
  Vec_Files.push_back(file_M8000_R0p3);
  Vec_Files.push_back(file_M8000_R0p5);
  Vec_Files.push_back(file_M8000_R0p7);
  Vec_Files.push_back(file_M8000_R0p9);

  std::vector< float > Vec_Mvalues;
  std::vector< float > Vec_Rvalues;
  
  Vec_Mvalues = {500,500,500,500,500,500
		 ,1000,1000,1000,1000,1000,1000
		 ,4000,4000,4000,4000,4000,4000
		 ,8000,8000,8000,8000,8000,8000};
  Vec_Rvalues = {0.1,0.2,0.3,0.5,0.7,0.9
		 ,0.1,0.2,0.3,0.5,0.7,0.9
		 ,0.1,0.2,0.3,0.5,0.7,0.9
		 ,0.1,0.2,0.3,0.5,0.7,0.9};
  
  //make plots

  std::vector< TH1F* > histVec_Mall_R0p1_Res2_pt;
  string variable = "genAnalyzer/h1_Res2_pt";
  histVec_Mall_R0p1_Res2_pt.push_back( (TH1F*)file_M500_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_Res2_pt.push_back( (TH1F*)file_M1000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_Res2_pt.push_back( (TH1F*)file_M4000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_Res2_pt.push_back( (TH1F*)file_M8000_R0p1->Get(variable.c_str())->Clone() );
  std::vector< float > Vec_M = {500,1000,4000,8000};
  std::vector< float > Vec_R = {0.1, 0.1, 0.1, 0.1};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_Res2pT_Mall_R0p1",histVec_Mall_R0p1_Res2_pt,Vec_M,Vec_R,2,"Res2 pT [GeV]","Events",0,5000,false);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p3_Res2_pt;
  variable = "genAnalyzer/h1_Res2_pt";
  histVec_Mall_R0p3_Res2_pt.push_back( (TH1F*)file_M500_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_Res2_pt.push_back( (TH1F*)file_M1000_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_Res2_pt.push_back( (TH1F*)file_M4000_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_Res2_pt.push_back( (TH1F*)file_M8000_R0p3->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.3, 0.3, 0.3, 0.3};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_Res2pT_Mall_R0p3",histVec_Mall_R0p3_Res2_pt,Vec_M,Vec_R,2,"Res2 pT [GeV]","Events",0,5000,false);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p7_Res2_pt;
  variable = "genAnalyzer/h1_Res2_pt";
  histVec_Mall_R0p7_Res2_pt.push_back( (TH1F*)file_M500_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_Res2_pt.push_back( (TH1F*)file_M1000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_Res2_pt.push_back( (TH1F*)file_M4000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_Res2_pt.push_back( (TH1F*)file_M8000_R0p7->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.7, 0.7, 0.7, 0.7};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_Res2pT_Mall_R0p7",histVec_Mall_R0p7_Res2_pt,Vec_M,Vec_R,2,"Res2 pT [GeV]","Events",0,5000,false);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_M1000_Rall_DeltaRP1P2;
  variable = "genAnalyzer/h1_P1P2_DeltaR";
  histVec_M1000_Rall_DeltaRP1P2.push_back( (TH1F*)file_M1000_R0p1->Get(variable.c_str())->Clone() );
  histVec_M1000_Rall_DeltaRP1P2.push_back( (TH1F*)file_M1000_R0p2->Get(variable.c_str())->Clone() );
  histVec_M1000_Rall_DeltaRP1P2.push_back( (TH1F*)file_M1000_R0p3->Get(variable.c_str())->Clone() );
  histVec_M1000_Rall_DeltaRP1P2.push_back( (TH1F*)file_M1000_R0p5->Get(variable.c_str())->Clone() );
  histVec_M1000_Rall_DeltaRP1P2.push_back( (TH1F*)file_M1000_R0p7->Get(variable.c_str())->Clone() );
  histVec_M1000_Rall_DeltaRP1P2.push_back( (TH1F*)file_M1000_R0p9->Get(variable.c_str())->Clone() );
  Vec_M = {1000,1000,1000,1000,1000,1000};
  Vec_R = {0.1, 0.2, 0.3, 0.5, 0.7, 0.9};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_DeltaR12_M1000_Rall",histVec_M1000_Rall_DeltaRP1P2,Vec_M,Vec_R,20,"#DeltaR(P1P2)","Events",0,5,false);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p2_DeltaRP1P2;
  variable = "genAnalyzer/h1_P1P2_DeltaR";
  histVec_Mall_R0p2_DeltaRP1P2.push_back( (TH1F*)file_M500_R0p2->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p2_DeltaRP1P2.push_back( (TH1F*)file_M1000_R0p2->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p2_DeltaRP1P2.push_back( (TH1F*)file_M4000_R0p2->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p2_DeltaRP1P2.push_back( (TH1F*)file_M8000_R0p2->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.2, 0.2, 0.2, 0.2};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_DeltaR12_Mall_R0p2",histVec_Mall_R0p2_DeltaRP1P2,Vec_M,Vec_R,20,"#DeltaR(P1P2)","Events",0,5,false);
  Vec_M.clear(); Vec_R.clear();

  //--

  std::vector< TH1F* > histVec_Mall_R0p1_Mjj;
  variable = "genAnalyzer/h1_Mjj";
  histVec_Mall_R0p1_Mjj.push_back( (TH1F*)file_M500_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_Mjj.push_back( (TH1F*)file_M1000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_Mjj.push_back( (TH1F*)file_M4000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_Mjj.push_back( (TH1F*)file_M8000_R0p1->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.1, 0.1, 0.1, 0.1};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_Mjj_Mall_R0p1",histVec_Mall_R0p1_Mjj,Vec_M,Vec_R,20,"#M_{jj} [GeV]","Events",0,9000,false);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p7_Mjj;
  variable = "genAnalyzer/h1_Mjj";
  histVec_Mall_R0p7_Mjj.push_back( (TH1F*)file_M500_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_Mjj.push_back( (TH1F*)file_M1000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_Mjj.push_back( (TH1F*)file_M4000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_Mjj.push_back( (TH1F*)file_M8000_R0p7->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.7, 0.7, 0.7, 0.7};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_Mjj_Mall_R0p7",histVec_Mall_R0p7_Mjj,Vec_M,Vec_R,20,"#M_{jj} [GeV]","Events",0,9000,false);
  Vec_M.clear(); Vec_R.clear();

  //--

  std::vector< TH1F* > histVec_Mall_R0p1_Mjjj;
  variable = "genAnalyzer/h1_Mjjj";
  histVec_Mall_R0p1_Mjjj.push_back( (TH1F*)file_M500_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_Mjjj.push_back( (TH1F*)file_M1000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_Mjjj.push_back( (TH1F*)file_M4000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_Mjjj.push_back( (TH1F*)file_M8000_R0p1->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.1, 0.1, 0.1, 0.1};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_Mjjj_Mall_R0p1",histVec_Mall_R0p1_Mjjj,Vec_M,Vec_R,20,"#M_{jj} [GeV]","Events",0,9000,false);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p7_Mjjj;
  variable = "genAnalyzer/h1_Mjjj";
  histVec_Mall_R0p7_Mjjj.push_back( (TH1F*)file_M500_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_Mjjj.push_back( (TH1F*)file_M1000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_Mjjj.push_back( (TH1F*)file_M4000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_Mjjj.push_back( (TH1F*)file_M8000_R0p7->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.7, 0.7, 0.7, 0.7};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_Mjjj_Mall_R0p7",histVec_Mall_R0p7_Mjjj,Vec_M,Vec_R,20,"#M_{jj} [GeV]","Events",0,9000,false);
  Vec_M.clear(); Vec_R.clear();

  //--

  std::vector< TH1F* > histVec_Mall_R0p1_AK8Jet1Pt;
  variable = "genAnalyzer/h1_AK8jet1_pt";
  histVec_Mall_R0p1_AK8Jet1Pt.push_back( (TH1F*)file_M500_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet1Pt.push_back( (TH1F*)file_M1000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet1Pt.push_back( (TH1F*)file_M4000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet1Pt.push_back( (TH1F*)file_M8000_R0p1->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.1, 0.1, 0.1, 0.1};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet1Pt_Mall_R0p1",histVec_Mall_R0p1_AK8Jet1Pt,Vec_M,Vec_R,2,"#AK8 Gen Jet1 pT [GeV]","Events",0,5000,true);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p1_AK8Jet2Pt;
  variable = "genAnalyzer/h1_AK8jet2_pt";
  histVec_Mall_R0p1_AK8Jet2Pt.push_back( (TH1F*)file_M500_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet2Pt.push_back( (TH1F*)file_M1000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet2Pt.push_back( (TH1F*)file_M4000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet2Pt.push_back( (TH1F*)file_M8000_R0p1->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.1, 0.1, 0.1, 0.1};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet2Pt_Mall_R0p1",histVec_Mall_R0p1_AK8Jet2Pt,Vec_M,Vec_R,2,"#AK8 Gen Jet2 pT [GeV]","Events",0,5000,true);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p1_AK8Jet3Pt;
  variable = "genAnalyzer/h1_AK8jet3_pt";
  histVec_Mall_R0p1_AK8Jet3Pt.push_back( (TH1F*)file_M500_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet3Pt.push_back( (TH1F*)file_M1000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet3Pt.push_back( (TH1F*)file_M4000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet3Pt.push_back( (TH1F*)file_M8000_R0p1->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.1, 0.1, 0.1, 0.1};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet3Pt_Mall_R0p1",histVec_Mall_R0p1_AK8Jet3Pt,Vec_M,Vec_R,2,"#AK8 Gen Jet3 pT [GeV]","Events",0,5000,true);
  Vec_M.clear(); Vec_R.clear();

  //--

  std::vector< TH1F* > histVec_Mall_R0p3_AK8Jet1Pt;
  variable = "genAnalyzer/h1_AK8jet1_pt";
  histVec_Mall_R0p3_AK8Jet1Pt.push_back( (TH1F*)file_M500_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_AK8Jet1Pt.push_back( (TH1F*)file_M1000_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_AK8Jet1Pt.push_back( (TH1F*)file_M4000_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_AK8Jet1Pt.push_back( (TH1F*)file_M8000_R0p3->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.3, 0.3, 0.3, 0.3};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet1Pt_Mall_R0p3",histVec_Mall_R0p3_AK8Jet1Pt,Vec_M,Vec_R,2,"#AK8 Gen Jet1 pT [GeV]","Events",0,5000,true);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p3_AK8Jet2Pt;
  variable = "genAnalyzer/h1_AK8jet2_pt";
  histVec_Mall_R0p3_AK8Jet2Pt.push_back( (TH1F*)file_M500_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_AK8Jet2Pt.push_back( (TH1F*)file_M1000_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_AK8Jet2Pt.push_back( (TH1F*)file_M4000_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_AK8Jet2Pt.push_back( (TH1F*)file_M8000_R0p3->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.3, 0.3, 0.3, 0.3};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet2Pt_Mall_R0p3",histVec_Mall_R0p3_AK8Jet2Pt,Vec_M,Vec_R,2,"#AK8 Gen Jet2 pT [GeV]","Events",0,5000,true);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p3_AK8Jet3Pt;
  variable = "genAnalyzer/h1_AK8jet3_pt";
  histVec_Mall_R0p3_AK8Jet3Pt.push_back( (TH1F*)file_M500_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_AK8Jet3Pt.push_back( (TH1F*)file_M1000_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_AK8Jet3Pt.push_back( (TH1F*)file_M4000_R0p3->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p3_AK8Jet3Pt.push_back( (TH1F*)file_M8000_R0p3->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.3, 0.3, 0.3, 0.3};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet3Pt_Mall_R0p3",histVec_Mall_R0p3_AK8Jet3Pt,Vec_M,Vec_R,2,"#AK8 Gen Jet3 pT [GeV]","Events",0,5000,true);
  Vec_M.clear(); Vec_R.clear();

  //--

  std::vector< TH1F* > histVec_Mall_R0p7_AK8Jet1Pt;
  variable = "genAnalyzer/h1_AK8jet1_pt";
  histVec_Mall_R0p7_AK8Jet1Pt.push_back( (TH1F*)file_M500_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet1Pt.push_back( (TH1F*)file_M1000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet1Pt.push_back( (TH1F*)file_M4000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet1Pt.push_back( (TH1F*)file_M8000_R0p7->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.7, 0.7, 0.7, 0.7};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet1Pt_Mall_R0p7",histVec_Mall_R0p7_AK8Jet1Pt,Vec_M,Vec_R,2,"#AK8 Gen Jet1 pT [GeV]","Events",0,5000,true);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p7_AK8Jet2Pt;
  variable = "genAnalyzer/h1_AK8jet2_pt";
  histVec_Mall_R0p7_AK8Jet2Pt.push_back( (TH1F*)file_M500_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet2Pt.push_back( (TH1F*)file_M1000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet2Pt.push_back( (TH1F*)file_M4000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet2Pt.push_back( (TH1F*)file_M8000_R0p7->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.7, 0.7, 0.7, 0.7};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet2Pt_Mall_R0p7",histVec_Mall_R0p7_AK8Jet2Pt,Vec_M,Vec_R,2,"#AK8 Gen Jet2 pT [GeV]","Events",0,5000,true);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p7_AK8Jet3Pt;
  variable = "genAnalyzer/h1_AK8jet3_pt";
  histVec_Mall_R0p7_AK8Jet3Pt.push_back( (TH1F*)file_M500_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet3Pt.push_back( (TH1F*)file_M1000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet3Pt.push_back( (TH1F*)file_M4000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet3Pt.push_back( (TH1F*)file_M8000_R0p7->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.7, 0.7, 0.7, 0.7};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet3Pt_Mall_R0p7",histVec_Mall_R0p7_AK8Jet3Pt,Vec_M,Vec_R,2,"#AK8 Gen Jet3 pT [GeV]","Events",0,5000,true);
  Vec_M.clear(); Vec_R.clear();

  //--

  std::vector< TH1F* > histVec_Mall_R0p1_AK8Jet1Eta;
  variable = "genAnalyzer/h1_AK8jet1_eta";
  histVec_Mall_R0p1_AK8Jet1Eta.push_back( (TH1F*)file_M500_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet1Eta.push_back( (TH1F*)file_M1000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet1Eta.push_back( (TH1F*)file_M4000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet1Eta.push_back( (TH1F*)file_M8000_R0p1->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.1, 0.1, 0.1, 0.1};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet1Eta_Mall_R0p1",histVec_Mall_R0p1_AK8Jet1Eta,Vec_M,Vec_R,1,"#AK8 Gen Jet1 #eta","Events",-5,5,false);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p1_AK8Jet2Eta;
  variable = "genAnalyzer/h1_AK8jet2_eta";
  histVec_Mall_R0p1_AK8Jet2Eta.push_back( (TH1F*)file_M500_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet2Eta.push_back( (TH1F*)file_M1000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet2Eta.push_back( (TH1F*)file_M4000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet2Eta.push_back( (TH1F*)file_M8000_R0p1->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.1, 0.1, 0.1, 0.1};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet2Eta_Mall_R0p1",histVec_Mall_R0p1_AK8Jet2Eta,Vec_M,Vec_R,1,"#AK8 Gen Jet2 #eta","Events",-5,5,false);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p1_AK8Jet3Eta;
  variable = "genAnalyzer/h1_AK8jet3_eta";
  histVec_Mall_R0p1_AK8Jet3Eta.push_back( (TH1F*)file_M500_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet3Eta.push_back( (TH1F*)file_M1000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet3Eta.push_back( (TH1F*)file_M4000_R0p1->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p1_AK8Jet3Eta.push_back( (TH1F*)file_M8000_R0p1->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.1, 0.1, 0.1, 0.1};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet3Eta_Mall_R0p1",histVec_Mall_R0p1_AK8Jet3Eta,Vec_M,Vec_R,1,"#AK8 Gen Jet3 #eta","Events",-5,5,false);
  Vec_M.clear(); Vec_R.clear();

  //--

  std::vector< TH1F* > histVec_Mall_R0p7_AK8Jet1Eta;
  variable = "genAnalyzer/h1_AK8jet1_eta";
  histVec_Mall_R0p7_AK8Jet1Eta.push_back( (TH1F*)file_M500_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet1Eta.push_back( (TH1F*)file_M1000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet1Eta.push_back( (TH1F*)file_M4000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet1Eta.push_back( (TH1F*)file_M8000_R0p7->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.7, 0.7, 0.7, 0.7};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet1Eta_Mall_R0p7",histVec_Mall_R0p7_AK8Jet1Eta,Vec_M,Vec_R,1,"#AK8 Gen Jet1 #eta","Events",-5,5,false);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p7_AK8Jet2Eta;
  variable = "genAnalyzer/h1_AK8jet2_eta";
  histVec_Mall_R0p7_AK8Jet2Eta.push_back( (TH1F*)file_M500_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet2Eta.push_back( (TH1F*)file_M1000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet2Eta.push_back( (TH1F*)file_M4000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet2Eta.push_back( (TH1F*)file_M8000_R0p7->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.7, 0.7, 0.7, 0.7};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet2Eta_Mall_R0p7",histVec_Mall_R0p7_AK8Jet2Eta,Vec_M,Vec_R,1,"#AK8 Gen Jet2 #eta","Events",-5,5,false);
  Vec_M.clear(); Vec_R.clear();

  std::vector< TH1F* > histVec_Mall_R0p7_AK8Jet3Eta;
  variable = "genAnalyzer/h1_AK8jet3_eta";
  histVec_Mall_R0p7_AK8Jet3Eta.push_back( (TH1F*)file_M500_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet3Eta.push_back( (TH1F*)file_M1000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet3Eta.push_back( (TH1F*)file_M4000_R0p7->Get(variable.c_str())->Clone() );
  histVec_Mall_R0p7_AK8Jet3Eta.push_back( (TH1F*)file_M8000_R0p7->Get(variable.c_str())->Clone() );
  Vec_M = {500,1000,4000,8000};
  Vec_R = {0.7, 0.7, 0.7, 0.7};
  drawHisto("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/h_AK8Jet3Eta_Mall_R0p7",histVec_Mall_R0p7_AK8Jet3Eta,Vec_M,Vec_R,1,"#AK8 Gen Jet3 #eta","Events",-5,5,false);
  Vec_M.clear(); Vec_R.clear();

  // Efficiencies

  //dijet
  std::vector< TH1F* > histVec_Numerator_dijet;
  std::vector< TH1F* > histVec_Denominator_dijet;
  string variable_num = "genAnalyzer/h1_Mjj_sel";
  string variable_den = "genAnalyzer/h1_Mjj";

  for(int k=0; k<Vec_Files.size(); k++)
    {
      histVec_Denominator_dijet.push_back( (TH1F*)Vec_Files[k]->Get(variable_den.c_str())->Clone() );
      histVec_Numerator_dijet.push_back( (TH1F*)Vec_Files[k]->Get(variable_num.c_str())->Clone() );
    }
  drawEff("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/eff_dijet",histVec_Denominator_dijet,histVec_Numerator_dijet,Vec_Mvalues,Vec_Rvalues,1,"MRes1 [GeV]","R","Dijet selection");

  //trijet
  std::vector< TH1F* > histVec_Numerator_trijet;
  std::vector< TH1F* > histVec_Denominator_trijet;
  variable_num = "genAnalyzer/h1_Mjjj_sel";
  variable_den = "genAnalyzer/h1_Mjjj";

  for(int k=0; k<Vec_Files.size(); k++)
    {
      histVec_Denominator_trijet.push_back( (TH1F*)Vec_Files[k]->Get(variable_den.c_str())->Clone() );
      histVec_Numerator_trijet.push_back( (TH1F*)Vec_Files[k]->Get(variable_num.c_str())->Clone() );
    }
  drawEff("/afs/cern.ch/user/s/santanas/www/TrijetResoannces13TeV/GenStudies_ggg_madgraph/eff_trijet",histVec_Denominator_trijet,histVec_Numerator_trijet,Vec_Mvalues,Vec_Rvalues,1,"MRes1 [GeV]","R","Trijet selection");
 
}




