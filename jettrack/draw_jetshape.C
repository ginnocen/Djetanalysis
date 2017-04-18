#include "TFile.h"
#include "TH1.h"
#include "TMath.h"

#include <string>

int draw_jetshape(std::string sample, const char* input, const char* output, const char* type) {
    TFile* finput = new TFile(input, "read");

    TFile* foutput = new TFile(output, "recreate");

    TH1::SetDefaultSumw2();

    std::string tag = Form("%s_%s_0_200", sample.c_str(), type);

    TH1D* hjetpt = (TH1D*)finput->Get(Form("hjetpt_%s", tag.c_str()))->Clone();
    TH1D* hjetpt_mix = (TH1D*)finput->Get(Form("hjetptjetmix_%s", tag.c_str()))->Clone();

    TH1D* hjs = (TH1D*)finput->Get(Form("hjetshape_%s", tag.c_str()))->Clone();
    TH1D* hjs_ue = (TH1D*)finput->Get(Form("hjetshapeue_%s", tag.c_str()))->Clone();
    TH1D* hjs_jet = (TH1D*)finput->Get(Form("hjetshapejetmix_%s", tag.c_str()))->Clone();
    TH1D* hjs_jet_ue = (TH1D*)finput->Get(Form("hjetshapejetmixue_%s", tag.c_str()))->Clone();

    TH1D* hjs_sub = (TH1D*)hjs->Clone(Form("hjs_sub_%s", tag.c_str()));
    TH1D* hjs_jet_sub = (TH1D*)hjs_jet->Clone(Form("hjs_jet_sub_%s", tag.c_str()));

    hjs_sub->Add(hjs_ue, -1);
    hjs_jet_sub->Add(hjs_jet_ue, -1);

    TH1D* hjs_final = (TH1D*)hjs_sub->Clone(Form("hjs_final_%s", tag.c_str()));

    hjs_final->Add(hjs_jet_sub, -1);
    hjs_final->Scale(1.0/(hjetpt->Integral() - hjetpt_mix->Integral()));

    hjs_final->Scale(1/hjs_final->Integral(hjs_final->FindBin(0.01), hjs_final->FindBin(0.29)), "width");

    foutput->Write("", TObject::kOverwrite);
    foutput->Close();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 5)
        draw_jetshape(argv[1], argv[2], argv[3], argv[4]);
    else
        return 1;

    return 0;
}
