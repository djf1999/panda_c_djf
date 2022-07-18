/******* Original Forthan code
   module M_run_error
   use M_dimpar

   implicit none
   integer*4, parameter :: max_level=30

   integer*4,parameter :: ireturn_default = -999     ! means using default return code according to the action
   integer*4,parameter :: i_error_exit = 1
   integer*4,parameter :: i_normal_exit= 0

   integer*4, save :: lfnscr=0

   character(len=2560) cerror_message

   type T_calltree
     integer*4 :: i_level=0
     logical*4 ::  ldebug=.false.
     character(len=len_filename) cprog(max_level)
   endtype

   type(T_calltree) TTREE
 contains
 
  subroutine  handle_calltree(csubname,cmode,lshow,icode) 
  implicit none
  character(len=*) csubname
  character(len=*) cmode       ! in/out/normal_exit/error_exit/in+error_exit
  logical*4 lshow              ! show calltree
  integer*4,optional :: icode  ! return code, if == ireturn_default, using default
                               ! else using the value
!
!! local variables
  integer*4 i
  character(len=40) :: cblank='                                                  '
  integer*4 ireturn

  ireturn=ireturn_default

  select case (trim(cmode))
!
!! call a subroutine
    case ('in','in+error_exit')
      if(TTREE%i_level.eq.max_level) then
        write(lfnscr,*) '***ERROR(handle_calltree): too many calling levels, > ',max_level
        write(lfnscr,*) '   current subroutine is '//trim(csubname)
        write(lfnscr,*) '   check whether `handle_calltree` is properly called ' 
        ireturn=i_error_exit
      endif 
      TTREE%i_level=TTREE%i_level+1
      TTREE%cprog(TTREE%i_level)=csubname
      if(TTREE%ldebug) write(lfnscr,'(a40,30(1h/,a))') ' IN: '//trim(csubname)//cblank,(trim(TTREE%cprog(i)),i=1,TTREE%i_level)

      if(trim(cmode)=='in+error_exit') then
        if(len_trim(cerror_message).ne.0) call write_cerror_message(lfnscr,cerror_message)
        if(lshow) write(lfnscr,'(a,30(1h/,a))') ' CALL:',(trim(TTREE%cprog(i)),i=1,TTREE%i_level)
        ireturn=i_error_exit
      endif
!
!! out of a subroutine
    case ('out')
      if(TTREE%i_level.eq.1) then
        write(lfnscr,*) '***ERROR(handle_calltree): already in main program, no higher level to go,'
        write(lfnscr,*) '   current subroutine is '//trim(csubname)
        write(lfnscr,*) '   check whether `handle_calltree` is properly called '
        ireturn=i_error_exit
      endif
      TTREE%i_level=TTREE%i_level-1
      if(TTREE%ldebug) write(lfnscr,'(a40,30(1h/,a))') ' OUT:'//trim(csubname)//cblank,(trim(TTREE%cprog(i)),i=1,TTREE%i_level)
    case ('normal_exit')
      write(lfnscr,'(30(1x,a))') (trim(TTREE%cprog(i)),i=1,TTREE%i_level),': Normal End'  
      ireturn=i_normal_exit
    case ('error_exit')   
      if(lshow) then
        if(len_trim(cerror_message).ne.0) call write_cerror_message(lfnscr,cerror_message)
        write(lfnscr,'(a,30(1h/,a))') ' CALL:',(trim(TTREE%cprog(i)),i=1,TTREE%i_level)
      endif
      ireturn=i_error_exit
    case ('show')
      if(len_trim(cerror_message).ne.0) call write_cerror_message(lfnscr,cerror_message)
!
!! unknown actions
    case default
      write(lfnscr,*) '***ERROR(handle_calltree): unknown action request '//trim(cmode)
      write(lfnscr,'(a,30(1h/,a))') ' CALL:',(trim(TTREE%cprog(i)),i=1,TTREE%i_level)
      ireturn=i_error_exit     
  end select 

  if(ireturn.eq.ireturn_default)  return

  if(icode.ne.ireturn_default)  ireturn=icode

  call exit(ireturn)
!exit

  return
  end subroutine  

  subroutine write_cerror_message(lfn,cerror_message)
  implicit none
  integer*4 lfn
  character(len=*) cerror_message

  integer*4 i0,i1
  logical*4 lend

  lend=.false.
  i0=1
  do
    i1=index(cerror_message,'\n')
    if(i1.eq.0) then
      i1=len_trim(cerror_message)+1
      lend=.true.
    else
      cerror_message(i1:i1+1)='   '
    endif
    write(lfn,'(a)') cerror_message(i0:i1-1)
    if(lend) exit
    i0=i1+2
  enddo 

  return
  end subroutine

 end module
 ******************************/

/**
 * @M_run_error.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_run_error
 *
 *
 * @details
 * @see
 */

#ifndef _M_RUN_ERROR_H_
#define _M_RUN_ERROR_H_

#include"M_dimpar.h"

const int max_level = 30;
const int ireturn_default = -999;     // means using default return code according to the action
const int i_error_exit = 1;
const int i_normal_exit = 0;
static int lfnscr = 0;
char cerror_message[2560];

typedef struct
{
	int i_level = 0;
	bool ldebug = false;
	char cprog[max_level][len_filename];
}T_calltree;

T_calltree TTREE;

#endif //_M_RUN_ERROR_H_
