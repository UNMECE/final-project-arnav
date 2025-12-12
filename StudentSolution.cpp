#include "acequia_manager.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <cmath> 

const double FLOOD_SAFETY_MARGIN = 0.95;
const double SOURCE_SAFETY_BUFFER = 0.1; 

void solveProblems(AcequiaManager& manager)
{
    const auto& canals = manager.getCanals();

    while(!manager.isSolved && manager.hour < manager.SimulationMax) 
    {
        // Check every canal for a beneficial, safe transfer opportunity.
        for (Canal* canal : canals) 
        {
            Region* source = canal->sourceRegion;
            Region* dest = canal->destinationRegion;
            
            bool sourceIsNetSource = source->waterLevel > (source->waterNeed + SOURCE_SAFETY_BUFFER);
            
            bool destNeedsWater = dest->waterLevel < dest->waterNeed || dest->waterLevel == 0.0;
            
            bool destIsSafe = dest->waterLevel < (dest->waterCapacity * FLOOD_SAFETY_MARGIN);
            
            if (sourceIsNetSource && destNeedsWater && destIsSafe) 
            {
                canal->setFlowRate(1.0); 
                canal->toggleOpen(true);
            } 
            else 
            {
                canal->toggleOpen(false);
                canal->setFlowRate(0.0); 
            }
        }
        
        manager.nexthour();
    }
}


            bool sourceIsNetSource = source->waterLevel > (source->waterNeed + SOURCE_SAFETY_BUFFER);
            
            bool destNeedsWater = dest->waterLevel < dest->waterNeed || dest->waterLevel == 0.0;
            
            bool destIsSafe = dest->waterLevel < (dest->waterCapacity * FLOOD_SAFETY_MARGIN);
            
            if (sourceIsNetSource && destNeedsWater && destIsSafe) 
            {
                canal->setFlowRate(1.0); 
                canal->toggleOpen(true);
            } 
            else 
            {
                canal->toggleOpen(false);
                canal->setFlowRate(0.0); 
            }
        }
        
        manager.nexthour();
    }
}



