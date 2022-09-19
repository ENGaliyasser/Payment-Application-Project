#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "terminal.h"
#include "../Card/card.h"




EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("please, enter transaction date(DD/MM/YYYY): ");
	fgets(termData->transactionDate,11,stdin);
	int day = ((termData->transactionDate[0] - '0') * 10) + (termData->transactionDate[1] - '0');
	int month = ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
	if (strlen(termData->transactionDate) != 10 || termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/' || day > 31 || month > 12) {

		return WRONG_DATE;
	}
	else {
		return oK;
	}

}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	if (((cardData.cardExpirationDate[3] - '0') * 10) + (cardData.cardExpirationDate[4] - '0') > ((termData.transactionDate[8] - '0') * 10) + (termData.transactionDate[9] - '0')) {
		//       MM/YY             DD/MM/YY  
		return oK;
	}
	else if (((cardData.cardExpirationDate[3] - '0') * 10) + (cardData.cardExpirationDate[4] - '0') == ((termData.transactionDate[8] - '0') * 10) + (termData.transactionDate[9] - '0') && ((cardData.cardExpirationDate[0] - '0') * 10) + (cardData.cardExpirationDate[1] - '0') > ((termData.transactionDate[3] - '0') * 10) + (termData.transactionDate[4] - '0')) {

		return oK;
	}
	else {
		return EXPIRED_CARD;
	}
}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	int sum = 0, x, y;
	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i += 2) {
		if ((cardData->primaryAccountNumber[i] - '0') * 2 >= 10) {
			x = ((cardData->primaryAccountNumber[i] - '0') * 2) / 10;
			y = ((cardData->primaryAccountNumber[i] - '0') * 2) % 10;
			sum += x + y;
		}
		else {
			sum += (cardData->primaryAccountNumber[i] - '0') * 2;
		}
	}
	for (int j = 1; j < 16; j += 2) {
		sum += cardData->primaryAccountNumber[j] - '0';
	}
	if (sum % 10 == 0)
		return oK;

	else {
		return INVALID_CARD;
	}

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("please, enter transaction amount: ");
	scanf_s("%f", & termData->transAmount); //**
	if (termData->transAmount <= 0) {
		return INVALID_AMOUNT;
	}
	else {
		return oK;
	}

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	setMaxAmount(termData);
	if (termData->transAmount > termData->maxTransAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	else {
		return oK;
	}

}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	termData->maxTransAmount = MAX__AMOUNT;
	if (termData->maxTransAmount <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		return oK;
	}

}