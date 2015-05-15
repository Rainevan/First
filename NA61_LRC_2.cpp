/**************************************************************************************************************
* Author: Andrey Seryakov seryakov@yahoo.com

* --- Information about centrality classes (Emil 10.10.2013	emil.aleksander.kaptur@cern.ch)
* We take into consideration only first 28 mods of PSD with equal weights
* Determination of classes 
*			%				min PSD energy				max	PSD energy
* Be7+Be9 150A GeV/c
*	1.		0-5%			0							584.135				
*	2.		5-10%			584.135						657.519
*	3.		10-15%			657.519						719.161
*	4.		15-25%			719.161						798.416
*           20              773.1
* 
*
* BPD, FittedVertex, FitQuality, NVertexTracks, ZVertex, ImpactPoint, CENTRALITY  cuts don't work for simEvents
*
**************************************************************************************************************/

//FIXME имена гистограмм psd а так же гистограммы катов.
//FIXME не заходить в sim петлю если нет simHandlers


#ifndef CONST
#define CONST
#include "NA61_LRC_2_Const.h"
#endif

#ifndef HANDLERLIST
#define HANDLERLIST
#include "NA61_LRC_2_Handler_List.h"
#endif

#ifndef CUTLIST
#define CUTLIST
#include "NA61_LRC_2_Cut_List.h"
#endif


#ifndef HANDLERS
#define HANDLERS
#include "NA61_LRC_2_Handler.h"
#endif

#ifndef CUT
#define CUT
#include "NA61_LRC_2_Cut.h"
#endif

#include <iostream>
#include <iomanip>
#include <fstream>

#ifndef SHINELIB
#define SHINELIB
#include <evt/Event.h>
#include <evt/RecEvent.h>
#include <evt/rec/Trigger.h>
#include <fwk/CentralConfig.h>
#include <utl/ShineUnits.h>
#include <io/EventFile.h>
#include <io/EventFileChain.h>
#include <utl/ShineUnits.h>
#include <evt/rec/RecEventConst.h>
#include <det/TriggerConst.h>
#include <utl/MathConst.h>
#include <utl/PhysicalConst.h>
#include <det/TPCConst.h>
#include <det/Target.h>
#include <det/TargetConst.h>
#include <det/PSD.h>
#include <det/BPD.h>
#include <det/Beam.h>
#include <det/Detector.h>
#endif

#ifndef ROOTLIB
#define ROOTLIB
#include <TFile.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TH3.h>
#include <TCutG.h>
#include <TProfile.h>
#include <TList.h>
#include <TString.h>
#include <TMath.h>
#include <utl/Vector.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>
#endif

