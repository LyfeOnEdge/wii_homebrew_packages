// *************************************************************
//   Created with BCX -- The BASIC To C Translator (ver 5.05)
//  BCX (c) 1999, 2000, 2001, 2002, 2003, 2004 by Kevin Diggins
// *************************************************************
//     Translated for compiling using the Lcc-Win32 Compiler
// *************************************************************


#include <ctype.h>

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <stdarg.h>
#include <process.h>


// ***************************************************
// Compiler Defines
// ***************************************************

// C++
#if defined( __cplusplus )
#endif

// LCCWIN32 defs
#if defined( __LCC__ )
  #define USE_LCCWIN32C
#endif

// MingW32 defs
#if defined( __MINGW32__ )
  #define USE_MINGW32C
#endif

// PellesC defs
#if defined( __POCC__ )
  #ifndef _WINDOWS_H
    #include <windows.h>
  #endif
  #define USE_PELLESC
  #if !defined( __POCC__OLDNAMES )
    #define O_RDONLY         _O_RDONLY
    #define O_WRONLY         _O_WRONLY
    #define O_RDWR           _O_RDWR
    #define O_APPEND         _O_APPEND
    #define O_CREAT          _O_CREAT
    #define O_TRUNC          _O_TRUNC
    #define O_EXCL           _O_EXCL
    #define O_TEXT           _O_TEXT
    #define O_BINARY         _O_BINARY
    #define O_NOINHERIT      _O_NOINHERIT
    #define O_TEMPORARY      _O_TEMPORARY
    #define O_SEQUENTIAL     _O_SEQUENTIAL
    #define O_RANDOM         _O_RANDOM
    #define SH_DENYRW        _SH_DENYRW
    #define SH_DENYWR        _SH_DENYWR
    #define SH_DENYRD        _SH_DENYRD
    #define SH_DENYNO        _SH_DENYNO
    #define S_IREAD          _S_IREAD
    #define S_IWRITE         _S_IWRITE
    #define LK_UNLCK         _LK_UNLCK
    #define LK_LOCK          _LK_LOCK
    #define LK_NBLCK         _LK_NBLCK
    #define LK_RLCK          _LK_RLCK
    #define LK_NBRLCK        _LK_NBRLCK
    #define P_WAIT           _P_WAIT
    #define P_NOWAIT         _P_NOWAIT
    #define P_OVERLAY        _P_OVERLAY
    #define P_NOWAITO        _P_NOWAITO
    #define P_DETACH         _P_DETACH
    #define  access           _access
    #define  chdir            _chdir
    #define  chmod            _chmod
    #define  chsize           _chsize
    #define  close            _close
    #define  creat            _creat
    #define  cwait            _cwait
    #define  dup              _dup
    #define  dup2             _dup2
    #define  eof              _eof
    #define  fdopen           _fdopen
    #define  filelength       _filelength
    #define  fileno           _fileno
    #define  fstat            _fstat
    #define  ftime            _ftime
    #define  getch            _getch
    #define  getche           _getche
    #define  getcwd           _getcwd
    #define  getpid           _getpid
    #define  inp              _inp
    #define  inp              _inp
    #define  inpd             _inpd
    #define  inpw             _inpw
    #define  inpw             _inpw
    #define  isascii          _isascii
    #define  isatty           _isatty
    #define  itoa             _itoa
    #define  kbhit            _kbhit
    #define  locking          _locking
    #define  lrotl            _lrotl
    #define  lrotr            _lrotr
    #define  lseek            _lseek
    #define  ltoa             _ltoa
    #define  memicmp          _memicmp
    #define  mkdir            _mkdir
    #define  open             _open
    #define  out              _out
    #define  outp             _outp
    #define  outpd            _outpd
    #define  outpw            _outpw
    #define  outw             _outw
    #define  putch            _putch
    #define  putenv           _putenv
    #define  read             _read
    #define  rmdir            _rmdir
    #define  rotl             _rotl
    #define  rotr             _rotr
    #define  setmode          _setmode
    #define  sopen            _sopen
    #define  spawnl           _spawnl
    #define  spawnle          _spawnle
    #define  spawnlp          _spawnlp
    #define  spawnlpe         _spawnlpe
    #define  spawnv           _spawnv
    #define  spawnve          _spawnve
    #define  spawnvp          _spawnvp
    #define  spawnvpe         _spawnvpe
    #define  stat             _stat
    #define  strdup           _strdup
    #define  stricmp          _stricmp
    #define  strlwr           _strlwr
    #define  strnicmp         _strnicmp
    #define  strnset          _strnset
    #define  strrev           _strrev
    #define  strupr           _strupr
    #define  tell             _tell
    #define  ultoa            _ultoa
    #define  ungetch          _ungetch
    #define  unlink           _unlink
    #define  utime            _utime
    #define  wascii           _wascii
    #define  wcsdup           _wcsdup
    #define  wcsicmp          _wcsicmp
    #define  wcslwr           _wcslwr
    #define  wcsnicmp         _wcsnicmp
    #define  wcsnset          _wcsnset
    #define  wcsrev           _wcsrev
    #define  wcsupr           _wcsupr
    #define  write            _write
  #endif
  #define _asm    __asm
  #define strdate _strdate
  // ===== PellesC Libraries ==========
  #pragma comment(lib,"kernel32.lib")
  #pragma comment(lib,"user32.lib")
  #pragma comment(lib,"gdi32.lib")
  #pragma comment(lib,"comctl32.lib")
  #pragma comment(lib,"advapi32.lib")
  #pragma comment(lib,"winspool.lib")
  #pragma comment(lib,"shell32.lib")
  #pragma comment(lib,"ole32.lib")
  #pragma comment(lib,"oleaut32.lib")
  #pragma comment(lib,"uuid.lib")
  #pragma comment(lib,"odbc32.lib")
  #pragma comment(lib,"odbccp32.lib")
  #pragma comment(lib,"winmm.lib")
  #pragma comment(lib,"comdlg32.lib")
  // ==================================
