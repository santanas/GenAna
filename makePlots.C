void drawHisto(string output, std::vector< TH1F* > thisVector, std::vector<float> histVec_AllMass_R0p1_M, std::vector<float> histVec_AllMass_R0p1_R, int rebin, string xaxisTitle, string yaxisTitle, float xmin, float xmax){

  TCanvas c1;

  TLegend *legend=new TLegend(0.55,0.54,0.88,0.74);
  legend->SetTextFont(72);
  legend->SetTextSize(0.035);

  float ymax = 0;

  for(int k=0;k<thisVector.size();k++)
    {
      char name [100];
      sprintf(name, "M=%.1f R=%.1f", histVec_AllMass_R0p1_M[k] , histVec_AllMass_R0p1_R[k] ); 
      thisVector[k]->SetTitle(0);
      thisVector[k]->Rebin(rebin);
      thisVector[k]->SetLineColor(k+1);
      thisVector[k]->GetXaxis()->SetTitle(xaxisTitle.c_str());
      thisVector[k]->GetYaxis()->SetTitle(yaxisTitle.c_str());
      thisVector[k]->GetXaxis()->SetRangeUser(xmin,xmax);

      if(thisVector[k]->GetMaximum()>ymax)
	ymax=thisVector[k]->GetMaximum();

      legend->AddEntry(thisVector[k],name,"l");
      
      if(k==0)
	thisVector[k]->Draw();
      else
	thisVector[k]->Draw("same");
    }

  thisVector[0]->GetYaxis()->SetRangeUser(0,ymax*1.3);

  legend->Draw();

  char outputname[100];
  sprintf(outputname,"%s.png",output.c_str());
  c1.SaveAs(outputname);

  c1.Close();

}

void makePlots(){

  gROOT->Reset();
  gStyle->SetOptStat(0);

  TFile *file_M500_R0p1 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-500_R-0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M500_R0p2 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-500_R-0p2_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M500_R0p3 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-500_R-0p3_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M500_R0p5 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-500_R-0p5_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M500_R0p7 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-500_R-0p7_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M500_R0p9 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-500_R-0p9_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");

  TFile *file_M1000_R0p1 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M1000_R0p2 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p2_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M1000_R0p3 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p3_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M1000_R0p5 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p5_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M1000_R0p7 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p7_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M1000_R0p9 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-1000_R-0p9_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");

  TFile *file_M4000_R0p1 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-4000_R-0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M4000_R0p2 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-4000_R-0p2_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M4000_R0p3 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-4000_R-0p3_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M4000_R0p5 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-4000_R-0p5_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M4000_R0p7 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-4000_R-0p7_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M4000_R0p9 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-4000_R-0p9_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");

  TFile *file_M8000_R0p1 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-8000_R-0p1_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M8000_R0p2 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-8000_R-0p2_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M8000_R0p3 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-8000_R-0p3_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M8000_R0p5 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-8000_R-0p5_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M8000_R0p7 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-8000_R-0p7_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");
  TFile *file_M8000_R0p9 = TFile::Open("Output_Res1ToRes2GluTo3Glu/Res1ToRes2GluTo3Glu_M1-8000_R-0p9_slc6_amd64_gcc481_CMSSW_7_1_30_GEN_ANALYSIS.root");

  std::vector< TH1F* > histVec_Mall_R0p1;
  histVec_Mall_R0p1.push_back( (TH1F*)file_M500_R0p1->Get("genAnalyzer/h1_Res2_pt")->Clone() );
  histVec_Mall_R0p1.push_back( (TH1F*)file_M1000_R0p1->Get("genAnalyzer/h1_Res2_pt")->Clone() );
  histVec_Mall_R0p1.push_back( (TH1F*)file_M4000_R0p1->Get("genAnalyzer/h1_Res2_pt")->Clone() );
  histVec_Mall_R0p1.push_back( (TH1F*)file_M8000_R0p1->Get("genAnalyzer/h1_Res2_pt")->Clone() );
  std::vector< float > histVec_Mall_R0p1_M = {500,1000,4000,8000};
  std::vector< float > histVec_Mall_R0p1_R = {0.1, 0.1, 0.1, 0.1};
  drawHisto("h_Res2pT_Mall_R0p1",histVec_Mall_R0p1,histVec_Mall_R0p1_M,histVec_Mall_R0p1_R,5,"Res2 pT [GeV]","Events",0,5000);

  std::vector< TH1F* > histVec_M1000_Rall;
  histVec_M1000_Rall.push_back( (TH1F*)file_M1000_R0p1->Get("genAnalyzer/h1_Res2_pt")->Clone() );
  histVec_M1000_Rall.push_back( (TH1F*)file_M1000_R0p2->Get("genAnalyzer/h1_Res2_pt")->Clone() );
  histVec_M1000_Rall.push_back( (TH1F*)file_M1000_R0p3->Get("genAnalyzer/h1_Res2_pt")->Clone() );
  histVec_M1000_Rall.push_back( (TH1F*)file_M1000_R0p5->Get("genAnalyzer/h1_Res2_pt")->Clone() );
  histVec_M1000_Rall.push_back( (TH1F*)file_M1000_R0p7->Get("genAnalyzer/h1_Res2_pt")->Clone() );
  histVec_M1000_Rall.push_back( (TH1F*)file_M1000_R0p9->Get("genAnalyzer/h1_Res2_pt")->Clone() );
  std::vector< float > histVec_M1000_Rall_M = {1000,1000,1000,1000,1000,1000};
  std::vector< float > histVec_M1000_Rall_R = {0.1, 0.2, 0.3, 0.5, 0.7, 0.9};
  drawHisto("h_Res2pT_M1000_Rall",histVec_M1000_Rall,histVec_M1000_Rall_M,histVec_M1000_Rall_R,2,"Res2 pT [GeV]","Events",0,2000);

}




