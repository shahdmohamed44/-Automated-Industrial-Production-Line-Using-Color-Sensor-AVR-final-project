#include "interface.h"
#include "private.h"
#include "../../LIBRARY/macros.h"
#include "../../LIBRARY/standard_types.h"

void ADC_INIT(u8 Vref, u8 Division_factor){

    switch(Vref){
        case VREF_AVCC:   // 5V
            SET_BIT(ADMUX,REFS0);
            CLEAR_BIT(ADMUX,REFS1);
            break;

        case VREF_256:    // 2.56V
            SET_BIT(ADMUX,REFS0);
            SET_BIT(ADMUX,REFS1);
            break;
    }

    switch(Division_factor){
        case DIV_2:
            CLEAR_BIT(ADCSRA, ADPS2);
            CLEAR_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS0);
            break;

        case DIV_4:
            CLEAR_BIT(ADCSRA, ADPS2);
            SET_BIT(ADCSRA, ADPS1);
            CLEAR_BIT(ADCSRA, ADPS0);
            break;

        case DIV_8:
            CLEAR_BIT(ADCSRA, ADPS2);
            SET_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS0);
            break;

        case DIV_16:
            SET_BIT(ADCSRA, ADPS2);
            CLEAR_BIT(ADCSRA, ADPS1);
            CLEAR_BIT(ADCSRA, ADPS0);
            break;

        case DIV_32:
            SET_BIT(ADCSRA, ADPS2);
            CLEAR_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS0);
            break;

        case DIV_64:
            SET_BIT(ADCSRA, ADPS2);
            SET_BIT(ADCSRA, ADPS1);
            CLEAR_BIT(ADCSRA, ADPS0);
            break;

        case DIV_128:
            SET_BIT(ADCSRA, ADPS2);
            SET_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS0);
            break;
    }


    SET_BIT(ADCSRA, ADEN);
}

u16 ADC_readChannel(u8 channel){
    ADMUX = (ADMUX & 0xE0) | (channel & 0x07);
    SET_BIT(ADCSRA, ADSC);                      // Start conversion

    while (BIT_IS_CLEAR(ADCSRA, ADIF));

    SET_BIT(ADCSRA, ADIF);

    return ADCL;
}