#endif

// Open Watcom defs
#if defined( __WATCOMC__ )
  #define USE_WATCOMC
  #define strdate _strdate
  #define _fcloseall fcloseall
#endif

// Borland C++ 5.5.1 defs - bcc32.exe
#if defined( __BCPLUSPLUS__ )
  #define strdate _strdate
  #define USE_BCPLUSPLUS
  // ===== Borland Libraries ==========
  #pragma comment(lib,"import32.lib")
  #pragma comment(lib,"cw32.lib")
  // ==================================
#endif

// Borland C
#if defined( __BORLANDC__ )
  #define strdate _strdate
  #define USE_BORLANDC
  // ===== Borland Libraries ==========
  #pragma comment(lib,"import32.lib")
  #pragma comment(lib,"cw32.lib")
  // ==================================
#endif

// Microsoft C
#if defined( __MSC_VER )
  #define USE_MSC
#endif

// ***************************************************

#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include <time.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;


#if !defined( __LCC__ )
#else
#endif
// *************************************************
//                System Variables
// *************************************************

jmp_buf GosubStack[32];
int     GosubNdx;

// *************************************************
//            User Global Variables
// *************************************************

static int     c_pos;
static int     r_pos;
static int     i;
static int     pscore;
static int     cscore;
static int     leftpos;
static int     rightpos;
static int     netpos;
static int     angle;
static int     ballx;
static int     bally;
static int     twoplayers;
static int     x;
static int     y;
static int     ch;
static int     pkey;
static int     xdir;
static int     ydir;
static int     paddle;
static int     ballspeed;
static int     terminateflag;
static int     wii_toggle;
static int     paddlehits;
static int     c_delay;



// *************************************************
//                  Main Program
// *************************************************

