/**
* \file WorkshopController.h
* Workshop controller abstract base class.
*
* This class is the base class for an workshop controller class.
* That class provides the workshop control.
*
*  \author Charles B. Owen
*/

#pragma once

#include <string>

class CWorkshopWnd;

/**
* Workshop controller base class.
*
* Workshop controllers are derived from this base class.
*/
class AFX_EXT_CLASS CWorkshopController
{
public:
    /** Constructor */
    CWorkshopController();

    /// Number of rows of gifts
    static const int NumRows = 4;

    /// Number of columns of gifts
    static const int NumCols = 4;

    /// Column to move the platform to to bag
    static const double BaggingColumn;

    /// Row to move the platform to to bag
    static const double BaggingRow;

    /** Destructor */
    virtual ~CWorkshopController();
    /** Copy constructor disabled */
    CWorkshopController(const CWorkshopController &) = delete;
    /** Assignment operator disabled */
    void operator=(const CWorkshopController &) = delete;

    /** 
    * Initialization function.
    *
    * This function is called when the system is initialized. This is
    * later than when it is constructed, since the controller is not installed on
    * a workshop when it is constructed. This function is called when the workshop
    * controller is installed and ready to control a workshop.
    */
    virtual void Initialize() {}

    /**
     * Set the speed of the bag conveyer belt
     *
     * \param speed Speed to set. Positive values move the bag 
     * to the right, negative values to the left. Values should 
     * range from -1 to 1 (max left speed to max right speed)
     */
    void SetConveyerSpeed(double speed);

    /**
     * Get the bag position
     *
     * \returns Normalized value where 1 is off the screen to the right
     * and 0 is right at the loading area. Negative values are to the left 
     * the loading area 
     */
    double GetBagPosition();

    /**
     * Select a new bag 
     *
     * Call this function to select a new bag. The new bag and name
     * are selected and the bag is set on the end of the conveyer, 
     * which is off the screen. You should then set the speed to -1
     * to get the bag to roll into the loading area.
     */
    void NewBag();

    /**
     * Set the platform movement speed
     * \param speedX Speed from -1 to 1. 1 moves right 
     * \param speedY Speed from -1 to 1. 1 moves up 
     */
    void SetPlatformSpeed(double speedX, double speedY);

    /**
     * Get the platform position X
     * \return Relative platform position
     *
     * A value of 0 is centered on the first bin (left to right), 1 is centerned 
     * on the second, etc. Valid values should be 0-4, where 4 is 
     * where we dump into the bag 
     */
    double GetPlatformX();

    /**
     * Get the platform position Y
     * \return Relative platform position
     *
     * A value of 0 is in front of the first bin (bottom), 1 is in front of 
     * on the second, etc. Valid values should be 0-3, where 3 is 
     * the top most bin.
     */
    double GetPlatformY();


    /**
     * Enable or disable the Next On List button
     * \param enable True to enable the button
     */
    virtual void EnableButtonNext(bool enable);

    /**
     * Enable or disable the Naughty button
     * \param enable True to enable the button
     */
    virtual void EnableButtonNaughty(bool enable);

    /**
     * Enable or disable the Ship button
     * \param enable True to enable the button
     */
    virtual void EnableButtonShip(bool enable);

    /**
     * Indication that the Next On List button has been pressed
     *
     * This function is called whenever the Next On List button is pressed.
     * It is only called if the button is enabled.
     */
    virtual void OnNextPressed() {}

    /**
     * Indication that the Naughty button has been pressed
     *
     * This function is called whenever the Naughty button is pressed.
     * It is only called if the button is enabled.
     */
    virtual void OnNaughtyPressed() {}

    /**
     * Indication that the Ship button has been pressed
     *
     * This function is called whenever the Ship button is pressed.
     * It is only called if the button is enabled.
     */
    virtual void OnShipPressed() {}

    /**
     * Indication that a Gift has been clicked on
     *
     * This functin is called whenever the user clicks on 
     * any of the gifts.
     * \param col Column clicked on, left is 0, right is 3
     * \param row Row clicked on. Bottom row is 0, top is 3
     */
    virtual void OnGiftSelected(int col, int row) {}

    /**
     * Acquire the gift that is at a given column and row.
     *
     * This makes a copy of the gift on the platfrom so we
     * can move it to the bag.
     * \param col Column number
     * \param row Row number 
     */
    void Acquire(int col, int row);

    /**
     * Cause the platform to drop the gift into the bag
     *
     * Check when this is done using the function IsBagItDone()
     */
    void BagIt();

    /**
     * Determine if the BagIt operation is done
     * \return true if BagIt operation is done
     */
    bool IsBagItDone();

    /**
     * Cause coal to be dropped into the bag
     */
    void LoadCoal();

    /**
     * Determine if the process of dropping coal is done
     * \return true if coal has been loaded
     */
    bool IsCoalLoaded();

    /** Service the workshop.
    *
    * This function is called once every millisecond during workshop
    * operation. It provides a place to put code the controls the
    * workshop. Override in a local function.
    */
    virtual void Service() {};
    
    /** \cond */
    void SetWorkshop(CWorkshopWnd *workshop);

    /** Get the Workshop this controller is for
    * \returns Pointer to CWorkshopWnd object */
    CWorkshopWnd *GetWorkshop() { return mWorkshop; }

private:
    /// The workshop we are controlling
    CWorkshopWnd *mWorkshop = nullptr;
    
    /// \endcond
};

