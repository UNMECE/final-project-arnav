#include "acequia_manager.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <cmath> // Included for potential use, though not strictly required for the final logic

// Global constants for safety and efficiency
const double FLOOD_SAFETY_MARGIN = 0.95;    // Close canal if destination is 95% full
// CRITICAL: Minimal buffer for maximum transfer time to avoid running out of hours.
const double SOURCE_SAFETY_BUFFER = 0.001; 

void solveProblems(AcequiaManager& manager)
{
    // Use the correct getter for canals
    const auto& canals = manager.getCanals();

    // Use the correct members for the while loop condition
    while(!manager.isSolved && manager.hour < manager.SimulationMax) 
    {
        // Check every canal for a beneficial, safe transfer opportunity.
        for (Canal* canal : canals) 
        {
            // Access members directly (sourceRegion is a pointer to Region object)
            Region* source = canal->sourceRegion;
            Region* dest = canal->destinationRegion;
            
            // --- 1. Source Safety: Must have a surplus to give (avoids self-inflicted drought penalty).
            // Flow continues until the source is only 0.001 above its waterNeed.
            bool sourceIsNetSource = source->waterLevel > (source->waterNeed + SOURCE_SAFETY_BUFFER);
            
            // --- 2. Destination Need: Must be below its need OR at 0 (penalty mitigation).
            // A destination needs water if it is below the required level OR if it is at 0 (constant penalty).
            bool destNeedsWater = dest->waterLevel < dest->waterNeed || dest->waterLevel == 0.0;
            
            // --- 3. Destination Safety: Must be below the flood threshold (avoids overflow penalty).
            bool destIsSafe = dest->waterLevel < (dest->waterCapacity * FLOOD_SAFETY_MARGIN);
            
            
            // CONDITION TO OPEN:
            // If the source has a surplus, and the transfer is safe and needed, open the canal.
            if (sourceIsNetSource && destNeedsWater && destIsSafe) 
            {
                // Set to MAX flow rate (1.0) to solve the problem as fast as possible.
                canal->setFlowRate(1.0); 
                canal->toggleOpen(true);
            } 
            // CONDITION TO CLOSE:
            else 
            {
                // Close the canal if the transfer is no longer beneficial or is dangerous.
                canal->toggleOpen(false);
                canal->setFlowRate(0.0); 
            }
        }
        
        // Use the correct function to advance the simulation hour
        manager.nexthour();
    }
}
