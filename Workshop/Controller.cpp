/**
 * \file Controller.cpp
 *
 * \author Jenn Proos
 */

#include "stdafx.h"
#include "Controller.h"

/**
 * Constructor
 */
CController::CController()
{
}

/**
 * Destructor
 */
CController::~CController()
{
}


/** Initialization function.
*
* This function is called when the system is initialized. This is
* later than when it is constructed, since the controller is not installed on
* a workshop when it is constructed. This function is called when the workshop
* controller is installed and ready to control a workshop.
*/
void CController::Initialize()
{

}




/** Service the workshop.
*
* This function is called once every millisecond during workshop
* operation. It provides a place to put code the controls the
* workshop. Override in a local function.
*/
void CController::Service()
{
	// Increment the state time by 1 millisecond
	mStateTime += 0.001;

	switch (mState)
	{
	case Idle:
		mNaughtyPressed = false;
		mGiftSelected = false;
		break;

	case ConveyerMoving:
		if (GetBagPosition() < 0)
		{
			SetState(Waiting);
		}
		break;

	case Waiting:
		if ((mNaughtyPressed) && (!mGiftSelected))
		{
			SetState(Naughty);
		}
		if ((!mNaughtyPressed) && (mGiftSelected))
		{
			SetState(MovingToGift);
		}
		break;

	case AcquireGift:
		if (mStateTime < 1)
		{
			SetState(MovingFromGift);
		}
		break;

	case BagGift:
		if (IsBagItDone())
		{
			SetState(ShipStop);
		}
		break;

	case Naughty:
		if (IsCoalLoaded())
		{
			SetState(Shipping);
		}
		break;

	case Shipping:
		break;

	default:
		break;
	}



}

void CController::SetState(States state)
{
	mState = state;
	mStateTime = 0;

	// Entry activities for states
	switch (mState)
	{
	case Idle:
		EnableButtonNext(true);
		EnableButtonNaughty(false);
		EnableButtonShip(false);
		break;

	case ConveyerMoving:
		EnableButtonNext(false);
		NewBag();
		SetConveyerSpeed(-1);
		break;

	case Waiting:
		SetConveyerSpeed(0);
		EnableButtonNaughty(true);
		EnableButtonShip(false);
		EnableButtonNext(false);
		break;

	case MovingToGift:
		EnableButtonNaughty(false);

		if (mTargetRow < BaggingRow)
		{
			SetPlatformSpeed(-1, -1);
			mSpeedX = -1;
			mSpeedY = -1;
		}
		else
		{
			SetPlatformSpeed(-1, 1);
			mSpeedX = -1;
			mSpeedY = 1;
		}
		break;

	case MovingToGiftX:
		SetPlatformSpeed(-1, 0);
		mSpeedX = -1;
		mSpeedY = 0;
		break;

	case MovingToGiftY:
		if (mTargetRow < BaggingRow)
		{
			SetPlatformSpeed(0, -1);
			mSpeedX = 0;
			mSpeedY = -1;
		}
		else
		{
			SetPlatformSpeed(0, 1);
			mSpeedX = 0;
			mSpeedY = 1;
		}
		break;

	case AcquireGift:
		Acquire(mTargetCol, mTargetRow);
		SetPlatformSpeed(0, 0);
		break;

	case BagGift:
		BagIt();
		SetPlatformSpeed(0, 0);
		mSpeedX = 0;
		mSpeedY = 0;
		break;

	case Naughty:
		EnableButtonNaughty(false);
		LoadCoal();
		break;

	case Shipping:
		SetConveyerSpeed(-1);
		break;

	case ShipStop:
		EnableButtonShip(true);
		break;

	default:
		break;

	}
}


/**
* Indication that the Next On List button has been pressed
*
* This function is called whenever the Next On List button is pressed.
* It is only called if the button is enabled.
*/
void CController::OnNextPressed() 
{
	switch (mState)
	{
	case Idle:
		SetState(ConveyerMoving);
		break;

	default:
		break;
	}
}

/**
* Indication that the Naughty button has been pressed
*
* This function is called whenever the Naughty button is pressed.
* It is only called if the button is enabled.
*/
void CController::OnNaughtyPressed() 
{
	mNaughtyPressed = true;
	switch (mState)
	{
	case Waiting: 
		SetState(Naughty);
		break;

	default:
		break;
	}
}

/**
* Indication that the Ship button has been pressed
*
* This function is called whenever the Ship button is pressed.
* It is only called if the button is enabled.
*/
void CController::OnShipPressed() 
{
	EnableButtonShip(false);
	switch (mState)
	{
	case ShipStop:
		SetState(Shipping);
		break;
	default:
		break;
	}
}

/**
* Indication that a Gift has been clicked on
*
* This functin is called whenever the user clicks on
* any of the gifts.
* \param col Column clicked on, left is 0, right is 3
* \param row Row clicked on. Bottom row is 0, top is 3
*/
void CController::OnGiftSelected(int col, int row)
{
	mGiftSelected = true;
	mTargetCol = col;
	mTargetRow = row;

	switch (mState)
	{
	case MovingToGift:
		SetState(MovingToGift);
		break;

	case ShipStop:
		SetState(MovingToGift);
		break;

	default:
		break;
	}
}