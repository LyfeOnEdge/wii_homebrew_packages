$nowin

$header
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include <time.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

$header

	// Initialise the video system
	VIDEO_Init()
	
	// This function initialises the attached controllers
	WPAD_Init()
	
	// Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL)

	// Allocate memory for the display in the uncached region
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode))
	
	// Initialise the console, required for printf
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ)
	
	// Set up the video registers with the chosen mode
	VIDEO_Configure(rmode)
	
	// Tell the video hardware where our display memory is
	VIDEO_SetNextFramebuffer(xfb)
	
	// Make the display visible
	VIDEO_SetBlack(FALSE)

	// Flush the video register changes to the hardware
	VIDEO_Flush()

	// Wait for Video setup to complete
	VIDEO_WaitVSync()
	!if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();


	
	! static u32 p_key;
	! static u32 p_keyh;
	! static u32 delaycounter;
	! static u32 time2rumble;
	! static u32 time_up_pressed;
	! static u32 time_down_pressed;
	! static u32 cpaddle_moved;



dim c_pos as integer, r_pos as integer, i as integer, pscore as integer, cscore as integer
dim leftpos as integer, rightpos as integer, netpos as integer, angle as integer
dim ballx as integer, bally as integer, twoplayers as integer, x as integer, y as integer
dim ch as integer, pkey as integer, xdir as integer, ydir as integer, paddle as integer
dim ballspeed as integer, terminateflag as integer, wii_toggle as integer, paddlehits as integer
dim c_delay as integer

again:

ballspeed=5 	
leftpos=12 
rightpos=12
netpos=39
angle=3
ballx=1 
bally=1
twoplayers=0
delaycounter=0
cscore=0
pscore=0
wii_toggle=0
cpaddle_moved=0
paddlehits=0
c_delay=180 //delay to move computer paddle increased by paddlehits

'avoid warnings now
p_key=0
p_keyh=0
time_up_pressed=0
time_down_pressed=0

gosub do_cls
gosub printscore

x=leftpos
y=1
gosub printpaddle
x=rightpos
y=79

gosub printpaddle
gosub printmiddle
gosub instructions 'do not start immediately

do

'first wiimote
paddle=0
gosub check_wpad
if terminateflag=1 then exit loop
if pkey=3 then
	gosub instructions
	pkey=0
end if
gosub movepaddles

'second wiimote - if used
paddle=1
p_key=0
p_keyh=0
pkey=0
gosub check_wpad
if p_key > 0 then 
	twoplayers=1
end if
if pkey>0 and twoplayers=1 then
	incr pkey,2 '3+4 are for right paddle
	gosub movepaddles
endif 	

'move WII paddle if one player - make gently increasing delay to give player a chance
'each time the computer hits the ball it gets a bit slower - difficult to adjust to
'work well at different speeds
if twoplayers=0 then
	if (ticks_to_millisecs(gettime())>(cpaddle_moved+(c_delay-ballspeed*8)+paddlehits)) then
		if rightpos+1>ballx then pkey=3
		if rightpos+1<ballx then pkey=4
		gosub movepaddles
		cpaddle_moved = ticks_to_millisecs(gettime())
	end if
end if
	
$comment
r_pos=28
c_pos=1
gosub do_locate 
print c_delay-ballspeed*8+paddlehits;
$comment

'move ball
incr delaycounter
if delaycounter >= ballspeed then 'only move ball with delay

delaycounter=0
r_pos=ballx
c_pos=bally
gosub do_locate 
if bally <> netpos then print " "; 'clear if not on net position

if ballx > 24 then xdir=1 'move high now
if ballx < 2 then xdir=0  'move low now
if xdir=0 then incr ballx
if xdir=1 then decr ballx
'xdir=2 no change

if bally > 78 then ydir=1
if bally < 2 then ydir=0

if ydir=0 then incr bally,angle
if ydir=1 then decr bally,angle

'check for valid values
if ballx < 1 then ballx=1
if ballx > 25 then ballx=25
if bally < 2 then bally=2
if bally >78 then bally=78

'do not jmp over paddle if angle>1
if ballx >= leftpos and ballx =< (leftpos+3) then
	if bally<2 then bally=2
end if
if ballx >= rightpos and ballx =< (rightpos+3) then
	if bally>78 then bally=78
end if

r_pos=ballx
c_pos=bally
gosub do_locate 
if bally <> netpos then 
	ch=223 'print ball finally
	gosub print_char
end if

'did ball touch paddle?
if bally=2 and ydir=1 then 'ball nears left side
	if ballx >= leftpos and ballx =< (leftpos+2) then 'hit paddle?
        ydir=0
        if ballx=leftpos then
        	xdir=1 'move up
        elseif ballx=leftpos+1 then
        	xdir=2 'move horizontal
        else
        	xdir=0 'move down
        end if
		'lower angle (increase number) if paddle was hit
        if angle=5 then
        	angle=2
        else
        	incr angle
        end if
        
    else 'paddle did not get ball
        gosub do_rumble
		incr cscore
        gosub printscore
		r_pos=ballx
		c_pos=bally
		gosub do_locate 
		print " "; 'clear old ball position before incr
        decr bally
		paddlehits=0
    end if
