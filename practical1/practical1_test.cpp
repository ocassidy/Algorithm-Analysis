/*
* Name   : practical1_test.cpp
* Purpose: To test the Account class
* Author : a.mccaughey@ulster.ac.uk
* Version: 1.0
*/

// Use this definition to have catch provide a main method
#define CATCH_CONFIG_MAIN

// Use this definition when providing your own main method
//#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "Account.h"

/**
* Account Test Axioms
*/
TEST_CASE("Account Axioms", "[Account]")
{
	// arrange new customer with a zero balance and zero overdraft
	Account a("Bloggs");

	SECTION("Construct an Account")
	{
		//assert customer is Bloggs
		REQUIRE(a.getCustomer() == "Bloggs");
		// assert balance is 0.0
		REQUIRE(a.getBalance() == 0.0);
		//assert overdraft is 0.0
		REQUIRE(a.getOverdraft() == 0.0);
	}

	SECTION("Deposit Legal Amount")
	{
		// act
		a.deposit(50);

		// assert balance is 50
		REQUIRE(a.getBalance() == 50.0);
	}

	SECTION("Attempt to Deposit Illegal Amount")
	{
		// act
		a.deposit(-50);

		// assert balance unchanged
		REQUIRE(a.getBalance() == 0.0);
	}

	SECTION("Withdraw Legal Amount")
	{
		// act
		a.deposit(100.0);
		a.withdraw(10.0);

		// assert balance is 90
		REQUIRE(a.getBalance() == 90.0);
	}

	SECTION("Attempt to Withdraw Illegal Amount")
	{
		// act
		a.deposit(100.0);
		a.withdraw(110.0);

		// assert balance still 100
		REQUIRE(a.getBalance() == 100.0);
	}

	SECTION("Withdraw Using Overdraft")
	{
		// act
		a.deposit(100.0);
		a.setOverdraft(50);
		a.withdraw(110.0);

		// assert balance overdrawn by -10
		REQUIRE(a.getBalance() == -10.0);
	}

	SECTION("Set Legal overdraft")
	{
		// act
		a.setOverdraft(50.0);

		// assert balance unchanged
		REQUIRE(a.getOverdraft() == 50.0);
	}

	SECTION("Attempt to set Illegal overdraft")
	{
		// act
		a.setOverdraft(-50.0);

		// assert balance unchanged
		REQUIRE(a.getOverdraft() == 0.0);
	}

	SECTION("Attempt to Set overdraft that does not cover overdrawn balance")
	{
		// act
		a.setOverdraft(10.0);
		a.withdraw(10.0);
		// change would not cover overdrawn amount
		a.setOverdraft(0.0);
		
		// assert overdraft unchanged
		REQUIRE(a.getOverdraft() == 10.0);
	}

}
