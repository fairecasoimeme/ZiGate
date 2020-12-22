
When adding a new command, or page, follow the steps below.

========================================================================================================================================
Update Tab Index
========================================================================================================================================
On the design tab, go to properties and find TabIndex. This will display a number for each field on any tab.
When adding or changing fields in any way, ensure that all tab indices are kept up to date and in order.

========================================================================================================================================
Set Field Description
========================================================================================================================================

Find the GUIinitialize function in Form1.cs, and find the relevant cluster or group to the fields you created.
Then, enter a new line similar to;

descriptionTextBoxInit(ref textBoxName);

Where description is changed to something suitable for your new fields, and the name of the textbox in the brackets after 'ref'.
Next, find the relevant area later in the same function and insert the following lines;

private void textBoxName(ref TextBox textBox)
{
	textBox.ForeColor = System.Drawing.Color.Gray;
	textBox.Text = "description (data type)";
	textBox.MouseClick += new MouseEventHandler(textBoxClearSetTextBlack_MouseClick);
}

========================================================================================================================================
Restore Field Description
========================================================================================================================================

Next, locate the 'Leave' event under 'Focus'.
Double click this event.
In the new function, enter;

if (string.IsNullOrWhiteSpace(textBoxName.Text))
            {
                textBoxName.ForeColor = System.Drawing.Color.Gray;
                textBoxName.Text = "";
            }

Where textBoxName is the name of the field and the text in the speech marks is the same as how it appears in the GUIinitialize function.

Now move this function into the 'Restore Grey Text' region under the appropriate section.

========================================================================================================================================
Tooltip Boxes
========================================================================================================================================

For any text boxes and combo boxes, go to the 'Properties' tab and look under 'Events'.
Locate MouseHover and double click it to create a new function in Form1.cs.
In this function, enter;

showToolTipWindow("");

Enter the relevant description between the speech marks, e.g. "Destination Endpoint (8-bit Hex)".
This will bring up a tooltip when the mouse hovers over the field.

Return to the design tab and, rather than double clicking MouseHover, double click MouseLeave.
This will create a new function like the previous one.
In this function, enter;

hideToolTipWindow();

Move both of these functions into the 'Mouse Hover/Leave' region under the appropriate section.

========================================================================================================================================
New Pages
========================================================================================================================================

Finally, when creating a new page, click on the page and find the 'Click' action.
Double click this to create a new function.
In this function, enter;

richTextBoxCommandResponse.Focus();

And move the function into the 'PageClick' region, within the 'Restore Grey Text' region.
