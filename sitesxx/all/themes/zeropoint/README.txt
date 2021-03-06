README.TXT // 0 Point theme for Drupal 7.

Thank you for downloading this theme!


ABOUT THE 0 POINT THEME:
-------------------------------------------------------------------------+
0 Point is an advanced HTML5 theme, with layout and style configuration options built 
in that you can control through Drupal's UI, to be ideal for a wide range of sites.
It is a RTL ready theme having features that fully support right to left languages. 

The theme validates XHTML+RDFa, CSS 2/CSS 3, it is cross-browser compatible (including IE6 :)), 
and it passes WAVE and FAE.

Starting with version 7.x-3.x Zero Point is the only theme which validates HTML5/CSS3 with no errors.

Layout features
===============
- 1, 2, or 3 column layout with adaptive width (min. 1040px max.1200px at 1440px 
	disply width) based on "The Jello Mold Piefecta Layout" 
	(http://www.positioniseverything.net/articles/jello.html); 
- 17+1 collapsible block regions; 
- 8 colour styles + themer setting; 
- Advanced SEO optimization; 
- built-in IE transparent PNG fix; 
- Fixed / Variable width sidebars (more customization in /_custom/custom-style.css); 
- Round corners for page elements and main menu items;
- Page and block icons;
- jQuery Drop-down menu; 
- Main menu position (left, center or right); 
- Helpful body classes (unique classes for each page, term, website section, 
	browser, etc.). Everything can be controlled via CSS, including each menu
	item (for static menu), how colours and other items will be displayed in
	different browsers, or by terms, sections, etc.; 
- Full breadcrumb; 
- Possibility to change "Submitted by" display on all nodes;
- Bi-directional right to left (RTL) theming; 
- Works perfect in multilingual installations. 

Advanced theme settings features
===============================
Layout settings
- Style - Choose a colour palette from 9 options: 0 Point (Grey), Sky, Nature, 
  Ivy, Ink, Orange, Sangue, Lime and Themer. More colour options to come.
- Layout width - adaptive, fluid and fixed width;
- Sidebars layout - Fixed width sidebars or variable width sidebars;
- Themed blocks;
- Block icons - Choose between none, 32x32 pixel icons and 48x48 pixels icons;
- Page icons - Choose a layout with or without page icons;
- Menu type - Two-level Static or SuckerFish drop-down menu;
- Menu position - Left, center or right;
- 2 font size settings;
- Rounded corners - Option to have rounded corners in all browsers but IE;
- Header image rotator;
- No-followed login/register links.
- No-followed social links;
- Breadcrumb - display or not;
- Change "Submitted by" display on all nodes, site-wide;

Theme development settings
- Rebuild theme registry on every page, during theme development;
- Site ID body class - usefull in a multisite environment.

To know more, read Zero Point handbook (http://drupal.org/node/507792).



MODULE SUPPORT
-------------------------------------------------------------------------+
This theme can support virtualy any module.


  
THEME MODIFICATION
-------------------------------------------------------------------------+
If you feel like giving the theme a look of your own, I recommend to play
with /_custom/custom-style.css; please read the comments in this file.



SIDEBARS DIMMENSIONS
-------------------------------------------------------------------------+
The maximum with available for sidebars is as follow:

                                         | left | right | both
-----------------------------------------------------------------
Variable asyimmetrical sidebars (wide)   | 250  |  300  | 160-234
-----------------------------------------------------------------
Fixed asyimmetrical sidebars (wide)      | 160  |  234  | 160-234
-----------------------------------------------------------------
Variable asyimmetrical sidebars (narrow) | 230  |  280  | 140-214
-----------------------------------------------------------------
Fixed asyimmetrical sidebars (narrow)    | 140  |  214  | 140-214
-----------------------------------------------------------------
Equal width sidebars (narrow)            | 155  |  155  | 155-155
-----------------------------------------------------------------

NOTE: Do not exceed the available width (especially with images) or IE6 
(for those who still use it) will not behave so the sidebars may drop.  



USING THE jQuery DROP-DOWN MENU
-------------------------------------------------------------------------+
The menu can either be a two-level static menu or a jQuery drop-down menu.

Out of the box the theme will show the primary and secondary menu. If you select 
(/admin/structure/menu/settings) the same menu as source for main links and secondary 
links it will display the appropriate second level of your navigation hierarchy.

To activate the drop-down menu put the Main menu block in the "Drop Down menu" 
region and set the parent item to "expanded". 
NOTE: Go to /admin/structure/menu and expand all parents in your primary menu.



INSTALLATION INSTRUCTIONS
-------------------------------------------------------------------------+

1) Place the zeropoint directory into your themes directory (sites/all/themes/zeropoint).
2) Enable the 0 Point theme (/admin/appearance).
3) You can configure the theme's settings at /admin/appearance/settings/zeropoint. 

NOTE: If you place the theme in a location other than /sites/all/themes/zeropoint you 
should modify the path in /abc/css/ie6.css, accordingly.



UPGRADING to a new version of 0 Point
-------------------------------------------------------------------------+

1. If possible, log on as administrator user. 
2. Put the site in "Off-line" mode.
3. Check "Rebuild theme registry on every page" at /admin/appearance/settings/zeropoint
4. Place the zeropoint directory into your themes directory (sites/all/themes/zeropoint).
   In case you have done customization to the Zero Point theme, remember to overwrite theme's
   custom-style.css with your modified custom-style.css file.
5. Clear cached data at admin/settings/performance or, if you use Administration Menu module, 
   "Flush all caches".
6. Put the site in "On-line" mode. It is always a good idea to refresh the browser's cache (CTRL+F5).
7. Check the theme's settings at /admin/appearance/settings/zeropoint. Remember that all the theme's
   settings are multilingual variables, so you can have different settings for each language.

NOTE: In some very rare cases, if after upgrading the theme can not be configured you should 
delete all the zeropoint records in the data base.



SITES USING "ZERO POINT" THEME
-------------------------------------------------------------------------+
Demo/test site: http://www.softwo.com

Various implementations of Zero Point theme can be found here:
http://www.radut.net/ (modified theme)
http://www.eucopyright.com/
http://www.301.ro/
http://www.mlnar.ro/



RELATED THEMES
-------------------------------------------------------------------------+
- ABC (http://drupal.org/project/abc) - a very customizable HTML5 theme
- Black Hole (http://drupal.org/project/black_hole) - a dark HTML5 theme



CONTACT
-------------------------------------------------------------------------+
My drupal nick is florian <http://drupal.org/user/35316> � and I can be reached 
at florian@radut.net (http://www.radut.net).

I can also be contacted for paid customizations of 0 Point theme as well as
Drupal consulting, installation and customizations.