elseif bally=78 and ydir=0  then 'ball nears right side
	if ballx >= rightpos and ballx =< (rightpos+2) then 'hit paddle?
        ydir=1
        if ballx=rightpos then
        	xdir=1 'move up
        elseif ballx=rightpos+1 then
        	xdir=2 'move horizontal
        else
        	xdir=0 'move down
        end if
		'lower angle (increase number) if paddle was hit
        if angle=5 then
        	angle=2
        else
        	incr angle
        end if
		incr paddlehits,8
        
    else 'paddle did not get ball
        gosub do_rumble
		incr pscore
        gosub printscore
		r_pos=ballx
		c_pos=bally
		gosub do_locate 
		print " "; 'clear old ball position before incr
        incr bally
		paddlehits=0
	end if
end if

end if 'delaycounter

if terminateflag=1 then exit loop

loop

r_pos=5 : c_pos=42 : gosub do_locate 
print "Play again? "
r_pos=7 : c_pos=42 : gosub do_locate 
print "Press A for yes or B for no."
'now check within loop what key is pressed
do
paddle=0
terminateflag=0
gosub check_wpad
if (p_key & WPAD_BUTTON_A) then
			terminateflag=0
			exit loop
elseif (p_key & WPAD_BUTTON_B) then
			terminateflag=1
			exit loop
end if
loop
		
if terminateflag=0 then goto again 'start over

! return 0; //'quit



'**************************************************************************
do_cls:
	// The console understands VT terminal escape codes
	// This positions the cursor on row 2, column 0
	// we can use variables for this with format codes too
	// e.g. printf ("\x1b[%d;%dH", row, column );
	! printf("\x1b[40m"); //black background
	! printf("\x1b[37m"); //white text
	! printf("\x1b[2J");  //clear screen
	! printf("\x1b[2;0H"); //go to second line	
return
'--------------------------------------
do_locate:
	! printf("\x1b[%d;%dH", r_pos, c_pos );
return
'--------------------------------------
printscore:
r_pos=26
c_pos=1
gosub do_locate 
for i=1 to 79
print "_"; 'print bottom line
next i

r_pos=28
c_pos=33
gosub do_locate 
print "Score: ";
print pscore;
print " : ";
print cscore;
r_pos=14
c_pos=42
gosub do_locate 
if pscore=10 then 
	if twoplayers=0 then
		print " You won!  Congratulations by ";
	else
		print "Left player won! Congratulations by";
	end if
	r_pos=15
	c_pos=42
	gosub do_locate 
	print "Felix and Georg Potthast!"; 
	terminateflag=1
end if
if cscore=10 then 
	if twoplayers=0 then
		print " The WII won! "; 
	else
		print "Right player won! Congratulations by";	
		r_pos=15
		c_pos=42
		gosub do_locate 
		print "Felix and Georg Potthast!"; 
	end if
	terminateflag=1
end if
r_pos=28
c_pos=5
gosub do_locate 
print "ASCII PONG Rel. 1.0";
r_pos=28
c_pos=59
gosub do_locate 
print "Press A for help";
return
'--------------------------------------
printmiddle: 'paint the net
for i=1 to 25
	r_pos=i
	c_pos=netpos
	gosub do_locate 
	ch=254
	gosub print_char
next i
return
'--------------------------------------
printpaddle:
for i=0 to 2
	r_pos=x+i
	c_pos=y
	gosub do_locate 
	ch=219
	gosub print_char
next
return
'--------------------------------------
print_char: 'BCX does not allow chr$ for gcc
! printf("%c", ch);
return
'--------------------------------------
do_rumble:
WPAD_Rumble(0,5) 'Rumble pad number one
if twoplayers=1 then WPAD_Rumble(1,5)
time2rumble = ticks_to_millisecs(gettime())
do
'nothing - just wait to time expire
loop while(ticks_to_millisecs(gettime())<(time2rumble+500))
WPAD_Rumble(0,0) 'stop rumbling pad number one
if twoplayers=1 then WPAD_Rumble(1,0)
return
'--------------------------------------
movepaddles: 'depending on pkey value entered

if pkey=2 then
	r_pos=leftpos
	c_pos=1
	gosub do_locate 
	print " ";
	incr leftpos
        if leftpos=24 then leftpos=23
	x=leftpos 
	y=1
        gosub printpaddle
elseif pkey=1 then
	r_pos=leftpos+2
	c_pos=1
	gosub do_locate 
	print " ";
	decr leftpos
        if leftpos=0 then leftpos=1
	x=leftpos 
	y=1
        gosub printpaddle
