#ifndef TPARAMETERSET_H
#define TPARAMETERSET_H

class Event;            //charis
class EventSetup;       //charis
class EcalSeverityLevelAlgo;    //charis

struct tParameterSet {
    //!Contains the HLT paths
    std::string hltPath;
    //!Contains the index in trigger names where hltPath is kept
    int hltPathIndex;
    //!Contains the filters
    std::vector<std::string> hltFilters1;
    std::vector<std::string> hltFilters2;
    //!Contains the leg
    int leg1;
    int leg2;
};

typedef std::vector<tParameterSet> tVParameterSet;

#endif

