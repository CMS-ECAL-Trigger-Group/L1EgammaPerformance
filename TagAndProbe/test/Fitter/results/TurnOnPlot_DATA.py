import ROOT
import operator
import array


ROOT.gSystem.Load('libRooFit')


class TurnOn:
    def __init__(self, **args):
        self.name        = args.get("Name", "turnon")
        #self.legend      = args.get("Legend","")
        self.legend      = args.get("Legend","Turn-on")
        self.histo       = args.get("Histo", None)
        self.fit         = args.get("Fit", None)
        self.markerColor = args.get("MarkerColor", ROOT.kBlack)
        self.markerStyle = args.get("MarkerStyle", 20)
        self.lineColor   = args.get("LineColor", ROOT.kBlack)
        self.lineStyle   = args.get("LineStyle", 1)
        self.histo.SetName(self.name+"_histo")
	if self.fit!=None:
        	self.fit.SetName(self.name+"_fit")



class TurnOnPlot:
    def __init__(self, **args):
        self.name  = ""
        self.turnons = []
        self.plotDir = "plots/"
        self.xRange = (10, 120)
        self.xTitle = "p_{T}^{offl} [GeV]"
        #self.legendPosition = (0.6,0.2,0.9,0.4)
        self.legendPosition = (0.4,0.2,0.9,0.6)
        self.setPlotStyle()
        #self.triggerName = args.get("TriggerName", "Turn-On")
        self.triggerName = args.get("TriggerName", "")

    def addTurnOn(self, turnon):
        self.turnons.append(turnon)

    def plot(self):
        canvas = ROOT.TCanvas("c_"+self.name, self.name, 800, 800)
        canvas.SetGrid()
        #canvas.SetLogx()
        hDummy = ROOT.TH1F("hDummy_"+self.name, self.name, 1, self.xRange[0], self.xRange[1])
        hDummy.SetAxisRange(0, 1.05, "Y")
	if 'diff' in self.name:
		hDummy.SetAxisRange(-0.1,0.1,'Y')
        hDummy.SetXTitle(self.xTitle)
        #hDummy.SetYTitle("Test")
        hDummy.SetYTitle("Efficiency")
	if 'diff' in self.name:
        	hDummy.SetYTitle("Efficiency difference")
        hDummy.Draw()


        cmsTextFont     = 61  # font of the "CMS" label
        cmsTextSize   = 0.05  # font size of the "CMS" label
        extraTextFont   = 52     # for the "preliminary"
        extraTextSize   = 0.76 * cmsTextSize # for the "preliminary"
        xpos  = 0.177
        ypos  = 0.89

        CMSbox       = ROOT.TLatex  (xpos, ypos         , "CMS")
        extraTextBox = ROOT.TLatex  (xpos, ypos - 0.05 , "#splitline{preliminary}{2018}")
        CMSbox.SetNDC()
        extraTextBox.SetNDC()
        CMSbox.SetTextSize(cmsTextSize)
        CMSbox.SetTextFont(cmsTextFont)
        CMSbox.SetTextColor(ROOT.kBlack)
        CMSbox.SetTextAlign(13)
        extraTextBox.SetTextSize(extraTextSize)
        extraTextBox.SetTextFont(extraTextFont)
        extraTextBox.SetTextColor(ROOT.kBlack)
        extraTextBox.SetTextAlign(13)

        triggerNameBox = ROOT.TLatex(0.15, 0.95, self.triggerName)
        triggerNameBox.SetNDC()
        triggerNameBox.SetTextFont(42)
        triggerNameBox.SetTextSize(extraTextSize)
        triggerNameBox.SetTextColor(ROOT.kBlack)
        triggerNameBox.SetTextAlign(11)

        # lumi_num = float(cfg.readOption ("general::lumi"))
        # lumi_num = lumi_num/1000. # from pb-1 to fb-1
        # lumi = "%.1f fb^{-1} (13 TeV)" % lumi_num
        lumi = "0.21 fb^{-1} (13 TeV)"
        lumibox = ROOT.TLatex  (0.953, 0.95, lumi)
        lumibox.SetNDC()
        lumibox.SetTextAlign(31)
        lumibox.SetTextSize(extraTextSize)
        lumibox.SetTextFont(42)
        lumibox.SetTextColor(ROOT.kBlack)
        #Line legend
        legend = ROOT.TLegend(self.legendPosition[0],self.legendPosition[1],self.legendPosition[2],self.legendPosition[3])
        legend.SetTextFont(42)
        legend.SetFillColor(0)
        '''legend1 = ROOT.TLegend(0.14, 0.80, 0.80, 1.02)
        legend1.SetBorderSize(0)
        legend1.SetTextFont(62)
        legend1.SetTextSize(0.025)
        legend1.SetLineColor(0)
        legend1.SetLineStyle(1)
        legend1.SetLineWidth(1)
        legend1.SetFillColor(0)
        legend1.SetFillStyle(0)
        legend1.AddEntry("NULL","CMS Preliminary:                                              #sqrt{s}=13 TeV","h")
        legend1.AddEntry("NULL","L1 Threshold : 28 GeV","h")'''

        for turnon in self.turnons:
            histo = turnon.histo
            histo.SetMarkerStyle(turnon.markerStyle)
            histo.SetMarkerColor(turnon.markerColor)
            histo.SetLineColor(turnon.markerColor)
            histo.Draw("p same")
            fit = turnon.fit
	    if fit!=None:
            	fit.SetLineStyle(turnon.lineStyle)
            	fit.SetLineColor(turnon.lineColor)
            	fit.SetLineWidth(2)
            	fit.Draw("l same")
            # legends
            legend.AddEntry(histo, turnon.legend, "pe")
            legend.Draw()
            #if self.name=="turnon_Stage1_Stage2_EB":
        triggerNameBox.Draw()
        CMSbox.Draw()
        extraTextBox.Draw()
        lumibox.Draw()
        #print ("DEBUG: " + self.plotDir+"/"+self.name+".eps")
        #canvas.Print(self.plotDir+"/"+self.name+".pdf", "pdf")
        canvas.Print(self.plotDir+"/"+self.name+"2018.png", "png")
	canvas.SetLogx(1)
	hDummy.GetXaxis().SetRangeUser(1,1000)
        canvas.Print(self.plotDir+"/"+self.name+"2018log.png", "png")


    def setPlotStyle(self):
        ROOT.gROOT.SetStyle("Plain")
        ROOT.gStyle.SetOptStat()
        ROOT.gStyle.SetOptFit(0)
        ROOT.gStyle.SetOptTitle(0)
        ROOT.gStyle.SetFrameLineWidth(1)
        ROOT.gStyle.SetPadBottomMargin(0.13)
        ROOT.gStyle.SetPadLeftMargin(0.15)
        ROOT.gStyle.SetPadTopMargin(0.06)
        ROOT.gStyle.SetPadRightMargin(0.05)

        ROOT.gStyle.SetLabelFont(42,"X")
        ROOT.gStyle.SetLabelFont(42,"Y")
        ROOT.gStyle.SetLabelSize(0.04,"X")
        ROOT.gStyle.SetLabelSize(0.04,"Y")
        ROOT.gStyle.SetLabelOffset(0.01,"Y")
        ROOT.gStyle.SetTickLength(0.02,"X")
        ROOT.gStyle.SetTickLength(0.02,"Y")
        ROOT.gStyle.SetLineWidth(1)
        ROOT.gStyle.SetTickLength(0.02 ,"Z")

        ROOT.gStyle.SetTitleSize(0.1)
        ROOT.gStyle.SetTitleFont(42,"X")
        ROOT.gStyle.SetTitleFont(42,"Y")
        ROOT.gStyle.SetTitleSize(0.05,"X")
        ROOT.gStyle.SetTitleSize(0.05,"Y")
        ROOT.gStyle.SetTitleOffset(1.1,"X")
        ROOT.gStyle.SetTitleOffset(1.4,"Y")
        ROOT.gStyle.SetOptStat(0)
        ROOT.gStyle.SetPalette(1)
        ROOT.gStyle.SetPaintTextFormat("3.2f")
        ROOT.gROOT.ForceStyle()
