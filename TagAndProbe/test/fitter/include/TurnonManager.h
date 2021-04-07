/**
 *  @file  TurnonManager.h
 *  @brief  
 *
 *
 *  @author  Jean-Baptiste Sauvan <sauvan@llr.in2p3.fr>
 *
 *  @date    06/10/2014
 *
 *  @internal
 *     Created :  06/10/2014
 * Last update :  06/10/2014 14:24:37
 *          by :  JB Sauvan
 *
 * =====================================================================================
 */




#ifndef TURNONMANAGER_H
#define TURNONMANAGER_H

#include "TFile.h"
#include "TEnv.h"
#include "TurnonFit.h"

class TurnonManager
{
    public:
        TurnonManager();
        ~TurnonManager();

        bool readConfig(const std::string& config);
        void fit();

    private:
        TEnv m_params;
        int m_nCPU;
        bool m_noFit;
        std::vector<TurnonFit*> m_turnonFits;
        TFile* m_outputFile;


};


#endif
