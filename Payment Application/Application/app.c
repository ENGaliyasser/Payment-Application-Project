#include <stdio.h>
#include <ctype.h>
#include "app.h"
#include "../Server/server.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
void appStart() {
	ST_cardData_t test1;
	ST_terminalData_t test2;
	ST_transaction test3;
	setMaxAmount(&test2);

		if (getCardHolderName(&test1) == WRONG_NAME) {
			printf("declined, incorrect name\n");
			return 0;
		}
		if (getCardPAN(&test1) == WRONG_PAN) {
			printf("declined, incorrect PAN\n");
			return 0;
		}
		if (getCardExpiryDate(&test1) == WRONG_EXP_DATE) {
			printf("declined, incorrect card expiry date\n");
			return 0;
		}
		if (getTransactionDate(&test2) == WRONG_DATE) {
			printf("declined, incorrect date\n");
			return 0;
		}
		if (isCardExpired(test1, test2) == EXPIRED_CARD)
		{
			printf("declined, Expired Card\n");
			return 0;
		}

		if (getTransactionAmount(&test2) == INVALID_AMOUNT)
		{
			printf("declined, Invalid Amount\n");
			return 0;
		}
		if (isBelowMaxAmount(&test2) == EXCEED_MAX_AMOUNT)
		{
			printf("declined, Exceeded Maximum Amount\n ");
			return 0;
		}
		if (isValidAccount(&test1) == DECLINED_STOLEN_CARD)
		{
			printf("declined, Invalid Account\n");
			return 0;
		}
		else if (isValidAccount(&test1) == APPROVED)
		{
			if (isAmountAvailable(&test2) == LOW_BALANCE)
			{
				printf("declined, Not enough Money Available\n");
				return 0;
			}
		}


		saveTransaction(&test1, &test2, &test3);
		balanceUpdate(&test2);
		printf("Successful Transaction\n");
		printf("Your new balance is: %f\n", balanceGetter(index)); //
		char c;
		printf("Do you want to show transaction details (y/n) : ");
		scanf_s(" %c", &c);

		if (c == 'y')
		{
			getTransaction(test3.transactionSequenceNumber, transactions);
		}

}
/*
ali yasser ali abdallah
5507307157415502
07/25
27/07/2022
1000
*/

/*
ahmed ali ali abdallah
5452756439611913
07/25
27/07/2022
10000
*/

/*
ali yasser ali abdallah
5507307157415502
07/22
27/07/2025
1000
*/

/*
ahmed ali ali abdallah
5452756439611913
07/24
27/07/2026
10000
*/

/*
ali yasser ali abdallah
5507307157415502
07/25
27/07/2022
21000
*/

/*
ahmed ali ali abdallah
5452756439611913
07/25
27/07/2022
25000
*/
/*
ali yasser ali abdallah
5507307157415502
07/25
27/07/2022
11000
*/
/*
ahmed ali ali abdallah
5452756439611913
07/25
27/07/2022
18000
*/

/*
ali yasser ali abdallah
6507307157415502
07/25
27/07/2022
1000
/*
ahmed ali ali abdallah
6452756439611913
07/25
27/07/2022
1000
*/

