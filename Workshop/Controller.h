/**
 * \file Controller.h
 *
 * \author Jenn Proos
 *
 * 
 */

#include "WorkshopController.h"

#pragma once


/**
 * The controller for the workshop.
 */
class CController :
	public CWorkshopController
{
public:
	CController();
	virtual ~CController();

	enum States {
		Idle, ConveyerMoving, Waiting, MovingToGift, MovingToGiftX,
		MovingToGiftY, MovingFromGift, AcquireGift, BagGift, Naughty, Shipping, ShipStop };

	virtual void Initialize() override;

	virtual void OnNextPressed() override;
	virtual void OnNaughtyPressed() override;
	virtual void OnShipPressed() override;
	virtual void OnGiftSelected(int col, int row) override;
	virtual void Service() override;

private:
	/// Set initial state
	void SetState(States state);

	States mState = Idle;	///< The current state
	double mStateTime = 0;	///< The state time
	int mSpeedX = 0;		///< Speed of platform in X direction
	int mSpeedY = 0;		///< Speed of platform in Y direction
	bool mNaughtyPressed = false;	///< Whether or not the naughty button has been pressed
	bool mGiftSelected = false;		///< Whether or not the gift has been selected
	int mTargetCol= 0;		///< Target column
	int mTargetRow = 0;		///< Target row
};