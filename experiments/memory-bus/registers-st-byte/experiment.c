
/*!
@ingroup experiments-memory-registers-st-byte
@{
*/

#include <stdlib.h>
#include <string.h>

#include "uas_bsp.h"

#include "experiment.h"

#ifndef DLEN
    #define DLEN 128
#endif

uint8_t  zeros     [DLEN]; //!< TTest fixed input value.
uint8_t  di1_fixed,di1_rand ; //!< TTest random input values.
uint8_t  di2_fixed,di2_rand ; //!< TTest random input values.
uint8_t  din       [DLEN]; //!< Array of zeros except for TTest variable.
uint8_t  dindex1         ; //!< Index into DIN to load/modify.
uint8_t  dindex2         ; //!< Offset of DIN to load during experiment_run

//! Variables which the SCASS framework can control.
scass_target_var  experiment_variables [] = {
{"di1" , 1, &di1_rand, &di1_fixed, SCASS_FLAGS_TTEST_IN},
{"di2" , 1, &di2_rand, &di2_fixed, SCASS_FLAGS_TTEST_IN},
{"idx1", 1, &dindex1 , &dindex1  , SCASS_FLAG_INPUT    },
{"idx2", 1, &dindex2 , &dindex2  , SCASS_FLAG_INPUT    },
};

//! Declaration for the experiment payload function in store-byte.S
extern void     * experiment_payload(
    uint8_t * idx1,
    uint8_t * idx2, 
    uint8_t   d1  ,
    uint8_t   d2
);

/*!
@details Does nothing.
*/
uint8_t experiment_init(
    scass_target_cfg * cfg //!< SCASS Framework configuration object.
) {
    return 0;
}
 
/*!
@brief Runs prior to each experiment. Used for setup.
*/
uint8_t experiment_pre_run(
        scass_target_cfg * cfg,
        char               fixed
){
    for(int i = 0; i < DLEN; i ++) {
        din  [i] = 0;
        zeros[i] = 0;
    }
    return 0;
}

/*!
@details Runs the experiment, then finishes.
*/
uint8_t experiment_run(
    scass_target_cfg * cfg,  //!< SCASS Framework configuration object.
    char               fixed //!< used fixed variants of variables?
){
    
    uint8_t mask = cfg -> randomness[0];

    uint8_t d1 = (fixed ? di1_fixed: di1_rand) ^ mask;
    uint8_t d2 = (fixed ? di2_fixed: di2_rand) ^ mask;

    uas_bsp_trigger_set();
    
    experiment_payload(
        &din[dindex1],
        &din[dindex2],
        d1           ,
        d2
    );
    
    uas_bsp_trigger_clear();

    return 0;

}

void experiment_setup_scass(
    scass_target_cfg * cfg //!< The config object to setup.
){

    cfg -> scass_experiment_init    = experiment_init;
    cfg -> scass_experiment_pre_run = experiment_pre_run;
    cfg -> scass_experiment_run     = experiment_run ;

    cfg -> experiment_name       = "memory/registers-st-byte";

    cfg -> variables             = experiment_variables ;
    cfg -> num_variables         = 4                    ;
    cfg -> randomness_len        = experiment_variables[0].size;
    cfg -> randomness_refresh_rate = 1;

}

//! @}