elseif pkey=4 then
	r_pos=rightpos
	c_pos=79
	gosub do_locate 
	print " ";	
	incr rightpos
        if rightpos=24 then rightpos=23
	x=rightpos 
	y=79
        gosub printpaddle
elseif pkey=3 then
	r_pos=rightpos+2
	c_pos=79
	gosub do_locate 
	print " ";
	decr rightpos
        if rightpos=0 then rightpos=1
	x=rightpos 
	y=79
        gosub printpaddle
end if

return
'--------------------------------------
check_wpad: 'input$ function

WPAD_ScanPads()
	p_key = WPAD_ButtonsDown(paddle)
		'p_key_t=p_key
		if (p_key & WPAD_BUTTON_HOME) then
			terminateflag=1 'exit loop
		elseif (p_key & WPAD_BUTTON_UP) then
			time_up_pressed = ticks_to_millisecs(gettime())
			pkey=1
		elseif (p_key & WPAD_BUTTON_DOWN) then
			time_down_pressed = ticks_to_millisecs(gettime())
			pkey=2  			
		elseif (p_key & WPAD_BUTTON_MINUS) then
			incr ballspeed 'increase the delay number
			if ballspeed > 10 then ballspeed=10
		elseif (p_key & WPAD_BUTTON_PLUS) then
			decr ballspeed
			if ballspeed < 1 then ballspeed=1
		elseif (p_key & WPAD_BUTTON_A) then
			pkey=3 'gosub instructions
		else
			pkey=0
		end if
		if pkey>0 or terminateflag=1 then goto scanpads_done
	
	p_keyh = WPAD_ButtonsHeld(paddle)
		if (p_keyh & WPAD_BUTTON_UP) then
			if delaycounter=0 or delaycounter>=(ballspeed/2+1) then 
				pkey=1
			else
				pkey=0
			end if
			if (ticks_to_millisecs(gettime())<(time_up_pressed+30)) then pkey=0
		     
		elseif (p_keyh & WPAD_BUTTON_DOWN) then
			if delaycounter=0 or delaycounter>=(ballspeed/2+1) then 
				pkey=2       
			else
				pkey=0
			end if
			if (ticks_to_millisecs(gettime())<(time_down_pressed+30)) then pkey=0
		else
			pkey=0
		end if
	scanpads_done:	
	VIDEO_WaitVSync()
	
return	
'--------------------------------------
instructions: 'help screen
	r_pos=5 : c_pos=42 : gosub do_locate 
	print "Instructions: ";	
	r_pos=7 : c_pos=42 : gosub do_locate 
	print "ASCII Pong will run as a one player";
	r_pos=8 : c_pos=42 : gosub do_locate 
	print "game as default.";	
	r_pos=9 : c_pos=42 : gosub do_locate 
	print "If a key on the second Wiimote is ";
	r_pos=10 : c_pos=42 : gosub do_locate 
	print "pressed it switches into two player ";	
	r_pos=11 : c_pos=42 : gosub do_locate 
	print "mode at any time.";
	r_pos=13 : c_pos=42 : gosub do_locate 
	print "Press UP and DOWN to move paddle,";	
	r_pos=14 : c_pos=42 : gosub do_locate 
	print "plus and minus on first Wiimote to ";	
	r_pos=15 : c_pos=42 : gosub do_locate 
	print "modify ball speed, home to exit.";	
	r_pos=17 : c_pos=42 : gosub do_locate 
	print "Have fun! Press A to continue.";	

	r_pos=20 : c_pos=42 : gosub do_locate 
	print "Current speed: ";
	print 11-ballspeed;

	do
	WPAD_ScanPads()
	p_key = WPAD_ButtonsDown(0)
	if (p_key & WPAD_BUTTON_A) then
			exit loop
	elseif (p_key & WPAD_BUTTON_MINUS) then
		incr ballspeed 'increase the delay number
		if ballspeed > 10 then ballspeed=10
		r_pos=20 : c_pos=42 : gosub do_locate 
		print "Current speed: ";
		print 11-ballspeed;
		print " ";

	elseif (p_key & WPAD_BUTTON_PLUS) then
		decr ballspeed
		if ballspeed < 1 then ballspeed=1
		r_pos=20 : c_pos=42 : gosub do_locate 
		print "Current speed: ";
		print 11-ballspeed;
		print " ";
	end if
	loop

	'redraw screen
	gosub do_cls
	gosub printscore

	x=leftpos
	y=1
	gosub printpaddle
	x=rightpos
	y=79

	gosub printpaddle
	gosub printmiddle

	r_pos=ballx
	c_pos=bally
	gosub do_locate 
	if bally <> netpos then 
		ch=223 'print ball 
		gosub print_char
	end if

return

