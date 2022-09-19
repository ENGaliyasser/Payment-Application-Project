#ifndef CARD_H
#define CARD_H
#include <stdint.h>
//typedefs
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20]; //20
	uint8_t cardExpirationDate[6]; //6
}ST_cardData_t;

typedef enum EN_cardError_t
{
	ok, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;


//functions prototypes
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


#endif

