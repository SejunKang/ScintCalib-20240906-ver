void graph()
{
double x[14] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140};
double y1[14] = {9.21624,8.08113,7.27569,6.52269,5.96738,5.32107,4.96877,4.5857,4.29741,3.88768,3.7199,3.51435,3.30452,3.21831};
double y2[14] = {40,35,31,28,26,23,21,20,18,16,16,15,14,14};

TGraph *gr1 = new TGraph(14, x, y1);
gr1->SetMarkerStyle(8);
gr1->SetMarkerColor(kBlue);
gr1->SetLineColor(kBlue);
gr1->SetLineWidth(2);

TGraph *gr2 = new TGraph(14, x, y2);
gr2->SetMarkerStyle(22);
gr2->SetMarkerSize(2);
gr2->SetMarkerColor(kRed);
gr2->SetLineColor(kRed);
gr2->SetLineWidth(2);


TCanvas *c1 = new TCanvas();

TMultiGraph *mg = new TMultiGraph();
mg->Add(gr1);
mg->Add(gr2);
mg->Draw("ALPS");
mg->SetTitle("Photon Number vs Distance (X-ray only, 95%);Distance from PMT (cm);Photon Number");

auto legend = new TLegend(0.6,0.7,0.9,0.9);
legend->AddEntry(gr1, "Photon number with QE", "lp");
legend->AddEntry(gr2, "Photon number without QE", "lp");
legend->Draw();

TLatex *lat = new TLatex(20, 15, "(/run/beamOn 1000)");
lat->Draw();

}
