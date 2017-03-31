void plotter(TString suf="output_Jet80_D40.root"){

    TFile*file=new TFile(suf.Data());
    TH1D* hInCone = (TH1D*)file->Get("hInCone");
    TH1D* hOutCone = (TH1D*)file->Get("hOutCone");

    TCanvas*c=new TCanvas("c","c",1000,500);
    c->Divide(2,1);
    c->cd(1);
    //TH2F* hemptyInCone=new TH2F("hemptyInCone","",50,1.78,2.0,10,1,2000);  
    //TH2F* hemptyInCone=new TH2F("hemptyInCone","",50,1.78,2.0,10,1,8000);  
    TH2F* hemptyInCone=new TH2F("hemptyInCone","",50,1.78,2.0,10,1,500);  
    hemptyInCone->GetXaxis()->CenterTitle();
    hemptyInCone->GetYaxis()->CenterTitle();
    hemptyInCone->GetYaxis()->SetTitle("Entries / 8 MeV (#Delta R<0.5) ");
    hemptyInCone->GetXaxis()->SetTitle("Invariant mass K#pi (GeV/c^{2})");
    hemptyInCone->GetXaxis()->SetTitleOffset(0.9);
    hemptyInCone->GetYaxis()->SetTitleOffset(1.4);
    hemptyInCone->GetXaxis()->SetTitleSize(0.05);
    hemptyInCone->GetYaxis()->SetTitleSize(0.05);
    hemptyInCone->GetXaxis()->SetTitleFont(42);
    hemptyInCone->GetYaxis()->SetTitleFont(42);
    hemptyInCone->GetXaxis()->SetLabelFont(42);
    hemptyInCone->GetYaxis()->SetLabelFont(42);
    hemptyInCone->GetXaxis()->SetLabelSize(0.035);
    hemptyInCone->GetYaxis()->SetLabelSize(0.035);  
    hemptyInCone->Draw();
    hInCone->Draw("same");

    c->cd(2);
    //TH2F* hemptyOutCone=new TH2F("hemptyOutCone","",50,1.78,2.0,10,1,1000);  
    //TH2F* hemptyOutCone=new TH2F("hemptyOutCone","",50,1.78,2.0,10,1,100000);  
    TH2F* hemptyOutCone=new TH2F("hemptyOutCone","",50,1.78,2.0,10,1,100);  
    hemptyOutCone->GetXaxis()->CenterTitle();
    hemptyOutCone->GetYaxis()->CenterTitle();
    hemptyOutCone->GetYaxis()->SetTitle("Entries / 8 MeV (#Delta R>0.5) ");
    hemptyOutCone->GetXaxis()->SetTitle("Invariant mass K#pi (GeV/c^{2})");
    hemptyOutCone->GetXaxis()->SetTitleOffset(0.9);
    hemptyOutCone->GetYaxis()->SetTitleOffset(1.4);
    hemptyOutCone->GetXaxis()->SetTitleSize(0.05);
    hemptyOutCone->GetYaxis()->SetTitleSize(0.05);
    hemptyOutCone->GetXaxis()->SetTitleFont(42);
    hemptyOutCone->GetYaxis()->SetTitleFont(42);
    hemptyOutCone->GetXaxis()->SetLabelFont(42);
    hemptyOutCone->GetYaxis()->SetLabelFont(42);
    hemptyOutCone->GetXaxis()->SetLabelSize(0.035);
    hemptyOutCone->GetYaxis()->SetLabelSize(0.035);  
    hemptyOutCone->Draw();
    hOutCone->Draw("same");
    c->SaveAs("canvasJet60D20.pdf");



}