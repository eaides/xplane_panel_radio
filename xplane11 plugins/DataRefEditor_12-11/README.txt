--------------------------------------------------------------------------------
                            README - DATAREF EDITOR
--------------------------------------------------------------------------------

DataRef Editor (DRE) is a plugin by Sandy Barbour and Ben Supnik that lets you 
view and edit X-Plane's datarefs inside the simulator using a visual display.

Get the latest version of the plugin here:

http://www.xsquawkbox.net/xpsdk/mediawiki/DataRefEditor

--------------------------------------------------------------------------------
                                 VERSION NOTES
--------------------------------------------------------------------------------

2012-11-15

    This release updates DRE to be 64-bit as well as 32-bit.  It will work on
    all 3 operating systems, both 32 and 64-bit.

2011-7-25

    This is the first fat plugin release of DRE; it can be used with X-Plane
    9 or newer.  This release also has new features for sorting and saving
    the dataref displays.

--------------------------------------------------------------------------------
                           INSTALLATION AND BASIC USAGE
--------------------------------------------------------------------------------

INSTALLATION

DRE is a fat plugin; simply drag the folder "DataRefEditor" into the
plugins folder within your Resources folder.

DRE uses the file DataRefs.txt to list X-Plane's built in datarefs;
this file comes with X-Plane itself and does not need to be installed.

VIEWING DATAREFS

To open up a window to view datarefs, pick "Plugins -> Data Ref Editor -> 
Show DataRefs".  The resulting dataref viewing window can be resized by dragging
on the corners.  The vertical scroll bar will scroll the list; the horizontal
scroll bars will change the array index that is shown for array datarefs.

To the bottom left, you can type a string to filter the list.  Terms separated
by spaces search for datarefs with both terms; use the | separator to create
multiple searches.  For example:

cockpit/ N2|cockpit/ N1

will search for any dataref with either cockpit/ and N2 or cockpit/ and N1 in
the name.

You can open multiple windows with different filters; DRE will remember the
location of all of your editing windows and 

EDITING DATAREFS

To edit the value of a dataref, click on its value - you can then type a new
value.  Use the tab, escape and enter keys to advance or end editing.

Note: if a dataref is not writeable or X-Plane updates the dataref every frame,
you may not see the change.  X-Plane may change the dataref to a new value 
before the screen is redrawn.

DRE knows the types of datarefs and automatically converts your 
values to the right types (floats or ints, etc.).  If you can change a dataref
using DRE but not using your own plugin, check the dataref type - the XPLM won't
read or write a dataref if the type is not correct.

--------------------------------------------------------------------------------
                                 ADVANCED USAGE
--------------------------------------------------------------------------------

CREATING PRESETS

DRE stores its preferences in a file called DataRefEditor.dre, which lives in
Output/preferences.

You can turn the saved preferences into a preset as follows:

1. Set up your DRE windows the way you want for your preset.
2. Quit X-Plane.
3. Rename DataRefEditor.dre to a new file name (ending in .dre) and put it in
a subfolder called DRE Presets within the preferences folder.

When you restart DRE, the preset will be available as a new menu on DRE's main
menu.

VIEWING ART CONTROLS AND SIMULATOR STATISTICS

Besides datarefs, DRE can view X-Plane's built in "art controls" and simulator
statistics.  These private datarefs can be viewed in their own viewers using the
"Show Art Controls" and "Show Stats" menu items.

The meaning of the statistics and art controls are not published and are not
part of any official SDK.  However, in some cases the authoring guides for
X-Plane explain particular stats or art controls that can be used to performance
tune airplanes and scenery.

--------------------------------------------------------------------------------
                        USING DATAREF EDITOR WITH YOUR OWN DATAREFS
--------------------------------------------------------------------------------

You can use dataref editor to view the datarefs from your own plugin.  There are
two ways to do this:

1. You can edit DataRefs.txt and add your own datarefs.  This is not recommended
though because the file is updated as part of X-Plane's web updater.

2. You can use inter-plugin messaging to send a message to DRE adding your 
dataref to the list, as follows:

#define MSG_ADD_DATAREF 0x01000000           //  Add dataref to DRE message
 
float RegCounterDataRefInDRE(float elapsedMe, float elapsedSim, int counter, void * refcon)
{
    XPLMPluginID PluginID = XPLMFindPluginBySignature("xplanesdk.examples.DataRefEditor");
    if (PluginID != XPLM_NO_PLUGIN_ID)
    {
         XPLMSendMessageToPlugin(PluginID, MSG_ADD_DATAREF, (void*)"BSUB/CounterDataRef");   
    }

    return 0;  // Flight loop is called only once!  
}

Note that this routine requires that DataRefEditor already be running and enabled;
therefore you must call this code from a flight loop callback, not from your
XPluginStart routine.
