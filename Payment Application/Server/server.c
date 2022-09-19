#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//#define _CRT_SECURE_NO_WARNINGS
#include "server.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Application/app.h"
//databases
ST_accountsDB_t Accounts[255] = {
	{10000.0,"5507307157415502"},
	{11000.0, "36601208405111"},
	{12000.0, "340866940912598"},
	{13000.0, "677117787908848457"},
	{14000.0, "340036731823079"},
	{15000.0, "5538805685663157"},
	{16000.0, "5452756439611913"},
	{17000.0, "4175008306463310"},
	{18000.0, "375142995751192"},
	{19000.0, "30412722016087"}
};

Sequence = 0;


EN_transStat_t recieveTransactionData(ST_transaction* transData) {
	


	char isValidCard;
	char isValidAmount;
	char isSaved;
	isSaved = saveTransaction(&transData->cardHolderData, &transData->terminalData, transData);
	isValidCard = isValidAccount(&(transData->cardHolderData));
	isValidAmount = isAmountAvailable(&(transData->terminalData));

	if (isValidCard == DECLINED_STOLEN_CARD ) {
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	else if (isValidAmount == DECLINED_INSUFFECIENT_FUND) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (isSaved == INTERNAL_SERVER_ERROR) {
		transData->transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	else {
		transData->transState = APPROVED;
		return APPROVED;
	}
	
}

//************************************

EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	for (int i = 0; i < 10; i++) {
		if (!strcmp(cardData->primaryAccountNumber, Accounts[i].primaryAccountNumber)) {
			index = i;
			return OK;
		}
	}
	printf("*****STOLEN CARD*****\n");
	return DECLINED_STOLEN_CARD;

}

//************************************

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	if (termData->transAmount > Accounts[index].balance) {
		printf("*****LAW BALANCE*****\n");
		return LOW_BALANCE;
	}
	else {
		return OK;
	}
		
}

//************************************

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction* transData) {


		if (transData[index].transactionSequenceNumber == transactionSequenceNumber)
		{
			
			printf("************************\n");
			printf("Transaction Details:\n");
			printf("Card Holder Name          :%s\n", transData[Sequence].cardHolderData.cardHolderName);
			printf("Card PAN                  :%s\n", transData[Sequence].cardHolderData.primaryAccountNumber);
			printf("Transaction Date          :%s\n", transData[Sequence].terminalData.transactionDate);
			printf("Transaction Amount        :%f\n", transData[Sequence].terminalData.transAmount);
			printf("Transaction Maximum Amount:%f\n", transData[Sequence].terminalData.maxTransAmount);
			printf("Sequence Number           :%d\n", transData[Sequence].transactionSequenceNumber);
			switch (transData[Sequence].transState)
			{
			case 0:
				printf("Transaction state          :APPROVED\n");
				break;
			case 1:
				printf("Transaction state          :DECLINED_INSUFFECIENT_FUND\n");
				break;
			case 2:
				printf("Transaction state           :DECLINED_STOLEN_CARD\n");
				break;
			case 3:
				printf("Transaction state           :INTERNAL_SERVER_ERROR\n");
				break;
			}
			printf("********************************************************************************************************************");
			printf("****************************************Your new balance          :%f**********************************************\n", Accounts[index].balance);
			printf("************************************************************************************************************************");
			Sequence++;
			return OK;
		}
		else {
			printf("Transaction Not Found");
			return TRANSACTION_NOT_FOUND;
		}
}

//************************************

EN_serverError_t saveTransaction(ST_cardData_t* cardData, ST_terminalData_t* termData, ST_transaction* transData) {
	transData->transactionSequenceNumber = Sequence;
	if (Sequence >= 255)
	{
		return SAVING_FAILED;
	}

	strcpy_s(transactions[Sequence].cardHolderData.cardExpirationDate, 25 , cardData->cardExpirationDate);
	strcpy_s(transactions[Sequence].cardHolderData.cardHolderName, 25 ,cardData->cardHolderName);
	strcpy_s(transactions[Sequence].cardHolderData.primaryAccountNumber,25 ,cardData->primaryAccountNumber);
	strcpy_s(transactions[Sequence].terminalData.transactionDate, 25 ,termData->transactionDate);
	transactions[Sequence].terminalData.maxTransAmount = termData->maxTransAmount;
	transactions[Sequence].terminalData.transAmount = termData->transAmount;
	transactions[Sequence].transactionSequenceNumber = transData->transactionSequenceNumber;
	transactions[Sequence].transState = transData->transState;
	transactions[Sequence].transState = APPROVED; //updatethe the state
	return OK;

}

//************************************

float balanceGetter(int x) {
	return Accounts[x].balance;
}

void balanceUpdate(ST_terminalData_t* terminalData) {
	Accounts[index].balance -= terminalData->transAmount;
	//Sequence++;
}