int main(int argc, char *argv[])
{
  //   Initialise the video system 
  VIDEO_Init();
  //   This function initialises the attached controllers 
  WPAD_Init();
  //   Obtain the preferred video mode from the system 
  //   This will correspond to the settings in the Wii menu 
  rmode=VIDEO_GetPreferredMode(NULL);
  //   Allocate memory for the display in the uncached region 
  xfb=MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
  //   Initialise the console, required for printf 
  console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
  //   Set up the video registers with the chosen mode 
  VIDEO_Configure(rmode);
  //   Tell the video hardware where our display memory is 
  VIDEO_SetNextFramebuffer(xfb);
  //   Make the display visible 
  VIDEO_SetBlack(FALSE);
  //   Flush the video register changes to the hardware 
  VIDEO_Flush();
  //   Wait for Video setup to complete 
  VIDEO_WaitVSync();
 if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
  static u32 p_key;
  static u32 p_keyh;
  static u32 delaycounter;
  static u32 time2rumble;
  static u32 time_up_pressed;
  static u32 time_down_pressed;
  static u32 cpaddle_moved;

AGAIN:;
  ballspeed=5;
  leftpos=12;
  rightpos=12;
  netpos=39;
  angle=3;
  ballx=1;
  bally=1;
  twoplayers=0;
  delaycounter=0;
  cscore=0;
  pscore=0;
  wii_toggle=0;
  cpaddle_moved=0;
  paddlehits=0;
  c_delay=180;
  // avoid warnings now 
  p_key=0;
  p_keyh=0;
  time_up_pressed=0;
  time_down_pressed=0;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_CLS;
  if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTSCORE;
  x=leftpos;
  y=1;
  if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTPADDLE;
  x=rightpos;
  y=79;
  if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTPADDLE;
  if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTMIDDLE;
  if (setjmp(GosubStack[GosubNdx++])==0) goto INSTRUCTIONS;
  while(1)
    {
      // first wiimote 
      paddle=0;
      if (setjmp(GosubStack[GosubNdx++])==0) goto CHECK_WPAD;
      if(terminateflag==1)
        {
          break;
        }
      if(pkey==3)
        {
          if (setjmp(GosubStack[GosubNdx++])==0) goto INSTRUCTIONS;
          pkey=0;
        }
      if (setjmp(GosubStack[GosubNdx++])==0) goto MOVEPADDLES;
      // second wiimote - if used 
      paddle=1;
      p_key=0;
      p_keyh=0;
      pkey=0;
      if (setjmp(GosubStack[GosubNdx++])==0) goto CHECK_WPAD;
      if(p_key>0)
        {
          twoplayers=1;
        }
      if(pkey>0&&twoplayers==1)
        {
          pkey+=(2);
          if (setjmp(GosubStack[GosubNdx++])==0) goto MOVEPADDLES;
        }
      // move WII paddle if one player - make gently increasing delay to give player a chance 
      // each time the computer hits the ball it gets a bit slower - difficult to adjust to 
      // work well at different speeds 
      if(twoplayers==0)
        {
          if((ticks_to_millisecs(gettime())>(cpaddle_moved+(c_delay-ballspeed*8)+paddlehits)))
            {
              if(rightpos+1>ballx)
                {
                  pkey=3;
                }
              if(rightpos+1<ballx)
                {
                  pkey=4;
                }
              if (setjmp(GosubStack[GosubNdx++])==0) goto MOVEPADDLES;
              cpaddle_moved=ticks_to_millisecs(gettime());
            }
        }
// r_pos=28 
// c_pos=1 
// gosub do_locate 
// print c_delay-ballspeed*8+paddlehits; 
      // move ball 
      delaycounter++;
      if(delaycounter>=ballspeed)
        {
          delaycounter=0;
          r_pos=ballx;
          c_pos=bally;
          if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
          if(bally!=netpos)
            {
              printf("%s"," ");
            }
          if(ballx>24)
            {
              xdir=1;
            }
          if(ballx<2)
            {
              xdir=0;
            }
          if(xdir==0)
            {
              ballx++;
            }
          if(xdir==1)
            {
              ballx--;
            }
          // xdir=2 no change 
          if(bally>78)
            {
              ydir=1;
            }
          if(bally<2)
            {
              ydir=0;
            }
          if(ydir==0)
            {
              bally+=(angle);
            }
          if(ydir==1)
            {
              bally-=(angle);
            }
          // check for valid values 
          if(ballx<1)
            {
              ballx=1;
            }
          if(ballx>25)
            {
              ballx=25;
            }
          if(bally<2)
            {
              bally=2;
            }
          if(bally>78)
            {
              bally=78;
            }
          // do not jmp over paddle if angle>1 
          if(ballx>=leftpos&&ballx<=(leftpos+3))
            {
              if(bally<2)
                {
                  bally=2;
                }
            }
          if(ballx>=rightpos&&ballx<=(rightpos+3))
            {
              if(bally>78)
                {
                  bally=78;
                }
            }
          r_pos=ballx;
          c_pos=bally;
          if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
          if(bally!=netpos)
            {
              ch=223;
              if (setjmp(GosubStack[GosubNdx++])==0) goto PRINT_CHAR;
            }
          // did ball touch paddle? 
          if(bally==2&&ydir==1)
            {
              if(ballx>=leftpos&&ballx<=(leftpos+2))
                {
                  ydir=0;
                  if(ballx==leftpos)
                    {
                      xdir=1;
                    }
                  else if(ballx==leftpos+1)
                    {
                      xdir=2;
                    }
                  else
                    {
                      xdir=0;
                    }
                  // lower angle (increase number) if paddle was hit 
                  if(angle==5)
                    {
                      angle=2;
                    }
                  else
                    {
                      angle++;
                    }
                }
              else
                {
                  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_RUMBLE;
                  cscore++;
                  if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTSCORE;
                  r_pos=ballx;
                  c_pos=bally;
                  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
                  printf("%s"," ");
                  bally--;
                  paddlehits=0;
                }
            }
          else if(bally==78&&ydir==0)
            {
              if(ballx>=rightpos&&ballx<=(rightpos+2))
                {
                  ydir=1;
                  if(ballx==rightpos)
                    {
                      xdir=1;
                    }
                  else if(ballx==rightpos+1)
                    {
                      xdir=2;
                    }
                  else
                    {
                      xdir=0;
                    }
                  // lower angle (increase number) if paddle was hit 
                  if(angle==5)
                    {
                      angle=2;
                    }
                  else
                    {
                      angle++;
                    }
                  paddlehits+=(8);
                }
              else
                {
                  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_RUMBLE;
                  pscore++;
                  if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTSCORE;
                  r_pos=ballx;
                  c_pos=bally;
                  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
                  printf("%s"," ");
                  bally++;
                  paddlehits=0;
                }
            }
        }
      if(terminateflag==1)
        {
          break;
        }
    }
  r_pos=5;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s\n","Play again? ");
  r_pos=7;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s\n","Press A for yes or B for no.");
  // now check within loop what key is pressed 
  while(1)
    {
      paddle=0;
      terminateflag=0;
      if (setjmp(GosubStack[GosubNdx++])==0) goto CHECK_WPAD;
      if((p_key&WPAD_BUTTON_A))
        {
          terminateflag=0;
          break;
        }
      else if((p_key&WPAD_BUTTON_B))
        {
          terminateflag=1;
          break;
        }
    }
  if(terminateflag==0)
    {
      goto AGAIN;
    }
  return 0; //'quit
  // ************************************************************************** 

DO_CLS:;
  //   The console understands VT terminal escape codes 
  //   This positions the cursor on row 2, column 0 
  //   we can use variables for this with format codes too 
  //   e.g. printf ("\x1b[%d;%dH", row, column ); 
  printf("\x1b[40m"); //black background
  printf("\x1b[37m"); //white text
  printf("\x1b[2J");  //clear screen
  printf("\x1b[2;0H"); //go to second line
  longjmp (GosubStack [--GosubNdx],1 );

  // -------------------------------------- 

DO_LOCATE:;
  printf("\x1b[%d;%dH", r_pos, c_pos );
  longjmp (GosubStack [--GosubNdx],1 );

  // -------------------------------------- 

PRINTSCORE:;
  r_pos=26;
  c_pos=1;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  for(i=1; i<=79; i+=1)
    {
      printf("%s","_");
    }
  r_pos=28;
  c_pos=33;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","Score: ");
  printf("% d",(int)pscore);
  printf("%s"," : ");
  printf("% d",(int)cscore);
  r_pos=14;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  if(pscore==10)
    {
      if(twoplayers==0)
        {
          printf("%s"," You won!  Congratulations by ");
        }
      else
        {
          printf("%s","Left player won! Congratulations by");
        }
      r_pos=15;
      c_pos=42;
      if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
      printf("%s","Felix and Georg Potthast!");
      terminateflag=1;
    }
  if(cscore==10)
    {
      if(twoplayers==0)
        {
          printf("%s"," The WII won! ");
        }
      else
        {
          printf("%s","Right player won! Congratulations by");
          r_pos=15;
          c_pos=42;
          if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
          printf("%s","Felix and Georg Potthast!");
        }
      terminateflag=1;
    }
  r_pos=28;
  c_pos=5;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","ASCII PONG Rel. 1.0");
  r_pos=28;
  c_pos=59;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","Press A for help");
  longjmp (GosubStack [--GosubNdx],1 );

  // -------------------------------------- 

PRINTMIDDLE:;
  for(i=1; i<=25; i+=1)
    {
      r_pos=i;
      c_pos=netpos;
      if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
      ch=254;
      if (setjmp(GosubStack[GosubNdx++])==0) goto PRINT_CHAR;
    }
  longjmp (GosubStack [--GosubNdx],1 );

  // -------------------------------------- 

PRINTPADDLE:;
  for(i=0; i<=2; i+=1)
    {
      r_pos=x+i;
      c_pos=y;
      if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
      ch=219;
      if (setjmp(GosubStack[GosubNdx++])==0) goto PRINT_CHAR;
    }
  longjmp (GosubStack [--GosubNdx],1 );

  // -------------------------------------- 

PRINT_CHAR:;
  printf("%c", ch);
  longjmp (GosubStack [--GosubNdx],1 );

  // -------------------------------------- 

DO_RUMBLE:;
  WPAD_Rumble(0,5);
  if(twoplayers==1)
    {
      WPAD_Rumble(1,5);
    }
  time2rumble=ticks_to_millisecs(gettime());
  while(1)
    {
      // nothing - just wait to time expire 
      if(!((ticks_to_millisecs(gettime())<(time2rumble+500))))
        {
          break;
        }
    }
  WPAD_Rumble(0,0);
  if(twoplayers==1)
    {
      WPAD_Rumble(1,0);
    }
  longjmp (GosubStack [--GosubNdx],1 );

  // -------------------------------------- 

MOVEPADDLES:;
  if(pkey==2)
    {
      r_pos=leftpos;
      c_pos=1;
      if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
      printf("%s"," ");
      leftpos++;
      if(leftpos==24)
        {
          leftpos=23;
        }
      x=leftpos;
      y=1;
      if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTPADDLE;
    }
  else if(pkey==1)
    {
      r_pos=leftpos+2;
      c_pos=1;
      if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
      printf("%s"," ");
      leftpos--;
      if(leftpos==0)
        {
          leftpos=1;
        }
      x=leftpos;
      y=1;
      if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTPADDLE;
    }
  else if(pkey==4)
    {
      r_pos=rightpos;
      c_pos=79;
      if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
      printf("%s"," ");
      rightpos++;
      if(rightpos==24)
        {
          rightpos=23;
        }
      x=rightpos;
      y=79;
      if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTPADDLE;
    }
  else if(pkey==3)
    {
      r_pos=rightpos+2;
      c_pos=79;
      if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
      printf("%s"," ");
      rightpos--;
      if(rightpos==0)
        {
          rightpos=1;
        }
      x=rightpos;
      y=79;
      if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTPADDLE;
    }
  longjmp (GosubStack [--GosubNdx],1 );

  // -------------------------------------- 

CHECK_WPAD:;
  WPAD_ScanPads();
  p_key=WPAD_ButtonsDown(paddle);
  // p_key_t=p_key 
  if((p_key&WPAD_BUTTON_HOME))
    {
      terminateflag=1;
    }
  else if((p_key&WPAD_BUTTON_UP))
    {
      time_up_pressed=ticks_to_millisecs(gettime());
      pkey=1;
    }
  else if((p_key&WPAD_BUTTON_DOWN))
    {
      time_down_pressed=ticks_to_millisecs(gettime());
      pkey=2;
    }
  else if((p_key&WPAD_BUTTON_MINUS))
    {
      ballspeed++;
      if(ballspeed>10)
        {
          ballspeed=10;
        }
    }
  else if((p_key&WPAD_BUTTON_PLUS))
    {
      ballspeed--;
      if(ballspeed<1)
        {
          ballspeed=1;
        }
    }
  else if((p_key&WPAD_BUTTON_A))
    {
      pkey=3;
    }
  else
    {
      pkey=0;
    }
  if(pkey>0||terminateflag==1)
    {
      goto SCANPADS_DONE;
    }
  p_keyh=WPAD_ButtonsHeld(paddle);
  if((p_keyh&WPAD_BUTTON_UP))
    {
      if(delaycounter==0||delaycounter>=(ballspeed/2+1))
        {
          pkey=1;
        }
      else
        {
          pkey=0;
        }
      if((ticks_to_millisecs(gettime())<(time_up_pressed+30)))
        {
          pkey=0;
        }
    }
  else if((p_keyh&WPAD_BUTTON_DOWN))
    {
      if(delaycounter==0||delaycounter>=(ballspeed/2+1))
        {
          pkey=2;
        }
      else
        {
          pkey=0;
        }
      if((ticks_to_millisecs(gettime())<(time_down_pressed+30)))
        {
          pkey=0;
        }
    }
  else
    {
      pkey=0;
    }

SCANPADS_DONE:;
  VIDEO_WaitVSync();
  longjmp (GosubStack [--GosubNdx],1 );

  // -------------------------------------- 

INSTRUCTIONS:;
  r_pos=5;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","Instructions: ");
  r_pos=7;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","ASCII Pong will run as a one player");
  r_pos=8;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","game as default.");
  r_pos=9;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","If a key on the second Wiimote is ");
  r_pos=10;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","pressed it switches into two player ");
  r_pos=11;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","mode at any time.");
  r_pos=13;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","Press UP and DOWN to move paddle,");
  r_pos=14;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","plus and minus on first Wiimote to ");
  r_pos=15;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","modify ball speed, home to exit.");
  r_pos=17;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","Have fun! Press A to continue.");
  r_pos=20;
  c_pos=42;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  printf("%s","Current speed: ");
  printf("% d",(int)11-ballspeed);
  while(1)
    {
      WPAD_ScanPads();
      p_key=WPAD_ButtonsDown(0);
      if((p_key&WPAD_BUTTON_A))
        {
          break;
        }
      else if((p_key&WPAD_BUTTON_MINUS))
        {
          ballspeed++;
          if(ballspeed>10)
            {
              ballspeed=10;
            }
          r_pos=20;
          c_pos=42;
          if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
          printf("%s","Current speed: ");
          printf("% d",(int)11-ballspeed);
          printf("%s"," ");
        }
      else if((p_key&WPAD_BUTTON_PLUS))
        {
          ballspeed--;
          if(ballspeed<1)
            {
              ballspeed=1;
            }
          r_pos=20;
          c_pos=42;
          if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
          printf("%s","Current speed: ");
          printf("% d",(int)11-ballspeed);
          printf("%s"," ");
        }
    }
  // redraw screen 
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_CLS;
  if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTSCORE;
  x=leftpos;
  y=1;
  if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTPADDLE;
  x=rightpos;
  y=79;
  if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTPADDLE;
  if (setjmp(GosubStack[GosubNdx++])==0) goto PRINTMIDDLE;
  r_pos=ballx;
  c_pos=bally;
  if (setjmp(GosubStack[GosubNdx++])==0) goto DO_LOCATE;
  if(bally!=netpos)
    {
      ch=223;
      if (setjmp(GosubStack[GosubNdx++])==0) goto PRINT_CHAR;
    }
  longjmp (GosubStack [--GosubNdx],1 );

  return 0;   //  End of main program
}

// *************************************************
//                 Run Time Functions
// *************************************************

