#include "crib_helpers.h"

const char* int_to_phase(int phaseEnum){
    if(phaseEnum == 0){
        return "CHOOSING";
    } else if(phaseEnum == 1){
        return "ROUND";
    } else if(phaseEnum == 2){
        return "COUNT";
    } else {
        return "INVALID PHASE";
    };
}