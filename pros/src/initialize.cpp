#include "main.h"

AutonomousInfo autonomousInfoStruct;

void changeSelection(int valueToChange, int * selection, int size)
{
	if(valueToChange == -1)
	{
		if((* selection) > 0)
		{
			(* selection) --;
		}
		else
		{
			(* selection) = size - 1;
		}
	}
	else if(valueToChange == 1)
		{
			if((* selection) < size - 1)
			{
				(* selection) ++;
			}
			else
			{
				(* selection) = 0;
			}
		}
}

void lcdModeSelect()
{
	autonomousInfoStruct = {0,0};

	pros::lcd::initialize();

	bool inModeSelection = 1;
	int step = 1;
	bool lastButtonPress = 0;
	uint8_t newButtonPressed;
	int lastStep = 0;
	int alliance = RED;
	int autonomousSelection = 0;

	const char * selectionText[] = {"DO_NOTHING", "TEST"}; // MODE DEFINITIONS
	int size = sizeof(selectionText) / sizeof(int);

	autonomousSelection = 0;

	while((pros::competition::is_connected() ? (pros::competition::is_disabled() && inModeSelection) : inModeSelection))
	{
		if(lastButtonPress != pros::lcd::read_buttons())
		{
			newButtonPressed = pros::lcd::read_buttons();
		}
		else
		{
			newButtonPressed = 0;
		}

		lastButtonPress = pros::lcd::read_buttons();

		switch(step)
		{
		case(1):
			if(step != lastStep)
			{
				pros::lcd::set_text(2, "_____________Alliance_____________");
				pros::lcd::set_text(5, "_________Red_________Blue_________");
			}

			lastStep = step;

			if(newButtonPressed & LCD_BTN_LEFT)
			{
				alliance = RED;
				step ++;
			}

			if(newButtonPressed & LCD_BTN_RIGHT)
			{
				alliance = BLUE;
				step ++;
			}

			break;

		case(2):
			pros::lcd::set_text(2, "_______________Mode_______________");
			pros::lcd::set_text(5, selectionText[autonomousSelection]);

			if(newButtonPressed & LCD_BTN_LEFT)
			{
				changeSelection(-1, &autonomousSelection, size);
			}
			else if(newButtonPressed & LCD_BTN_RIGHT)
			{
				changeSelection(1, &autonomousSelection, size);
			}
			else if(newButtonPressed & LCD_BTN_CENTER)
			{
				step++;
			}
			break;

		default:
			pros::lcd::set_text(2, "____________Selection:____________");
			pros::lcd::print(5, "%s  %s", (alliance ? "Blue" : "Red"),
					selectionText[autonomousSelection]);

			long startTime = pros::millis();

			//Wait 5 seconds
			while((pros::competition::is_connected() ? (pros::millis() - startTime < 5000 && pros::competition::is_disabled())
					: pros::millis() - startTime < 5000))
			{
				pros::Task::delay(20);
			}

			inModeSelection = 0;

			break;

		}

		pros::Task::delay(20);
	}

	autonomousInfoStruct.alliance = alliance;
	autonomousInfoStruct.mode = autonomousSelection;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() 
{

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() 
{
	lcdModeSelect();
}