int main(int argc, char* argv[])
{
	// --- reading of filenames
	cout<<"START"<<endl;
	if (argc < 2) 
	{
		cerr << "usage: " << argv[0] << " <file list>" << endl;
		return 1;
	}

    cout << " reading file names from " << argv[1] << endl;
    ifstream fileList(argv[1]);
    
    if (!fileList.good() || !fileList.is_open())
    {
        cerr << " Error, cannot read file list " << argv[1] << endl;
        return 1;
    }

    //FIXME
    std::vector<std::string> offBranches;  
    offBranches.push_back("eventTree.fEvent.fRecEvent.fBeam");
    offBranches.push_back("eventTree.fEvent.fRawEvent.fBeam");
    std::vector<std::string> onBranches;
    onBranches.push_back("eventTree.fEvent.fRawEvent.fBeam");
    onBranches.push_back("eventTree.fEvent.fRecEvent.fBeam");
//    onBranches.push_back("eventTree.fEvent.fRecEvent.fPSD");
 //   onBranches.push_back("eventTree.fEvent.fRecEvent.fTracks");
 //   onBranches.push_back("eventTree.fEvent.fRecEvent.fVertexTracks");
 //   onBranches.push_back("eventTree.fEvent.fRecEvent.fVertices");
 //   onBranches.push_back("eventTree.fEvent.fRecEvent.fTrackList");
 //   onBranches.push_back("eventTree.fEvent.fRecEvent.fVertexTrackList");
 //   onBranches.push_back("eventTree.fEvent.fRecEvent.fVertexList");
 //   onBranches.push_back("eventTree.fEvent.fRecEvent.fMainVertexIndex");
  //  onBranches.push_back("eventTree.fEvent.fRecEvent.fPrimaryVertexMap");
    
    // --- creating of handlers 
    // ----- List of handlers 
	HandlerList* HandList = new HandlerList();
	// ----- Handlers

	// ------ Cuts for sim event

 /*	 someSimHandler->AddVtxTrackStatusCut();
     someSimHandler->AddChargeTrkCut(0);
        
     someSimHandler->AddVTPCAndGTPCCut(15,5);
     someSimHandler->AddTotalTPCCut(15);
     someSimHandler->AddImpactPointCut(4,2);
     someSimHandler->AddPtCut(0, 1.5);
 //    someSimHandler->AddPCut(0.3,200);
     someSimHandler->AddAcceptCut();*/

	// ----- Cuts for rec event

/*  someRecHandler->AddNVtxTracksCut(3);
    someRecHandler->AddZVtxCut(-586.5, -574.1);
        
    someRecHandler->AddVtxTrackStatusCut();
        
    someRecHandler->AddChargeTrkCut(0);
        
    someRecHandler->AddVTPCAndGTPCCut(15,5);
    someRecHandler->AddTotalTPCCut(15);
    someRecHandler->AddImpactPointCut(4,2);
    someRecHandler->AddPtCut(0, 1.5);
///    someRecHandler->AddPCut(0.3,200);
    someRecHandler->AddAcceptCut();*/

	// ----- Cuts for real data

/*	someRealHandler->AddT2Cut();
	someRealHandler->AddWFACut(-100,-200, 1.5);
	someRealHandler->AddChargeCut();
    someRealHandler->AddBPDCut();
    someRealHandler->AddFittedVtxCut();
    someRealHandler->AddFitQualityCut();
    someRealHandler->AddNVtxTracksCut(3);
    someRealHandler->AddZVtxCut(-586.5, -574.1);
        
    someRealHandler->AddVtxTrackStatusCut();
        
    someRealHandler->AddChargeTrkCut(0);
        
    someRealHandler->AddVTPCAndGTPCCut(15,5);
    someRealHandler->AddTotalTPCCut(15);
    someRealHandler->AddImpactPointCut(4,2);
    someRealHandler->AddPtCut(0, 1.5);
//    someRealHandler->AddPCut(0.3,200);
    someRealHandler->AddAcceptCut();*/
    
	
    const int N1=9;//9;
    LRCHandler* arHandlerTwoBasicRaw[N1];
    for (int i =0; i<N1; i++){
        TString name;
        TString nameBasic="name_Basic";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameBasic + name2;
        arHandlerTwoBasicRaw[i] = new LRCHandler(name+"Raw.root", false); 
		arHandlerTwoBasicRaw[i]->Raw();
  
		// --- start: cuts only for real data
		arHandlerTwoBasicRaw[i]->AddT2Cut();
		arHandlerTwoBasicRaw[i]->AddWFACut(-100,-200, 1.5);
		arHandlerTwoBasicRaw[i]->AddChargeCut();
        arHandlerTwoBasicRaw[i]->AddBPDCut();
        arHandlerTwoBasicRaw[i]->AddFittedVtxCut();
        arHandlerTwoBasicRaw[i]->AddFitQualityCut();
		// --- end.
        arHandlerTwoBasicRaw[i]->AddNVtxTracksCut(3);
        arHandlerTwoBasicRaw[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoBasicRaw[i]->AddCentrality(0,0.2);
        
        arHandlerTwoBasicRaw[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoBasicRaw[i]->AddChargeTrkCut(0);
        
        arHandlerTwoBasicRaw[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoBasicRaw[i]->AddTotalTPCCut(15);
        arHandlerTwoBasicRaw[i]->AddImpactPointCut(4,2);
        arHandlerTwoBasicRaw[i]->AddPtCut(0, 1.5);
//        arHandlerTwoBasicRaw[i]->AddPCut(0.3,200);
        arHandlerTwoBasicRaw[i]->AddAcceptCut();
        
        arHandlerTwoBasicRaw[i]->AddEtaBackward(3.2+i*0.2,3.7+i*0.2);
        arHandlerTwoBasicRaw[i]->AddEtaForward(5.5,6);
        
        HandList->AddHandler(arHandlerTwoBasicRaw[i]);
    }

	const int N2=24;//24;
    LRCHandler* arHandlerTwoShiftRaw[N2];
    for (int i =0; i<N2; i++){
        TString name;
        TString nameShift="name_Shift";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameShift + name2;
        arHandlerTwoShiftRaw[i] = new LRCHandler(name+"Raw.root", false); 
        arHandlerTwoShiftRaw[i]->Raw();   
        //--- start: cuts only for real data
		arHandlerTwoShiftRaw[i]->AddT2Cut();
		arHandlerTwoShiftRaw[i]->AddWFACut(-100,-200, 1.5);
		arHandlerTwoShiftRaw[i]->AddChargeCut();
        arHandlerTwoShiftRaw[i]->AddBPDCut();
        arHandlerTwoShiftRaw[i]->AddFittedVtxCut();
        arHandlerTwoShiftRaw[i]->AddFitQualityCut();
		//--- end;
        arHandlerTwoShiftRaw[i]->AddNVtxTracksCut(3);
        arHandlerTwoShiftRaw[i]->AddZVtxCut(-586.5, -574.1);
	    arHandlerTwoShiftRaw[i]->AddCentrality(0,0.2);
        
        arHandlerTwoShiftRaw[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoShiftRaw[i]->AddChargeTrkCut(0);
        
        arHandlerTwoShiftRaw[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoShiftRaw[i]->AddTotalTPCCut(15);
        arHandlerTwoShiftRaw[i]->AddImpactPointCut(4,2);
        arHandlerTwoShiftRaw[i]->AddPtCut(0, 1.5);
//        arHandlerTwoShiftRaw[i]->AddPCut(0.3,200);
        arHandlerTwoShiftRaw[i]->AddAcceptCut();
        
        arHandlerTwoShiftRaw[i]->AddEtaBackward(3.2+i*0.1,3.7+i*0.1);
        arHandlerTwoShiftRaw[i]->AddEtaForward(3.7+i*0.1,4.2+i*0.1);
        
		HandList->AddHandler(arHandlerTwoShiftRaw[i]);
    }
    
    const int N3=0;//9;
    LRCHandler* arHandlerTwoBasicSim[N3]; 
    LRCHandler* arHandlerTwoBasicRec[N3];
    for (int i =0; i<N3; i++){
        TString name;
        TString nameBasic="name_Basic";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameBasic + name2;
        arHandlerTwoBasicSim[i] = new LRCHandler(name+"Sim.root", true); 
        arHandlerTwoBasicRec[i] = new LRCHandler(name+"Rec.root", false); 
		arHandlerTwoBasicSim[i] -> Simulation();
		arHandlerTwoBasicRec[i] -> Simulation();
   
        //arHandlerTwoBasicSim[i]->AddBPDCut();
        //arHandlerTwoBasicSim[i]->AddFittedVtxCut();
        //arHandlerTwoBasicSim[i]->AddFitQualityCut();
        //arHandlerTwoBasicSim[i]->AddNVtxTracksCut(3);
        //arHandlerTwoBasicSim[i]->AddZVtxCut(-586.5, -574.1);
        
		arHandlerTwoBasicSim[i]->AddCentrality(0,0.2);
//		arHandlerTwoBasicSim[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoBasicSim[i]->AddChargeTrkCut(0);
        
  //      arHandlerTwoBasicSim[i]->AddVTPCAndGTPCCut(15,5);
   //     arHandlerTwoBasicSim[i]->AddTotalTPCCut(15);
   //     arHandlerTwoBasicSim[i]->AddImpactPointCut(4,2);
        arHandlerTwoBasicSim[i]->AddPtCut(0, 1.5);
 //       arHandlerTwoBasicSim[i]->AddPCut(0.3,200);
        arHandlerTwoBasicSim[i]->AddAcceptCut();
        
        arHandlerTwoBasicSim[i]->AddEtaBackward(3.2+i*0.2,3.7+i*0.2);
        arHandlerTwoBasicSim[i]->AddEtaForward(5.5,6);
       
		// --- start: cuts only for real data
		// --- end.
        arHandlerTwoBasicRec[i]->AddNVtxTracksCut(3);
        arHandlerTwoBasicRec[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoBasicRec[i]->AddCentrality(0,0.2);
        
        arHandlerTwoBasicRec[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoBasicRec[i]->AddChargeTrkCut(0);
        
        arHandlerTwoBasicRec[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoBasicRec[i]->AddTotalTPCCut(15);
        arHandlerTwoBasicRec[i]->AddImpactPointCut(4,2);
        arHandlerTwoBasicRec[i]->AddPtCut(0, 1.5);
  //      arHandlerTwoBasicRec[i]->AddPCut(0.3,200);
        arHandlerTwoBasicRec[i]->AddAcceptCut();
        
        arHandlerTwoBasicRec[i]->AddEtaBackward(3.2+i*0.2,3.7+i*0.2);
        arHandlerTwoBasicRec[i]->AddEtaForward(5.5,6);
              
		HandList->AddHandler(arHandlerTwoBasicSim[i]);
        HandList->AddHandler(arHandlerTwoBasicRec[i]);
    }
       
    const int N4=0;//24;
    LRCHandler* arHandlerTwoShiftsSim[N4]; 
    LRCHandler* arHandlerTwoShiftsRec[N4];
    for (int i =0; i<N4; i++){
        TString name;
        TString nameShifts="name_Shifts";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameShifts + name2;
        arHandlerTwoShiftsSim[i] = new LRCHandler(name+"Sim.root", true); 
        arHandlerTwoShiftsRec[i] = new LRCHandler(name+"Rec.root", false); 
		arHandlerTwoShiftsSim[i] -> Simulation();
		arHandlerTwoShiftsRec[i] -> Simulation();
   
        //arHandlerTwoShiftsSim[i]->AddBPDCut();
        //arHandlerTwoShiftsSim[i]->AddFittedVtxCut();
        //arHandlerTwoShiftsSim[i]->AddFitQualityCut();
        //arHandlerTwoShiftsSim[i]->AddNVtxTracksCut(3);
        //arHandlerTwoShiftsSim[i]->AddZVtxCut(-586.5, -574.1);
        
		arHandlerTwoShiftsSim[i]->AddCentrality(0,0.2);
//		arHandlerTwoShiftsSim[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoShiftsSim[i]->AddChargeTrkCut(0);
        
  //      arHandlerTwoShiftsSim[i]->AddVTPCAndGTPCCut(15,5);
   //     arHandlerTwoShiftsSim[i]->AddTotalTPCCut(15);
   //     arHandlerTwoShiftsSim[i]->AddImpactPointCut(4,2);
        arHandlerTwoShiftsSim[i]->AddPtCut(0, 1.5);
  //      arHandlerTwoShiftsSim[i]->AddPCut(0.3,200);
        arHandlerTwoShiftsSim[i]->AddAcceptCut();
        
        arHandlerTwoShiftsSim[i]->AddEtaBackward(3.2+i*0.1,3.7+i*0.1);
        arHandlerTwoShiftsSim[i]->AddEtaForward(3.7+i*0.1,4.2+i*0.1);
       
		// --- start: cuts only for real data
		// --- end.
        arHandlerTwoShiftsRec[i]->AddNVtxTracksCut(3);
        arHandlerTwoShiftsRec[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoShiftsRec[i]->AddCentrality(0,0.2);
        
        arHandlerTwoShiftsRec[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoShiftsRec[i]->AddChargeTrkCut(0);
        
        arHandlerTwoShiftsRec[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoShiftsRec[i]->AddTotalTPCCut(15);
        arHandlerTwoShiftsRec[i]->AddImpactPointCut(4,2);
        arHandlerTwoShiftsRec[i]->AddPtCut(0, 1.5);
   //     arHandlerTwoShiftsRec[i]->AddPCut(0.3,200);
        arHandlerTwoShiftsRec[i]->AddAcceptCut();
        
        arHandlerTwoShiftsRec[i]->AddEtaBackward(3.2+i*0.1,3.7+i*0.1);
        arHandlerTwoShiftsRec[i]->AddEtaForward(3.7+i*0.1,4.2+i*0.1);
              
		HandList->AddHandler(arHandlerTwoShiftsSim[i]);
        HandList->AddHandler(arHandlerTwoShiftsRec[i]);
    }
    
    const int N5=0;//9;
    LRCHandler* arHandlerTwoBasicSimWA[N3]; 
    for (int i =0; i<N3; i++){
        TString name;
        TString nameBasic="name_Basic";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameBasic + name2;
        arHandlerTwoBasicSimWA[i] = new LRCHandler(name+"SimWA.root", true); 
		arHandlerTwoBasicSimWA[i] -> Simulation();

		arHandlerTwoBasicSimWA[i]->AddCentrality(0,0.2);
        
        arHandlerTwoBasicSimWA[i]->AddChargeTrkCut(0);
        arHandlerTwoBasicSimWA[i]->AddPtCut(0, 1.5);
  //      arHandlerTwoBasicSimWA[i]->AddPCut(0.3,200);
 //      arHandlerTwoBasicSimWA[i]->AddAcceptCut();
        
        arHandlerTwoBasicSimWA[i]->AddEtaBackward(3.2+i*0.2,3.7+i*0.2);
        arHandlerTwoBasicSimWA[i]->AddEtaForward(5.5,6);
              
		HandList->AddHandler(arHandlerTwoBasicSimWA[i]);
    }
       
    const int N6=0;//24;
    LRCHandler* arHandlerTwoShiftsSimWA[N4]; 
    for (int i =0; i<N4; i++){
        TString name;
        TString nameShifts="name_Shifts";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameShifts + name2;
        arHandlerTwoShiftsSimWA[i] = new LRCHandler(name+"SimWA.root", true); 
		arHandlerTwoShiftsSimWA[i] -> Simulation();
        
		arHandlerTwoShiftsSimWA[i]->AddCentrality(0,0.2);
        
        arHandlerTwoShiftsSimWA[i]->AddChargeTrkCut(0);

        arHandlerTwoShiftsSimWA[i]->AddPtCut(0, 1.5);
//        arHandlerTwoShiftsSimWA[i]->AddPCut(0.3,200);
 //       arHandlerTwoShiftsSimWA[i]->AddAcceptCut();
        
        arHandlerTwoShiftsSimWA[i]->AddEtaBackward(3.2+i*0.1,3.7+i*0.1);
        arHandlerTwoShiftsSimWA[i]->AddEtaForward(3.7+i*0.1,4.2+i*0.1);
                     
		HandList->AddHandler(arHandlerTwoShiftsSimWA[i]);
    }
	const int N7=0;//9;
    LRCHandler* arHandlerTwoBasicRecDil[N7];
    for (int i =0; i<N7; i++){
        TString name;
        TString nameBasic="name_Basic";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameBasic + name2;
        arHandlerTwoBasicRecDil[i] = new LRCHandler(name+"RecDil.root", false); 
		arHandlerTwoBasicRecDil[i] -> Simulation();
   
        arHandlerTwoBasicRecDil[i]->AddNVtxTracksCut(3);
        arHandlerTwoBasicRecDil[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoBasicRecDil[i]->AddCentrality(0,0.2);
        
        arHandlerTwoBasicRecDil[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoBasicRecDil[i]->AddChargeTrkCut(0);
        
        arHandlerTwoBasicRecDil[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoBasicRecDil[i]->AddTotalTPCCut(15);
        arHandlerTwoBasicRecDil[i]->AddImpactPointCut(4,2);
        arHandlerTwoBasicRecDil[i]->AddPtCut(0, 1.5);
        arHandlerTwoBasicRecDil[i]->AddAcceptCut();
		arHandlerTwoBasicRecDil[i]->AddDiluteCut(0.2);
        
        arHandlerTwoBasicRecDil[i]->AddEtaBackward(3.2+i*0.2,3.7+i*0.2);
        arHandlerTwoBasicRecDil[i]->AddEtaForward(5.5,6);
              
        HandList->AddHandler(arHandlerTwoBasicRecDil[i]);
    }
       
    const int N8=0;//24;
    LRCHandler* arHandlerTwoShiftsRecDil[N8];
    for (int i =0; i<N8; i++){
        TString name;
        TString nameShifts="name_Shifts";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameShifts + name2;
        arHandlerTwoShiftsRecDil[i] = new LRCHandler(name+"RecDil.root", false); 
		arHandlerTwoShiftsRecDil[i] -> Simulation();

        arHandlerTwoShiftsRecDil[i]->AddNVtxTracksCut(3);
        arHandlerTwoShiftsRecDil[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoShiftsRecDil[i]->AddCentrality(0,0.2);
        
        arHandlerTwoShiftsRecDil[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoShiftsRecDil[i]->AddChargeTrkCut(0);
        
        arHandlerTwoShiftsRecDil[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoShiftsRecDil[i]->AddTotalTPCCut(15);
        arHandlerTwoShiftsRecDil[i]->AddImpactPointCut(4,2);
        arHandlerTwoShiftsRecDil[i]->AddPtCut(0, 1.5);
        arHandlerTwoShiftsRecDil[i]->AddAcceptCut();
        arHandlerTwoShiftsRecDil[i]->AddDiluteCut(0.2);
        arHandlerTwoShiftsRecDil[i]->AddEtaBackward(3.2+i*0.1,3.7+i*0.1);
        arHandlerTwoShiftsRecDil[i]->AddEtaForward(3.7+i*0.1,4.2+i*0.1);
              
        HandList->AddHandler(arHandlerTwoShiftsRecDil[i]);
    }

	const int N9=0;//9;
    LRCHandler* arHandlerTwoBasicRecPCu[N9];
    for (int i =0; i<N9; i++){
        TString name;
        TString nameBasic="name_Basic";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameBasic + name2;
        arHandlerTwoBasicRecPCu[i] = new LRCHandler(name+"RecPCu.root", false); 
		arHandlerTwoBasicRecPCu[i] -> Simulation();
   
        arHandlerTwoBasicRecPCu[i]->AddNVtxTracksCut(3);
        arHandlerTwoBasicRecPCu[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoBasicRecPCu[i]->AddCentrality(0,0.2);
        
        arHandlerTwoBasicRecPCu[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoBasicRecPCu[i]->AddChargeTrkCut(0);
        
        arHandlerTwoBasicRecPCu[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoBasicRecPCu[i]->AddTotalTPCCut(15);
        arHandlerTwoBasicRecPCu[i]->AddImpactPointCut(4,2);
        arHandlerTwoBasicRecPCu[i]->AddPtCut(0, 1.5);
        arHandlerTwoBasicRecPCu[i]->AddAcceptCut();
		arHandlerTwoBasicRecPCu[i]->AddPCut(2.5, 200);
        
        arHandlerTwoBasicRecPCu[i]->AddEtaBackward(3.2+i*0.2,3.7+i*0.2);
        arHandlerTwoBasicRecPCu[i]->AddEtaForward(5.5,6);
              
        HandList->AddHandler(arHandlerTwoBasicRecPCu[i]);
    }
       
    const int N10=0;//24;
    LRCHandler* arHandlerTwoShiftsRecPCu[N10];
    for (int i =0; i<N10; i++){
        TString name;
        TString nameShifts="name_Shifts";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameShifts + name2;
        arHandlerTwoShiftsRecPCu[i] = new LRCHandler(name+"RecPCu.root", false); 
		arHandlerTwoShiftsRecPCu[i] -> Simulation();

        arHandlerTwoShiftsRecPCu[i]->AddNVtxTracksCut(3);
        arHandlerTwoShiftsRecPCu[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoShiftsRecPCu[i]->AddCentrality(0,0.2);
        
        arHandlerTwoShiftsRecPCu[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoShiftsRecPCu[i]->AddChargeTrkCut(0);
        
        arHandlerTwoShiftsRecPCu[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoShiftsRecPCu[i]->AddTotalTPCCut(15);
        arHandlerTwoShiftsRecPCu[i]->AddImpactPointCut(4,2);
        arHandlerTwoShiftsRecPCu[i]->AddPtCut(0, 1.5);
        arHandlerTwoShiftsRecPCu[i]->AddAcceptCut();
        arHandlerTwoShiftsRecPCu[i]->AddPCut(2.5, 200);
        arHandlerTwoShiftsRecPCu[i]->AddEtaBackward(3.2+i*0.1,3.7+i*0.1);
        arHandlerTwoShiftsRecPCu[i]->AddEtaForward(3.7+i*0.1,4.2+i*0.1);
              
        HandList->AddHandler(arHandlerTwoShiftsRecPCu[i]);
    }

	const int N11=0;//9;
    LRCHandler* arHandlerTwoBasicRecPtC[N11];
    for (int i =0; i<N11; i++){
        TString name;
        TString nameBasic="name_Basic";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameBasic + name2;
        arHandlerTwoBasicRecPtC[i] = new LRCHandler(name+"RecPtC.root", false); 
		arHandlerTwoBasicRecPtC[i] -> Simulation();
   
        arHandlerTwoBasicRecPtC[i]->AddNVtxTracksCut(3);
        arHandlerTwoBasicRecPtC[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoBasicRecPtC[i]->AddCentrality(0,0.2);
        
        arHandlerTwoBasicRecPtC[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoBasicRecPtC[i]->AddChargeTrkCut(0);
        
        arHandlerTwoBasicRecPtC[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoBasicRecPtC[i]->AddTotalTPCCut(15);
        arHandlerTwoBasicRecPtC[i]->AddImpactPointCut(4,2);
        arHandlerTwoBasicRecPtC[i]->AddPtCut(0, 0.8);
        arHandlerTwoBasicRecPtC[i]->AddAcceptCut();
        
        arHandlerTwoBasicRecPtC[i]->AddEtaBackward(3.2+i*0.2,3.7+i*0.2);
        arHandlerTwoBasicRecPtC[i]->AddEtaForward(5.5,6);
              
        HandList->AddHandler(arHandlerTwoBasicRecPtC[i]);
    }
       
    const int N12=0;//24;
    LRCHandler* arHandlerTwoShiftsRecPtC[N12];
    for (int i =0; i<N12; i++){
        TString name;
        TString nameShifts="name_Shifts";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameShifts + name2;
        arHandlerTwoShiftsRecPtC[i] = new LRCHandler(name+"RecPtC.root", false); 
		arHandlerTwoShiftsRecPtC[i] -> Simulation();

        arHandlerTwoShiftsRecPtC[i]->AddNVtxTracksCut(3);
        arHandlerTwoShiftsRecPtC[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoShiftsRecPtC[i]->AddCentrality(0,0.2);
        
        arHandlerTwoShiftsRecPtC[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoShiftsRecPtC[i]->AddChargeTrkCut(0);
        
        arHandlerTwoShiftsRecPtC[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoShiftsRecPtC[i]->AddTotalTPCCut(15);
        arHandlerTwoShiftsRecPtC[i]->AddImpactPointCut(4,2);
        arHandlerTwoShiftsRecPtC[i]->AddPtCut(0, 0.8);
        arHandlerTwoShiftsRecPtC[i]->AddAcceptCut();

		arHandlerTwoShiftsRecPtC[i]->AddEtaBackward(3.2+i*0.1,3.7+i*0.1);
        arHandlerTwoShiftsRecPtC[i]->AddEtaForward(3.7+i*0.1,4.2+i*0.1);
              
        HandList->AddHandler(arHandlerTwoShiftsRecPtC[i]);
    }

    const int N13=0;//9;
    LRCHandler* arHandlerTwoBasicDiR[N13];
    for (int i =0; i<N13; i++){
        TString name;
        TString nameBasic="name_Basic";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameBasic + name2;
        arHandlerTwoBasicDiR[i] = new LRCHandler(name+"DiR.root", false); 
		arHandlerTwoBasicDiR[i]->Raw();
  
		// --- start: cuts only for real data
		arHandlerTwoBasicDiR[i]->AddT2Cut();
		arHandlerTwoBasicDiR[i]->AddWFACut(-100,-200, 1.5);
		arHandlerTwoBasicDiR[i]->AddChargeCut();
        arHandlerTwoBasicDiR[i]->AddBPDCut();
        arHandlerTwoBasicDiR[i]->AddFittedVtxCut();
        arHandlerTwoBasicDiR[i]->AddFitQualityCut();
		// --- end.
        arHandlerTwoBasicDiR[i]->AddNVtxTracksCut(3);
        arHandlerTwoBasicDiR[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoBasicDiR[i]->AddCentrality(0,0.2);
        
        arHandlerTwoBasicDiR[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoBasicDiR[i]->AddChargeTrkCut(0);
        
        arHandlerTwoBasicDiR[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoBasicDiR[i]->AddTotalTPCCut(15);
        arHandlerTwoBasicDiR[i]->AddImpactPointCut(4,2);
        arHandlerTwoBasicDiR[i]->AddPtCut(0, 1.5);
//        arHandlerTwoBasicDiR[i]->AddPCut(0.3,200);
        arHandlerTwoBasicDiR[i]->AddAcceptCut();
		arHandlerTwoBasicDiR[i]->AddDiluteCut(0.2);
         
        arHandlerTwoBasicDiR[i]->AddEtaBackward(3.2+i*0.2,3.7+i*0.2);
        arHandlerTwoBasicDiR[i]->AddEtaForward(5.5,6);
        
        HandList->AddHandler(arHandlerTwoBasicDiR[i]);
    }

	const int N14=0;//24;
    LRCHandler* arHandlerTwoShiftDiR[N14];
    for (int i =0; i<N14; i++){
        TString name;
        TString nameShift="name_Shift";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameShift + name2;
        arHandlerTwoShiftDiR[i] = new LRCHandler(name+"DiR.root", false); 
        arHandlerTwoShiftDiR[i]->Raw();   
        //--- start: cuts only for real data
		arHandlerTwoShiftDiR[i]->AddT2Cut();
		arHandlerTwoShiftDiR[i]->AddWFACut(-100,-200, 1.5);
		arHandlerTwoShiftDiR[i]->AddChargeCut();
        arHandlerTwoShiftDiR[i]->AddBPDCut();
        arHandlerTwoShiftDiR[i]->AddFittedVtxCut();
        arHandlerTwoShiftDiR[i]->AddFitQualityCut();
		//--- end;
        arHandlerTwoShiftDiR[i]->AddNVtxTracksCut(3);
        arHandlerTwoShiftDiR[i]->AddZVtxCut(-586.5, -574.1);
	    arHandlerTwoShiftDiR[i]->AddCentrality(0,0.2);
        
        arHandlerTwoShiftDiR[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoShiftDiR[i]->AddChargeTrkCut(0);
        
        arHandlerTwoShiftDiR[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoShiftDiR[i]->AddTotalTPCCut(15);
        arHandlerTwoShiftDiR[i]->AddImpactPointCut(4,2);
        arHandlerTwoShiftDiR[i]->AddPtCut(0, 1.5);
//        arHandlerTwoShiftDiR[i]->AddPCut(0.3,200);
        arHandlerTwoShiftDiR[i]->AddAcceptCut();
		arHandlerTwoShiftDiR[i]->AddDiluteCut(0.2);
        
        arHandlerTwoShiftDiR[i]->AddEtaBackward(3.2+i*0.1,3.7+i*0.1);
        arHandlerTwoShiftDiR[i]->AddEtaForward(3.7+i*0.1,4.2+i*0.1);
        
		HandList->AddHandler(arHandlerTwoShiftDiR[i]);
    }

    const int N15=0;//9;
    LRCHandler* arHandlerTwoBasicPRa[N15];
    for (int i =0; i<N15; i++){
        TString name;
        TString nameBasic="name_Basic";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameBasic + name2;
        arHandlerTwoBasicPRa[i] = new LRCHandler(name+"PRa.root", false); 
		arHandlerTwoBasicPRa[i]->Raw();
  
		// --- start: cuts only for real data
		arHandlerTwoBasicPRa[i]->AddT2Cut();
		arHandlerTwoBasicPRa[i]->AddWFACut(-100,-200, 1.5);
		arHandlerTwoBasicPRa[i]->AddChargeCut();
        arHandlerTwoBasicPRa[i]->AddBPDCut();
        arHandlerTwoBasicPRa[i]->AddFittedVtxCut();
        arHandlerTwoBasicPRa[i]->AddFitQualityCut();
		// --- end.
        arHandlerTwoBasicPRa[i]->AddNVtxTracksCut(3);
        arHandlerTwoBasicPRa[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoBasicPRa[i]->AddCentrality(0,0.2);
        
        arHandlerTwoBasicPRa[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoBasicPRa[i]->AddChargeTrkCut(0);
        
        arHandlerTwoBasicPRa[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoBasicPRa[i]->AddTotalTPCCut(15);
        arHandlerTwoBasicPRa[i]->AddImpactPointCut(4,2);
        arHandlerTwoBasicPRa[i]->AddPtCut(0, 1.5);
	    arHandlerTwoBasicPRa[i]->AddPCut(2.5,200);
        arHandlerTwoBasicPRa[i]->AddAcceptCut();
        
        arHandlerTwoBasicPRa[i]->AddEtaBackward(3.2+i*0.2,3.7+i*0.2);
        arHandlerTwoBasicPRa[i]->AddEtaForward(5.5,6);
        
        HandList->AddHandler(arHandlerTwoBasicPRa[i]);
    }

	const int N16=0;//24;
    LRCHandler* arHandlerTwoShiftPRa[N16];
    for (int i =0; i<N16; i++){
        TString name;
        TString nameShift="name_Shift";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameShift + name2;
        arHandlerTwoShiftPRa[i] = new LRCHandler(name+"PRa.root", false); 
        arHandlerTwoShiftPRa[i]->Raw();   
        //--- start: cuts only for real data
		arHandlerTwoShiftPRa[i]->AddT2Cut();
		arHandlerTwoShiftPRa[i]->AddWFACut(-100,-200, 1.5);
		arHandlerTwoShiftPRa[i]->AddChargeCut();
        arHandlerTwoShiftPRa[i]->AddBPDCut();
        arHandlerTwoShiftPRa[i]->AddFittedVtxCut();
        arHandlerTwoShiftPRa[i]->AddFitQualityCut();
		//--- end;
        arHandlerTwoShiftPRa[i]->AddNVtxTracksCut(3);
        arHandlerTwoShiftPRa[i]->AddZVtxCut(-586.5, -574.1);
	    arHandlerTwoShiftPRa[i]->AddCentrality(0,0.2);
        
        arHandlerTwoShiftPRa[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoShiftPRa[i]->AddChargeTrkCut(0);
        
        arHandlerTwoShiftPRa[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoShiftPRa[i]->AddTotalTPCCut(15);
        arHandlerTwoShiftPRa[i]->AddImpactPointCut(4,2);
        arHandlerTwoShiftPRa[i]->AddPtCut(0, 1.5);
        arHandlerTwoShiftPRa[i]->AddPCut(2.5,200);
        arHandlerTwoShiftPRa[i]->AddAcceptCut();
        
        arHandlerTwoShiftPRa[i]->AddEtaBackward(3.2+i*0.1,3.7+i*0.1);
        arHandlerTwoShiftPRa[i]->AddEtaForward(3.7+i*0.1,4.2+i*0.1);
        
		HandList->AddHandler(arHandlerTwoShiftPRa[i]);
    }

    const int N17=0;//9;
    LRCHandler* arHandlerTwoBasicPtR[N17];
    for (int i =0; i<N17; i++){
        TString name;
        TString nameBasic="name_Basic";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameBasic + name2;
        arHandlerTwoBasicPtR[i] = new LRCHandler(name+"PtR.root", false); 
		arHandlerTwoBasicPtR[i]->Raw();
  
		// --- start: cuts only for real data
		arHandlerTwoBasicPtR[i]->AddT2Cut();
		arHandlerTwoBasicPtR[i]->AddWFACut(-100,-200, 1.5);
		arHandlerTwoBasicPtR[i]->AddChargeCut();
        arHandlerTwoBasicPtR[i]->AddBPDCut();
        arHandlerTwoBasicPtR[i]->AddFittedVtxCut();
        arHandlerTwoBasicPtR[i]->AddFitQualityCut();
		// --- end.
        arHandlerTwoBasicPtR[i]->AddNVtxTracksCut(3);
        arHandlerTwoBasicPtR[i]->AddZVtxCut(-586.5, -574.1);
        arHandlerTwoBasicPtR[i]->AddCentrality(0,0.2);
        
        arHandlerTwoBasicPtR[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoBasicPtR[i]->AddChargeTrkCut(0);
        
        arHandlerTwoBasicPtR[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoBasicPtR[i]->AddTotalTPCCut(15);
        arHandlerTwoBasicPtR[i]->AddImpactPointCut(4,2);
        arHandlerTwoBasicPtR[i]->AddPtCut(0, 0.8);
//        arHandlerTwoBasicPtR[i]->AddPCut(0.3,200);
        arHandlerTwoBasicPtR[i]->AddAcceptCut();
        
        arHandlerTwoBasicPtR[i]->AddEtaBackward(3.2+i*0.2,3.7+i*0.2);
        arHandlerTwoBasicPtR[i]->AddEtaForward(5.5,6);
        
        HandList->AddHandler(arHandlerTwoBasicPtR[i]);
    }

	const int N18=0;//24;
    LRCHandler* arHandlerTwoShiftPtR[N18];
    for (int i =0; i<N18; i++){
        TString name;
        TString nameShift="name_Shift";
        char name2[50];
        sprintf(name2,"_%i",i);
        name = nameShift + name2;
        arHandlerTwoShiftPtR[i] = new LRCHandler(name+"PtR.root", false); 
        arHandlerTwoShiftPtR[i]->Raw();   
        //--- start: cuts only for real data
		arHandlerTwoShiftPtR[i]->AddT2Cut();
		arHandlerTwoShiftPtR[i]->AddWFACut(-100,-200, 1.5);
		arHandlerTwoShiftPtR[i]->AddChargeCut();
        arHandlerTwoShiftPtR[i]->AddBPDCut();
        arHandlerTwoShiftPtR[i]->AddFittedVtxCut();
        arHandlerTwoShiftPtR[i]->AddFitQualityCut();
		//--- end;
        arHandlerTwoShiftPtR[i]->AddNVtxTracksCut(3);
        arHandlerTwoShiftPtR[i]->AddZVtxCut(-586.5, -574.1);
	    arHandlerTwoShiftPtR[i]->AddCentrality(0,0.2);
        
        arHandlerTwoShiftPtR[i]->AddVtxTrackStatusCut();
        
        arHandlerTwoShiftPtR[i]->AddChargeTrkCut(0);
        
        arHandlerTwoShiftPtR[i]->AddVTPCAndGTPCCut(15,5);
        arHandlerTwoShiftPtR[i]->AddTotalTPCCut(15);
        arHandlerTwoShiftPtR[i]->AddImpactPointCut(4,2);
        arHandlerTwoShiftPtR[i]->AddPtCut(0, 0.8);
//        arHandlerTwoShiftPtR[i]->AddPCut(0.3,200);
        arHandlerTwoShiftPtR[i]->AddAcceptCut();
        
        arHandlerTwoShiftPtR[i]->AddEtaBackward(3.2+i*0.1,3.7+i*0.1);
        arHandlerTwoShiftPtR[i]->AddEtaForward(3.7+i*0.1,4.2+i*0.1);
        
		HandList->AddHandler(arHandlerTwoShiftPtR[i]);
    }

	HandList->Init();
    int i=0;
	time_t     now;
	struct tm  *ts;
	char       buf[80];
	int nFiles = 0;

    while (true){
        string fileName;
        fileList >> fileName;
        if(!fileList.good())
            break;
        cout << " ->processing " << fileName << endl;
        EventFile eventFile(fileName, eRead, Verbosity::eSilent, offBranches, onBranches);
        Event event;

        cout<<"event loop ... "<<endl;
        // --- loop over events
        
        while (eventFile.Read(event) == eSuccess){
			i++;
	//		cout<<"event_event"<<i<<endl;
			// --- working status output
//			cout<<i<<"\t";
			if(i%1000==0){
				// Get the current time
				now = time(NULL);          
				// Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" 
				ts = localtime(&now);
				strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", ts);
				printf("running event %5d time: %s\n",(int) i,buf);
			} 
			CutList::eventCutChecking.Reset();
//			cout<<"eat"<<endl;
            HandList->EatEvent(event);
        }
    }      

    delete HandList; 
    
	return 0;
}
