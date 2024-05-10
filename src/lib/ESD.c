#include "ESD.h"
#include "customio.h"
#include <stdint.h>

void new_ESD_t(ESD_t *ESD, IO_t *SDI, IO_t *SFTCLK, IO_t *LCHCLK, uint8_t NoD) {
    ESD->SDI = SDI;
    ESD->SFTCLK = SFTCLK;
    ESD->LCHCLK = LCHCLK;
    ESD->NoD = NoD;

}

