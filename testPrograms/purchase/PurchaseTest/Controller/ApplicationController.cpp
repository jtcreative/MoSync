/*
 Copyright (C) 2012 MoSync AB

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License,
 version 2, as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA 02110-1301, USA.
 */

/**
 * @file ApplicationController.cpp
 * @author Bogdan Iusco
 * @date 8 May 2012
 *
 * @brief Application's controller.
 */

#include <maapi.h>

#include "ApplicationController.h"
#include "../View/MainScreen.h"

#include "../tests/ITest.h"
#include "../tests/Test1.h"

namespace PurchaseTest
{

	/**
	 * Constructor.
	 */
	ApplicationController::ApplicationController() :
		mMainScreen(NULL),
		mCountSucceededTests(0)
	{
		this->createTests();

		mMainScreen = new MainScreen();
		mMainScreen->show();
	}

	/**
	 * Destructor.
	 */
	ApplicationController::~ApplicationController()
	{
		delete mMainScreen;

		// Delete any remaining tests.
		while (mTests.size() > 0)
		{
			ITest* test = mTests[0];
			mTests.remove(0);
			delete test;
		}

		// Delete failed test names.
		while (mFailedTests.size() > 0)
		{
			MAUtil::String* testName = mFailedTests[0];
			mFailedTests.remove(0);
			delete testName;
		}
	}

	/**
	 * Notify controller that a test has failed.
	 * @param test Test that failed.
	 */
	void ApplicationController::testFailed(ITest& test)
	{
		MAUtil::String* testName = new MAUtil::String(test.getTestName());
		mFailedTests.add(testName);
		mTests.remove(0);
		this->runNextTest();
	}

	/**
	 * Notify controller that a test has successfully finished.
	 * @param test That that has finished.
	 */
	void ApplicationController::testSucceeded(ITest& test)
	{
		mCountSucceededTests++;
		mTests.remove(0);
		this->runNextTest();
	}

	/**
	 * Print log on the screen.
	 * @param test Text to be printed.
	 */
	void ApplicationController::log(MAUtil::String& test)
	{

	}

	/**
	 * Creates test objects and stores them into an array.
	 */
	void ApplicationController::createTests()
	{
		mTests.add(new Test1(*this));
	}

	/**
	 * Run the next text from the array.
	 */
	void ApplicationController::runNextTest()
	{
		if (mTests.size() == 0)
		{
			this->finishTesting();
			return;
		}
		ITest* test = mTests[0];
		test->startTest();
	}

	/**
	 * Show tests results.
	 * Call this method after all test have been finished.
	 */
	void ApplicationController::finishTesting()
	{

	}

} // namespace PurchaseTest
