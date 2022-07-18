/******* Original Forthan code
!
!! satellite structure parameter for atmosphere drag and solar radiation
!! The defination is now only for panels of  plane-form
!!
module M_oi_control
  use M_dimpar 
  use M_time 
  use M_file
  use M_orbit
  use M_force_model
!
!! this is also as header of orbit-file
  type T_oi_control
    type(T_orbit_header)  OH                  ! header of orbit file

    type(T_file)  FICS                        ! file contains initial value of space craft
    type(T_file)  FATT                        ! file contains attitude information
    type(T_file)  FPAN                        ! file contains panel information
    type(T_file)  FORB                        ! file contains orbit information
    type(T_file)  FACC                        ! file contains accelerometer observations (only for LEO)
    type(T_file)  FYAW                        ! GNSS yaw-file
  end type

end module M_oi_control
*****************************/

/**
 * @M_oi_control.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_oi_control
 *
 *
 * @details
 * @see
 */

// satellite structure parameter for atmosphere drag and solar radiation
// The defination is now only for panels of  plane - form

#ifndef _M_OI_CONTROL_H_
#define _M_OI_CONTROL_H_

#include"M_dimpar.h"
#include"M_time.h" 
#include"M_file.h" 
#include"M_orbit.h"
#include"M_force_model.h"

// this is also as header of orbit - file

typedef struct
{
	T_orbit_header  OH;                  // header of orbit file

	T_file  FICS;                        // file contains initial value of space craft
	T_file  FATT;                        // file contains attitude information
	T_file  FPAN;                        //file contains panel information
	T_file  FORB;                        //file contains orbit information
	T_file  FACC;                        //file contains accelerometer observations(only for LEO)
	T_file  FYAW;                        //GNSS yaw - file


}T_oi_control;


#endif //_M_OI_CONTROL_H_