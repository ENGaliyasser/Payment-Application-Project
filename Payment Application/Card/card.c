#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("please, enter card holder name: ");
	fgets(cardData->cardHolderName, 25, stdin); //25
	if (cardData->cardHolderName == NULL || strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24) {
		return WRONG_NAME;
	}
	else {
		return ok ;
	}

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("please, enter card expiry date(MM/YY): ");
	gets(cardData->cardExpirationDate);
	int month = ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
	if (strlen(cardData->cardExpirationDate) != 5 || cardData->cardExpirationDate[2] != '/' || month > 12) {
		return WRONG_EXP_DATE;
	}
	else {
		//printf("%d", strlen(cardData->cardExpirationDate));
		return ok;
	}

}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("please, enter card PAN: ");
	gets(cardData->primaryAccountNumber);
	if (cardData->primaryAccountNumber == NULL || strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19) {
		return WRONG_PAN;
	}
	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i++) {
		if (isalnum(cardData->primaryAccountNumber[i])==0) {
			return WRONG_PAN;
		}
	}
		return ok;
	

}